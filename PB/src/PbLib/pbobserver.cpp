#include "stdafx.h"
#include "pbobserver.h"
#include "pbdriver.h"
#include "pbgameinfo.h"
#include "pbgameinfos.h"
#include "json.h"

PBObserver::PBObserver(PBGameInfos *games, QObject *parent) : QObject(parent)
{
	_games = games;

	new RMessageAdaptor(this);
	startTimer(2000);
	qLog(Info)<<"Observer started";
}

void PBObserver::openTable(RMessage *msg, PBSiteGameInfo *gi)
{
	gi->setNeedTableOpened(1);

	RMessage reply;
	reply.replyTo(msg);
	reply.setType("OpenTable");
	reply.send(this);
	qLog(Debug)<<"OpenTable "<<gi->gameId()<<" to "<<gi->ownerId();
}

void PBObserver::closeTourney(RMessage *msg, PBSiteGameInfo *gi)
{
	gi->setNeedTourneyOpened(0);

	RMessage reply;
	reply.replyTo(msg);
	reply.setType("CloseTourney");
	reply.send(this);
	qLog(Debug)<<"CloseTourney "<<gi->gameId()<<" to "<<gi->ownerId();
}

void PBObserver::onGameInfo(RMessage *msg)
{
	PBLobbyDriver *drv = PBLobbyDriver::fromMessage(msg);

	Q_ASSERT(drv);

	PBSiteGameInfo *gi= _games->gameInfo(msg->getString("gameId"));
	
	PBGameInfo temp;
	msg->get(&temp);

	if(!gi->owner())	// if not observed by anyone
	{
		if(gi->canOpen())
			if(drv->canHandleMoreTables())
			{
				gi->setOwner(drv);	// locks the game
				gi->setLastUpdateTime(QTime::currentTime());
				gi->updateState(&temp);
				openTable(msg, gi);
			}
		
	}else
	{
		PBLobbyDriver *obsDrv = gi->owner();

		if(drv==obsDrv)
		{
			gi->updateState(&temp);
			if(gi->tableOpened())
				gi->setNeedTableOpened(-1); // opened ok
			else if(gi->canOpen())
			{
				// was closde by someone manualy
				openTable(msg, gi);
			}
			gi->setLastUpdateTime(QTime::currentTime());
		}else   // locked by	 other driver
		{
			closeTourney(msg, gi);
		}
	}
	
	//// CLEANUP. will change if JOINs
	if(gi->tourneyOpened())
	{
		if(gi->tableOpened())
			closeTourney(msg, gi);	// dont keep any TL with opened tables

		if(!gi->canOpen()) // is "completed"
			closeTourney(msg, gi);
	}
	_games->dump();
}

void PBObserver::timerEvent(QTimerEvent *e)
{
	QList<PBSiteGameInfo*> games = qFindChildren<PBSiteGameInfo*>(_games,QRegExp(".*"));
	Q_FOREACH(PBSiteGameInfo*gi, games)
	{
		if(gi->owner())
		{
			int elaps = gi->lastUpdateTime().elapsed();
			if(elaps>3000)
			{
				// we eve wanted to open table but it wasnt
				if(gi->needTableOpened()!=-1 && gi->tableOpened()!=gi->needTableOpened())
				{
					qLog(Debug)<<"No updates of locked game ("<<elaps<<","<<gi->owner()->isTimedOut()<<" from "<<gi->ownerId()<<" for 10s "<<gi->gameId();
					gi->setOwner(0); // unlock
				}
			}
		}
	}
}
