#pragma once
class PBServer;

class PBLobbyDriver;

class PBLobbyDriverProfile : public QObject
{
	Q_OBJECT;
public:
	PBLobbyDriverProfile(QObject *parent);

	void init(PBLobbyDriver *ld);
protected:
	QString _grabberProfile;
	QString _grabberMode;
};

class PBLobbyDriver :public QObject
{
	Q_OBJECT;
public:
	PBLobbyDriver(QObject *parent);

	void setDriverName(QString name, int index);
	int driverIndex();
	static PBLobbyDriver *fromMessage(RMessage *msg);
	void sendConfig();
	QString grabberMode(){return _grabberMode;}
	PBServer *server();
	void onGameInfo(RMessage *msg);
	virtual void timerEvent(QTimerEvent *e);
	bool isTimedOut();
	bool canHandleMoreTables();
	int tablesObserved(){ return _tablesObserved; }
	int tablesMax(){ return _tablesMax; }
public slots:
	void onDisconnected();
protected:
	long _pid;
	int _driverIndex;
	int _tablesObserved;
	int _tablesMax;
	QString _grabberMode;
	QString _grabberProfile;
	QTime _lastPingTime;
	friend class PBLobbyDriverProfile;
};



