#pragma once


class PBGameInfos;
class PBSiteGameInfo;

class PBObserver : public QObject
{
	Q_OBJECT
public:
	PBObserver(PBGameInfos *games, QObject *parent);

	virtual void timerEvent(QTimerEvent *e);

	void openTable(RMessage *msg, PBSiteGameInfo *gi);
	void closeTourney(RMessage *msg, PBSiteGameInfo *gi);

public slots:
	void onGameInfo(RMessage *msg);
	
protected:
	QPointer<PBGameInfos> _games;
};
