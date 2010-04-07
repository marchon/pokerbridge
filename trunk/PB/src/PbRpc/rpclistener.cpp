#include "StdAfx.h"
#include "RpcListener.h"
#include "rpcconnection.h"
#include "rpcchannel.h"

RpcListener::RpcListener(RpcConnection *parent)
	: QObject(parent)
{
	
}

RpcListener::~RpcListener()
{
	
}

RpcConnection *RpcListener::connection()
{
	return static_cast<RpcConnection*>(parent());
}

bool RpcListener::listen(uint port)
{
	_server = new QTcpServer(this);
	connect(_server, SIGNAL(newConnection()), SLOT(newConnection()));
	bool res = _server->listen(QHostAddress::Any, port);
	
	qLog(Debug)<<"Server listens at port "<<port;
	return res;
}

void RpcListener::newConnection()
{
	RpcChannel *ch = new RpcChannel(_server->nextPendingConnection(), connection());
	qLog(Debug) << "newConnection" <<endl;

	connection()->channelConnected(ch);
}

