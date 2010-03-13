#ifndef RpcConnection_H
#define RpcConnection_H

//#include <QObject>

class RpcListener;
class RpcChannel;
class PB_EXPORT RpcConnection : public QObject
{
	Q_OBJECT

public:
	RpcConnection(QObject *parent = 0);
	~RpcConnection();

	void registerObject(const QString &path, QObject *obj);
	void registerObject(QObject *obj);
	void setListener(RpcListener *list);
	
	static RpcConnection *instance();

	bool connect(const char *path, const char *signal, QObject *receiver, const char*member);

	bool invoke(QObject *self, const QString &remote, const QByteArray &method, const QList<QVariant> &args);

	bool listenTcp(uint port);
	bool connectTcp(QString host, uint port);

	//void registerAllWithConnection(RpcConnection*conn);

	QObject *target(QString path);
	QString pathOf(QObject *obj);

	QHash<QString, QPointer<QObject>> published(){ return _published; }
signals:
	void incomingMessage(QVariantMap map, RpcChannel *ch);
	void channelOpened(RpcChannel *ch);
	void channelClosed(RpcChannel *ch);
protected Q_SLOTS:
	void unregisterSender();
public Q_SLOTS:
	void sendMessage(QVariantMap map, RpcChannel *ch = 0);
	void newChannel(RpcChannel *ch);
public Q_SLOTS:
	void channelIncomingMessage(QVariantMap map);
	void channelDisconnected(RpcChannel *ch);
private:
	QHash<QString, QPointer<QObject>> _published;
	QPointer<RpcListener> _listener;
	QPointer<RpcConnection> _instance;
};

#endif // RpcConnection_H
