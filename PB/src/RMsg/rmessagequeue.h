#ifndef RMESSAGEQUEUE_H
#define RMESSAGEQUEUE_H

#include <rmessageadaptor.h>

class RMSG_EXPORT RMessageQueue : public RMessageAdaptor
{
	Q_OBJECT

public:
	RMessageQueue(QObject *parent=0, bool inherited=false);
	~RMessageQueue();

	virtual void handleRMsg(RMessage *rmsg);
	virtual void putRMsg(RMessage *rmsg);
	virtual void onNewRMsg(RMessage *rmsg);
	void putOpenRMsg();
signals:
	void opened();
	void closed();
private:
	QList<RMessage> _queue;
};

#endif // RMESSAGEQUEUE_H
