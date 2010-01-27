

#include "OWI_Group.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Group_SetTextColor(void* pGroup,unsigned int color)
{
	((WinGroup*)pGroup)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Group_GetTextColor(void* pGroup)
{
	return ((WinGroup*)pGroup)->GetTextColor();
}

OFL_API void _stdcall Group_DestroyControl(void* pGroup)
{
	((WinGroup*)pGroup)->DestroyControl();
}

OFL_API char* _stdcall Group_GetClass(void* pGroup)
{
	return (char*)((WinGroup*)pGroup)->GetClass();
}

OFL_API void _stdcall Group_Enable(void* pGroup,bool bEnable)
{
	((WinGroup*)pGroup)->Enable(bEnable);
}

OFL_API bool _stdcall Group_IsEnabled(void* pGroup)
{
	return ((WinGroup*)pGroup)->IsEnabled();
}

