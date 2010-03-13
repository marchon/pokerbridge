#ifndef RpcListener_H
#define RpcListener_H

class QTcpServer;
class RpcConnection;
class RpcRegistry;
class RpcChannel;
class PB_EXPORT  RpcListener : public QObject
{
	Q_OBJECT

public:
	RpcListener(RpcConnection *parent = 0);
	~RpcListener();

	bool listen(uint port);

	RpcConnection *connection();

signals:
	void incomingMessage(QVariantMap msg, RpcChannel *ch);
private Q_SLOTS:
	void newConnection();
	void connNewMessage(QVariantMap msg);
private:
	QTcpServer *_server;	
	RpcRegistry *_reg;
};

#endif // RpcListener_H
