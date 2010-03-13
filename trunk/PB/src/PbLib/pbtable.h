#ifndef PBTABLE_H
#define PBTABLE_H

#pragma once


class PBTable : public QObject 
{
	Q_OBJECT
	
	Q_PROPERTY(PBHandId handId READ handId WRITE setHandId)
	Q_PROPERTY(PBSeats *seats READ seats WRITE setSeats)
public:
	PBTable(QObject *parent);
	
	// properties

	QString roomId();
	QString tableId();
	void setTableId(QString tableId);
	PBHandId handId();
	void setHandId(const PBHandId &handId);
	PBSeats *seats();
	void setSeats(PBSeats *seats);
protected:
	PBSeats *_seats;
	PBCards _board;
	PBHandId _handId;
};


#endif