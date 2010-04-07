#include "stdafx.h"
#include "fttasks.h"
#include "fttourneyopener.h"

FTTasks::FTTasks(QObject *parent) : QObject(parent)
{
	new RMessageAdaptor(this);
}

void FTTasks::stop()
{
	QList<FTTask*> tasks = qFindChildren<FTTask*>(this);
	Q_FOREACH(FTTask*task, tasks)
	{
		qLog(Info)<<"fttasks stops "<<task;
		task->stop();
	}
}

FTTask *FTTasks::tourneyOpener()
{
	FTTourneyOpener *tsk= qFindChild<FTTourneyOpener*>(this);
	if(tsk)
		return tsk;
	return newTourneyOpener();
}

FTTask *FTTasks::newTourneyOpener()
{
	FTTourneyOpener *tsk = new FTTourneyOpener(this);
	return tsk;
}


