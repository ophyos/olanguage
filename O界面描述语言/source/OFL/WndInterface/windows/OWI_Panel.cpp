
#include "OWI_Panel.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Panel_DestroyControl(void* pPanel)
{
	((WinPanel*)pPanel)->DestroyControl();
}

OFL_API char* _stdcall Panel_GetClass(void* pPanel)
{
	return (char*)((WinPanel*)pPanel)->GetClass();
}

OFL_API char* _stdcall Panel_GetCaption(void* pPanel)
{
	return (char*)((WinPanel*)pPanel)->GetCaption();
}

OFL_API void _stdcall Panel_SetCaption(void* pPanel,char* string)
{
	((WinPanel*)pPanel)->SetCaption(string);
}
