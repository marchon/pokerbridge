#include "StdAfx.h"
#include "rmessage.h"
#include "rmessageadaptor.h"
#include "json.h"

RMessage::RMessage(const char *type)
{
	qRegisterMetaType<RMessage>();

	_flags = 0;
	_flags |= NotifyChildren;
	_flags |= NotifyParents;

	_sender = 0;
	_queue = 0;
	setType(type);

}

RMessage::~RMessage()
{

}

QByteArray RMessage::type()
{
	return _args.value("r-type", "").toByteArray();
}

void RMessage::setType(const QByteArray &type)
{
	_args["r-type"] = type;
}

void RMessage::setVisited(RMessageAdaptor *a)
{
	_visited.insert(a);
}

bool RMessage::isVisited(RMessageAdaptor *a)
{
	return _visited.contains(a);
}

RMessage &RMessage::put(const char *attr, const QVariant &value)
{
	_args.insert(attr, value);
	return *this;
}

RMessage &RMessage::put(QObject *obj)
{
	ObjectVariant::objectToVariant(_args, obj);
	return *this;
}

void RMessage::get(QObject *obj)
{
	ObjectVariant::variantToObject(args(), obj);
}

void RMessage::copyFrom(RMessage *other)
{
	Q_FOREACH(QString key, other->args().keys())
	{
		if(!key.startsWith("r-"))
			put(key.toAscii(), other->args()[key]);
	}
}

void RMessage::replyTo(RMessage *other)
{
	copyFrom(other);
	_queue = other->_queue;
	_flags = other->_flags;
}

int RMessage::getInt(const char *attr, int def)
{
	return _args.value(attr, def).toInt();
}

QString RMessage::getString(const char *attr, const QString &def)
{
	return _args.value(attr, def).toString();
}

QVariant RMessage::get(const char *attr, const QVariant &def)
{
	return _args.value(attr,def);
}



QObject *RMessage::sender()
{
	return _sender;
}

RMessageQueue *RMessage::queue()
{
	return _queue;
}

void RMessage::setQueue(RMessageQueue *queue)
{
	_queue = queue;
}

void RMessage::send(QObject *target)
{
	RMessageAdaptor *adaptor = RMessageAdaptor::getRMsg(target);
	if(0!=adaptor)
		adaptor->sendRMsg(this);
	else
		qLog(Debug)<<"RMessage::send(): failed to get adaptor for "<<target;
}

void RMessage::fromMap(const QVariantMap &map)
{
	_args = map;
}

void RMessage::toMap(QVariantMap &map)
{
	map = _args;
}
