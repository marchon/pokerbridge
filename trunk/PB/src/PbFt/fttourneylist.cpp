#include "stdafx.h"
#include "fttourneylist.h"
#include "pbtourney.h"

FTTourneyList::FTTourneyList(QWidget *w, QObject *parent) : FTList(w, parent)
{
}
	
void FTTourneyList::onListUpdated()
{
	FTList *list = qobject_cast<FTList*>(sender());

	Q_FOREACH(PBTourneyInfo* ti, _info)
	{
		ti->deleteLater();
	}
	_info.clear();
	for(int i=0;i<list->rowCount();i++)
	{
		PBTourneyInfo* ti = new PBTourneyInfo(this);
		bool parsedOk = parse(list, i, ti);

		if(parsedOk)
			_info.append(ti);
	}
	emit tourneysUpdated();
}

bool FTTourneyList::parse(FTList *list, int row, PBTourneyInfo *ti)
{
	bool parsedOk = true;

	int col = list->indexOfColumn("Buy-In");

	if(col>=0)
		if(!parseBuyIn(list->value(row, col), ti))
			parsedOk = false;

	col = list->indexOfColumn("Status");
	if(col>=0)
	{
		QString s = list->value(row, col);
		if(s=="Registering")
			ti->setTourneyStatus(PBTourneyInfo::Registering);
		else if(s=="Running")
			ti->setTourneyStatus(PBTourneyInfo::Running);
	}
	return parsedOk;
}

bool FTTourneyList::parseBuyIn(QString sBuyin, PBTourneyInfo *ti)
{
	ti->setBuyIn(10);
	ti->setRake(1);
	return true;
}

void FTTourneyList::openTourneyLobby(FTListClicker *filter)
{
	click(filter);
}