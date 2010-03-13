#include "stdafx.h"
#include "PBTableEvents.h"
#include "pbtable.h"
#include "pbevent.h"

PBEvent *PBTableEvents::newActionEvent(const QString &action, const QString &playerId, double amount)
{
	PBEvent *e = new PBEvent(action);
	e->setProperty("playerId", playerId);
	e->setProperty("amount", amount);
	return e;
}

PBEvent *PBTableEvents::newPotEvent(const QString &action, int potId, double amount)
{
	PBEvent *e = new PBEvent(action);
	if(potId!=-1)
		e->setProperty("potId", potId);
	e->setProperty("amount", amount);
	return e;
}

void PBTableEvents::raiseEvent(PBEvent *e)
{
	emit newEvent(e);
	delete e;
}

void PBTableEvents::postSmallBlind(const QString &playerId, double amount)
{
	PBEvent *e = newActionEvent("postSmallBlind", playerId, amount);
	raiseEvent(e);
}

void PBTableEvents::postDeadBlind(const QString &playerId, double amount)
{
	PBEvent *e = newActionEvent("postDeadBlind", playerId, amount);
	raiseEvent(e);
}

void PBTableEvents::check(const QString &playerId)
{
	PBEvent *e = newActionEvent("check", playerId, 0.0);
	raiseEvent(e);
}

void PBTableEvents::call(const QString &playerId, double amount)
{
	PBEvent *e = newActionEvent("call", playerId, amount);
	raiseEvent(e);
}

void PBTableEvents::raise(const QString &playerId, double amount)
{
	PBEvent *e = newActionEvent("raise", playerId, amount);
	raiseEvent(e);
}

void PBTableEvents::fold(const QString &playerId)
{
	PBEvent *e = newActionEvent("fold", playerId, 0);
	raiseEvent(e);
}

void PBTableEvents::bet(const QString &playerId, double amount)
{
	PBEvent *e = newActionEvent("bet", playerId, amount);
	raiseEvent(e);
}

void PBTableEvents::winMainPot(const QString &playerId, double amount)
{
	PBEvent *e = newPotEvent("winMainPot", -1, amount);
	raiseEvent(e);
}

void PBTableEvents::tieMainPot(const QString &playerId, double amount)
{
	PBEvent *e = newPotEvent("tieMainPot", -1, amount);
	raiseEvent(e);
}

void PBTableEvents::winSidePot(const QString &playerId, int sidePot, double amount)
{
	PBEvent *e = newPotEvent("winSidePot", sidePot, amount);
	raiseEvent(e);
}

void PBTableEvents::tieSidePot(const QString &playerId, int sidePot, double amount)
{
	PBEvent *e = newPotEvent("tieSidePot", sidePot, amount);
	raiseEvent(e);
}

void PBTableEvents::sitOut(const QString &playerId)
{
	
}

void PBTableEvents::sitIn(const QString &playerId)
{
}

void PBTableEvents::join(int seat, const QString &playerId, double stake, bool sittingOut)
{

}

void PBTableEvents::leave(const QString &playerId)
{
}

void PBTableEvents::riverCard(const QString &riverCard)
{

}

void PBTableEvents::turnCard(const QString &turnCard)
{

}

void PBTableEvents::flopCards(const QString &flopCard)
{

}

void PBTableEvents::showCards(const QString &playerId, const QString &holeCards)
{
}

void PBTableEvents::dealCards(const QString &playerId, const QString &holeCards)
{
}

