#include "stdafx.h"
#include "fttourneys.h"
#include "pbhandinfo.h"
#include "ftlist.h"
#include "fttourneylobby.h"
#include "fthooks.h"


FTTourneys::FTTourneys(QWidget *w, QObject *parent) : FTWidgetHook(w, parent)
{

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
		if(!parseTourneyCaption(capt, tourneyId));
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

void FTTourneys::observeClicked(FTTourneyLobby *lobby)
{
	emit tourneyLobbyObserveClickedEvent(lobby);
}
