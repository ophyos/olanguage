
#ifndef _OWI_WINDOW_H_
#define _OWI_WINDOW_H_

#include "../../ExportDefine.h"
#include <Windows.h>

OFL_API void _stdcall Wnd_SetMaximized(void* pWnd,bool max);
OFL_API bool _stdcall Wnd_IsMaximized(void* pWnd);
OFL_API void _stdcall Wnd_SetMinimized(void* pWnd,bool min);
OFL_API bool _stdcall Wnd_IsMinimized(void* pWnd);	 
OFL_API void _stdcall Wnd_SetTopmost(void* pWnd,bool topmost);
OFL_API bool _stdcall Wnd_GetTopmost(void* pWnd);
OFL_API void _stdcall Wnd_SetSmallIcon(void* pWnd,HICON icon);
OFL_API void _stdcall Wnd_SetBigIcon(void* pWnd,HICON icon);  
OFL_API HICON _stdcall Wnd_GetSmallIcon(void* pWnd);
OFL_API HICON _stdcall Wnd_GetBigIcon(void* pWnd);

//关闭并销毁这个窗口和其所有子窗口
OFL_API void _stdcall Wnd_Close(void* pWnd); 
//设置窗口的位置与大小
OFL_API void _stdcall Wnd_MoveWindow(void* pWnd,int x,int y,int width,int height);
//最大化窗口
OFL_API void _stdcall Wnd_Maximize(void* pWnd);
//最小化窗口
OFL_API void _stdcall Wnd_Minimize(void* pWnd);
//还原已经最大化或最小化的窗口
OFL_API void _stdcall Wnd_Restore(void* pWnd);

#endif //_OWI_WINDOW_H_