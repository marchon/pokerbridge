#pragma once

#include "ftlistclicker.h"

class FTTourneyOpener: public FTListClicker
{
	Q_OBJECT
public:
	FTTourneyOpener(QObject *parent=0);
	~FTTourneyOpener();

	FTLobby *lobby();

	virtual void timerEvent(QTimerEvent *e);

	void closeExtraLobbies();
	bool isTourneyForClose(FTTourneyLobby *tl);
	bool isTourneyForOpen(FTTourneyLobby *tl);
protected slots:
	void onOpenTable(RMessage *msg);
	void onCloseTourney(RMessage *msg);
	void onTourneyLobbyOpened(FTTourneyLobby *tl);
	void onTourneyLobbyClosed(QString tourneyId);
	//void closeLobbies(bool all);
protected:
	int _splitIndex,_splitFactor;
	QSet<QString> _observeList;
	QSet<QString> _registerList;
	QSet<QString> _closeList;
};