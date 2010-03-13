#include "stdafx.h"
#include "pbhandinfo.h"

double PBGameInfo::smallBlind()
{
	return _smallBlind;
}

void PBGameInfo::setSmallBlind(double sb)
{
	_smallBlind = sb;
}

double PBGameInfo::bigBlind()
{
	return _bigBlind;
}

void PBGameInfo::setBigBlind(double bb)
{
	_bigBlind = bb;
}

int PBGameInfo::maxSeats()
{
	return _maxSeats;
}

void PBGameInfo::setMaxSeats(int seats)
{
	_maxSeats = seats;
}


QString PBGameInfo::gameType()
{
	return _gameType;
}

void PBGameInfo::setGameType(QString type)
{
	_gameType = type;
}





QString PBHandInfo::handId()
{
	return _handId;
}

void PBHandInfo::setHandId(QString handId)
{
	_handId = handId;
}

QString PBHandInfo::tableId()
{
	return _tableId;
}

void PBHandInfo::setTableId(QString tableId)
{
	_tableId = tableId;
}

QString PBHandInfo::toTypeString()
{
	return gameType()+QString(" %0").arg(maxSeats())+"Max "+QString("$%0/$%1").arg(smallBlind()).arg(bigBlind());
}

