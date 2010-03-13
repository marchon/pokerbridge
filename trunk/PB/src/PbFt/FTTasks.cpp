#include "stdafx.h"
#include "fttasks.h"
#include "ftregistertourneys.h"

FTTasks::FTTasks(QObject *parent) : QObject(parent)
{

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

FTTask *FTTasks::tableOpener()
{
	FTRegisterTourneys *rt = qFindChild<FTRegisterTourneys*>(this);
	if(!rt)
		rt= new FTRegisterTourneys(this);
	return rt;
}
