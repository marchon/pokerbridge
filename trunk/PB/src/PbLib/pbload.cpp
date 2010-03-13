#include "StdAfx.h"
#include "pbapi.h"
#include "pbhook.h"
#include <stdlib.h>
#include <time.h>

void printTime()
{
 time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "%s", asctime (timeinfo) );
}

int pbStart(LPCSTR processName, LPCSTR dirName, LPCSTR dllPath)
{
	std::cout<<"injecting "<<dllPath<<std::endl;

	WCHAR wDllPath[_MAX_PATH];
	mbstowcs(wDllPath,dllPath,strlen(dllPath)+1);
	bool cycle=false;
	do{
		ULONG pid = RtlGetProcessID(processName);
		
		NTSTATUS res;

		if(0L==pid)
		{
			printTime();
			std::cout << "process "<<processName<<" not found, try launching from "<<dirName<<std::endl;
			WCHAR path[_MAX_PATH];
			memset(path,0,sizeof(path));
			mbstowcs(path,dirName,strlen(dirName));
			mbstowcs(path+wcslen(path),"\\",1);
			mbstowcs(path+wcslen(path),processName,strlen(processName)+2);
			*(path+wcslen(path))=0;
			res = RhCreateAndInject(path,NULL,CREATE_SUSPENDED,EASYHOOK_INJECT_DEFAULT,wDllPath,NULL,NULL,0,&pid);
			if(res==0L)
			{
				std::cout<<"created process "<<processName<<", pid="<<pid<<std::endl;
				cycle=true;
			}
		}else
		{
			res = RhInjectLibrary(pid, 0L, EASYHOOK_INJECT_DEFAULT,  wDllPath, NULL, NULL,0L);
			return 0;
		}

		if(res!=0L)
		{
			std::wcout << "error: "<<RtlGetLastErrorString();
//			return -2;
		}

		if(!cycle)
			return -2;
		do{
			Sleep(3000);
			pid = RtlGetProcessID(processName);
			if(pid==0)
			{
				printTime();
				std::cout<<"process "<<processName<<" has died. relaunching in 3 seconds";
				Sleep(3000);
				break;
			}
		}while(1);
	}while(1);
	return 0;
}



