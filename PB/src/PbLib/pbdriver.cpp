#include "stdafx.h"
#include "pbdriver.h"
#include "pbserver.h"
#include "pbgameinfo.h"

PBLobbyDriver::PBLobbyDriver(QObject *parent):QObject(parent)
{
	_driverIndex = -1;
	startTimer(10000);
	_lastPingTime = QTime::currentTime();
	_tablesObserved = 0;
	_tablesMax = 1000;
}

PBLobbyDriver *PBLobbyDriver::fromMessage(RMessage *msg)
{
	if(msg->queue()==0)
		return 0;
	PBLobbyDriver *drv = qobject_cast<PBLobbyDriver*>(msg->queue()->targetRMsg());
	return drv;
}

int PBLobbyDriver::driverIndex()
{
	return _driverIndex;
}

void PBLobbyDriver::setDriverName(QString name, int index)
{
	setObjectName(name);
	QStringList sl = name.split("-");
	_pid = -1;
	if(sl.size()>1)
		_pid = sl[1].toInt();
	_driverIndex = index;
}

bool PBLobbyDriver::isTimedOut()
{
	return _lastPingTime.elapsed()>30000;
}

/*
bool PBLobbyDriver::isDead()
{
	DWORD ProcessesIDs[1024], cbNeeded, cProcesses; 
	EnumProcesses( ProcessesIDs, sizeof(ProcessesIDs), &cbNeeded ) ;
	cProcesses = cbNeeded / sizeof(DWORD);
	for(int i=0;i<cProcesses;i++)
		if(cProcesses[i]==_pid)
			return false;
	return true;
}
*/

PBServer *PBLobbyDriver::server()
{
	return qobject_cast<PBServer*>(parent());
}
void PBLobbyDriver::sendConfig()
{
	RMessage msg("Config");
	msg.setQueue(static_cast<RMessageQueue*>(RMessageAdaptor::getRMsg(this)));
	msg.put("Grabber/SplitIndex", _driverIndex);
	msg.put("Grabber/SplitFactor", server()->driversCount());
	msg.put("Grabber/Mode", _grabberMode);
	msg.put("Grabber/Profile", _grabberProfile);
		
	msg.send(this);
}

void PBLobbyDriver::onDisconnected()
{
	qLog(Debug)<<"Driver "+objectName()+" dies";
	deleteLater();
}

void PBLobbyDriver::onGameInfo(RMessage *msg)
{
	PBLobbyDriver *drv = PBLobbyDriver::fromMessage(msg);
	if(drv==this)
	{
		PBGameInfo gi;
		msg->get(&gi);
		_tablesMax = gi.tablesMax();
		_tablesObserved = gi.openedTablesCount();

		_lastPingTime = QTime::currentTime();
	}
}

bool PBLobbyDriver::canHandleMoreTables()
{
	return _tablesObserved < _tablesMax;
}

void PBLobbyDriver::timerEvent(QTimerEvent *te)
{
	if(isTimedOut())
		emit server()->driverTimeout(this);
}


void PBLobbyDriverProfile::init(PBLobbyDriver *ld)
{
	ld->_grabberMode = _grabberMode;
	ld->_grabberProfile = _grabberProfile;
}

PBLobbyDriverProfile::PBLobbyDriverProfile(QObject *parent):QObject(parent)
{
	_grabberMode = PBServer::instance()->settings()->value("Grabber/Mode").toString();
	_grabberProfile = PBServer::instance()->settings()->value("Grabber/Profile1").toString();
}

