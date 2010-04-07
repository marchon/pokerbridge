#include "StdAfx.h"
#include "RpcConnection.h"
#include "rpcadaptor.h"
#include "rpcmap.h"
#include "rpcconnection.h"
#include "rpcchannel.h"
#include "rpclistener.h"

RpcConnection::RpcConnection(QObject *parent)
	: QObject(parent)
{
	_instance = this;
	qLog()<<"RpcConnection created"<<this;
}

RpcConnection::~RpcConnection()
{
	
}

RpcConnection* RpcConnection::instance()
{
	return _instance;
}

QPointer<RpcConnection> RpcConnection::_instance;

void RpcConnection::registerObject(const QString &path, QObject *obj)
{
	RpcAdaptor *adaptor  = RpcAdaptor::get(obj);
	Q_ASSERT(adaptor);
	if(0!=adaptor)
	{
		//adaptor->setConnection(this);
		adaptor->setPath(path);
		_objects[path] = adaptor;
		qLog(Debug)<<"registered "<<path<<"=>"<<obj<<", total "<<_objects.size();
//		dumpObjects();
	}
}

void RpcConnection::registerProxy(const QString &path, QObject *obj)
{
	registerObject("proxy-for-"+path, obj);
}

RpcAdaptor *RpcConnection::findObject(const QString &path)
{
	return _objects.value(path,0);
}

RpcAdaptor *RpcConnection::findProxy(const QString &path)
{
	return findObject("proxy-for-"+path);
}

QString RpcConnection::localHost()
{
	if(_channels.size()==0)
		return "";
	return _channels.values().first()->localHost();
}

const RpcUrl &RpcConnection::remoteSender()
{
	return _remoteSender;
}

void RpcConnection::channelConnected(RpcChannel *ch)
{
	_channels.insert(ch->remoteHost(),ch);
	
	_remoteSender.host = ch->remoteHost();
	_remoteSender.path = "";
	// in DIRECT connected  handlers, the remoteSender() will contain host-id 
	emit connected(ch);
	_remoteSender.clear();
}


void RpcConnection::chanelDisconnected(RpcChannel *ch)
{
	_remoteSender.host = ch->remoteHost();
	_remoteSender.path = "";
	emit disconnected(ch);
	_channels.remove(ch->remoteHost());
	ch->deleteLater();
	_remoteSender.clear();
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

void RpcConnection::channelSignal(const QByteArray &signal, const QList<QVariant> &args, const RpcUrl &senderUrl)
{
	qLog(Debug)<<"RecvSignal: "<<signal<<" from "<<senderUrl.toString();
	for(int i=0;i<args.length();i++)
		qLog(Debug)<<args[i];

	int dispatched = 0;
	Q_FOREACH(RpcAdaptor *a, _objects.values())
	{
		const char *slot = a->subscriber(senderUrl, signal);
		if(slot)
		{
			_remoteSender = senderUrl;
			if(a->invokeMethod(slot, args))
			{
				dispatched++;
			}
			_remoteSender.clear();
		}
	}
	if(!dispatched)
	{
		qWarning()<<"no subscriber for signal "<<signal<<" from "<<senderUrl.toString();
//		dumpObjects();
	}
}

void RpcConnection::channelCall(const RpcUrl &url, const QByteArray &method, const QList<QVariant> &args, const RpcUrl &senderUrl)
{
//	if(url.host!=localHost())
//		return;

	qLog(Debug)<<"RecvCall: "<<method<<" to "<<url.toString()<<" from "<<senderUrl.toString();

	RpcAdaptor *a = _objects.value(url.path,0);
	if(a)
	{
		_remoteSender = senderUrl;
		a->invokeMethod(method, args);
		_remoteSender.clear();
	}else
	{
		qWarning()<<"no adaptor for "<<url.toString()<<"-"<<method<<" called by "<<senderUrl.toString();
//		dumpObjects();
	}
}

void RpcConnection::dumpObjects()
{
	qLog(Debug)<<"remoting map:";
	Q_FOREACH(QString path, _objects.keys())
	{
		RpcAdaptor *a = _objects.value(path);
		qLog(Debug)<<path<<"=>"
			<<"{path="<<a->path()<<",obj="
			<<a->target()<<"}";
		a->dumpSubscribers();
	}
}

bool RpcConnection::remoteCall(const RpcUrl &target, const QByteArray &method, const QList<QVariant> &args, const QString &senderPath)
{
	RpcUrl localUrl(senderPath);
	RpcChannel *chan = _channels.value(target.host,0);
	if(chan)
	{
		localUrl.host=chan->localHost();
		chan->remoteCall(target, method, args,localUrl);
	}
	else
		qWarning()<<"no channel for "<<target.toString()<<"-"<<method<<" called by "<<localUrl.toString();
	return true;
}

bool RpcConnection::remoteSignal(const QByteArray &signal, const QList<QVariant> &args, const QString &senderPath)
{
//	qLog(Debug)<<"SIGNAL "<<signal<<"("<<args<<") from"<<senderUrl.toString();
	Q_FOREACH(RpcChannel *chan, _channels.values())
	{
		RpcUrl localUrl(senderPath, chan->localHost());
		chan->remoteSignal(signal, args, localUrl);
	}
	return true;
}



RpcUrl RpcUrl::remote(QString path)
{
	return RpcUrl(path, RpcConnection::instance()->remoteSender().host);
}
