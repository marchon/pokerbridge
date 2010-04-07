#include "StdAfx.h"
#include "rmessagequeue.h"

static int queueNo = 1;
RMessageQueue::RMessageQueue(QObject *parent, bool inherited)
	: RMessageAdaptor(parent, inherited)
{
	if(!inherited && parent)
		setObjectName(parent->objectName());
	else
	{
	}
	//setOpt(RMessage::NotifyParents, false);
	qLog(Debug)<<"Queue "<<this<<" created";
}

RMessageQueue::~RMessageQueue()
{

}

void RMessageQueue::handleRMsg(RMessage *msg)
{
	//Q_ASSERT(!objectName().isEmpty());

//	qLog(Debug)<<"msgq handle "<<this;
	RMessageAdaptor::handleRMsg(msg);
	if(!msg->isDone())
	{
		if(msg->queue() && msg->queue()!=this)
			;//qLog(Debug)<<"message "<<msg->type()<<" not sent back to queue "<<objectName();
		else
		{
			msg->put("r-queue-id", objectName());
			putRMsg(msg);
		}
	}
}

void RMessageQueue::onNewRMsg(RMessage *msg)
{
	if(msg->type()=="queue-open")
	{
		setObjectName(msg->getString("r-queue-id"));
		qLog(Debug)<<"queue opened "<<objectName();
		emit opened();
	}else
	{
		msg->setQueue(this);
		msg->setVisited(this);	// this will prevent the message from being dispatched again into the queue
		msg->put("r-queue-id", objectName());
		dispatchRMsg(msg);
	}
}

void RMessageQueue::putRMsg(RMessage *next)
{
	_queue.append(*next);
}

void RMessageQueue::putOpenRMsg()
{
	RMessage msg("queue-open");
	msg.put("r-queue-id", objectName());
	putRMsg(&msg);
}