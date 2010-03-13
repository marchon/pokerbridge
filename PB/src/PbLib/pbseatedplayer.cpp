#include "stdafx.h"
#include "pbseatedplayer.h"
#include "pbtable.h"

PBSeatedPlayer::PBSeatedPlayer(QString playerId, QObject *parent)
	:QObject(parent)
{
	setPlayerId(playerId);
	setSittingOut(true);
	setStake(0);
	setSeat(-1);
}


PBTable *PBSeatedPlayer::table()
{
	return qobject_cast<PBTable*>(parent());
}

int PBSeatedPlayer::seat()
{
	return _seat;
}

void PBSeatedPlayer::setSeat(int seat)
{
	_seat = seat;
}

PBPlayerId PBSeatedPlayer::playerId()
{
	return objectName();
}

void PBSeatedPlayer::setPlayerId(const PBPlayerId &id)
{
	setObjectName(id);
}

double PBSeatedPlayer::stake()
{
	return _stake;
}

void PBSeatedPlayer::setStake(double stake)
{
	_stake = stake;
}
	
PBCards PBSeatedPlayer::holeCards()
{
	return "";
}

void PBSeatedPlayer::setHoleCards(const PBCards &cards)
{
}

bool PBSeatedPlayer::sittingOut()
{
	return _sittingOut;
}

void PBSeatedPlayer::setSittingOut(bool sittingOut)
{
	_sittingOut = sittingOut;
}
	
