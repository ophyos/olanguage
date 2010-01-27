
#include "OWI_Splitter.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Splitter_SetControl1(void* pSplitter,void* c)
{
	((WinSplitter*)pSplitter)->SetControl1((WinControl*)c);
}

OFL_API void _stdcall Splitter_SetControl2(void* pSplitter,void* c)
{
	((WinSplitter*)pSplitter)->SetControl2((WinControl*)c);
}

OFL_API void* _stdcall Splitter_GetControl1(void* pSplitter)
{
	return ((WinSplitter*)pSplitter)->GetControl1();
}

OFL_API void* _stdcall Splitter_GetControl2(void* pSplitter)
{
	return ((WinSplitter*)pSplitter)->GetControl2();
}


OFL_API void _stdcall Splitter_DestroyControl(void* pSplitter)
{
	((WinSplitter*)pSplitter)->DestroyControl();
}

OFL_API char* _stdcall Splitter_GetClass(void* pSplitter)
{
	return (char*)((WinSplitter*)pSplitter)->GetClass();
}

OFL_API char* _stdcall Splitter_GetCaption(void* pSplitter)
{
	return (char*)((WinSplitter*)pSplitter)->GetCaption();
}

OFL_API void _stdcall Splitter_SetCaption(void* pSplitter,char* string)
{
	((WinSplitter*)pSplitter)->SetCaption(string);
}

