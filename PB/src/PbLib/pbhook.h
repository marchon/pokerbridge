#ifndef PBHOOK_H
#define PBHOOK_H

#ifdef __cplusplus
extern "C"{
#endif

extern void __declspec(dllexport) APIENTRY NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* pInfo);

extern BOOL EasyHook(LPCSTR module, LPSTR procName, LPVOID hookProc, HOOK_TRACE_INFO *pInfo);

#define EasyHookCpp(dll,decorated,member,handle) EasyHook(dll,decorated,member_ptr(0,&member),handle)

extern ULONG RtlGetProcessID(LPCSTR szProcessNameQuery, int *count);

#ifdef __cplusplus
}
#endif

inline LPVOID member_ptr(int x,...)
{
	va_list ap;
	va_start(ap, x);
	return va_arg(ap, LPVOID);
};



#endif // PBHOOK_H
