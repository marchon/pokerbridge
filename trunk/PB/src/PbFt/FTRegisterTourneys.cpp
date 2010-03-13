#include "stdafx.h"
#include "ftlist.h"
#include "ftregistertourneys.h"
#include "ftlobby.h"
#include "fttourneys.h"
#include "fttourneylobby.h"
#include "fttourneylist.h"
#include "fttables.h"
#include "fttable.h"

FTRegisterTourneys::FTRegisterTourneys(QObject *parent):FTTask(parent)
{
	_state = Inactive;
	//_tourneys = tourneys;
	//connect(_tourneys, SIGNAL(tourneysUpdated()), 
	//	this, SLOT(onTourneysUpdated()));
	_filter = new FTDefaultListClicker();
	//_filter->add("Status", "Registering");
	_filter->add("Status", "Running");

	qLog(Debug)<<"regtour constructing, lobby="<<lobby();

	connect(lobby(), SIGNAL(widgetClosing(FTWidgetHook*)), 
		this, SLOT(onLobbyClosing(FTWidgetHook*)));
	
	connect(lobby()->tourneys(), SIGNAL(tourneyLobbyOpenedEvent(FTTourneyLobby*)),
		this, SLOT(onTourneyLobbyOpened(FTTourneyLobby*)));
	connect(lobby()->tourneys(), SIGNAL(tourneyLobbyObserveClickedEvent(FTTourneyLobby*)),
		this, SLOT(onTourneyLobbyObserveClicked(FTTourneyLobby*)));
	
	//connect(lobby()->tables(), SIGNAL(tableOpenedEvent(QString)),
	//	this, SLOT(onTableOpenedEvent(QString)));

	connect(lobby(), SIGNAL(tooManyWindows()),
		this, SLOT(onTooManyWindows()));


	connect(lobby()->lists(), SIGNAL(listUpdatedEvent(FTList*)), this, SLOT(onListUpdated(FTList*)));

	connect(&_tmr,SIGNAL(timeout()), this, SLOT(execute()));

	_windowsLimit = -1;
	_timer = -1;
}

bool FTRegisterTourneys::checkLobbyAlive()
{
	if(lobby() && lobby()->isAlive())
		return true;
	if(isRunning())
	{
		qLog(Info)<<"tourney clicker stops upon checkAlive=false";
		stop();
	}
	return false;
}

bool FTRegisterTourneys::isRunning()
{
	return _state!=Inactive;
}

void FTRegisterTourneys::onLobbyClosing(FTWidgetHook *wh)
{
	qLog(Info)<<"toruney clicker stops upon lobby closing";
	if(isRunning())
		stop();
}

void FTRegisterTourneys::onLobbyHooked(FTWidgetHook *wh)
{
	qLog(Info)<<"regtour::onLobbyHooked";
	if(!lobby())
		return;

	if(!isRunning())
		start();
}

#define CHECK(msg) if(!checkLobbyAlive()){ qLog(Info)<<msg; return;}

void FTRegisterTourneys::onTooManyWindows()
{
	if(!lobby())
		return;
//	CHECK("FTRegisterTourneys::onTooManyWindows");

	_windowsLimit = lobby()->tables()->tableCount();
}

void FTRegisterTourneys::start()
{
	if(!lobby() || !lobby()->isAlive())
	{
		qLog(Info)<<" failed to start regtour, lobby="<<lobby();
		if(lobby())
			qLog(Info)<<" failed to start regtour, lobbyalive="<<lobby()->isAlive();
		return;
	}

	Q_ASSERT(_state==Inactive);
	int period = PB_OPTION_INT("TableOpener/Periodicity",10000);
	//_timer = startTimer(period);
	_tmr.setInterval(20);
	_tmr.start();
	_state = WaitListUpdate;
	qLog(Info)<<"tourney clicker started period="<<period;
}

void FTRegisterTourneys::stop()
{
	qLog(Info)<<"tourney clicker stopped";
	if(_timer!=-1)
	{
		qLog(Info)<<"tourney clicker timer stopped";
		//killTimer(_timer);
//		_tmr.stop();
		_state = Inactive;
		_timer=-1;
	}
}

void FTRegisterTourneys::timerEvent(QTimerEvent *e)
{
//	CHECK("FTRegisterTourneys::timerEvent");
	if(!lobby())
		return;

	execute();
}

void FTRegisterTourneys::execute()
{
	if(_state==Idle)
	{
		_state = WaitListUpdate;
		qLog(Info)<<"waiting tourney list";
	}
	
	bool overWindowsLimit = false;
	if(_windowsLimit>-1 && 
		lobby()->tables()->tableCount()>=_windowsLimit)
	{
		overWindowsLimit = true;
	}

	int step = PB_OPTION_INT("TableOpener/SplitFactor",1);

	
	
	if(_state==Click)
		if(_list)
		{
			if(!overWindowsLimit)
			{
				qLog(Info)<<"click tourney "<<_filter->index()<<" of "<<_list->rowCount();
				_list->click(_filter, 9999);
				
				_filter->setIndex(_filter->index()+step);
				if(_filter->index()>_list->rowCount())
				{
					_state = Idle;
				}
			}else
			{
				qLog(Info)<<" skipped click too many windows";
			}
			
		}

	closeLobbies(overWindowsLimit);
	qLog(Info)<<"starting observe";
	if(!overWindowsLimit)
	{
		// try click observe button
		for(int i=0;i<_forObserve.size();i++)
		{
			QPointer<FTTourneyLobby> tl = _forObserve[i];
			if(tl)
				tl->observe();
		}
	}
	qLog(Info)<<"ending observe";
}

// model is shown, go through and click all rows matching the filter
void FTRegisterTourneys::onTourneysUpdated()
{
//	CHECK("FTRegisterTourneys::onTourneysUpdated");
	if(!lobby())
		return;

}

void FTRegisterTourneys::onTourneyLobbyOpened(FTTourneyLobby *tl)
{
//	CHECK("FTRegisterTourneys::onTourneyLobbyOpened");
//	CHECK(tl,"FTRegisterTourneys::onTourneyLobbyOpened, tl=0");
	if(!lobby())
		return;

	_forObserve.append(tl);
		qLog(Info)<<"Tourney lobby "<<tl->tourneyId()<<" opened, waiting observe "<<_forObserve.size();
}

void FTRegisterTourneys::onTourneyLobbyObserveClicked(FTTourneyLobby *tl)
{
	if(!lobby())
		return;

	//	CHECK("FTRegisterTourneys::onTourneyLobbyObserveClicked, lobby()==0");
	//CHECK(tl,"FTRegisterTourneys::onTourneyLobbyObserveClicked, tl=0");
}

void FTRegisterTourneys::closeLobbies(bool all)
{
	for(int i=0;i<_forObserve.size();)
	{
		QPointer<FTTourneyLobby> tl = _forObserve[i];
		if(!tl)
			_forObserve.remove(i);
		else if(all || lobby()->tables()->tourneyTable(tl->tourneyId()))
		{
			tl->close();
			_forObserve.remove(i);
			qLog(Info)<<"closing lobby "<<tl->tourneyId();

		}
		else
			i++;
	}
}

void FTRegisterTourneys::onTableOpened(QString tableId)
{
}

void FTRegisterTourneys::onListUpdated(FTList *list)
{
	if(!lobby())
		return;

	if(_state==WaitListUpdate)
	{
		if(list->objectName()==ftSngLobbyModel)
		{
			_list = list;
			int first =  PB_OPTION_INT("TableOpener/SplitIndex",0);
			_filter->setIndex(first);
			_state = Click;
			qLog(Info)<<"click, start="<<first;
		}
	}
}

FTLobby *FTRegisterTourneys::lobby()
{
	return FTLobby::instance();
}