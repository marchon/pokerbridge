#pragma once
class PBSiteGameInfo;
class PBGameInfos : public QObject
{
	Q_OBJECT;
public:
	PBGameInfos(QObject *parent);
	PBSiteGameInfo *gameInfo(QString gameId);


public:
	void dump();
public slots:
	void onGameInfo(RMessage *msg);
	int priGameInfo(RMessage *msg);

	
protected:
	QTime _requestTime;
};