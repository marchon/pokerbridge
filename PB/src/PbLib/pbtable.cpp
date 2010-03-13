#include "stdafx.h"

#include "pbtable.h"
#include "pbseatedplayer.h"
#include "pbseats.h"

PBTable::PBTable(QObject *parent) : QObject(parent)
{
	setSeats(new PBSeats(this));
}


PBHandId PBTable::handId()
{
	return _handId;
}

void PBTable::setHandId(const PBHandId &handId)
{
	_handId = handId;
}


PBSeats *PBTable::seats()
{
	return _seats;
}
void PBTable::setSeats(PBSeats *seats)
{
	_seats = seats;
}