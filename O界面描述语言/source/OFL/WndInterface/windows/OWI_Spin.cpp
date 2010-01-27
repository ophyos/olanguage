
#include "OWI_Spin.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Spin_SetPosition(void* pSpin,int pos)
{
	((WinUpDown*)pSpin)->SetPosition(pos);
}

OFL_API int _stdcall Spin_GetPosition(void* pSpin)
{
	return ((WinUpDown*)pSpin)->GetPosition();
}

OFL_API void _stdcall Spin_SetBase(void* pSpin,int base)
{
	((WinUpDown*)pSpin)->SetBase(base);
}

OFL_API int _stdcall Spin_GetBase(void* pSpin)
{
	return ((WinUpDown*)pSpin)->GetBase();
}

OFL_API void _stdcall Spin_SetBuddy(void* pSpin,void* buddy)
{
	((WinUpDown*)pSpin)->SetBuddy((WinControl*)buddy);
}

OFL_API void* _stdcall Spin_GetBuddy(void* pSpin)
{
	return ((WinUpDown*)pSpin)->GetBuddy();
}


//设置控件的最小、最大调节范围
OFL_API void _stdcall Spin_SetRange(void* pSpin,int min, int max)
{
	((WinUpDown*)pSpin)->SetRange(min,max);
}

//获取控件的最小调节范围
OFL_API int _stdcall Spin_GetRangeMin(void* pSpin)
{
	return ((WinUpDown*)pSpin)->GetRangeMin();
}

//获取控件的最大调节范围
OFL_API int _stdcall Spin_GetRangeMax(void* pSpin)
{
	return ((WinUpDown*)pSpin)->GetRangeMax();
}

//获取控件的最小、最大调节范围
OFL_API void _stdcall Spin_GetRange(void* pSpin,int& min, int& max)
{
	((WinUpDown*)pSpin)->GetRange(min,max);
}


OFL_API void _stdcall Spin_DestroyControl(void* pSpin)
{
	((WinUpDown*)pSpin)->DestroyControl();
}

OFL_API char* _stdcall Spin_GetClass(void* pSpin)
{
	return (char*)((WinUpDown*)pSpin)->GetClass();
}

OFL_API void _stdcall Spin_SetCaption(void* pSpin,char* string)
{
	((WinUpDown*)pSpin)->SetCaption(string);
}

OFL_API char* _stdcall Spin_GetCaption(void* pSpin)
{
	return (char*)((WinUpDown*)pSpin)->GetCaption();
}
