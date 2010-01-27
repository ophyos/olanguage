
#ifndef _OWI_TEXT_H_
#define _OWI_TEXT_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Text_SetTextColor(void* pText,unsigned int color);
OFL_API unsigned int _stdcall Text_GetTextColor(void* pText);

OFL_API void _stdcall Text_DestroyControl(void* pText);
OFL_API char* _stdcall Text_GetClass(void* pText);
OFL_API void _stdcall Text_Enable(void* pText,bool enable);
OFL_API bool _stdcall Text_IsEnabled(void* pText);

#endif //_OWI_TEXT_H_