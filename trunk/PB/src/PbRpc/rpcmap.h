#pragma once

class RpcChannel;
class RpcMap : public QObject
{
public:
	RpcMap(QObject *parent=0);
	void put(const QString &path, QObject *obj);

	QObject* find(const QString &path);
	QString pathOf(QObject *obj);

	//QSetIterator &all(){ return children(); }

	bool invoke(QString path, QVariantMap msg, RpcChannel *chan);
	bool signal(QVariantMap msg, RpcChannel *chan);

protected slots:
	void onDestroyed();
protected:
	QSet<RpcAdaptor*> _remotes;
};