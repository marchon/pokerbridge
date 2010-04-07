#ifndef RMESSAGEADAPTOR_H
#define RMESSAGEADAPTOR_H

#include "rmessage.h"

class RPath 
{
public:
	static bool match(const QString &mask, const QString &path);
};

class RMessageQueue;

class RMSG_EXPORT RMessageAdaptor : public QObject
{
	Q_OBJECT

public:
	RMessageAdaptor(QObject *parent = 0, bool inheritedMode=false);
	~RMessageAdaptor();

	virtual void dispatchRMsg(RMessage *msg);
	virtual void onRMsg(RMessage *msg);
	
	virtual void sendRMsg(RMessage *msg);

	static RMessageAdaptor *getRMsg(QObject *obj);
	virtual bool filterRMsg(RMessage *msg);

	virtual void targetsRMsg(QList<RMessageAdaptor*> *targets, RMessage *msg);
	
	int testRMsg(RMessage *msg); // return priority

	QString pathRMsg();
	QString nameRMsg();
	RMessageAdaptor* parentRMsg();
	QList<RMessageAdaptor*> childrenRMsg();
	RMessageAdaptor &setOpt(RMessage::RMessageFlags option, bool enable=true){ enable? _flags|=option:_flags&=~option; return *this;}
	QObject *targetRMsg();
protected:
	virtual void handleRMsg(RMessage *msg);
signals:
	void rmsg(RMessage *msg);
protected:
	bool _inheritedMode;
	RMessage::Flags _flags;
};

#endif // RMESSAGEADAPTOR_H
