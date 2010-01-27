
#include "OWI_Control.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API HWND  _stdcall Ctrl_GetHandle(void* pCtrl)
{
	return ((WinControl*)pCtrl)->GetHandle();
}

OFL_API void  _stdcall Ctrl_GetClientRect(void* pCtrl,RECT& rc)
{
	Rect rect = ((WinControl*)pCtrl)->GetClientRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

//把自己调到屏幕最前方，盖住所有其他窗口(即改变它的Z秩序)
OFL_API void  _stdcall Ctrl_BringToTop(void* pCtrl)
{
	((WinControl*)pCtrl)->BringToTop();
}

//把自己调到屏幕最后方(因此它可能位置垫底，被许多窗口盖住)
OFL_API void  _stdcall Ctrl_BringToBottom(void* pCtrl)
{
	((WinControl*)pCtrl)->BringToBottom();
}

//设置窗口的焦点
OFL_API void  _stdcall Ctrl_SetFocus(void* pCtrl)
{
	((WinControl*)pCtrl)->SetFocus();
}

OFL_API void  _stdcall Ctrl_SetCaption(void* pCtrl,char* pchCaption)
{
	((WinControl*)pCtrl)->SetCaption(pchCaption);
}

OFL_API char* _stdcall Ctrl_GetCaption(void* pCtrl)
{	
	return (char*)((WinControl*)pCtrl)->GetCaption();
}

OFL_API void  _stdcall Ctrl_Show(void* pCtrl)
{
	((WinControl*)pCtrl)->Show();
}

OFL_API void  _stdcall Ctrl_Hide(void* pCtrl)
{
	((WinControl*)pCtrl)->Hide();
}

OFL_API void  _stdcall Ctrl_Enable(void* pCtrl,bool bEnable)
{
	((WinControl*)pCtrl)->Enable(bEnable);
}

OFL_API bool  _stdcall Ctrl_IsEnabled(void* pCtrl)
{
	return ((WinControl*)pCtrl)->IsEnabled();
}

OFL_API bool  _stdcall Ctrl_IsVisible(void* pCtrl)
{	
	return ((WinControl*)pCtrl)->IsVisible();
}

OFL_API void  _stdcall Ctrl_Move(void* pCtrl,int dx,int dy)
{
	((WinControl*)pCtrl)->Move(dx,dy);
}

OFL_API void  _stdcall Ctrl_SetSize(void* pCtrl,int width,int height)
{
	((WinControl*)pCtrl)->SetSize(width,height);
}

OFL_API void  _stdcall Ctrl_SetPositionSize(void* pCtrl,int nLeft,int nRight,int nWidth,int nHeight)
{
	((WinControl*)pCtrl)->SetPositionSize(nLeft,nRight,nWidth,nHeight);
}

OFL_API void  _stdcall Ctrl_Align(void* pCtrl,unsigned int edge)
{
	((WinControl*)pCtrl)->Align(edge);
}


