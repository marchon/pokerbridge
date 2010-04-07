#include "StdAfx.h"
#include "rtcpqueuelsnr.h"
#include "rtcpmessagequeue.h"

RTcpQueueListener::RTcpQueueListener(QObject *parent, bool inherited)
	: RMessageQueue(parent, inherited)
{

}

RTcpQueueListener::~RTcpQueueListener()
{

}

bool RTcpQueueListener::listen(uint port)
{
	_server = new QTcpServer(this);
	connect(_server, SIGNAL(newConnection()), SLOT(newConnection()));
	bool res = _server->listen(QHostAddress::Any, port);
	
	qLog(Debug)<<"RTcpQueueListener listens at TCP port "<<port;
	return res;
}

void RTcpQueueListener::newConnection()
{
	QTcpSocket *socket = _server->nextPendingConnection();
	qLog(Debug) << "RTcpQueueListener::newConnection from "<<socket->peerAddress()<<":"<<socket->peerPort();
	RTcpMessageQueue *queue = new RTcpMessageQueue(this, false);
	queue->bind(socket);
	connect(queue, SIGNAL(opened()), SLOT(_queueOpened()), Qt::DirectConnection);
}

void RTcpQueueListener::_queueOpened()
{
	RTcpMessageQueue *queue = qobject_cast<RTcpMessageQueue*>(sender());
	emit queueOpened(queue);
}
