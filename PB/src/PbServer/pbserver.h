#pragma once
class RpcConnection;
class PBRemoteLobbies;

class PBServerApp : public QCoreApplication
{
	Q_OBJECT
public:
	PBServerApp(int argc, char*argv[]);

protected:
	QPointer<PBRemoteLobbies> _remoteLobbies;
	QPointer<RpcConnection> _conn;
};