
#ifndef _OWI_CONTROL_H_
#define _OWI_CONTROL_H_

#include "../../ExportDefine.h"
#include <Windows.h>

OFL_API HWND  _stdcall Ctrl_GetHandle(void* pCtrl);

OFL_API void  _stdcall Ctrl_GetClientRect(void* pCtrl,RECT& rc);

//把自己调到屏幕最前方，盖住所有其他窗口(即改变它的Z秩序)
OFL_API void  _stdcall Ctrl_BringToTop(void* pCtrl);
//把自己调到屏幕最后方(因此它可能位置垫底，被许多窗口盖住)
OFL_API void  _stdcall Ctrl_BringToBottom(void* pCtrl);
//设置窗口的焦点
OFL_API void  _stdcall Ctrl_SetFocus(void* pCtrl);

OFL_API void  _stdcall Ctrl_SetCaption(void* pCtrl,char* pchCaption);
OFL_API char* _stdcall Ctrl_GetCaption(void* pCtrl);
OFL_API void  _stdcall Ctrl_Show(void* pCtrl);
OFL_API void  _stdcall Ctrl_Hide(void* pCtrl);
OFL_API void  _stdcall Ctrl_Enable(void* pCtrl,bool bEnable);
OFL_API bool  _stdcall Ctrl_IsEnabled(void* pCtrl);
OFL_API bool  _stdcall Ctrl_IsVisible(void* pCtrl);   	
OFL_API void  _stdcall Ctrl_Move(void* pCtrl,int dx,int dy);
OFL_API void  _stdcall Ctrl_SetSize(void* pCtrl,int width,int height);
OFL_API void  _stdcall Ctrl_SetPositionSize(void* pCtrl,int nLeft,int nRight,int nWidth,int nHeight);
OFL_API void  _stdcall Ctrl_Align(void* pCtrl,unsigned int edge);

#endif //_OWI_CONTROL_H_

