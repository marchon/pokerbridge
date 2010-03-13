#ifndef PBSEATEDPLAYER_H
#define PBSEATEDPLAYER_H

class PBSeatedPlayer : public QObject
{
	Q_OBJECT;
	
	Q_PROPERTY(int seat READ seat WRITE setSeat) 
	Q_PROPERTY(QString playerId READ playerId WRITE setPlayerId)
	Q_PROPERTY(double stake READ stake WRITE setStake) 
	Q_PROPERTY(bool sittingOut READ sittingOut WRITE setSittingOut)
	Q_PROPERTY(QString holeCards READ holeCards WRITE setHoleCards);

public:
	PBSeatedPlayer(PBPlayerId playerId, QObject *parent = 0);

// properties
	int seat();
	void setSeat(int seat);

	PBPlayerId playerId();
	void setPlayerId(const PBPlayerId &id);

	double stake();
	void setStake(double stake);
	
	PBCards holeCards();
	void setHoleCards(const PBCards &cards);

	bool sittingOut();
	void setSittingOut(bool sittingOut);
	
	PBTable *table();

signals:
	void sitIn(PBSeatedPlayer *player);
	void sitOut(PBSeatedPlayer *player);

protected:
	double _stake;
	bool _sittingOut;
	PBCards _holeCards;
	int _seat;
};
#endif