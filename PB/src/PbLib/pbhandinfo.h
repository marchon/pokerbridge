#ifndef PBGAMEINFO_H
#define PBGAMEINFO_H

/*
class PBGameInfo : public QObject
{
	Q_OBJECT

	Q_PROPERTY(double smallBlind READ smallBlind WRITE setSmallBlind);
	Q_PROPERTY(double bigBlind READ bigBlind WRITE setBigBlind);
	Q_PROPERTY(QString site READ site WRITE setSite);
public:
	PBGameInfo(QObject *parent = 0) : QObject(parent)
	{
		_smallBlind = -1;
	}

	QString site();
	void setSite(const QString &site);

	double smallBlind();
	void setSmallBlind(double sb);

	double bigBlind();
	void setBigBlind(double bb);

	// "FR" "SH" "HU" "SNG", etc
	QString gameType();
	void setGameType(QString type);

	int maxSeats();
	void setMaxSeats(int seats);

protected:
	double _smallBlind;
	double _bigBlind;
	QString _gameType;
	int _maxSeats;
	QString _site;
};
*/
#include "pbgameinfo.h"

class PBHandInfo: public PBGameInfo
{
	Q_OBJECT
	Q_PROPERTY(QString handId READ handId WRITE setHandId);
	Q_PROPERTY(QString tableId READ tableId WRITE setTableId);
public:

	PBHandInfo(QObject *parent = 0) : PBGameInfo(parent){}


	QString handId();
	void setHandId(QString handId);

	QString tableId();
	void setTableId(QString tableId);

	QString toTypeString();
protected:
	QString _handId;
	QString _tableId;
};

#endif