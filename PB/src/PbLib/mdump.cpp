
#include "stdafx.h"
#include "tchar.h"
#include "mdump.h"

LPCSTR MiniDumper::m_szAppName = 0;
LPTOP_LEVEL_EXCEPTION_FILTER MiniDumper::m_oldHandler = 0;

void MiniDumper::Install( LPCSTR szAppName )
{
	// if this assert fires then you have two instances of MiniDumper
	// which is not allowed
	//assert( m_szAppName==NULL );

	m_szAppName = szAppName ? strdup(szAppName) : "Application";

	m_oldHandler = ::SetUnhandledExceptionFilter( TopLevelFilter );
}

void MiniDumper::Uninstall()
{
	::SetUnhandledExceptionFilter(m_oldHandler);
}

void LogException(struct _EXCEPTION_POINTERS *pExceptionInfo )
{
	qLog(Debug)<<"**** EXCEPTION **** at "<<pExceptionInfo->ExceptionRecord->ExceptionAddress;
}

LONG MiniDumper::TopLevelFilter( struct _EXCEPTION_POINTERS *pExceptionInfo )
{
	LogException(pExceptionInfo);

	LONG retval = EXCEPTION_CONTINUE_SEARCH;
	HWND hParent = NULL;						// find a better value for your app

	// firstly see if dbghelp.dll is around and has the function we need
	// look next to the EXE first, as the one in System32 might be old 
	// (e.g. Windows 2000)
	HMODULE hDll = NULL;
	char szDbgHelpPath[_MAX_PATH];

	if (GetModuleFileNameA( NULL, szDbgHelpPath, _MAX_PATH ))
	{
		char *pSlash = _tcsrchr( szDbgHelpPath, '\\' );
		if (pSlash)
		{
			_tcscpy( pSlash+1, "DBGHELP.DLL" );
			hDll = ::LoadLibraryA( szDbgHelpPath );
		}
	}

	if (hDll==NULL)
	{
		// load any version we can
		hDll = ::LoadLibraryA( "DBGHELP.DLL" );
	}

	char* szResult = NULL;

	if (hDll)
	{
		MINIDUMPWRITEDUMP pDump = (MINIDUMPWRITEDUMP)::GetProcAddress( hDll, "MiniDumpWriteDump" );
		if (pDump)
		{
			char szDumpPath[_MAX_PATH];
			char szScratch [_MAX_PATH];

			// work out a good place for the dump file
			GetCurrentDirectoryA(_MAX_PATH, szDumpPath);
			//if (!GetTempPath( _MAX_PATH, szDumpPath ))
			//	_tcscpy( szDumpPath, "c:\\temp\\" );
			_tcscat( szDumpPath, "\\");
			_tcscat( szDumpPath, m_szAppName );
			_tcscat( szDumpPath, ".dmp" );

				// create the file
				HANDLE hFile = ::CreateFileA( szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL, NULL );

				if (hFile!=INVALID_HANDLE_VALUE)
				{
					_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

					ExInfo.ThreadId = ::GetCurrentThreadId();
					ExInfo.ExceptionPointers = pExceptionInfo;
					ExInfo.ClientPointers = NULL;

					// write the dump
					BOOL bOK = pDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
					if (bOK)
					{
						sprintf( szScratch, "Saved dump file to '%s'", szDumpPath );
						szResult = szScratch;
						retval = EXCEPTION_EXECUTE_HANDLER;
					}
					else
					{
						sprintf( szScratch, "Failed to save dump file to '%s' (error %d)", szDumpPath, GetLastError() );
						szResult = szScratch;
					}
					::CloseHandle(hFile);
				}
				else
				{
					sprintf( szScratch, "Failed to create dump file '%s' (error %d)", szDumpPath, GetLastError() );
					szResult = szScratch;
				}
			
		}
		else
		{
			szResult = "DBGHELP.DLL too old";
		}
	}
	else
	{
		szResult = "DBGHELP.DLL not found";
	}

	if (szResult)
		::MessageBoxA( NULL, szResult, m_szAppName, MB_OK );

	return retval;
}
