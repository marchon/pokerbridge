#include "StdAfx.h"
#include "rpcadaptor.h"
#include "qslotinvoker.h"
#include "qsignalintercepter.h"
#include "rpcconnection.h"
#include "json.h"
#include "rpcchannel.h"

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


RpcAdaptor::RpcAdaptor(QObject *parent)
	: QObject(parent)
{
	_conn = 0;
	setAutoRelaySignals(true);
	spySignals();
}

RpcAdaptor::~RpcAdaptor()
{

}


QObject *RpcAdaptor::target()
{
	if(!qstrcmp(metaObject()->className(),"RpcAdaptor"))
		return parent();
	return this;
}

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
}

void RpcAdaptor::spySignals()
{
    const QMetaObject *them = target()->metaObject();
	for(int idx=0;idx<them->methodCount();idx++)
	{
		QMetaMethod mm = them->method(idx);
		if (mm.methodType() != QMetaMethod::Signal)
            continue;
		QByteArray sig = QMetaObject::normalizedSignature(mm.signature());
		sig.prepend(QSIGNAL_CODE + '0');
		QSignalIntercepter *si = new RpcSignalIntercepter(target(), sig, this);
	}
}



bool RpcAdaptor::signalMessage(QVariantMap msg, RpcChannel *ch)
{
	QString sender = msg.value("sender").toString();
	QString signal = msg.value("method").toString();
	QVariantList params = msg.value("params").toList();

	Q_ASSERT(_senderPath.isEmpty());
	QByteArray member = _subscribed.value(QPair<QString,QByteArray>(sender, signal.toAscii()),QByteArray());
	if(!member.isEmpty())
	{
		QSlotInvoker invoker(target(), member);
		if(!invoker.memberPresent())
		{
			qLog(Debug)<<" member "<<member<<" not found!";
			return false;
		}
		_senderPath = sender;
		_senderChannel = ch;
		invoker.invoke(params);
		_senderPath = "";
		_senderChannel = 0;
		return true;
	}else{
		qLog(Debug)<<" sender "+sender+" emited "+signal+" with no subscribers";
	}
	return false;
}

bool RpcAdaptor::invokeMessage(QVariantMap msg, RpcChannel *ch)
{
	QString sender = msg.value("sender").toString();
	QString method = msg.value("method").toString();
	QVariantList params = msg.value("params").toList();

	QSlotInvoker invoker(target(), method.toLatin1());
	if(!invoker.memberPresent())
	{
		qLog(Debug)<<" member "<<method<<" not found!";
		return false;
	}
	_senderPath = sender;
	_senderChannel = ch;
	invoker.invoke(params);
	_senderPath = "";
	_senderChannel = 0;
	return true;
}


QString RpcAdaptor::path()
{
	return _conn ? _conn->pathOf(target()):"";
}

void RpcAdaptor::activated(const QByteArray &method, const QList<QVariant>& args)
{
	QVariantMap msg;
	msg["method"] = method;
	msg["params"] = args;
	msg["sender"] = path();
	sendMessage(msg);
}

void RpcAdaptor::sendMessage(QVariantMap map, RpcChannel *ch)
{
	_conn->sendMessage(map, ch);
}

bool RpcAdaptor::invoke(const QString &remotePath, const QByteArray &method, const QVariant &val0, const QVariant &val1 )
{
	QList<QVariant> args;
	if(val0.type()!=QVariant::Invalid)
		args.append(val0);
	if(val1.type()!=QVariant::Invalid)
		args.append(val1);
	return invoke1(remotePath, method, args);
}

bool RpcAdaptor::invoke1(const QString &remotePath, const QByteArray &method, const QList<QVariant> &args)
{
	QVariantMap msg;
	msg["method"] = method;
	msg["params"] = args;
	msg["sender"] = path();
	msg["target"] = remotePath;
	sendMessage(msg);
	return true;
}

QString RpcAdaptor::senderPath()
{
	return _senderPath;
}

RpcChannel *RpcAdaptor::senderChannel()
{
	return _senderChannel;
}

QString RpcAdaptor::senderHost()
{
	RpcChannel *ch = senderChannel();
	if(ch)
		return ch->remoteUrl();
	return "";
}

RpcAdaptor *RpcAdaptor::get(QObject *obj)
{
	RpcAdaptor *a = qobject_cast<RpcAdaptor*>(obj);
	if(0==a)
		a=obj->findChild<RpcAdaptor*>();
//	if(0==a)
//		a=new RpcAdaptor(obj);
	return a;
}

bool RpcAdaptor::connect(const char *path, const char *signal, QObject *receiver, const char*member)
{
	QByteArray sig = QMetaObject::normalizedSignature(member);
	_subscribed.insert(QPair<QString,QByteArray>(path, signal), sig);
	return true;
}


void RpcAdaptor::serialize(QVariantMap &map, QObject *obj, bool read)
{
	if(read)
		ObjectVariant::variantToObject(map, obj);
	else
		ObjectVariant::objectToVariant(map, obj);
	
	/*if(read)
	{
		QVariantList list = map.value("children");
		Q_FOREACH(QVariant v, list)
		{
			QVariantMap vMap = v.toMap();
			RpcAdaptor*adapt = RpcAdaptor::get(child);
			adapt->serialize(list.last(), obj, true);
		}
	}else{
		QVariantList list;
		Q_FOREACH(QObject *child, children())
		{
			list.append(QVariantMap());
			RpcAdaptor*adapt = RpcAdaptor::get(child);
			adapt->serialize(list.last(), obj, false);
		}
		if(list.size()>0)
			map["children"] = list;
	}*/
}
