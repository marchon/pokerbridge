#pragma once

#include "pbhandinfo.h"

class PBTourneyInfo : public PBGameInfo
{
	Q_OBJECT;
	
	Q_ENUMS(TourneyStatus)
	Q_PROPERTY(TourneyStatus tourneyStatus READ tourneyStatus WRITE setTourneyStatus);
	Q_PROPERTY(double buyIn READ buyIn WRITE setBuyIn);
	Q_PROPERTY(double rake READ rake WRITE setRake);
	Q_PROPERTY(QString tourneyId READ tourneyId WRITE setTourneyId);

public:
	enum TourneyStatus
	{
		Registering,
		Running,
		Completed
	};

	PBTourneyInfo(QObject *parent=0) : PBGameInfo(parent){}

	TourneyStatus tourneyStatus() { return _tourneyStatus; }
	void setTourneyStatus(TourneyStatus status) { _tourneyStatus = status; }

	double buyIn() { return _buyIn; }
	void setBuyIn(double buyIn) { _buyIn = buyIn; }

	double rake() {return _rake;}	
	void setRake(double rake) {_rake=rake; }
	
	QString tourneyId() {return _tourneyId;}
	void setTourneyId(QString tourneyId){ _tourneyId = tourneyId; }
private:
	QString _tourneyId;
	TourneyStatus _tourneyStatus;
	double _buyIn;
	double _rake;
};

