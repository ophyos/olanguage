
#ifndef _OWI_PANEL_H_
#define _OWI_PANEL_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Panel_DestroyControl(void* pPanel);
OFL_API char* _stdcall Panel_GetClass(void* pPanel);
OFL_API char* _stdcall Panel_GetCaption(void* pPanel);
OFL_API void _stdcall Panel_SetCaption(void* pPanel,char* string);

#endif //_OWI_PANEL_H_