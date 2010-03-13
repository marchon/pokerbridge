#include "StdAfx.h"
#include "pbhook.h"
#include "qpblog.h"

BOOL EasyHook(LPCSTR module, LPSTR procName, LPVOID hookProc, HOOK_TRACE_INFO *hHook)
{
	HMODULE hModule = GetModuleHandleA(module);
	if(NULL==hModule)
	{
		qLog(Error) << "No module found " << module;
		return FALSE;
	}
	
	LPVOID proc = GetProcAddress(hModule, procName);
	if(NULL==proc)
	{
		qLog(Error) << "No proc found " << procName;
		return FALSE;
	}
	
	ULONG ACLEntries[1]={0};
	memset(hHook,0,sizeof(HOOK_TRACE_INFO));

	if(0!=LhInstallHook(proc, hookProc, NULL, hHook))
	{
		qLog(Error) << "LhInstallHook failed %s" << RtlGetLastErrorString();
		return FALSE;
	}
	if(0!=LhSetExclusiveACL(ACLEntries, 1, hHook))
	{
		qLog(Error) << "SetExclusiveACL failed";
		return FALSE;
	}

	qLog(Error) << "Function " << module << "!" << procName << " patched";
	return TRUE;
}
