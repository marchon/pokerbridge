#pragma once

#include "pbtourney.h"
#include "ftlist.h"
#include "fttasks.h"

class FTTourneyLobby;
class FTTourneyList;
class FTList;
class FTTourneys;

class FTListFilter
{
public:
	//FTListFilter();
	void add(QString column, QString value);
	bool filter(FTList *list, int row);
protected:
	QHash<QString,QList<QString>> _filters;
};

class FTListClicker: public FTTask
{
	Q_OBJECT
public:
	FTListClicker(QObject *parent=0);
	~FTListClicker();

	void start();
	void stop();
	bool isRunning();
	virtual bool isPaused();
	virtual void timerEvent(QTimerEvent *e);
	
	FTLobby *lobby();

	virtual void listFound();
	virtual void checkState();
protected slots:
	void onListUpdated(FTList *list);

protected:
	FTListFilter _filter;
	QPointer<FTList> _list;
	
	int _state;
	int _windowsLimit;
	int _timer;
	int _currentRow;
	int _currentColumn;
	int _firstRow;
	int _deltaRow;
	int _speed;

	QString _listName;

	enum{
		Inactive,
		Idle,
		WaitListUpdate,
		Click,
		Paused,
	};
};


