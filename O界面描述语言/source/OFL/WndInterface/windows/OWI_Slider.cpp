
#include "OWI_Slider.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Slider_SetLineSize(void* pSlider,int line)
{
	((WinTrackbar*)pSlider)->SetLineSize(line);
}

OFL_API int _stdcall Slider_GetLineSize(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetLineSize();
}

OFL_API void _stdcall Slider_SetPageSize(void* pSlider,int page)
{
	((WinTrackbar*)pSlider)->SetPageSize(page);
}

OFL_API int _stdcall Slider_GetPageSize(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetPageSize();
}

OFL_API void _stdcall Slider_SetPosition(void* pSlider,int pos)
{
	((WinTrackbar*)pSlider)->SetPosition(pos);
}

OFL_API int _stdcall Slider_GetPosition(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetPosition();
}

OFL_API void _stdcall Slider_SetRangeMin(void* pSlider,int min)
{
	((WinTrackbar*)pSlider)->SetRangeMin(min);
}

OFL_API int _stdcall Slider_GetRangeMin(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetRangeMin();
}

OFL_API void _stdcall Slider_SetRangeMax(void* pSlider,int max)
{
	((WinTrackbar*)pSlider)->SetRangeMax(max);
}

OFL_API int _stdcall Slider_GetRangeMax(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetRangeMax();
}

OFL_API void _stdcall Slider_SetSelectStart(void* pSlider,int start)
{
	((WinTrackbar*)pSlider)->SetSelectStart(start);
}

OFL_API int _stdcall Slider_GetSelectStart(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetSelectStart();
}

OFL_API void _stdcall Slider_SetSelectEnd(void* pSlider,int end)
{
	((WinTrackbar*)pSlider)->SetSelectEnd(end);
}

OFL_API int _stdcall Slider_GetSelectEnd(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetSelectEnd();
}

OFL_API void _stdcall Slider_SetSliderSize(void* pSlider,int size)
{
	((WinTrackbar*)pSlider)->SetSliderSize(size);
}

OFL_API int _stdcall Slider_GetSliderSize(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetSliderSize();
}

OFL_API int _stdcall Slider_GetTickCount(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetTickCount();
}

OFL_API void _stdcall Slider_SetTickFrequency(void* pSlider,int freq)
{
	((WinTrackbar*)pSlider)->SetTickFrequency(freq);
}

OFL_API void _stdcall Slider_SetToolTip(void* pSlider,HWND tip)
{
	((WinTrackbar*)pSlider)->SetToolTip(tip);
}

OFL_API void _stdcall Slider_SetToolTipSide(void* pSlider,int edge)
{
	((WinTrackbar*)pSlider)->SetToolTipSide((EdgeType)edge);
}

OFL_API void _stdcall Slider_GetSliderRect(void* pSlider,RECT& rc)
{
	Rect rect = ((WinTrackbar*)pSlider)->GetSliderRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall Slider_GetChannelRect(void* pSlider,RECT& rc)
{
	Rect rect = ((WinTrackbar*)pSlider)->GetChannelRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API HWND _stdcall Slider_GetToolTip(void* pSlider)
{
	return ((WinTrackbar*)pSlider)->GetToolTip();
}


//设置Trackbar的逻辑位置的有效范围(控件创建之后通常应当调用此函数来设置自己的有效范围)
OFL_API void _stdcall Slider_SetRange(void* pSlider,int min,int max)
{
	((WinTrackbar*)pSlider)->SetRange(min,max);
}

//选择Trackbar范围内的某一段，使之高亮显示(Trackbar的mCanSelect风格必须为true)
OFL_API void _stdcall Slider_SetSelect(void* pSlider,int min,int max)
{
	((WinTrackbar*)pSlider)->SetSelect(min,max);
}

//清除以前设置的高亮选择段
OFL_API void _stdcall Slider_ClearSelect(void* pSlider)
{
	((WinTrackbar*)pSlider)->ClearSelect();
}

//在指定的逻辑位置显示一个Tick(系统自动创第一个和最后一个Tick，此函数只可创建中间位置的Tick)
OFL_API void _stdcall Slider_SetTick(void* pSlider,int logicPos)
{
	((WinTrackbar*)pSlider)->SetTick(logicPos);
}

//返回某个Tick的逻辑位置(逻辑位置必须在SetRange()所设定的范围)									 
OFL_API int _stdcall Slider_GetTick(void* pSlider,int tick)
{
	return ((WinTrackbar*)pSlider)->GetTick(tick);
}

//清除首尾之间的所有Tick(并不清除控件自动创建的第一个和最后一个Tick)
OFL_API void _stdcall Slider_ClearAllTick(void* pSlider)
{
	((WinTrackbar*)pSlider)->ClearAllTick();
}


OFL_API void _stdcall Slider_DestroyControl(void* pSlider)
{
	((WinTrackbar*)pSlider)->DestroyControl();
}

OFL_API char* _stdcall Slider_GetClass(void* pSlider)
{
	return (char*)((WinTrackbar*)pSlider)->GetClass();
}

OFL_API void _stdcall Slider_SetCaption(void* pSlider,char* string)
{
	((WinTrackbar*)pSlider)->SetCaption(string);
}

OFL_API char* _stdcall Slider_GetCaption(void* pSlider)
{
	return (char*)((WinTrackbar*)pSlider)->GetCaption();
}

OFL_API void _stdcall Slider_RedrawControl(void* pSlider,bool redraw)
{
	((WinTrackbar*)pSlider)->RedrawControl(redraw);
}
