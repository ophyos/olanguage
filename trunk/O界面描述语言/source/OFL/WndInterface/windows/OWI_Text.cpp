
#include "OWI_Text.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Text_SetTextColor(void* pText,unsigned int color)
{
	((WinText*)pText)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Text_GetTextColor(void* pText)
{
	return ((WinText*)pText)->GetTextColor();
}


OFL_API void _stdcall Text_DestroyControl(void* pText)
{
	((WinText*)pText)->DestroyControl();
}

OFL_API char* _stdcall Text_GetClass(void* pText)
{
	return (char*)((WinText*)pText)->GetClass();
}

OFL_API void _stdcall Text_Enable(void* pText,bool enable)
{
	((WinText*)pText)->Enable(enable);
}

OFL_API bool _stdcall Text_IsEnabled(void* pText)
{
	return ((WinText*)pText)->IsEnabled();
}
