#include "stdafx.h"
#include "ftstopwatch.h"

FTStopWatch::FTStopWatch(QObject *parent ) : QObject(parent)
{
	stopWatchPath =  "pb-stop.sig"; 
	if(QFile::exists(stopWatchPath))
		QFile::remove(stopWatchPath); 
}

void FTStopWatch::onTimer()
{
	if(QFile::exists(stopWatchPath))
	{
		qLog(Info) << "PTFB.DLL stop signal";
		QThread::currentThread()->exit(1);
	}  
}
