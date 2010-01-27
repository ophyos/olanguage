
#ifndef _OWI_SPIN_H_
#define _OWI_SPIN_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Spin_SetPosition(void* pSpin,int pos);
OFL_API int _stdcall Spin_GetPosition(void* pSpin);
OFL_API void _stdcall Spin_SetBase(void* pSpin,int base);
OFL_API int _stdcall Spin_GetBase(void* pSpin);
OFL_API void _stdcall Spin_SetBuddy(void* pSpin,void* buddy);
OFL_API void* _stdcall Spin_GetBuddy(void* pSpin);

//设置控件的最小、最大调节范围
OFL_API void _stdcall Spin_SetRange(void* pSpin,int min, int max);
//获取控件的最小调节范围
OFL_API int _stdcall Spin_GetRangeMin(void* pSpin);
//获取控件的最大调节范围
OFL_API int _stdcall Spin_GetRangeMax(void* pSpin);	
//获取控件的最小、最大调节范围
OFL_API void _stdcall Spin_GetRange(void* pSpin,int& min, int& max);

OFL_API void _stdcall Spin_DestroyControl(void* pSpin);	
OFL_API char* _stdcall Spin_GetClass(void* pSpin);
OFL_API void _stdcall Spin_SetCaption(void* pSpin,char* string);
OFL_API char* _stdcall Spin_GetCaption(void* pSpin);

#endif //_OWI_SPIN_H_