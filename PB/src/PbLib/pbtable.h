#ifndef PBTABLE_H
#define PBTABLE_H

#pragma once

class PBGameOptions;
#include "pbgameoptions.h"
class PBTable : public QObject 
{
	Q_OBJECT
	
	Q_PROPERTY(PBHandId handId READ handId WRITE setHandId)
	Q_PROPERTY(PBSeats *seats READ seats WRITE setSeats)
	Q_PROPERTY(PBGameOptions gameOptions READ gameOptions)
public:
	PBTable(QObject *parent);
	
	// properties
	QString tableId();
	void setTableId(QString tableId);
	
	PBHandId handId();
	void setHandId(const PBHandId &handId);
	
	PBGameOptions &gameOptions();

	PBSeats *seats();
	void setSeats(PBSeats *seats);
protected:
	PBSeats *_seats;
	PBCards _board;
	PBHandId _handId;
	PBGameOptions _gameOptions;
};


#endif