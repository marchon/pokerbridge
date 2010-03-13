#ifndef RPCADAPTER_H
#define RPCADAPTER_H

class RpcConnection;
class RpcChannel;

class PB_EXPORT RpcAdaptor : public QObject
{
	Q_OBJECT

public:
	RpcAdaptor(QObject *parent = 0);
	~RpcAdaptor();
	
	void setAutoRelaySignals(bool enable = true);
	void spySignals();
	static RpcAdaptor *get(QObject *obj);
	QString path();
	void sendMessage(QVariantMap map, RpcChannel *ch=0);

public:
	virtual void activated(const QByteArray &method, const QList<QVariant>& args);
	
	RpcConnection *connection(){ return _conn; }
	void setConnection(RpcConnection *conn){_conn = conn;}
	
	bool connect(const char *path, const char *signal, QObject *receiver, const char*member);
	
	bool invoke1(const QString &remotePath, const QByteArray &method, const QList<QVariant> &args);
	bool invoke(const QString &remotePath, const QByteArray &method, const QVariant &val0 = QVariant(), const QVariant &val1 = QVariant());
	QString senderPath();
	RpcChannel *senderChannel();
	QString senderHost();

	QObject *target();
	virtual void serialize(QVariantMap &map, QObject *obj, bool read);

	bool signalMessage(QVariantMap msg, RpcChannel *ch);
	bool invokeMessage(QVariantMap msg, RpcChannel *ch);
private:
	QHash<QPair<QString, QByteArray>, QByteArray> _subscribed;
	RpcConnection *_conn;
	QString _senderPath;
	QPointer<RpcChannel> _senderChannel;
};

#endif // RPCADAPTER_H
