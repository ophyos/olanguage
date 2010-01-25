
#ifndef _OWI_SCROLLBAR_H_
#define _OWI_SCROLLBAR_H_

#include "../../ExportDefine.h"

OFL_API int _stdcall ScrollBar_GetRangeMin(void* pScrollBar);
OFL_API int _stdcall ScrollBar_GetRangeMax(void* pScrollBar);
OFL_API void _stdcall ScrollBar_SetPosition(void* pScrollBar,int pos);
OFL_API int _stdcall ScrollBar_GetPosition(void* pScrollBar);
OFL_API void _stdcall ScrollBar_SetPageSize(void* pScrollBar,int page);
OFL_API int _stdcall ScrollBar_GetPageSize(void* pScrollBar);	  
OFL_API void _stdcall ScrollBar_EnableLeftArrow(void* pScrollBar,bool leftarrow);
OFL_API bool _stdcall ScrollBar_GetLeftArrowEnabled(void* pScrollBar);
OFL_API void _stdcall ScrollBar_EnableRightArrow(void* pScrollBar,bool rightarrow);
OFL_API bool _stdcall ScrollBar_GetRightArrowEnabled(void* pScrollBar); 
OFL_API void _stdcall ScrollBar_EnableUpArrow(void* pScrollBar,bool uparrow);
OFL_API bool _stdcall ScrollBar_GetUpArrowEnabled(void* pScrollBar);
OFL_API void _stdcall ScrollBar_EnableDownArrow(void* pScrollBar,bool downarrow);
OFL_API bool _stdcall ScrollBar_GetDownArrowEnabled(void* pScrollBar);
//设置滚动条的滚动范围到【min,max】
OFL_API void _stdcall ScrollBar_SetRange(void* pScrollBar,int min, int max);	

OFL_API void _stdcall ScrollBar_DestroyControl(void* pScrollBar);   
OFL_API char* _stdcall ScrollBar_GetClass(void* pScrollBar);
OFL_API char* _stdcall ScrollBar_GetCaption(void* pScrollBar);
OFL_API void _stdcall ScrollBar_SetCaption(void* pScrollBar,char* string); 

#endif //_OWI_SCROLLBAR_H_