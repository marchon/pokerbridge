#ifndef RpcChannel_H
#define RpcChannel_H

class JsonReader;
class QTcpSocket;
class RpcConnection;
class RpcMap;
class RpcUrl;
class PB_EXPORT RpcChannel : public QObject
{
	Q_OBJECT

public:
	RpcChannel(QTcpSocket *socket, RpcConnection *conn);
	RpcChannel(RpcConnection *conn);
	~RpcChannel();
public:
	RpcConnection *connection();
public:
	// connects to tcp RPC server
	bool connectToServer(QString url, uint port);
	QString remoteHost();
	QString localHost();

	bool remoteCall(const RpcUrl &path, const QByteArray &method, const QList<QVariant> &args, const RpcUrl &senderUrl);
	bool remoteSignal(const QByteArray &signal, const QList<QVariant> &args, const RpcUrl &senderUrl);

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
	QString _localHost;
	int _localPort;
	RpcMap* _map;
};

#endif // RpcChannel_H
