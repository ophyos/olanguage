
#ifndef _OWI_RADIO_H_
#define _OWI_RADIO_H_

#include "../../ExportDefine.h"

OFL_API bool _stdcall Radio_GetSelected(void* pRadio);
OFL_API void _stdcall Radio_SetSelected(void* pRadio,bool select);
OFL_API void _stdcall Radio_SetGroup(void* pRadio,unsigned int group);
OFL_API unsigned int _stdcall Radio_GetGroup(void* pRadio);
OFL_API void _stdcall Radio_SetTextColor(void* pRadio,unsigned int color);
OFL_API unsigned int _stdcall Radio_GetTextColor(void* pRadio);
OFL_API void _stdcall Radio_DestroyControl(void* pRadio);	
OFL_API char* _stdcall Radio_GetClass(void* pRadio);

#endif //_OWI_RADIO_H_