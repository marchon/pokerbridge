#include "stdafx.h"
#ifdef __cplusplus
extern "C" ULONG RtlGetProcessID(LPCSTR szProcessNameQuery);
#endif

ULONG RtlGetProcessID(LPCSTR szProcessNameQuery)
{
 DWORD ProcessesIDs[1024], cbNeeded, cProcesses; 
 unsigned int i;
 CHAR szProcessName[1024] = "Unknown";

 
 //if Enumprocess returns zero (fails) then quit the program.
 if ( !EnumProcesses( ProcessesIDs, sizeof(ProcessesIDs), &cbNeeded ) )
 return 0; 
  
 // Calculate how many process identifiers were returned.
 cProcesses = cbNeeded / sizeof(DWORD);
  ULONG pid = 0;
 // This for loop will be enumerating each process.
 for ( i = 0; i < cProcesses && pid==0; i++ )
 {
 // Get a handle to the process. The process to which the handle will be returned //will depend on the variable i.
     HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessesIDs[i] );
  
     // Get the process name.
     if (NULL != hProcess )
         {
         GetModuleBaseNameA( hProcess, NULL, (LPSTR)szProcessName, sizeof(szProcessName)/sizeof(CHAR) );
         }
  
   
 

	if(stricmp(szProcessName, szProcessNameQuery)==0)
	{
			pid = GetProcessId(hProcess);
	}
	    //Every handel is to be closed after its use is over.
     CloseHandle( hProcess );
     //End of for loop.
 }
 return pid;
}
