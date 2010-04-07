#include "StdAfx.h"

#include "ftmainthread.h"
#include "mdump.h"
#include "fthooks.h"

// qt stuff will work only in Qt thread...
FTMainThread mainThread;

void PB_EXPORT APIENTRY NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* pInfo)
{

	installSysHooks();
	//Sleep(2000);
	
	QStringHooks::install();
	QWidgetHooks::install();
	QAbstractItemViewHooks::install();
	//installSsl();



	RhWakeUpProcess();
	//Sleep(5000); // QT should get  initialized

	


	//qLog(Info)<<"starting main thread";
	
	mainThread.start();
	
	// here we wait until mainThread terminated
	mainThread.wait();
	
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

