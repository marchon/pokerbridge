#include "stdafx.h"
#include "ftlist.h"
#include "ftlistclicker.h"
#include "ftlobby.h"

#include "fttourneys.h"
#include "fttourneylobby.h"
#include "fttourneylist.h"
#include "fttables.h"
#include "fttable.h"



void FTListFilter::add(QString column, QString value)
{
	_filters[column].append(value);
}

bool FTListFilter::filter(FTList *list, int row)
{
	bool include = false;
	bool exclude = false;
	Q_FOREACH(QString scol, _filters.keys())
	{
		QList<QString> &filts = _filters[scol];
		int col = list->indexOfColumn(scol);
		if(col>=0)
		{
			QString value = list->value(row,col);
			if(filts.indexOf(value)>=0)
			{
				qLog(Debug)<<"INCL: "<<value;
				include=true;
			}else 
			{
				qLog(Debug)<<"EXCL: "<<value;
				exclude=true;
			}
		}
	}
	return include && !exclude;
}

/////////
FTListClicker::FTListClicker(QObject *parent) : FTTask(parent)
{
	_listName = ftSngLobbyModel;

	_firstRow = 0;
	_deltaRow = 1;
	_currentRow = 0;
	_currentColumn = 0;
	_timer = -1;
	_speed = 2000;
	_state = Inactive;

	connect(lobby()->lists(), SIGNAL(listUpdatedEvent(FTList*)), this, SLOT(onListUpdated(FTList*)));
}

FTListClicker::~FTListClicker()
{
	if(isRunning())
		stop();
}

bool FTListClicker::isRunning()
{
	return _state!=Inactive;
}

FTLobby *FTListClicker::lobby()
{
	return FTLobby::instance();
}

void FTListClicker::start()
{
	if(_timer!=-1)
	{
		//qLog(Info)<<"FTListClicker failed to start, timer=="<<_timer;
		return;
	}
	if(_state!=Inactive)
	{
		//qLog(Info)<<"FTListClicker failed to start, Inactive!=state="<<_state;
		return;
	}
	_timer = startTimer(_speed);
	_state = WaitListUpdate;
	srand(QTime::currentTime().msec());
	//qLog(Info)<<"FTListClicker started";
}

void FTListClicker::stop()
{
	if(_timer==-1)
	{
		qLog(Info)<<"FTListClicker stop() called without start()";
		return;
	}
	//qLog(Info)<<"FTListClicker timer stopping";
	killTimer(_timer);
	_state = Inactive;
	_timer=-1;
}

void FTListClicker::timerEvent(QTimerEvent *e)
{
	checkState();

	if(_state==Inactive)
	{
		return;
	}

	//qLog(Info)<<metaObject()->className()<<"::timerEvent()";

	if(_state==Idle)
	{
		_state = WaitListUpdate;
		qLog(Info)<<"waiting for list";
	}
	
	if(_state==Click)
		if(!isPaused())
	{
		Q_ASSERT(_list);
		if(_list)
		{
			if(_filter.filter(_list, _currentRow))
			{
				qLog(Info)<<"click row "<<_currentRow <<" of "<<_list->rowCount();
				_list->dblClick(_currentRow, _currentColumn);
			}
			int group = _currentRow/_deltaRow;
			int totgroups = _list->rowCount()/_deltaRow+1;
			group = rand()%totgroups;
			group--;
			_currentRow=(group+1)*_deltaRow+_firstRow;
			qLog(Debug)<<"next row=("<<group+1<<")*"<<_deltaRow<<"+"<<_firstRow<<"="<<_currentRow;
			if(_currentRow>=_list->rowCount())
			{
				_currentRow = _firstRow;
				//_state=Idle;
				//qLog(Info)<<" state->Idle, end of the list at row="<<_list->rowCount();
				qLog(Info)<<" rolling to start of the list";
			}			
		}
	}
}

void FTListClicker::checkState()
{

}

bool FTListClicker::isPaused()
{
	return false;
}
void FTListClicker::onListUpdated(FTList *list)
{
	if(_state==WaitListUpdate)
	{
		if(list->objectName()==_listName)
		{
			_list = list;
			listFound();
		}
	}
}
void FTListClicker::listFound()
{
	_currentRow = _firstRow;
	_state = Click;
	//qLog(Info)<<"FTListClicker state->Click";
}

