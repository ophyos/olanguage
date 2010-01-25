
#include "OWI_Radio.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API bool _stdcall Radio_GetSelected(void* pRadio)
{
	return ((WinRadio*)pRadio)->GetSelected();
}

OFL_API void _stdcall Radio_SetSelected(void* pRadio,bool select)
{
	((WinRadio*)pRadio)->SetSelected(select);
}

OFL_API void _stdcall Radio_SetGroup(void* pRadio,unsigned int group)
{
	((WinRadio*)pRadio)->SetGroup(group);
}

OFL_API unsigned int _stdcall Radio_GetGroup(void* pRadio)
{
	return ((WinRadio*)pRadio)->GetGroup();
}

OFL_API void _stdcall Radio_SetTextColor(void* pRadio,unsigned int color)
{
	((WinRadio*)pRadio)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Radio_GetTextColor(void* pRadio)
{
	return ((WinRadio*)pRadio)->GetTextColor();
}

OFL_API void _stdcall Radio_DestroyControl(void* pRadio)
{
	((WinRadio*)pRadio)->DestroyControl();
}

OFL_API char* _stdcall Radio_GetClass(void* pRadio)
{
	return (char*)((WinRadio*)pRadio)->GetClass();
}
