#include "stdafx.h"
#include "pbhook.h"

#include "fthooks.h"
#include "ftpanel.h"
#include "fthandhistory.h"
#include "ftlobby.h"
#include "ftstopwatch.h"
#include "mdump.h"
#include "ftmainthread.h"

HMODULE FTMainThread::hInjectionLib;
QWaitCondition FTMainThread::threadExited;

void FTMainThread::run()
{
	qLog(Info) << "lib=("<<hInjectionLib<<") thread=" << QThread::currentThread();

	FTLobbyHooks::installHooks();

	qLog(Debug) << "waiting for lobby...";

	QPBLog::addHandler(FTPanel::msgHandler);

	static QMutex waitMutex;
	waitMutex.lock();
	FTLobby::lobbyCreated.wait(&waitMutex);
	waitMutex.unlock();



	QWidgetHooks::installFilter();	// do it after lobby interception

	FTStopWatch stopWatch; 

	QTimer timer;
	timer.setInterval(1000);
	QObject::connect(&timer, SIGNAL(timeout()), &stopWatch, SLOT(onTimer()));
	timer.start();

	
	int exitValue = QThread::exec();

	qLog(Debug)<<"stopping stapwatch";
	timer.stop();

	QPBLog::removeHandler(FTPanel::msgHandler);

	FTLobbyHooks::uninstallHooks();

	QWidgetHooks::uninstall();
	
	
	LhUninstallAllHooks();  
	LhWaitForPendingRemovals();
	qLog(Info) << "PTFB.DLL("<<hInjectionLib<<") terminating("<<exitValue<<")";

	FTPanel::destroyInstance();

	//FTLobby::instance();
	qLog(Info) << "Main thread exit";
}