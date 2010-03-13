#include "stdafx.h"
#include "pbserver.h"
#include "rpcconnection.h"
#include "pbremotetable.h"

PBServerApp::PBServerApp(int argc, char*argv[]) : QCoreApplication(argc, argv)
{
	_conn = new RpcConnection(this);
	_conn->listenTcp(777);
	_conn->registerObject("/server/lobbies", _remoteLobbies);
}


int main(int argc, char*argv[])
{
	PBServerApp app(argc, argv);

	return app.exec();
}