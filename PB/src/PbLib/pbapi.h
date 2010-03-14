#ifndef PBAPI_H
#define PBAPI_H

#include "pbglobal.h"
#include "windows.h"
#ifdef __cplusplus
extern "C"{
#endif

extern int PB_EXPORT pbStart(LPCSTR processName,LPCSTR dirName, LPCSTR dllPath, BOOL bLaunch);

#ifdef __cplusplus
}
#endif
#endif

