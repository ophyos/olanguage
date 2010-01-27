
#include "OWI_Button.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API int _stdcall Button_GetIconWidth(void* pButton)
{
	return ((WinButton*)pButton)->GetIconWidth();
}

OFL_API void _stdcall Button_SetPressed(void* pButton,bool pressed)
{
	((WinButton*)pButton)->SetPressed(pressed);
}

OFL_API bool _stdcall Button_IsPressed(void* pButton)
{
	return ((WinButton*)pButton)->IsPressed();
}

OFL_API bool _stdcall Button_IsFocused(void* pButton)
{
	return ((WinButton*)pButton)->IsFocused();
}

OFL_API void _stdcall Button_SetTextColor(void* pButton,unsigned int color)
{
	((WinButton*)pButton)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Button_GetTextColor(void* pButton)
{
	return ((WinButton*)pButton)->GetTextColor();
}

OFL_API void _stdcall Button_SetIcon(void* pButton,HICON icon)
{
	((WinButton*)pButton)->SetIcon(icon);
}

OFL_API HICON _stdcall Button_GetIcon(void* pButton)
{
	return  ((WinButton*)pButton)->GetIcon();
}

OFL_API void _stdcall Button_DestroyControl(void* pButton)
{
	((WinButton*)pButton)->DestroyControl();
}

OFL_API char* _stdcall Button_GetClass(void* pButton)
{
	return (char*)((WinButton*)pButton)->GetClass();
}

