#include "stdafx.h"
#include "fttourneyopener.h"
#include "ftlobby.h"
#include "fttourneys.h"
#include "fttourneylobby.h"
#include "fttables.h"

//////////////////////
FTTourneyOpener::FTTourneyOpener(QObject *parent) : FTListClicker(parent)
{
	_filter.add("Status", "Running");
	_filter.add("Status", "Seating");
	_filter.add("Status", "Registering");


	connect(lobby()->tourneys(), SIGNAL(tourneyLobbyOpenedEvent(FTTourneyLobby*)),
		this, SLOT(onTourneyLobbyOpened(FTTourneyLobby*)));
	//connect(lobby()->tourneys(), SIGNAL(tourneyLobbyObserveClickedEvent(FTTourneyLobby*)),
	//	this, SLOT(onTourneyLobbyObserveClicked(FTTourneyLobby*)));
	
	_timer = -1;

	_currentRow = _firstRow =  0;//PB_OPTION_INT("TableOpener/SplitIndex",0);
	_deltaRow = 1; //PB_OPTION_INT("TableOpener/SplitFactor",1);
	_speed = PB_OPTION_INT("Grabber/Periodicity",2000);
	_splitIndex = PB_OPTION_INT("Grabber/SplitIndex",0);
	_splitFactor = PB_OPTION_INT("Grabber/SplitFactor",1);

	new RMessageAdaptor(this);
}

FTTourneyOpener::~FTTourneyOpener()
{
	if(isRunning())
		stop();
}

FTLobby *FTTourneyOpener::lobby()
{
	return FTLobby::instance();
}

void FTTourneyOpener::timerEvent(QTimerEvent *e)
{
	//_firstRow =  PB_OPTION_INT("TableOpener/SplitIndex",0);
	//_deltaRow = PB_OPTION_INT("TableOpener/SplitFactor",1);

	if(_list)
	{
	/*	int myCount = 0;
		for(int i=0;i<_list->rowCount();i++)
			if(_filter.filter(_list,i))
				myCount++;

		int oldDelta=_deltaRow;
		int drvCount = PB_OPTION_INT("Launcher/DriversCount", 1);
		if(drvCount<1)
			drvCount=1;
		_deltaRow = myCount/drvCount;
		if(_deltaRow<1)
			_deltaRow=1;
		if(_deltaRow>18)
			_deltaRow=18;
		if(oldDelta!=_deltaRow)
		{
			qLog(Debug)<<"DELTA="<<_deltaRow<<", Drivers Count="<<drvCount;
		}
	*/
	}

	FTListClicker::timerEvent(e);
	if(_state!=Inactive)
	{
		closeExtraLobbies();
	}
}

void FTTourneyOpener::closeExtraLobbies()
{
	QList<FTTourneyLobby*> extraLobbies;
	QList<FTTable*> extraTables;

	Q_FOREACH(QObject *obj, lobby()->tourneys()->children())
	{
		FTTourneyLobby *tl = qobject_cast<FTTourneyLobby*>(obj);
		if(!tl)
			continue;
		
		if(isTourneyForClose(tl))
			extraLobbies.append(tl);
	}

	Q_FOREACH(FTTourneyLobby* tl, extraLobbies)
	{
		tl->immediateClose();
	}
}

bool FTTourneyOpener::isTourneyForClose(FTTourneyLobby*tl)
{
	// never close not-ready widgets (they are in unknown state)
	if(!tl->ready())
		return false;

	// 1. close if completed, registering (no observe) or has opened table
	if(tl->status()=="Completed")
	{
		qLog(Debug)<<"closing on "<<tl->status()<<", tbl="<<tl->table();
		return true;
	}

	// if tlobby opened, but nobody does nothing with it (failed opentable for ex)
	// then close it upon timeout
	if(tl->openedTime().elapsed()>60000)
	{
		qLog(Debug)<<"closing TL "<<tl->tourneyId()<<" on eta="<<tl->openedTime().elapsed();
		return true;
	}

	if(_closeList.contains(tl->tourneyId()))
		return true;
	return false;
}

void FTTourneyOpener::onTourneyLobbyOpened(FTTourneyLobby *tl)
{
	/*
	int tId = tl->tourneyId().toInt();
	if(tId%_splitFactor==_splitIndex)
		tl->observe();
	else
		tl->immediateClose();
	*/

}

bool FTTourneyOpener::isTourneyForOpen(FTTourneyLobby *tl)
{
	int maxTablesToStop = PB_OPTION_INT("Grabber/StopTablesCount",1000);
	if(lobby()->tables()->tableCount()>=maxTablesToStop)
		return false;

	if(lobby()->tables()->tableCount()>=lobby()->tables()->tableCountLimit())
	{
		return false;
	}
	
	return true;
}

void FTTourneyOpener::onOpenTable(RMessage *msg)
{
	QString tableId = msg->getString("tableId");
	qLog(Info)<<"--OpenTable-- "<<tableId;

	FTTourneyLobby *tl = lobby()->tourneys()->getTourneyLobby(tableId);

	if(0!=tl)
		if(isTourneyForOpen(tl))
		{
			tl->observe();
		}
}

void FTTourneyOpener::onCloseTourney(RMessage *msg)
{
	QString tableId = msg->getString("tableId");
	qLog(Info)<<"--CloseTourney--"<<tableId;

	FTTourneyLobby *tl = lobby()->tourneys()->getTourneyLobby(tableId);

	if(0!=tl)
	{
		tl->immediateClose();
	}
}

void FTTourneyOpener::onTourneyLobbyClosed(QString tourneyId)
{
	_closeList.remove(tourneyId);
	_observeList.remove(tourneyId);
	_registerList.remove(tourneyId);
}

