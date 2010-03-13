#ifndef RpcChannel_H
#define RpcChannel_H

class JsonReader;
class QTcpSocket;
class RpcConnection;

class PB_EXPORT RpcChannel : public QObject
{
	Q_OBJECT

public:
	RpcChannel(QTcpSocket *socket, RpcConnection *conn);
	RpcChannel(RpcConnection *conn);
	~RpcChannel();
public:
	RpcConnection *connection();
	// connects obj signals and slots to this channel
	void registerObject( QObject *obj);

public:
	// connects to tcp RPC server
	bool connectToServer(QString url, uint port);
	QString remoteUrl();
protected:
	void init();

signals:
	//void incomingMessage(QVariantMap msg);
	//void disconnected();
public slots:
	void readyRead();
	void connected();
	void sendMessage(QVariantMap msg);
	void newMessage(QVariantMap msg);
	void socketDisconnected();
protected:
	QTcpSocket *_socket;
	JsonReader *_reader;
	RpcConnection *_conn;
	QString _remoteHost;
	int _remotePort;
};

#endif // RpcChannel_H
