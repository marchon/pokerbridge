#include "StdAfx.h"
#include "rpcconnection.h"
#include "json.h"
#include "rpcadaptor.h"
#include "rpclistener.h"
#include "rpcchannel.h"

RpcChannel::RpcChannel(QTcpSocket *socket, RpcConnection *conn)
	: QObject(conn)
{
	_socket = socket;
	_remoteHost =  _socket->peerAddress().toString();
	_remotePort = _socket->peerPort();
	_localHost = _socket->localAddress().toString();
	_localPort = _socket->localPort();
	init();
}

RpcChannel::RpcChannel(RpcConnection *conn) : QObject(conn)
{
	_socket = 0;
	_remoteHost = "";
	_remotePort = -1;
}

RpcChannel::~RpcChannel()
{

}

QString RpcChannel::remoteHost()
{
	return QString().append(_remoteHost).append(":%1").arg(_remotePort);
}

QString RpcChannel::localHost()
{
	return QString().append(_localHost).append(":%1").arg(_localPort);
}

RpcConnection *RpcChannel::connection()
{
	return static_cast<RpcConnection*>(parent());
}


void RpcChannel::init()
{
	_socket->setParent(this);
	
	_reader = new JsonReader(this);
	_reader->setInput(_socket);

	connect(_socket, SIGNAL(disconnected()), SLOT(socketDisconnected()));
	connect(_socket, SIGNAL(readyRead()), SLOT(readyRead()));
	connect(_socket, SIGNAL(connected()), SLOT(connected()));

	connect(_reader, SIGNAL(parsed(QVariantMap)),this, SLOT(newMessage(QVariantMap)));

}


void RpcChannel::socketDisconnected()
{
	connection()->chanelDisconnected(this);
}


bool RpcChannel::connectToServer(QString url, uint port)
{
	qLog(Debug)<<"connect rpc to "<<url<<":"<<port;
	Q_ASSERT(_socket==0);
	_socket = new QTcpSocket(this);
	_socket->connectToHost(url, port);
	init();

	if(!_socket->waitForConnected())
	{
		qLog(Debug)<<"timeout while connecting to server "<<url<<":"<<port;
		return false;
	}
	return true;
}

void RpcChannel::connected()
{
	_localHost = _socket->localAddress().toString();
	_localPort = _socket->localPort();
	_remoteHost = _socket->peerAddress().toString();
	_remotePort = _socket->peerPort();
	qLog(Debug) << "socket connected ("<<_localHost<<"("<<_localPort<<")->"<<_remoteHost<<"("<<_remotePort<<")";

	connection()->channelConnected(this);
}

void RpcChannel::readyRead()
{
	if(_socket->bytesAvailable()>0)
		_reader->parse();
}

bool getMethod(const QVariantMap &msg, RpcUrl &target, QString &method, RpcUrl &sender)
{
	method = msg.value("method").toString();
	target.parse(msg.value("target").toString());
	sender.parse(msg.value("sender").toString());
	return true;
}

void RpcChannel::newMessage(QVariantMap msg)
{
	RpcUrl target;
	RpcUrl sender;
	QString method;
	QVariantList args;

	getMethod(msg, target, method, sender );
	args = msg.value("params").toList();

	bool isCall = !target.isEmpty();
	if(isCall)
	{
		if(target.host==localHost())
			connection()->channelCall(target, method.toLatin1(), args, sender);
		else
			qLog(Debug)<<"call to host "<<target.host<<"!=localhost="<<localHost();
	}
	else
		connection()->channelSignal(method.toLatin1(), args, sender);
}

void putMethod(QVariantMap &msg, const RpcUrl &target, const QString &method, const RpcUrl &senderUrl)
{
	msg["sender"]=senderUrl.toString();
	msg["target"]=target.toString();
	msg["method"]=method;
}

bool RpcChannel::remoteCall(const RpcUrl &path, const QByteArray &method, const QList<QVariant> &args, const RpcUrl &senderUrl)
{
	QVariantMap msg;
	msg["params"]=args;
	putMethod(msg,path,method,senderUrl);
	sendMessage(msg);

	qLog(Debug)<<"SendCall: "<<method<<" to "<<path.toString()<<" from "<<senderUrl.toString();

	return true;
}

bool RpcChannel::remoteSignal(const QByteArray &signal, const QList<QVariant> &args, const RpcUrl &senderUrl)
{
	QVariantMap msg;
	msg["params"]=args;
	RpcUrl target;
	putMethod(msg,target,signal,senderUrl);
	sendMessage(msg);
	
	qLog(Debug)<<"SendSignal: "<<signal<<" from "<<senderUrl.toString();

	return true;
}

void RpcChannel::sendMessage(QVariantMap msg)
{
	QString data = VariantToJson::toJson(msg);
	qLog(Debug)<<"write: "<<data;
	_socket->write(data.toAscii());
	//qLog(Debug)<<"RpcChannel::sendMessage "<<msg<<endl<<"data:"<<data;
}

