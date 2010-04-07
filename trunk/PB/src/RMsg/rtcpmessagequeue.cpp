#include "StdAfx.h"
#include "rtcpmessagequeue.h"
#include "json.h"

#define QMSG_LOG

RTcpMessageQueue::RTcpMessageQueue(QObject *parent, bool inherited)
	: RMessageQueue(parent, inherited), _socket(0)
{

}

RTcpMessageQueue::~RTcpMessageQueue()
{

}

void RTcpMessageQueue::connectToHost(QString url, uint port)
{
	_socket = new QTcpSocket(this);
	init();
	_socket->connectToHost(url, port);
}

void RTcpMessageQueue::waitConnected()
{
	_socket->waitForConnected();
}

void RTcpMessageQueue::bind(QTcpSocket *socket)
{
	_socket = socket;
	init();
}

void RTcpMessageQueue::init()
{
	_socket->setParent(this);
	
	_reader = new JsonReader(this);
	_reader->setInput(_socket);

	connect(_socket, SIGNAL(disconnected()), SLOT(disconnected()));
	connect(_socket, SIGNAL(readyRead()), SLOT(readyRead()));
	connect(_socket, SIGNAL(connected()), SLOT(connected()));

	connect(_reader, SIGNAL(parsed(QVariantMap)),this, SLOT(messageReceived(QVariantMap)));
}


void RTcpMessageQueue::connected()
{
	qLog(Debug) << "socket connected ("<<_socket->localAddress()<<"("<<_socket->localPort()<<")->"<<_socket->peerAddress()<<"("<<_socket->peerPort()<<")";
	putOpenRMsg();

}
void RTcpMessageQueue::disconnected()
{
	qLog(Debug) << "socket disconnected ("<<_socket->localAddress()<<"("<<_socket->localPort()<<")->"<<_socket->peerAddress()<<"("<<_socket->peerPort()<<")";
	emit closed();
}

void RTcpMessageQueue::messageReceived(QVariantMap msg)
{
	RMessage rmsg;
	rmsg.fromMap(msg);
//	qLog(Debug)<<"\nREAD: "<<ObjectVariant::toShortString(msg);
#ifdef QMSG_LOG	
	qLog(Debug)<<"\nREAD: "<<rmsg.type()<<" "<<_socket->peerAddress().toString()+QString(":%1").arg(_socket->peerPort())<<"->"<<_socket->localAddress().toString()+QString(":%1").arg(_socket->localPort());
	qLog(Debug)<<ObjectVariant::toShortString(msg);
#endif
	onNewRMsg(&rmsg);
}

void RTcpMessageQueue::putRMsg(RMessage *rmsg)
{
	//qLog(Debug)<<"tcpmq putrm "<<this;
	if(!_socket)
	{
		qLog(Debug)<<"RTcpMessageQueue("<<objectName()<<")::put : NO SOCKET "<<rmsg->args();
		return;
	}
	rmsg->put("r-from-host",_socket->localAddress().toString()+QString(":%1").arg(_socket->localPort()));
	QVariantMap map;
	rmsg->toMap(map);
	QString data = VariantToJson::toJson(map);
	//qLog(Debug)<<"\nWRITE: "<<ObjectVariant::toShortString(map);
#ifdef QMSG_LOG	
	qLog(Debug)<<"\nWRITE: "<<rmsg->type()<<" "<<rmsg->getString("r-from-host")<<"->"<<_socket->peerAddress().toString()+QString(":%1").arg(_socket->peerPort());
	qLog(Debug)<<ObjectVariant::toShortString(map);
#endif

	_socket->write(data.toAscii());
	_socket->flush();
}

void RTcpMessageQueue::readyRead()
{
	if(_socket->bytesAvailable()>0)
		_reader->parse();
}
