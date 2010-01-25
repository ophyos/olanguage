
#ifndef _OWI_CHECK_H_
#define _OWI_CHECK_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Check_SetChecked(void* pCheck,bool check);
OFL_API bool _stdcall Check_GetChecked(void* pCheck);
OFL_API void _stdcall Check_SetTextColor(void* pCheck,unsigned int color);
OFL_API unsigned int _stdcall Check_GetTextColor(void* pCheck);
OFL_API void _stdcall Check_DestroyControl(void* pCheck);	 
OFL_API char* _stdcall Check_GetClass(void* pCheck);

#endif //_OWI_CHECK_H_