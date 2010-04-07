#include "stdafx.h"
#include "pbtourney.h"

PBTourney::PBTourney(QString tourneyId, QObject *parent)
{
	setTourneyStatus("Unknown");
	setTourneyId(tourneyId);
}

void PBTourney::setTourneyId(QString tourneyId)
{
	setObjectName(tourneyId);
}

QString PBTourney::tourneyId()
{
	return objectName();
}

PBTourneys* PBTourney::tourneys()
{
	return static_cast<PBTourneys*>(parent()); 
}
	
void PBTourney::emitUpdated()
{
	tourneys()->emitTourneyUpdated(this);
}

PBTourneyStatus PBTourney::parseStatus(QString status)
{
	return status;
}

PBTourneys::PBTourneys(QObject *parent) : QObject(parent)
{
}

PBTourney *PBTourneys::newTourney(QString tourneyId)
{
	PBTourney *trn = new PBTourney(tourneyId, this);
	emit newTourneyEvent(trn);
	return trn;
}


void PBTourneys::emitTourneyUpdated(PBTourney *trn)
{
	emit tourneyUpdatedEvent(trn);
}

PBTourney *PBTourneys::tourney(QString tourneyId)
{
	return qFindChild<PBTourney*>(this, tourneyId);
}