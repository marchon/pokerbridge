#include "stdafx.h"
#include "pblobby.h"
#include "pbtables.h"

PBLobby::PBLobby(QObject *parent)
{
	_tables = new PBTables(this);
	_tourneys = new PBTourneys(this);
}

void PBLobby::ping()
{
	emit pong();
}


void PBLib_init()
{
	//qRegisterMetaType<PBTourneyStatus>();
}