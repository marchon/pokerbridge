#pragma once

class PBSeatedPlayer;
class PBTable;
class PBEvent;

class PBTableEvents
{

public:
	PBTableEvents(PBTable *table);

	PBEvent *newActionEvent(const QString &action, const QString &playerId, double amount);
	PBEvent *newPotEvent(const QString &action, int potId, double amount);

	void postSmallBlind(const QString &playerId, double amount);
	void postDeadBlind(const QString &playerId, double amount);
	void check(const QString &playerId);
	void call(const QString &playerId, double amount);
	void raise(const QString &playerId, double amount);
	void fold(const QString &playerId);
	void bet(const QString &playerId, double amount);
	void winMainPot(const QString &playerId, double amount);
	void tieMainPot(const QString &playerId, double amount);
	void winSidePot(const QString &playerId, int sidePot, double amount);
	void tieSidePot(const QString &playerId, int sidePot, double amount);

	void sitOut(const QString &playerId);
	void sitIn(const QString &playerId);

	void join(int seat, const QString &playerId, double stake = 100,  bool sittingOut = false);
	void leave(const QString &playerId);

	void riverCard(const QString &riverCard);
	void turnCard(const QString &turnCard);
	void flopCards(const QString &flopCard);

	void showCards(const QString &playerId, const QString &holeCards);
	void dealCards(const QString &playerId, const QString &holeCards);

protected:
	void raiseEvent(PBEvent *e);
protected:
	QPointer<PBTable> _table;
signals:
	void newEvent(PBEvent *e);

};