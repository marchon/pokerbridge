#ifndef RpcConnection_H
#define RpcConnection_H

//#include <QObject>

class RpcListener;
class RpcChannel;
#include "rpcurl.h"
#include "rpcadaptor.h"

class PB_EXPORT RpcConnection : public QObject
{
	Q_OBJECT

public:
	RpcConnection(QObject *parent = 0);
	~RpcConnection();

	// registers object
	void registerObject(const QString &path, QObject *obj);
	void registerProxy(const QString &path, QObject *obj);
	static RpcConnection *instance();
	RpcAdaptor *findObject(const QString &path);
	RpcAdaptor *findProxy(const QString &path);

	bool invoke(QObject *self, const QString &remote, const QByteArray &method, const QList<QVariant> &args);

	void dumpObjects();
	const RpcUrl &remoteSender();

	QString localHost();
	// called by RpcAdaptor
public:
	bool remoteCall(const RpcUrl &path, const QByteArray &method, const QList<QVariant> &args, const QString &senderPath);
	bool remoteSignal(const QByteArray &signal, const QList<QVariant> &args, const QString &senderPath);

	// called by RpcChannel
	void channelConnected(RpcChannel *chan);
	void chanelDisconnected(RpcChannel *chan);
	void channelSignal(const QByteArray &signal, const QList<QVariant> &args, const RpcUrl &senderUrl);
	void channelCall(const RpcUrl &path, const QByteArray &method, const QList<QVariant> &args, const RpcUrl &senderUrl);

	// implementation (tcp)
	void setListener(RpcListener *list);
	bool listenTcp(uint port);
	bool connectTcp(QString host, uint port);

	// notify all about channels
signals:
	void disconnected(RpcChannel *chan);
	void connected(RpcChannel *chan);

protected:
	QString _localHost;
	int _localPort;
	QMap<QString, QPointer<RpcAdaptor>> _objects; // path->adaptor
	QMap<QString, QPointer<RpcChannel>> _channels;	// host->channel
	RpcUrl _remoteSender;
	QPointer<RpcListener> _listener;
	static QPointer<RpcConnection> _instance;
};

#endif // RpcConnection_H
