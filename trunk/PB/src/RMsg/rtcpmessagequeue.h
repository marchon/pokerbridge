#ifndef RTCPMESSAGEQUEUE_H
#define RTCPMESSAGEQUEUE_H

#include "rmessagequeue.h"
class JsonReader;
class QTcpSocket;
class RMSG_EXPORT RTcpMessageQueue : public RMessageQueue
{
	Q_OBJECT
public:
	RTcpMessageQueue(QObject *parent=0, bool inherited=false);
	~RTcpMessageQueue();

public:
	void sendMessage(QVariantMap msg);

	void connectToHost(QString url, uint port);
	void bind(QTcpSocket *socket);
	void waitConnected();
	virtual void putRMsg(RMessage *rmsg);

public slots:
	void readyRead();
	void connected();
	void disconnected();
	void messageReceived(QVariantMap msg);
protected:
	void init();

private:
	QTcpSocket *_socket;
	JsonReader *_reader;

};

#endif // RTCPMESSAGEQUEUE_H
