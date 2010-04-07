#include "StdAfx.h"
#include "rmessageadaptor.h"
//#include "qslotinvoker.h"
#include "json.h"

//#define RMSG_LOG

RMessageAdaptor::RMessageAdaptor(QObject *parent, bool inheritedMode)
	: QObject(parent), _inheritedMode(inheritedMode)
{
	_flags |= RMessage::NotifyChildren;
	_flags |= RMessage::NotifyParents;
}

RMessageAdaptor::~RMessageAdaptor()
{

}

typedef QPair<int,RMessageAdaptor*> RPrio ;

bool prioLessThan(const RPrio &a, const RPrio &b)
{
	return a.first<b.first;
}

void RMessageAdaptor::dispatchRMsg(RMessage *msg)
{
	if(msg->isDone())
		return;
#ifdef RMSG_LOG
	qLog(Debug)<<"dispatch at "<<this<<" of "<<msg->type()<<ObjectVariant::toShortString(msg->args());
#endif
	
//	onRMsg(msg);
//	if(msg->isDone())
//		return;

	// collect targets
	QList<RMessageAdaptor*> targets;
	targetsRMsg(&targets, msg);	

	// sort targets by priority
	QVector<QPair<int,RMessageAdaptor*>> prio;
	Q_FOREACH(RMessageAdaptor *tgt, targets)
	{
		prio.append(RPrio(tgt->testRMsg(msg), tgt));
	}
	qSort(prio.begin(), prio.end(), prioLessThan);
#ifdef RMSG_LOG
	Q_FOREACH(RPrio p1, prio)
	{
		qLog(Debug)<<p1.first<<" - "<<p1.second<<"("<<p1.second->targetRMsg();
	}
#endif
	// fire targets in priority order
	Q_FOREACH(RPrio p, prio)
	{
		p.second->onRMsg(msg);
	}

/*	Q_FOREACH(RMessageAdaptor* rmsg, targets)
	{
		if(rmsg)
		{
			if(!msg->isVisited(rmsg))
				rmsg->dispatchRMsg(msg);
			if(msg->isDone())
				return;
		}
	}
*/}

void RMessageAdaptor::onRMsg(RMessage *msg)
{
	if(msg->isVisited(this))
		return;

	msg->setVisited(this);
//	qLog(Debug)<<"("<<pathRMsg()<<")onRMsg: target="<<targetRMsg()<<","<<targetRMsg()->objectName()<<", msg="<<msg->args();
	if(filterRMsg(msg))
		handleRMsg(msg);
}

QObject *RMessageAdaptor::targetRMsg()
{
	QObject *target = this;
	if(!_inheritedMode)
		target = parent();
	return target;
}

void RMessageAdaptor::handleRMsg(RMessage *msg)
{
	QObject *atarget = targetRMsg();
	if(!atarget)
		return;

	QByteArray &msgType = msg->type();

	QByteArray methodName("on");
	methodName.append(msgType);
	methodName.append("(RMessage*)");

	int methodIndex = atarget->metaObject()->indexOfMethod(methodName);
	if(methodIndex>-1)
	{
		void* args[2];
		args[0]=0;
		args[1]=&msg;

		atarget->qt_metacall(QMetaObject::InvokeMetaMethod, methodIndex, args);
	}
}

int RMessageAdaptor::testRMsg(RMessage *msg)
{
	QObject *atarget = targetRMsg();
	if(!atarget)
		return 0;

	QByteArray methodName("pri");
	QByteArray &msgType = msg->type();
	methodName.append(msgType);
	methodName.append("(RMessage*)");
	int methodIndex = atarget->metaObject()->indexOfMethod(methodName);
	if(methodIndex>-1)
	{
		void* args[2];
		int ret = 0;
		args[0]=&ret;
		args[1]=&msg;
		atarget->qt_metacall(QMetaObject::InvokeMetaMethod, methodIndex, args);
		return ret;
	}
	return 0;
}

QString RMessageAdaptor::nameRMsg()
{
	QString name = targetRMsg()->objectName();
	if(name.isEmpty())
		name="?";
	return name;
}

QString RMessageAdaptor::pathRMsg()
{
	QString path = nameRMsg();
	RMessageAdaptor *next = parentRMsg();
	while(next)
	{
		path.prepend("/");
		path.prepend(next->nameRMsg());
		next = next->parentRMsg();
	}
	path.prepend("/");
	return path;
}

bool RMessageAdaptor::filterRMsg(RMessage *rmsg)
{
	QString to = rmsg->getString("r-to");
	
	if(to.isEmpty())
		return true;

	if(RPath::match(to, pathRMsg()))
		return true;
	return false;
}

void RMessageAdaptor::sendRMsg(RMessage *msg)
{
	//qLog(Debug)<<"sendRMsg "<<ObjectVariant::toShortString(msg->args());
	msg->_sender = this;
	msg->put("r-sender", pathRMsg());

	dispatchRMsg(msg);
}

RMessageAdaptor* RMessageAdaptor::parentRMsg()
{
	if(_inheritedMode)
		return getRMsg(parent());
	return getRMsg(parent()->parent());
}

QList<RMessageAdaptor*> RMessageAdaptor::childrenRMsg()
{
	QList<RMessageAdaptor*> list;
	if(_inheritedMode)
		list = qFindChildren<RMessageAdaptor*>(this);
	else
	{
		// in non-inherited mode, parent is target of all children
		Q_FOREACH(QObject *child, parent()->children())
		{
			if(child!=this)
			{
				RMessageAdaptor *childRmsg = getRMsg(child);
				if(childRmsg)
					list.append(childRmsg);
			}
		}
		// but each adaptor could have subadaptors also
/*		Q_FOREACH(QObject *child, children())
		{
			RMessageAdaptor *childRmsg = qobject_cast<RMessageAdaptor*>(child);
			if(childRmsg)
				list.append(childRmsg);
		}
*/
	}
	return list;
}

void RMessageAdaptor::targetsRMsg(QList<RMessageAdaptor*> *targets, RMessage *msg)
{
#ifdef RMSG_LOG
	qLog(Debug)<<"collect targets at "<<this<<" -> "<<targetRMsg();
#endif

	if(targets->contains(this))
	{
#ifdef RMSG_LOG
		qLog(Debug)<<"already";
#endif
		return;
	}

	targets->append(this);

	bool notifyChildren = msg->_flags & RMessage::NotifyChildren
		&& _flags & RMessage::NotifyChildren;
	
	if(notifyChildren)
	{
		//qLog(Debug)<<"adding children";	
		QList<RMessageAdaptor*> childs = childrenRMsg();
		//targets.append(childs);
		// append childs
		int n=0;
		Q_FOREACH(RMessageAdaptor *child, childs)
		{
			child->targetsRMsg(targets, msg);
			n++;
		}
	}

	bool notifyParents = msg->_flags & RMessage::NotifyParents &&
		_flags & RMessage::NotifyParents;
	if(notifyParents)
	{
		//qLog(Debug)<<"adding parent";	
		RMessageAdaptor *parent = parentRMsg();		
		if(parent)
		{
			parent->targetsRMsg(targets, msg);
		}else
		{
#ifdef RMSG_LOG
			qLog(Debug)<<"no parent";
#endif
		}
		//targets.append(parentRMsg());
	}

}

RMessageAdaptor* RMessageAdaptor::getRMsg(QObject *obj)
{
	if(!obj)
		return 0;
	RMessageAdaptor *rmsg = qobject_cast<RMessageAdaptor*>(obj);
	if(!rmsg)
		Q_FOREACH(QObject *child, obj->children())
		{
			rmsg = qobject_cast<RMessageAdaptor*>(child);
			if(rmsg)
				return rmsg;
		}
	return rmsg;
}







bool RPath::match(const QString &mask, const QString &path)
{
	if(mask.startsWith("//"))
		return path.endsWith(mask.mid(2));
	
	return path==mask;
}