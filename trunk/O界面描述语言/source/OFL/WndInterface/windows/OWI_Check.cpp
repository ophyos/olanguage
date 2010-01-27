
#include "OWI_Check.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Check_SetChecked(void* pCheck,bool check)
{
	((WinCheck*)pCheck)->SetChecked(check);
}

OFL_API bool _stdcall Check_GetChecked(void* pCheck)
{
	return ((WinCheck*)pCheck)->GetChecked();
}

OFL_API void _stdcall Check_SetTextColor(void* pCheck,unsigned int color)
{
	((WinCheck*)pCheck)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Check_GetTextColor(void* pCheck)
{
	return ((WinCheck*)pCheck)->GetTextColor();
}

OFL_API void _stdcall Check_DestroyControl(void* pCheck)
{
	((WinCheck*)pCheck)->DestroyControl();
}

OFL_API char* _stdcall Check_GetClass(void* pCheck)
{
	return (char*)((WinCheck*)pCheck)->GetClass();
}
