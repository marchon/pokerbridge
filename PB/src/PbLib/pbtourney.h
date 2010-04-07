#pragma once

#include "pbhandinfo.h"

#define PBTourneyStatus QString

class PBTourneyInfo : public PBGameInfo
{
	Q_OBJECT;
	
	Q_ENUMS(PBTourneyStatus)
	Q_PROPERTY(PBTourneyStatus tourneyStatus READ tourneyStatus WRITE setTourneyStatus);
	Q_PROPERTY(double buyIn READ buyIn WRITE setBuyIn);
	Q_PROPERTY(double rake READ rake WRITE setRake);
	Q_PROPERTY(QString tourneyId READ tourneyId WRITE setTourneyId);

public:
	PBTourneyInfo(QObject *parent=0) : PBGameInfo(parent){}

	PBTourneyStatus tourneyStatus() { return _tourneyStatus; }
	void setTourneyStatus(PBTourneyStatus status) { _tourneyStatus = status; }

	double buyIn() { return _buyIn; }
	void setBuyIn(double buyIn) { _buyIn = buyIn; }

	bool isLocked(){return _lockTime>-1;}
	void lock(){ }

	double rake() {return _rake;}	
	void setRake(double rake) {_rake=rake; }
	
	QString tourneyId() {return _tourneyId;}
	void setTourneyId(QString tourneyId){ _tourneyId = tourneyId; }
private:
	QString _tourneyId;
	PBTourneyStatus _tourneyStatus;
	double _buyIn;
	double _rake;
	
	long _lockTime;
};

class PBTourneys;

class PBTourney : public QObject
{
	Q_OBJECT
//	Q_ENUMS(PBTourneyStatus)
	Q_PROPERTY(PBTourneyStatus tourneyStatus READ tourneyStatus WRITE setTourneyStatus);
	Q_PROPERTY(QString tourneyId READ tourneyId WRITE setTourneyId);
	Q_PROPERTY(QString siteId READ siteId WRITE setSiteId);
public:
	PBTourney(QString tourneyId, QObject *parent=0);

	PBTourneyStatus parseStatus(QString status);

	// FT=FullTilt,...
	QString siteId(){ return _site; }
	void setSiteId(QString site){ _site=site; }

	void setTourneyId(QString tourneyId);
	QString tourneyId();
	
	PBTourneyStatus tourneyStatus() { return _tourneyStatus; }
	void setTourneyStatus(PBTourneyStatus status) { _tourneyStatus = status; }
	
	PBTourneys *tourneys();
	void emitUpdated();
protected:
	PBTourneyStatus _tourneyStatus;
	QString _site;
};

class PBTourneys : public QObject
{
	Q_OBJECT
public:
	PBTourneys(QObject *parent=0);
	PBTourney *newTourney(QString tourneyId);
	PBTourney *tourney(QString tourneyId);

	void emitTourneyUpdated(PBTourney *trn);
signals:
	void newTourneyEvent(PBTourney *trn);
	void tourneyUpdatedEvent(PBTourney *trn);
};