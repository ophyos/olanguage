
#ifndef _OWI_BUTTON_H_
#define _OWI_BUTTON_H_

#include "../../ExportDefine.h"
#include <Windows.h>

OFL_API int _stdcall Button_GetIconWidth(void* pButton);
OFL_API void _stdcall Button_SetPressed(void* pButton,bool pressed);
OFL_API bool _stdcall Button_IsPressed(void* pButton);
OFL_API bool _stdcall Button_IsFocused(void* pButton);  
OFL_API void _stdcall Button_SetTextColor(void* pButton,unsigned int color);
OFL_API unsigned int _stdcall Button_GetTextColor(void* pButton);
OFL_API void _stdcall Button_SetIcon(void* pButton,HICON icon);
OFL_API HICON _stdcall Button_GetIcon(void* pButton); 
OFL_API void _stdcall Button_DestroyControl(void* pButton);	
OFL_API char* _stdcall Button_GetClass(void* pButton);

#endif //_OWI_BUTTON_H_