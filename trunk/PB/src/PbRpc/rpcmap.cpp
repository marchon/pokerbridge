#include "stdafx.h"
#include "rpcmap.h"
#include "rpcadaptor.h"
#include "rpcchannel.h"

RpcMap::RpcMap(QObject *parent):QObject(parent)
{
}

void RpcMap::put(const QString &path, QObject *obj)
{
	_remotes.insert(obj);
	QObject::connect(obj, SIGNAL(destroyed()), this, SLOT(onDestroyed()));
}

void RpcMap::onDestroyed()
{
	_remotes.remove(sender());
}

QObject* RpcMap::find(const QString &path)
{
	Q_FOREACH(QObject *obj, _remotes)
	{
		RpcAdaptor *ra = RpcAdaptor::get(obj);
		Q_ASSERT(ra);
		if(ra->path()==path)
			return obj;
	}
}

QString RpcMap::pathOf(QObject *obj)
{
	return RpcAdaptor::get(obj)->path();
}

bool RpcMap::invoke(QString path, QVariantMap msg, RpcChannel *chan)
{
	QObject *target = find(path);
	if(0!=target)
	{
		RpcAdaptor *ra = RpcAdaptor::get(target);
		if(0!=ra)
		{
			ra->invokeMessage(msg, chan);
			return true;
		}
	}
	qWarning()<<"target "<<path<<" not found, message="<<msg<<", channel="<<chan->remoteUrl();
	return false;
}

bool RpcMap::signal(QVariantMap msg, RpcChannel *chan)
{
	bool dispatched = false;
	Q_FOREACH(QObject *obj, _remotes)
	{
		RpcAdaptor *ra = RpcAdaptor::get(obj);
		if(0!=ra)
		{
			ra->signalMessage(msg, chan);
			dispatched = true;
		}
	}
	if(!dispatched)
	{
		qLog(Debug)<<"message "<<msg<<" had no listeners";
	}
	return dispatched;
}
