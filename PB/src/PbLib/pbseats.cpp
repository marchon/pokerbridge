#include "stdafx.h"
#include "pbseats.h"
#include "pbseatedplayer.h"

PBSeats::PBSeats(QObject *parent)
{
	_buttonSeat = -1;
}

void PBSeats::join(PBSeatedPlayer *p)
{
	_seats[p->seat()] = p;
}

PBSeatedPlayer *PBSeats::join(int seat, const PBPlayerId & playerId, double stake, bool sittingOut )
{
	//Q_ASSERT(0<=seat && seat<seatsCount());
	//Q_ASSERT(isEmptySeat(seat));
	//Q_ASSERT(seatOf(playerId)<0);

	_seats[seat] = new PBSeatedPlayer(playerId, this);
	_seats[seat]->setStake( stake );
	_seats[seat]->setSittingOut(sittingOut);
	_seats[seat]->setSeat(seat);

//	qLog(Info)<<handId()<<": "<<seat<<":"<<playerId<<"("<<stake<<")"<<(sittingOut?", sitting out":"");

	return _seats[seat];
}

QString PBSeats::playerIdAt(int seat)
{
	Q_ASSERT(seat<_seats.size());
	return 0!=_seats[seat] ? _seats[seat]->playerId() : "<empty>";
}

PBSeatedPlayer *PBSeats::playerAt(int seat)
{
	Q_ASSERT(seat<_seats.size());
	return _seats[seat];
}

int PBSeats::seatOf(QString playerId)
{
	for(int i=0; i< _seats.size(); i++)
		if(0!=_seats[i] && playerId == _seats[i]->playerId())
			return i;
	return -1;
}

int PBSeats::prevSeat(int seat)
{
	return (--seat + _seats.size()) % _seats.size();
}

int PBSeats::nextSeat(int seat)
{
	return ++seat % _seats.size();
}

bool PBSeats::isEmptySeat(int seat)
{
	Q_ASSERT(seat<_seats.size());
	return _seats[seat] == 0;
}



void PBSeats::leave(PBSeatedPlayer *p)
{
	_seats[p->seat()]->deleteLater();
	_seats[p->seat()] = 0;
}

PBSeatedPlayer *PBSeats::player(const QString &playerId)
{
	int seat = seatOf(playerId);
	if(seat<0)
		return 0;
	return _seats[seat];
}

void PBSeats::reset()
{
	_buttonSeat = -1;
	for(int i=0;i<_seats.size();i++)
		if(!isEmptySeat(i))
			leave(playerAt(i));
}

int PBSeats::buttonSeat()
{
	return _buttonSeat;
}

void PBSeats::setButtonSeat(int seat)
{
	_buttonSeat = seat;

	//qLog(Info)<<handId()<<": button seat " << (buttonSeat()+1) << playerIdAt(buttonSeat());
}
int PBSeats::seatsCount()
{
	return _seats.size();
}

void PBSeats::setSeatsCount(int seatCount)
{
	while(_seats.size()<seatCount)
		_seats.append(0);
}
