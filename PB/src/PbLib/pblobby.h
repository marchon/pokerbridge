#pragma once

class PBTables;

class PBLobby : public QObject
{
public:
	PBTables *tables();

protected:
	QPointer<PBTables> _tables;
};