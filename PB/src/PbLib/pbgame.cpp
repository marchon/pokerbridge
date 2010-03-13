#include "stdafx.h"
#include "pbgameinfo.h"

void PBGame::winMainPot(PBSeatedPlayer *p, double amount)
{
//	qLog(Info)<<handId()+": "+player+" wins main pot "+QString().sprintf("%f",amount);
//	qLog(Info)<<handId()+": "+player+" ties main pot "+QString().sprintf("%f",amount);
}
void PBGame::winSidePot(PBSeatedPlayer *p, int potNo, double amount)
{
}

void PBGame::showCards(PBSeatedPlayer *p, QString holeCards)
{
}
void PBGame::dealCards(PBSeatedPlayer *p, QString holeCards)
{
}
void PBGame::riverCard(QString riverCard)
{
}
void PBGame::turnCard(QString turnCard)
{
}
void PBGame::flopCards(QString flopCard)
{
}
void PBGame::bet(PBSeatedPlayer *p, double amount)
{
	//qLog(Info)<<handId()+": "+player+" bets "+QString().sprintf("%f",amount);
}

void PBGame::check(PBSeatedPlayer *p)
{
	//qLog(Info)<<handId()+": "+player+" checks";
}

void PBGame::raise(PBSeatedPlayer *p, double amount)
{
	//qLog(Info)<<handId()+": "+player+" raises to "+QString().sprintf("%f",amount);
}

void PBGame::call(PBSeatedPlayer *p, double amount)
{
	//qLog(Info)<<handId()+": "+player+" calls "+QString().sprintf("%f",amount);
}

void PBGame::fold(PBSeatedPlayer *p)
{
	//qLog(Info)<<handId()+": "+player+" folds";
}

void PBGame::postSmallBlind(PBSeatedPlayer *p, double amount)
{
//	qLog(Info)<<handId()<<": "<<p->playerId()<<" posts small blind "<<amount;
}

void PBGame::postBigBlind(PBSeatedPlayer *p, double amount)
{

}

void PBGame::postDeadBlind(PBSeatedPlayer *p, double amount)
{
//	qLog(Info)<<handId()+": "+player+" posts dead blind "+QString().sprintf("%f",amount);
}
