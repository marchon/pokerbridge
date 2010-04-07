#ifndef RMESSAGE_H
#define RMESSAGE_H

class RMessageAdaptor;
class RMessageQueue;


class RMSG_EXPORT RMessage 
{
	Q_GADGET
	Q_FLAGS(RMessageFlags Flags);
public:
	enum RMessageFlags
	{
		NotifyChildren	= 0x0001,
		NotifyParents	= 0x0002,
		Done			= 0x0004,
		SingleQueue		= 0x0008
	};
public:
	RMessage(const char *type = "");
	~RMessage();
public:
	QByteArray type();
	void setType(const QByteArray &type);

	QObject *sender();
	RMessageQueue *queue();
	void setQueue(RMessageQueue *queue);

	RMessage &put(const char *attr, const QVariant &value);
	RMessage &put(QObject *obj);
	
	int getInt(const char *attr, int def=0);
	QString getString(const char *attr, const QString &def=QString());
	QVariant get(const char *attr, const QVariant &def=QVariant());
	void get(QObject *obj);

	void copyFrom(RMessage *other);

	void replyTo(RMessage *other);

	Q_DECLARE_FLAGS(Flags, RMessageFlags);

	void send(QObject *target);
	
	void setVisited(RMessageAdaptor *a);
	bool isVisited(RMessageAdaptor *a);
	bool isDone(){ return _flags & Done; }
	void setDone(){ _flags |= Done; }
	
	RMessage& setOpt(RMessageFlags option, bool enable=true){ enable? _flags|=option:_flags&=~option; return *this;}

public:
	void fromMap(const QVariantMap &map);
	void toMap(QVariantMap &map);
	const QVariantMap &args() const { return _args; }
private:
	Flags _flags;
	QObject *_sender;
	RMessageQueue *_queue;
	QSet<RMessageAdaptor*> _visited;
	QVariantMap _args;
	friend class RMessageAdaptor;
};

Q_DECLARE_METATYPE(RMessage);
#endif // RMESSAGE_H
