#ifndef PBGLOBAL_H
#define PBGLOBAL_H

#define PB_EXPORT
#ifdef PB_LIB_EXPORTS
#undef PB_EXPORT
#define PB_EXPORT __declspec(dllexport)
#endif

#endif