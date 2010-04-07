#include "StdAfx.h"
#include "rpcadaptor.h"
#include "qslotinvoker.h"
#include "qsignalintercepter.h"
#include "rpcconnection.h"
#include "json.h"
#include "rpcchannel.h"

const char *RpcUrl::anyHost = "*";

class RpcSignalIntercepter : public QSignalIntercepter
{
public:
	RpcSignalIntercepter(QObject *sender, QByteArray &signal, RpcAdaptor *parent)
		: QSignalIntercepter(sender, signal, parent){ }
protected:
    virtual void activated( const QList<QVariant>& args )
	{
		static_cast<RpcAdaptor*>(parent())->activated(signal(), args);
	}
};


RpcAdaptor::RpcAdaptor( QObject *parent)
	: QObject(parent)
{
	_adaptParent = false;
}

void RpcAdaptor::adaptParent()
{
	_adaptParent = true;
}

bool RpcAdaptor::isAdaptParent()
{
	return _adaptParent;
}

void RpcAdaptor::proxyInit(const RpcUrl &rurl)
{
	setRemoteUrl(rurl);
	connection()->registerProxy(rurl.toString(), this);
	setObjectName(rurl.toString());
}

QObject *RpcAdaptor::findProxy(const QString &path)
{
	return connection()->findProxy(path);
}

void RpcAdaptor::init(const QString &path)
{
	setPath(path);
	_adaptParent = true;
	spySignals(this);
	connection()->registerObject(path, this);
}

RpcAdaptor::~RpcAdaptor()
{

}


QObject *RpcAdaptor::target()
{
	return _adaptParent ? parent() : this;
}

/*
void RpcAdaptor::setAutoRelaySignals(bool enable)
{
    const QMetaObject *us = metaObject();
    const QMetaObject *them = target()->metaObject();
    bool connected = false;
    for (int idx = staticMetaObject.methodCount(); idx < us->methodCount(); ++idx) {
        QMetaMethod mm = us->method(idx);

        if (mm.methodType() != QMetaMethod::Signal)
            continue;

        // try to connect/disconnect to a signal on the parent that has the same method signature
        QByteArray sig = QMetaObject::normalizedSignature(mm.signature());
        if (them->indexOfSignal(sig) == -1)
            continue;
        sig.prepend(QSIGNAL_CODE + '0');
        target()->disconnect(sig, this, sig);
        if (enable)
			connected = QObject::connect(target(), sig, sig) || connected;
    }
    //d_func()->autoRelaySignals = connected;
}*/

void RpcAdaptor::spySignals(QObject *target)
{
    const QMetaObject *them = target->metaObject();
	for(int idx=0;idx<them->methodCount();idx++)
	{
		QMetaMethod mm = them->method(idx);
		if (mm.methodType() != QMetaMethod::Signal)
            continue;
		QByteArray sig = QMetaObject::normalizedSignature(mm.signature());
		sig.prepend(QSIGNAL_CODE + '0');
		QSignalIntercepter *si = new RpcSignalIntercepter(target, sig, this);
//		qLog(Debug)<<"signalspy:"<<sig;
	}
}

bool RpcAdaptor::invokeMethod(const QByteArray &method, const QVariantList &args)
{
	QSlotInvoker invoker(this, method);
	if(!invoker.memberPresent())
	{
		if(_adaptParent)
		{
			QSlotInvoker invoker2(parent(),method);
			if(!invoker2.memberPresent())
			{
				qLog(Debug)<<"RpcAdaptor:: member "<<method<<" not found in "<<parent()<< " or "<<this;
				return false;
			}
			invoker2.invoke(args);
			return true;
		}else
			qLog(Debug)<<"RpcAdaptor:: member "<<method<<" not found in "<<this;
		return false;
	}
	invoker.invoke(args);
	return true;
}

bool RpcAdaptor::remoteCall(const QByteArray &method, const QVariant &val0, const QVariant &val1 )
{
	QList<QVariant> args;
	if(val0.type()!=QVariant::Invalid)
		args.append(val0);
	if(val1.type()!=QVariant::Invalid)
		args.append(val1);
	return remoteCall(method, args);
}

bool RpcAdaptor::remoteCall(const QByteArray &method, const QList<QVariant> &args)
{
	/*QVariantMap msg;
	msg["method"] = method;
	msg["params"] = args;
	msg["sender"] = path();
	msg["target"] = remotePath;
	
	sendMessage(msg);*/
	connection()->remoteCall(remoteUrl(), method, args, path());
	return true;
}


const QString &RpcAdaptor::path() const
{
	return _path;
}

RpcUrl RpcAdaptor::url() const
{
	return RpcUrl(path(), connection()->localHost());
}

void RpcAdaptor::setPath(const QString &path)
{
	_path = path;
}

const RpcUrl &RpcAdaptor::remoteUrl() const
{
	return _remoteUrl;
}

void RpcAdaptor::setRemoteUrl(const RpcUrl &url)
{
	_remoteUrl = url;
}

RpcConnection *RpcAdaptor::connection() const
{
	return RpcConnection::instance();
}
/*
void RpcAdaptor::setConnection(RpcConnection *conn)
{
	_conn=conn;
}
*/

void RpcAdaptor::activated(const QByteArray &member, const QList<QVariant>& args)
{
/*	QVariantMap msg;
	msg["method"] = method;
	msg["params"] = args;
	msg["sender"] = path();
	sendMessage(msg);
*/
	// delegate to connection 
	QByteArray name = member;
	if ( member.size() > 0 && member[0] >= '0' && member[0] <= '9' )
		name=member.mid(1);
	connection()->remoteSignal(name, args, path());
}



const RpcUrl &RpcAdaptor::remoteSender()
{
	return connection()->remoteSender();
}

RpcAdaptor *RpcAdaptor::get(QObject *obj)
{
	// if obj is RpcAdaptor, then object is adapted via inheritance
	RpcAdaptor *a = qobject_cast<RpcAdaptor*>(obj);
	if(0==a)
		a=obj->findChild<RpcAdaptor*>();
	return a;
}

bool RpcAdaptor::connect(const RpcUrl &remoteUrl, const char *signal, const char*member)
{
	QByteArray memberSignature = QMetaObject::normalizedSignature(member);
	QByteArray signalName = QMetaObject::normalizedSignature(signal);
	if ( signalName.size() > 0 && signalName[0] >= '0' && signalName[0] <= '9' )
		signalName=signalName.mid(1);

	_subscribed.insert(RpcMethod(remoteUrl, signalName), memberSignature);

	qLog(Debug)<<"connecting "<<remoteUrl.toString()<<"::"<<signalName<<" to "<<memberSignature;
	return true;
}


void RpcAdaptor::serialize(QVariantMap &map, QObject *obj, bool read)
{
	if(read)
		ObjectVariant::variantToObject(map, obj);
	else
		ObjectVariant::objectToVariant(map, obj);
}


const char *RpcAdaptor::subscriber(const RpcUrl &remoteUrl, const char *signal)
{
	Q_FOREACH(const RpcMethod &m, _subscribed.keys())
	{
		if(remoteUrl.match(m))
			if(m.method == signal)
				return _subscribed[m];
	}
	return 0;
}

void RpcAdaptor::dumpSubscribers()
{
	Q_FOREACH(const RpcMethod &m, _subscribed.keys())
	{
		qLog(Debug)<<"  subscribed to "<<m.method<<" from "<<m.toString()<<", slot="<<_subscribed.value(m);
	}
}