#include "StdAfx.h"
#include "RpcConnection.h"
#include "rpcadaptor.h"
#include "rpcconnection.h"
#include "rpcchannel.h"
#include "rpclistener.h"

RpcConnection::RpcConnection(QObject *parent)
	: QObject(parent)
{
	_instance = this;
}

RpcConnection::~RpcConnection()
{
	
}

bool RpcConnection::connect(const char *path, const char *signal, QObject *receiver, const char*member)
{
	RpcAdaptor *adptr = RpcAdaptor::get(receiver);
	Q_ASSERT(adptr);
	return adptr->connect(path, signal, receiver, member);
}

void RpcConnection::registerObject(QObject *obj)
{
	registerObject(obj->objectName(), obj);
}

void RpcConnection::registerObject(const QString &path, QObject *obj)
{
	_published.insert(path, obj);
	QObject::connect(obj, SIGNAL(destroyed()), this, SLOT(unregisterSender()));
	
	RpcAdaptor *adaptor  = RpcAdaptor::get(obj);
	Q_ASSERT(adaptor);
	if(0!=adaptor)
	{
		adaptor->setConnection(this);
	}
}


void RpcConnection::unregisterSender()
{
	Q_FOREACH(QString key, _published.keys())
	{
		if(_published[key]==sender())
			_published.remove(key);
	}
}

QObject *RpcConnection::target(QString target)
{
	return _published.value(target,0);
}

QString RpcConnection::pathOf(QObject *obj)
{
	Q_FOREACH(QString key, _published.keys())
	{
		return key;
	}
	return "";
}

void RpcConnection::newChannel(RpcChannel *ch)
{
	QObject::connect(ch, SIGNAL(incomingMessage(QVariantMap)), this, SLOT(channelIncomingMessage(QVariantMap)));
	emit channelOpened(ch);
}

void RpcConnection::channelDisconnected(RpcChannel *ch)
{
	emit channelClosed(ch);
	ch->deleteLater();
}

void RpcConnection::channelIncomingMessage(QVariantMap map)
{
	emit incomingMessage(map, qobject_cast<RpcChannel*>(sender()));
}

void RpcConnection::sendMessage(QVariantMap map, RpcChannel *ch)
{
	if(0!=ch)
		ch->sendMessage(map);
	else
		Q_FOREACH(QObject *obj, children())
		{
			RpcChannel *chan = qobject_cast<RpcChannel*>(obj);
			if(0!=chan)
				chan->sendMessage(map);
		}
}

void RpcConnection::setListener(RpcListener *list)
{
	_listener = list;
	_listener->setParent(this);
}

bool RpcConnection::listenTcp(uint port)
{
	_listener = new RpcListener(this);
	return _listener->listen(port);
}

bool RpcConnection::connectTcp(QString host, uint port)
{
	RpcChannel *channel = new RpcChannel(this);
	return channel->connectToServer(host, port);
}

bool RpcConnection::invoke(QObject *self, const QString &remote, const QByteArray &method, const QList<QVariant> &args)
{
	RpcAdaptor* adapt = RpcAdaptor::get(self);
	Q_ASSERT(adapt);
	return adapt->invoke1(remote,method,args);
}