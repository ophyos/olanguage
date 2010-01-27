
#ifndef _OWI_STATUSBAR_H_
#define _OWI_STATUSBAR_H_

#include "../../ExportDefine.h"
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
//StatusBarPart
OFL_API int _stdcall StatusBarPart_GetIndex(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetWidth(void* pStatusBarPart,int width);
OFL_API int _stdcall StatusBarPart_GetWidth(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetText(void* pStatusBarPart,char* string);
OFL_API char* _stdcall StatusBarPart_GetText(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetTextColor(void* pStatusBarPart,unsigned int color);
OFL_API unsigned int _stdcall StatusBarPart_GetTextColor(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetStyle(void* pStatusBarPart,unsigned int style);
OFL_API unsigned int _stdcall StatusBarPart_GetStyle(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetTipText(void* pStatusBarPart,char* string);
OFL_API char* _stdcall StatusBarPart_GetTipText(void* pStatusBarPart);
OFL_API void _stdcall StatusBarPart_SetIcon(void* pStatusBarPart,HICON icon);
OFL_API void _stdcall StatusBarPart_GetRect(void* pStatusBarPart,RECT& rc);
OFL_API HICON _stdcall StatusBarPart_GetIcon(void* pStatusBarPart);
OFL_API void* _stdcall StatusBarPart_GetOwner(void* pStatusBarPart);

//////////////////////////////////////////////////////////////////////////
//StatusBar

OFL_API void _stdcall StatusBar_SetPartCount(void* pStatusBar,int count);
OFL_API int _stdcall StatusBar_GetPartCount(void* pStatusBar);
OFL_API void* _stdcall StatusBar_GetPart(void* pStatusBar,int index);

OFL_API void _stdcall StatusBar_DestroyControl(void* pStatusBar);
OFL_API char* _stdcall StatusBar_GetClass(void* pStatusBar);
OFL_API char* _stdcall StatusBar_GetCaption(void* pStatusBar);
OFL_API void _stdcall StatusBar_SetCaption(void* pStatusBar,char* string);

#endif //_OWI_STATUSBAR_H_