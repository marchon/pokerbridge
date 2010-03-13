#ifndef PBSEATS_H
#define PBSEATS_H

#pragma once

class PBSeats : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int buttonSeat READ buttonSeat WRITE setButtonSeat)
	Q_PROPERTY(int seatsCount READ seatsCount)
public:
	PBSeats(QObject *parent);

	QString playerIdAt(int seat);
	PBSeatedPlayer *player(const QString &playerId);
	
	PBSeatedPlayer *playerAt(int seat);
	void join(PBSeatedPlayer *p);
	PBSeatedPlayer *join(int seat, const PBPlayerId &playerId, double stake, bool sittingOut);

	int seatOf(QString playerId);
	int prevSeat(int seat);
	int nextSeat(int seat);
	bool isEmptySeat(int seat);

	void reset();	// all players leave
	
	void leave(PBSeatedPlayer *p);

	void setButtonSeat(int seat);
	int buttonSeat();

	int seatsCount();
	void setSeatsCount(int seatCount);
protected:
	QList<QPointer<PBSeatedPlayer>> _seats;
	int _buttonSeat;
};

#endif