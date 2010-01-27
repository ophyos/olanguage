
#ifndef _EXPORT_DEFINE_H_
#define _EXPORT_DEFINE_H_

//#define OFL_API

#ifdef OFL_EXPORTS
#define OFL_API extern "C"__declspec(dllexport)
#else
#define OFL_API extern "C" __declspec(dllimport)
#endif
 
#endif //_EXPORT_DEFINE_H_