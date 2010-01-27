
#include "OWI_StatusBar.h"
#include "../../CreateWnd/windows/OFControl.h"

//////////////////////////////////////////////////////////////////////////
//StatusBarPart

OFL_API int _stdcall StatusBarPart_GetIndex(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetIndex();
}

OFL_API void _stdcall StatusBarPart_SetWidth(void* pStatusBarPart,int width)
{
	((StatusBarPart*)pStatusBarPart)->SetWidth(width);
}

OFL_API int _stdcall StatusBarPart_GetWidth(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetWidth();
}

OFL_API void _stdcall StatusBarPart_SetText(void* pStatusBarPart,char* string)
{
	((StatusBarPart*)pStatusBarPart)->SetText(string);
}

OFL_API char* _stdcall StatusBarPart_GetText(void* pStatusBarPart)
{
	return (char*)((StatusBarPart*)pStatusBarPart)->GetText();
}

OFL_API void _stdcall StatusBarPart_SetTextColor(void* pStatusBarPart,unsigned int color)
{
	((StatusBarPart*)pStatusBarPart)->SetTextColor(color);
}

OFL_API unsigned int _stdcall StatusBarPart_GetTextColor(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetTextColor();
}

OFL_API void _stdcall StatusBarPart_SetStyle(void* pStatusBarPart,unsigned int style)
{
	((StatusBarPart*)pStatusBarPart)->SetStyle(style);
}

OFL_API unsigned int _stdcall StatusBarPart_GetStyle(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetStyle();
}

OFL_API void _stdcall StatusBarPart_SetTipText(void* pStatusBarPart,char* string)
{
	((StatusBarPart*)pStatusBarPart)->SetTipText(string);
}

OFL_API char* _stdcall StatusBarPart_GetTipText(void* pStatusBarPart)
{
	return (char*)((StatusBarPart*)pStatusBarPart)->GetTipText();
}

OFL_API void _stdcall StatusBarPart_SetIcon(void* pStatusBarPart,HICON icon)
{
	((StatusBarPart*)pStatusBarPart)->SetIcon(icon);
}

OFL_API void _stdcall StatusBarPart_GetRect(void* pStatusBarPart,RECT& rc)
{
	Rect rect = ((StatusBarPart*)pStatusBarPart)->GetRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API HICON _stdcall StatusBarPart_GetIcon(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetIcon();
}

OFL_API void* _stdcall StatusBarPart_GetOwner(void* pStatusBarPart)
{
	return ((StatusBarPart*)pStatusBarPart)->GetOwner();
}

//////////////////////////////////////////////////////////////////////////
//StatusBar

OFL_API void _stdcall StatusBarPart_SetPartCount(void* pStatusBar,int count)
{
	((WinStatusBar*)pStatusBar)->SetPartCount(count);
}

OFL_API int _stdcall StatusBarPart_GetPartCount(void* pStatusBar)
{
	return ((WinStatusBar*)pStatusBar)->GetPartCount();
}

OFL_API void* _stdcall StatusBarPart_GetPart(void* pStatusBar,int index)
{
	return ((WinStatusBar*)pStatusBar)->GetPart(index);
}

OFL_API void _stdcall StatusBarPart_DestroyControl(void* pStatusBar)
{
	((WinStatusBar*)pStatusBar)->DestroyControl();
}

OFL_API char* _stdcall StatusBarPart_GetClass(void* pStatusBar)
{
	return (char*)((WinStatusBar*)pStatusBar)->GetClass();
}

OFL_API char* _stdcall StatusBarPart_GetCaption(void* pStatusBar)
{
	return (char*)((WinStatusBar*)pStatusBar)->GetCaption();
}

OFL_API void _stdcall StatusBarPart_SetCaption(void* pStatusBar,char* string)
{
	((WinStatusBar*)pStatusBar)->SetCaption(string);
}
