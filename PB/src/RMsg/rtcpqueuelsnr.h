#ifndef RTCPQUEUELSNR_H
#define RTCPQUEUELSNR_H

#include "rmessagequeue.h"
class QTcpServer;
class RMSG_EXPORT RTcpQueueListener : public RMessageQueue
{
	Q_OBJECT

public:
	RTcpQueueListener(QObject *parent=0, bool inherited=false);
	~RTcpQueueListener();

	bool listen(uint port);
protected slots:
	void newConnection();
	void _queueOpened();
signals:
	void queueOpened(RMessageQueue *q);
private:
	QTcpServer *_server;
};

#endif // RTCPQUEUELSNR_H
