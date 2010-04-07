#include "stdafx.h"
#include "pbserver.h"
#include "PBGameInfo.h"
#include "pbgameinfos.h"
#include "pbobserver.h"
#include "pbdriver.h"
#include "pblauncher.h"

PBServer::PBServer(QObject *parent) : QObject(parent)
{
	QString	settingsFilePath = QDir::currentPath()+QDir().separator()+"PBFT.INI";
	_settings = new QSettings(settingsFilePath, QSettings::IniFormat);

	_instance = this;

	RTcpQueueListener *tql = new RTcpQueueListener(this);
	connect(tql, SIGNAL(queueOpened(RMessageQueue*)), this , SLOT(queueOpened(RMessageQueue*)));
	tql->listen(777);

	PBGameInfos *gis = new PBGameInfos(this);

	new PBObserver(gis, this);


	_agentsCount = settings()->value("Launcher/DriversCount",1).toInt();
	

	_launcher = new PBLauncher();

	_launcher->setMaxCount(_agentsCount);
	_launcher->setPath(settings()->value("Launcher/Directory",".").toString());
	_launcher->start();


	PBLobbyDriverProfile *profile = new PBLobbyDriverProfile(this);
	profile->setObjectName("profile");

}

QSettings *PBServer::settings()
{
	return _settings;
}

void PBServer::queueOpened(RMessageQueue *queue)
{
	PBLobbyDriver *ld = new PBLobbyDriver(this);
	queue->setParent(ld);
	profile()->init(ld);

	QSet<int> usedIndexes; 
	QList<PBLobbyDriver*> drivers = qFindChildren<PBLobbyDriver*>(this, QRegExp(".*"));
	foreach(PBLobbyDriver *drv, drivers)
	{
		if(drv!=ld)
			usedIndexes.insert(drv->driverIndex());
	}
	int nextIndex = -1;
	for(int i=0;i<_agentsCount;i++)
	{
		if(!usedIndexes.contains(i))
		{
			nextIndex = i;
			break;
		}
	}
	if(nextIndex<0)
	{
		qLog(Debug)<<" ERROR: no holes in driver indexes!";
		nextIndex = 0;
	}

	ld->setDriverName(queue->objectName(), nextIndex);
	connect(queue, SIGNAL(closed()), ld, SLOT(onDisconnected()));
	ld->sendConfig();
	qLog(Debug)<<"new drv created "<<ld<<" index="<<nextIndex<<" total drivers "<<drivers.size()<<" of max="<<_agentsCount;
}

PBServer *PBServer::_instance = 0;

PBServer *PBServer::instance()
{
	return _instance;
}

PBLobbyDriverProfile *PBServer::profile()
{
	return qFindChild<PBLobbyDriverProfile*>(this,"profile");
}

int PBServer::driversCount()
{
	return _agentsCount;
}