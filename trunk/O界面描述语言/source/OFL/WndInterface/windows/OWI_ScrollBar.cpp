
#include "OWI_ScrollBar.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API int _stdcall ScrollBar_GetRangeMin(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetRangeMin();
}

OFL_API int _stdcall ScrollBar_GetRangeMax(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetRangeMax();
}

OFL_API void _stdcall ScrollBar_SetPosition(void* pScrollBar,int pos)
{
	((WinScrollBar*)pScrollBar)->SetPosition(pos);
}

OFL_API int _stdcall ScrollBar_GetPosition(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetPosition();
}

OFL_API void _stdcall ScrollBar_SetPageSize(void* pScrollBar,int page)
{
	((WinScrollBar*)pScrollBar)->SetPageSize(page);
}

OFL_API int _stdcall ScrollBar_GetPageSize(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetPageSize();
}

OFL_API void _stdcall ScrollBar_EnableLeftArrow(void* pScrollBar,bool leftarrow)
{
	((WinScrollBar*)pScrollBar)->EnableLeftArrow(leftarrow);
}

OFL_API bool _stdcall ScrollBar_GetLeftArrowEnabled(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetLeftArrowEnabled();
}

OFL_API void _stdcall ScrollBar_EnableRightArrow(void* pScrollBar,bool rightarrow)
{
	((WinScrollBar*)pScrollBar)->EnableRightArrow(rightarrow);
}

OFL_API bool _stdcall ScrollBar_GetRightArrowEnabled(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetRightArrowEnabled();
}

OFL_API void _stdcall ScrollBar_EnableUpArrow(void* pScrollBar,bool uparrow)
{
	((WinScrollBar*)pScrollBar)->EnableUpArrow(uparrow);
}

OFL_API bool _stdcall ScrollBar_GetUpArrowEnabled(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetUpArrowEnabled();
}

OFL_API void _stdcall ScrollBar_EnableDownArrow(void* pScrollBar,bool downarrow)
{
	((WinScrollBar*)pScrollBar)->EnableDownArrow(downarrow);
}

OFL_API bool _stdcall ScrollBar_GetDownArrowEnabled(void* pScrollBar)
{
	return ((WinScrollBar*)pScrollBar)->GetDownArrowEnabled();
}

//设置滚动条的滚动范围到【min,max】
OFL_API void _stdcall ScrollBar_SetRange(void* pScrollBar,int min, int max)
{
	((WinScrollBar*)pScrollBar)->SetRange(min,max);
}


OFL_API void _stdcall ScrollBar_DestroyControl(void* pScrollBar)
{
	((WinScrollBar*)pScrollBar)->DestroyControl();
}

OFL_API char* _stdcall ScrollBar_GetClass(void* pScrollBar)
{
	return (char*)((WinScrollBar*)pScrollBar)->GetClass();
}

OFL_API char* _stdcall ScrollBar_GetCaption(void* pScrollBar)
{
	return (char*)((WinScrollBar*)pScrollBar)->GetCaption();
}

OFL_API void _stdcall ScrollBar_SetCaption(void* pScrollBar,char* string)
{
	((WinScrollBar*)pScrollBar)->SetCaption(string);
}
