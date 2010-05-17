#include "stdafx.h"
#include "PBGameInfos.h"
#include "PBGameInfo.h"


PBGameInfos::PBGameInfos(QObject *parent) : QObject(parent)
{
	new RMessageAdaptor(this);
}

PBSiteGameInfo *PBGameInfos::gameInfo(QString gameId)
{
	return qFindChild<PBSiteGameInfo*>(this, gameId);
}

void PBGameInfos::onGameInfo(RMessage *msg)
{
	QString gameId = msg->getString("gameId");
	PBSiteGameInfo *gi = gameInfo(gameId);
	if(0==gi)
	{
		gi = new PBSiteGameInfo(this);
		msg->get(gi);
		qLog(DebugNet)<<"created "<<gi->gameId();
	}else{
			PBGameInfo temp;
			msg->get(&temp);
			gi->updateInfo(&temp);
			qLog(DebugNet)<<"updated "<<gi->gameId();
	}
	dump();
}

int PBGameInfos::priGameInfo(RMessage *msg)
{
	return -100;
}


void PBGameInfos::dump()
{
	QPBDumpFile df("games.txt",QIODevice::WriteOnly|QIODevice::Append);
	df<<"\n\nTables "<<QTime::currentTime().toString()<<"\n";
	QList<PBSiteGameInfo*> all = qFindChildren<PBSiteGameInfo*>(this);
	Q_FOREACH(PBSiteGameInfo *gi, all)
	{
		df<<gi->gameId()<<"\t\t"<<gi->ownerId()<<"\t\t"<<gi->tableOpened()<<"\t\t"<<gi->tourneyOpened()<<"\t\t"<<gi->gameComplete()<<"\n";
	}
}


