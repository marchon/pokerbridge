#include "StdAfx.h"
#include "rpcconnection.h"
#include "json.h"
#include "rpcadaptor.h"
#include "rpclistener.h"
#include "RpcChannel.h"

RpcChannel::RpcChannel(QTcpSocket *socket, RpcConnection *conn)
	: QObject(conn)
{
	_socket = socket;
	_remoteHost =  _socket->peerAddress().toString();
	_remotePort = _socket->peerPort();
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

QString RpcChannel::remoteUrl()
{
	return QString().append(_remoteHost).append(":%1").arg(_remotePort);
}

RpcConnection *RpcChannel::connection()
{
	return static_cast<RpcConnection*>(parent());
	/*if(0==_conn)
	{
		RpcServer *serv = qobject_cast<RpcServer*>(parent());
		if(0!=serv && 0!=serv->registry())
			_reg = serv->registry();
		if(0==_reg)
			_reg = new RpcRegistry(this);
	}
	return _reg;
	*/
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
	connection()->channelDisconnected(this);
}


bool RpcChannel::connectToServer(QString url, uint port)
{
	Q_ASSERT(_socket==0);
	_socket = new QTcpSocket(this);
	_socket->connectToHost(url, port);
	init();
	if(!_socket->waitForConnected())
	{
		qLog(Debug)<<"timeout while connecting to server "<<url<<":"<<port;
		return false;
	}
	_remoteHost = url;
	_remotePort = port;
	return true;
}

void RpcChannel::connected()
{
	qLog(Debug) << "socket connected";
}

void RpcChannel::readyRead()
{
	if(_socket->bytesAvailable()>0)
		_reader->parse();
}

void RpcChannel::newMessage(QVariantMap msg)
{
	QString targetPath = msg.value("target").toString();
	if(!targetPath.isEmpty())
	{
		QObject *target = connection()->target(targetPath);
		if(0!=target)
		{
			RpcAdaptor *ra = RpcAdaptor::get(target);
			if(0!=ra)
			{
				ra->invokeMessage(msg, this);
			}
		}else{
			qWarning()<<"target "<<targetPath<<" not found, message="<<msg;
		}
	}else{
		bool dispatched = false;
		Q_FOREACH(QObject*obj, connection()->published().values())
		{
			RpcAdaptor *ra = RpcAdaptor::get(obj);
			if(0!=ra)
			{
				if(ra->signalMessage(msg, this))
					dispatched=true;
			}
		}
		if(!dispatched)
		{
			qLog(Debug)<<"message "<<msg<<" had no listeners";
		}
	}
	//emit incomingMessage(msg);
}

void RpcChannel::sendMessage(QVariantMap msg)
{
	QString data = VariantToJson::toJson(msg);
	_socket->write(data.toAscii());
	//qLog(Debug)<<"RpcChannel::sendMessage "<<msg<<endl<<"data:"<<data;
}

void RpcChannel::registerObject(QObject *obj)
{
	RpcAdaptor *adaptor = RpcAdaptor::get(obj);
	Q_ASSERT(adaptor);

	connect(adaptor, SIGNAL(sendMessage(QVariantMap)), this, SLOT(sendMessage(QVariantMap)));
}