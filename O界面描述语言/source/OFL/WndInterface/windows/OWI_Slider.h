
#ifndef _OWI_SLIDER_H_
#define _OWI_SLIDER_H_

#include "../../ExportDefine.h"
#include <Windows.h>

OFL_API void _stdcall Slider_SetLineSize(void* pSlider,int line);
OFL_API int _stdcall Slider_GetLineSize(void* pSlider);
OFL_API void _stdcall Slider_SetPageSize(void* pSlider,int page);
OFL_API int _stdcall Slider_GetPageSize(void* pSlider);
OFL_API void _stdcall Slider_SetPosition(void* pSlider,int pos);
OFL_API int _stdcall Slider_GetPosition(void* pSlider);
OFL_API void _stdcall Slider_SetRangeMin(void* pSlider,int min);
OFL_API int _stdcall Slider_GetRangeMin(void* pSlider);
OFL_API void _stdcall Slider_SetRangeMax(void* pSlider,int max);
OFL_API int _stdcall Slider_GetRangeMax(void* pSlider);
OFL_API void _stdcall Slider_SetSelectStart(void* pSlider,int start);
OFL_API int _stdcall Slider_GetSelectStart(void* pSlider);
OFL_API void _stdcall Slider_SetSelectEnd(void* pSlider,int end);
OFL_API int _stdcall Slider_GetSelectEnd(void* pSlider);
OFL_API void _stdcall Slider_SetSliderSize(void* pSlider,int size);
OFL_API int _stdcall Slider_GetSliderSize(void* pSlider);
OFL_API int _stdcall Slider_GetTickCount(void* pSlider);
OFL_API void _stdcall Slider_SetTickFrequency(void* pSlider,int freq);
OFL_API void _stdcall Slider_SetToolTip(void* pSlider,HWND tip);
OFL_API void _stdcall Slider_SetToolTipSide(void* pSlider,int edge);
OFL_API void _stdcall Slider_GetSliderRect(void* pSlider,RECT& rc);
OFL_API void _stdcall Slider_GetChannelRect(void* pSlider,RECT& rc);
OFL_API HWND _stdcall Slider_GetToolTip(void* pSlider);

//设置Trackbar的逻辑位置的有效范围(控件创建之后通常应当调用此函数来设置自己的有效范围)
OFL_API void _stdcall Slider_SetRange(void* pSlider,int min,int max);
//选择Trackbar范围内的某一段，使之高亮显示(Trackbar的mCanSelect风格必须为true)
OFL_API void _stdcall Slider_SetSelect(void* pSlider,int min,int max);
//清除以前设置的高亮选择段
OFL_API void _stdcall Slider_ClearSelect(void* pSlider);
//在指定的逻辑位置显示一个Tick(系统自动创第一个和最后一个Tick，此函数只可创建中间位置的Tick)
OFL_API void _stdcall Slider_SetTick(void* pSlider,int logicPos);
//返回某个Tick的逻辑位置(逻辑位置必须在SetRange()所设定的范围)									 
OFL_API int _stdcall Slider_GetTick(void* pSlider,int tick);
//清除首尾之间的所有Tick(并不清除控件自动创建的第一个和最后一个Tick)
OFL_API void _stdcall Slider_ClearAllTick(void* pSlider);

OFL_API void _stdcall Slider_DestroyControl(void* pSlider);
OFL_API char* _stdcall Slider_GetClass(void* pSlider);
OFL_API void _stdcall Slider_SetCaption(void* pSlider,char* string);
OFL_API char* _stdcall Slider_GetCaption(void* pSlider); 
OFL_API void _stdcall Slider_RedrawControl(void* pSlider,bool redraw);

#endif //_OWI_SLIDER_H_