
#ifndef _OWI_GROUP_H_
#define _OWI_GROUP_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Group_SetTextColor(void* pGroup,unsigned int color);
OFL_API unsigned int _stdcall Group_GetTextColor(void* pGroup);
OFL_API void _stdcall Group_DestroyControl(void* pGroup);	
OFL_API char* _stdcall Group_GetClass(void* pGroup);
OFL_API void _stdcall Group_Enable(void* pGroup,bool bEnable);
OFL_API bool _stdcall Group_IsEnabled(void* pGroup);

#endif //_OWI_GROUP_H_