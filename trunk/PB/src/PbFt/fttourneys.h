#pragma once

#include "ftlist.h"
#include "pbtourney.h"
#include "ftwidgethook.h"

class FTTourneyLobby;
class FTTables;

class FTTourneys : public FTWidgetHook
{
	Q_OBJECT;
public:
	FTTourneys(QWidget *w, QObject *parent=0);

	void setTables(FTTables *tables);
	FTTables *tables();

	virtual void onWidget(QWidget *w);
	virtual void timerEvent(QTimerEvent *e);

	int tourneyLobbyCount();

	FTTourneyLobby *getTourneyLobby(const QString &tourneyId);
	FTTourneyLobby *tourneyLobby(const QString &tourneyId);
	bool parseTourneyCaption(QString capt, QString &tourneyId);
	QWidget *tourneyFrame(QWidget *w, QString &tourneyId);

	void tourneyLobbyOpened(FTTourneyLobby *lobby);
	void tourneyLobbyClosed(FTTourneyLobby *lobby);
	void tourneyStatusChanged(FTTourneyLobby *lobby);

	void tourneyIsOver(QString tourneyId);
	void sendTourneyInfo(QString tourneyId);

public slots:
	void onTableOpenedEvent(QString tableId);
	void observeTourney(QString tourneyId);
	void registerTourney(QString tourneyId);
	
	
signals:
	void tourneyLobbyOpenedEvent(FTTourneyLobby *tl);
	void tourneyLobbyClosedEvent(FTTourneyLobby *tl);
	void tourneyStatusChangedEvent(FTTourneyLobby *tl);
//	void tourneyLobbyObserveClickedEvent(QString tourneyId);
protected:
	QPointer<FTTables> _tables;
};

