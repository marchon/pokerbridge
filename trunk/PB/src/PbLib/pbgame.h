#ifndef PBGAME_H
#define PBGAME_H

#pragma once
class PBSeatedPlayer;
class PBTable;
class PBGame : public QObject
{
	Q_OBJECT
public:
	PBGame(QObject *parent);

	void winMainPot(PBSeatedPlayer *p, double amount);
	void tieMainPot(PBSeatedPlayer *p, double amount);
	void winSidePot(PBSeatedPlayer *p, int potNo, double amount);
	void tieSidePot(PBSeatedPlayer *p, int potNo, double amount);
	
	void showCards(PBSeatedPlayer *p, PBCards holeCards);
	void dealCards(PBSeatedPlayer *p, PBCards holeCards);
	
	void riverCard(PBCards riverCard);
	void turnCard(PBCards turnCard);
	void flopCards(PBCards flopCard);

	void bet(PBSeatedPlayer *p, double amount);
	void check(PBSeatedPlayer *p);
	void raise(PBSeatedPlayer *p, double amount);
	void call(PBSeatedPlayer *p, double amount);
	void fold(PBSeatedPlayer *p);

	void postSmallBlind(PBSeatedPlayer *p, double amount);
	void postBigBlind(PBSeatedPlayer *p, double amount);
	void postDeadBlind(PBSeatedPlayer *p, double amount);

	PBTable *table();
};

#endif