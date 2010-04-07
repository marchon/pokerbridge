#ifndef RPCADAPTER_H
#define RPCADAPTER_H

#include "rpcchannel.h"
#include "rpcurl.h"

class RpcConnection;
class PB_EXPORT RpcAdaptor : public QObject
{
	Q_OBJECT
public:
	RpcAdaptor(QObject *parent);
	//RpcAdaptor(RpcConnection *conn, QObject *parent = 0);
	//RpcAdaptor(const RpcUrl &myUrl, QObject *parent=0);

	~RpcAdaptor();

	static RpcAdaptor *get(QObject *obj);

	void proxyInit(const RpcUrl &rurl);
	void init(const QString &path);
	QObject *findProxy(const QString &path);

	// local object path
	const QString &path() const;
	void setPath(const QString &path);

	RpcUrl url() const;

	const RpcUrl &remoteUrl() const;
	void setRemoteUrl(const RpcUrl &url);

	//void registerObject(QString path, QString host=RpcUrl::anyHost);

	//void registerProxy(QString remotePath);

	RpcConnection *connection() const;
	void setConnection(RpcConnection *conn);

	// connect remote signal to this object
	bool connect(const RpcUrl &remoteUrl, const char *signal, const char*member);
	const char *subscriber(const RpcUrl &remoteUrl, const char *signal);

	const RpcUrl &remoteSender();

	// call remote method
	bool remoteCall(const QByteArray &method, const QList<QVariant> &args);
	bool remoteCall(const QByteArray &method, const QVariant &val0 = QVariant(), const QVariant &val1 = QVariant());

	// we adapt parent or we adapt ourself?
	void adaptParent();
	bool isAdaptParent();

	QObject *target();

	void dumpSubscribers();

	// serialization
	virtual void serialize(QVariantMap &map, QObject *obj, bool read);

	// adaptor-mode invokers
	bool invokeMethod(const QByteArray &method, const QVariantList &args);

	// implementation
protected:
	void setAutoRelaySignals(bool enable = true);
	void spySignals(QObject *target);
public:
	virtual void activated(const QByteArray &method, const QList<QVariant>& args);


	bool invokeMessage(QVariantMap msg, RpcChannel *ch);

private:
	bool _adaptParent;
	QMap<RpcMethod, QByteArray> _subscribed;
	RpcUrl _remoteUrl;	// remote object url (for proxy)
	QString _path;	// url under which this object is registered in the hash
	RpcUrl _remoteSender;	// remote sender which issued the signal (TODO: TLS?)
};

#endif // RPCADAPTER_H
