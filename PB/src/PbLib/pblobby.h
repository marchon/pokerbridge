#pragma once

#include "pbtables.h"
#include "pbtourney.h"

class PBTables;
class RpcChannel;
class PBLobby : public QObject
{
	Q_OBJECT;
public:
	PBLobby(QObject *parent=0);
	PBTables *tables(){ return _tables; }
	PBTourneys *tourneys(){ return _tourneys; }
signals:
	void pong();

public slots:
	void ping();
protected:
	QPointer<PBTables> _tables;
	QPointer<PBTourneys> _tourneys;
};

