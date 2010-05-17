#include "stdafx.h"
#include "fttourneys.h"
#include "pbhandinfo.h"
#include "ftlist.h"
#include "fttourneylobby.h"
#include "fthooks.h"
#include "fttables.h"
#include "fttable.h"
#include "ftlobby.h"

FTTourneys::FTTourneys(QWidget *w, QObject *parent) : FTWidgetHook(w, parent)
{
	new  RMessageAdaptor(this);
	startTimer(60000);
}

void FTTourneys::setTables(FTTables *tables)
{
	_tables = tables;
	connect(tables, SIGNAL(tableOpenedEvent(QString)), this,
		SLOT(onTableOpenedEvent(QString)));
}

FTTables *FTTourneys::tables()
{
	return _tables;
}


FTTourneyLobby *FTTourneys::getTourneyLobby(const QString &tourneyId)
{
	FTWidgetHook *h = hookFor(tourneyId);
	FTTourneyLobby *tl= qobject_cast<FTTourneyLobby*>(h);
	
	//Q_ASSERT(!(h && !tl));
	return tl;
}

FTTourneyLobby *FTTourneys::tourneyLobby(const QString &tourneyId)
{
	FTTourneyLobby *tl = getTourneyLobby(tourneyId);
	
	if(0==tl)
	{
		Q_ASSERT(false);
		tl = new FTTourneyLobby(0, this);
		tl->setTourneyId(tourneyId);

	}

	return tl;
}

QWidget *FTTourneys::tourneyFrame(QWidget *w, QString &tourneyId)
{
	tourneyId = "";
	QWidget *tourneyWidget = QTUtil::parentWithClass(w,"CTourneyWindow");
	if(0!=tourneyWidget)
	{
		QString capt = tourneyWidget->windowTitle();
		if(parseTourneyCaption(capt, tourneyId))
			return tourneyWidget;
	}
	return 0;
}

bool FTTourneys::parseTourneyCaption(QString capt, QString &tourneyId)
{
	if(!capt.isEmpty())
	{
		//qLog(Info)<<"parse "<<capt;
		QRegExp re("Full Tilt Poker - Tournament (\\d+)");
		if(re.indexIn(capt)!=-1)
		{
			tourneyId = re.cap(1);
			return true;
		}
		qLog(Info)<<"failed to parse tourney caption "<<capt;
	}
	return false;
}

void FTTourneys::onWidget(QWidget *w)
{
	FTWidgetHook::onWidget(w);

//	if(hookFor(w)==0)
	{
		QString tourneyId;
		QWidget *tourneyWidget = tourneyFrame(w, tourneyId);	
		if(0!=tourneyWidget)
		{
			FTTourneyLobby *lobby = qobject_cast<FTTourneyLobby*>(hookFor(tourneyWidget));
			if(0==lobby)
			{
				lobby = new FTTourneyLobby(tourneyWidget, this);
				onWidgetChilds(tourneyWidget, true);
			}
			if(lobby->objectName().isEmpty())
				lobby->setObjectName(tourneyId);
		}
	}
}

void FTTourneys::tourneyLobbyOpened(FTTourneyLobby *lobby)
{

	emit tourneyLobbyOpenedEvent(lobby);
}

void FTTourneys::tourneyLobbyClosed(FTTourneyLobby *lobby)
{
	emit tourneyLobbyClosedEvent(lobby);
}


void FTTourneys::tourneyStatusChanged(FTTourneyLobby *lobby)
{
	emit tourneyStatusChangedEvent(lobby);
}

void FTTourneys::onTableOpenedEvent(QString tableId)
{
	/*FTTable *tbl = _tables->getTable(tableId);
	if(tbl->isTourney())
	{
		qLog(Debug)<<"TableOpened "<<tableId<<" tId="<<tbl->tourneyId();	
		sendTourneyInfo(tbl->tourneyId());
	}
	*/
}

void FTTourneys::observeTourney(QString tourneyId)
{
	FTTourneyLobby *tl = getTourneyLobby(tourneyId);
	if(tl)
		tl->observe();
	else
		qLog(Debug)<<"FTTourneys::observeTourney: "<<tourneyId<<" lobby is not opened";
}

void FTTourneys::registerTourney(QString tourneyId)
{

}



void FTTourneys::sendTourneyInfo(QString tourneyId)
{
	PBGameInfo gi;

	gi.setOpenedTablesCount(0);
	gi.setTablesMax(18);

	FTTourneyLobby *tl = getTourneyLobby(tourneyId);
	gi.setTourneyOpened(tl!=0 && tl->isAlive());

	QString tourneyStatus = "Unknown";

	if(tl)
		tourneyStatus = tl->status();

	FTTable *tbl = 0;
	if(_tables)
	{
		tbl = _tables->tourneyTable(tourneyId);
		gi.setOpenedTablesCount(_tables->tableCount());
		if(tourneyStatus=="Unknown")
			if(tbl)
				if(tbl->tourneyComplete())
					tourneyStatus="Complete";
				else
					tourneyStatus="Running";
	}

	bool tableOpened = (tbl!=0) && tbl->isAlive();

	gi.setTableOpened(tableOpened);
	gi.setTableId(tourneyId);
	gi.setSiteId("FT");
	gi.setTourneyTableId("1");

	gi.setBigBlind(2);
	gi.setSmallBlind(1);

	int canJoin = (tourneyStatus=="Registering")?1:0;
	gi.setCanJoin(canJoin);

	int complete = (tourneyStatus=="Complete") || (tbl && tbl->tourneyComplete());

	int canOpen = (tourneyStatus=="Seating" || tourneyStatus=="Running" )?1:0;
	gi.setCanOpen(canOpen);

	gi.setGameComplete(complete);

	gi.setDriver(FTLobby::instance()->objectName());

	RMessage msg("GameInfo");
	msg.put(&gi);
	msg.send(this);
}

int FTTourneys::tourneyLobbyCount()
{
	QList<FTTourneyLobby*> lobbies = qFindChildren<FTTourneyLobby*>(this, QRegExp(".*"));
	return lobbies.size();

}

bool FTTourneys::hasUnknownStateLobbies()
{
	QList<FTTourneyLobby*> lobbies = qFindChildren<FTTourneyLobby*>(this, QRegExp(".*"));
	Q_FOREACH(FTTourneyLobby *tl, lobbies)
	{
		if(!tl->ready())
			return true;
	}
	return false;
}

void FTTourneys::timerEvent(QTimerEvent *e)
{
	QSet<QString> tourneys;
	
	qLog(Debug)<<"Sending ping info about "<<tourneys.size()<<" tourneys";

	QList<FTTourneyLobby*> lobbies = qFindChildren<FTTourneyLobby*>(this, QRegExp(".*"));
	Q_FOREACH(FTTourneyLobby*tl, lobbies)
	{
		if(tl->ready()){
			tourneys.insert(tl->tourneyId());
		}
	}
	if(_tables)
	{
		QList<FTTable*> tables = qFindChildren<FTTable*>(_tables, QRegExp(".*"));
		Q_FOREACH(FTTable *tbl, tables)
		{
			if(tbl->isTourney())
			{
				tourneys.insert(tbl->tourneyId());
			}
		}
	}

	Q_FOREACH(QString tid, tourneys)
	{
		sendTourneyInfo(tid);
	}
}