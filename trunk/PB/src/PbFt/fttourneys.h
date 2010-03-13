#pragma once

#include "ftlist.h"
#include "pbtourney.h"
#include "ftwidgethook.h"

class FTTourneyLobby;

class FTTourneys : public FTWidgetHook
{
	Q_OBJECT;
public:
	FTTourneys(QWidget *w, QObject *parent=0);

	virtual void onWidget(QWidget *w);

	FTTourneyLobby *getTourneyLobby(const QString &tourneyId);
	FTTourneyLobby *tourneyLobby(const QString &tourneyId);
	bool parseTourneyCaption(QString capt, QString &tourneyId);
	QWidget *tourneyFrame(QWidget *w, QString &tourneyId);

	void observeClicked(FTTourneyLobby *lobby);
	void tourneyLobbyOpened(FTTourneyLobby *lobby);
signals:
	void tourneyLobbyOpenedEvent(FTTourneyLobby *lobby);
	void tourneyLobbyObserveClickedEvent(FTTourneyLobby *lobby);

};