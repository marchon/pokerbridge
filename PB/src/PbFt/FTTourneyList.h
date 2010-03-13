#pragma once
#include "ftlist.h"


class PBTourneyInfo;
class FTTourneyList : public FTList
{
	Q_OBJECT;
public:
	FTTourneyList(QWidget *w, QObject *parent=0);
	
	bool parseBuyIn(QString sBuyin, PBTourneyInfo *ti);
	bool parse(FTList *list, int row, PBTourneyInfo *ti);
	void openTourneyLobby(FTListClicker *filter);
public slots:
	void onListUpdated();
signals:
	void tourneysUpdated();
protected:
	QList<PBTourneyInfo*> _info;
};