#pragma once

#include "pbtourney.h"
#include "ftlist.h"
#include "fttasks.h"

class FTTourneyLobby;
class FTTourneyList;
class FTList;
class FTTourneys;


class FTRegisterTourneys : public FTTask
{
	Q_OBJECT
public:
	FTRegisterTourneys(QObject *parent=0);
	~FTRegisterTourneys();

	void start();
	void stop();
	bool isRunning();

	virtual void timerEvent(QTimerEvent *e);
	FTLobby *lobby();
	bool checkLobbyAlive();
	void closeLobbies(bool all);
	//void setFilter(const PBTourneyInfo &info);
protected slots:
	void execute();
	void onTooManyWindows();
	void onTourneysUpdated();
	void onTourneyLobbyOpened(FTTourneyLobby *lobby);
	void onListUpdated(FTList *list);
	void onTourneyLobbyObserveClicked(FTTourneyLobby *lobby);
	void onTableOpened(QString tableId);
	void onLobbyClosing(FTWidgetHook *wh);
	void onLobbyHooked(FTWidgetHook *wh);
private:
	QPointer<PBTourneyInfo> _mask;
	FTDefaultListClicker *_filter;
	QPointer<FTList> _list;
	int _state;
	int _windowsLimit;
	int _timer;
	QPointer<QTimer> _tmr;
	enum{
		Inactive,
		Idle,
		WaitListUpdate,
		Click,
	};
	QVector<QPointer<FTTourneyLobby>> _forObserve;
	QPointer<FTLobby> _lobby;
};

class FTTableStatus : public QObject
{
public:
private:
	QHash<QString, QString> tableStatus;
};