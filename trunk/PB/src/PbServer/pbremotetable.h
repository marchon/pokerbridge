#pragma once
#include "rpcadaptor.h"

class PBTables;
class PBLobby;

class PBRemoteTable : public QObject
{
	Q_OBJECT
public:
	PBRemoteTable(PBTable *table);

};


class PBRemoteTables: public QObject
{
	Q_OBJECT

public:
	PBRemoteTables(QObject *parent = 0);

	PBTables *tables();
public Q_SLOTS:
	void onTableOpened(QString tableId);
};


class PBRemoteLobby : public RpcAdaptor
{
	Q_OBJECT
public:
	PBRemoteLobby(QObject *parent=0);
};


class PBRemoteLobbies : public RpcAdaptor
{
	Q_OBJECT

public:
	PBRemoteLobbies(QObject *parent=0);


};