#include "StdAfx.h"

#include "ftmainthread.h"
#include "mdump.h"
#include "fthooks.h"

// qt stuff will work only in Qt thread...
FTMainThread mainThread;

void PB_EXPORT APIENTRY NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* pInfo)
{
	installSysHooks();
	Sleep(2000);

	QStringHooks::install();
	QWidgetHooks::install();
	QAbstractItemViewHooks::install();
	//installSsl();

	RhWakeUpProcess();
	Sleep(5000); // QT should get initialized


	QPBLog::install();
	static char logName[_MAX_PATH];
	static char dumpName[_MAX_PATH];
	sprintf(logName,"pbft-%d.log",GetCurrentProcessId());
	sprintf(dumpName,"pbft-%d",GetCurrentProcessId());
	QPBLog::logToFile(logName);
	MiniDumper::Install(dumpName);

	qLog(Info)<<"starting main thread";
	
	mainThread.start();
	
	// here we wait until mainThread terminated
	mainThread.wait();
	qLog(Debug)<<"exiting injection point thread";
	
	MiniDumper::Uninstall();
	QPBLog::uninstall();
	//FreeLibraryAndExitThread(FTMainThread::hInjectionLib,0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		FTMainThread::hInjectionLib = hModule;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

