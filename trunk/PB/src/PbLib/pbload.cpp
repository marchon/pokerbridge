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

WCHAR path[_MAX_PATH];
WCHAR* pbMakePath(LPCSTR dirName, LPCSTR processName)
{
	memset(path,0,sizeof(path));
	mbstowcs(path,dirName,strlen(dirName));
	mbstowcs(path+wcslen(path),"\\",1);
	mbstowcs(path+wcslen(path),processName,strlen(processName)+2);
	*(path+wcslen(path))=0;
	return path;
}

int pbStart(LPCSTR processName, LPCSTR dirName, LPCSTR dllPath, int maxCount)
{
	std::cout<<"injecting "<<dllPath<<std::endl;

	WCHAR wDllPath[_MAX_PATH];
	mbstowcs(wDllPath,dllPath,strlen(dllPath)+1);
	int count = 0;

	if(0==maxCount)
	{
		ULONG pid = RtlGetProcessID(processName, &count);
		if(pid==0)
		{
			std::cout<<"no such process "<<processName;
			return -1;
		}
		NTSTATUS res = RhInjectLibrary(pid, 0L, EASYHOOK_INJECT_DEFAULT,  wDllPath, NULL, NULL,0L);	
		if(res!=0L)
		{
			std::wcout << "error: "<<RtlGetLastErrorString();
			return -2;
		}
	}

	do{
		ULONG pid=0;
		NTSTATUS res = RhCreateAndInject(pbMakePath(dirName,processName),NULL,CREATE_SUSPENDED,EASYHOOK_INJECT_DEFAULT,wDllPath,NULL,NULL,0,&pid);
		if(res==0L)
		{
			std::cout<<"created process "<<processName<<", pid="<<pid<<std::endl;
		}
		else
		{
			std::wcout<<"error: "<<RtlGetLastErrorString();
			return -2;
		}
		do{
			Sleep(10000);
			pid = RtlGetProcessID(processName, &count);
			if(count<maxCount)
			{
				printTime();
				std::cout<<"process "<<processName<<" count is "<<count<<" < "<<maxCount<<". creating more..."<<std::endl;
				break;
			}
		}while(1);
	}while(1);
	return 0;
}



