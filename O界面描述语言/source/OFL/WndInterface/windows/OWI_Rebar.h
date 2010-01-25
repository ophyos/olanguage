
#ifndef _OWI_REBAR_H_
#define _OWI_REBAR_H_

#include "../../ExportDefine.h"
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
//RebarBand
OFL_API unsigned int _stdcall RebarBand_GetId(void* pRebarBand);
OFL_API int _stdcall RebarBand_GetIndex(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetText(void* pRebarBand,char* text);
OFL_API char* _stdcall RebarBand_GetText(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetImage(void* pRebarBand,int index);
OFL_API int _stdcall RebarBand_GetImage(void* pRebarBand); 
OFL_API void _stdcall RebarBand_SetWidth(void* pRebarBand,int width);
OFL_API int _stdcall RebarBand_GetWidth(void* pRebarBand);   
OFL_API void _stdcall RebarBand_SetVisible(void* pRebarBand,bool visible);
OFL_API bool _stdcall RebarBand_GetVisible(void* pRebarBand);   
OFL_API bool _stdcall RebarBand_HasChevron(void* pRebarBand); 
OFL_API void _stdcall RebarBand_SetTextColor(void* pRebarBand,unsigned int color);
OFL_API unsigned int _stdcall RebarBand_GetTextColor(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetBackColor(void* pRebarBand,unsigned int color);
OFL_API unsigned int _stdcall RebarBand_GetBackColor(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetLeftMargin(void* pRebarBand,int margin);
OFL_API int _stdcall RebarBand_GetLeftMargin(void* pRebarBand); 
OFL_API void _stdcall RebarBand_SetChevronLimit(void* pRebarBand,int limit);
OFL_API int _stdcall RebarBand_GetChevronLimit(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetMinChildWidth(void* pRebarBand,int width);
OFL_API int _stdcall RebarBand_GetMinChildWidth(void* pRebarBand);
OFL_API void _stdcall RebarBand_SetMinHeight(void* pRebarBand,int height);
OFL_API int _stdcall RebarBand_GetMinHeight(void* pRebarBand);		
OFL_API void _stdcall RebarBand_GetRect(void* pRebarBand,RECT& rc);
OFL_API void _stdcall RebarBand_SetBackBitmap(void* pRebarBand,HBITMAP bitmap);
OFL_API HBITMAP _stdcall RebarBand_GetBackBitmap(void* pRebarBand);	 
OFL_API void* _stdcall RebarBand_GetParent(void* pRebarBand);
OFL_API void* _stdcall RebarBand_GetChild(void* pRebarBand);	

OFL_API void* _stdcall RebarBand_GetOwner(void* pRebarBand);
OFL_API bool _stdcall RebarBand_IsClientEmpty(void* pRebarBand);
OFL_API void _stdcall RebarBand_AddControl(void* pRebarBand,void* pControl);
OFL_API void _stdcall RebarBand_RemoveControl(void* pRebarBand,void* pControl);

OFL_API void _stdcall RebarBand_SetColor(void* pRebarBand,unsigned int foreColor,unsigned int backColor);
OFL_API void _stdcall RebarBand_GetColor(void* pRebarBand,unsigned int& foreColor,unsigned int& backColor);	
OFL_API void _stdcall RebarBand_SetMinChildSize(void* pRebarBand,int minWidth,int minHeight);
OFL_API void _stdcall RebarBand_GetMinChildSize(void* pRebarBand,int& minWidth,int& minHeight);

//////////////////////////////////////////////////////////////////////////
//Rebar
OFL_API int _stdcall Rebar_GetBandCount(void* pRebar);
OFL_API int _stdcall Rebar_GetRowCount(void* pRebar);
OFL_API int _stdcall Rebar_GetRowHeight(void* pRebar,int index);
OFL_API void _stdcall Rebar_SetTextColor(void* pRebar,unsigned int color);
OFL_API unsigned int _stdcall Rebar_GetTextColor(void* pRebar);
OFL_API void _stdcall Rebar_GetBandRect(void* pRebar,int pos,RECT& rc); 
OFL_API void _stdcall Rebar_SetImageList(void* pRebar,void* imageList);
OFL_API void* _stdcall Rebar_GetBand(void* pRebar,int index);	 
OFL_API void* _stdcall Rebar_GetImageList(void* pRebar);

//添加一个Band，参数1指明Band的宽度，参数2指明Band的最小高度，参数3表明是否要把Band放在新的一行，参数4指明是否Band的尺寸要固定下来
OFL_API void* _stdcall Rebar_AddBand(void* pRebar,int width=50,int height=10,bool newLine=true,bool fixedSize=false);
//在索引为index的Band之前插入一个新的Band，其他参数可参考AddBand()的注释说明
OFL_API void* _stdcall Rebar_InsertBand(void* pRebar,int index,int width=50,int height=10,bool newLine=true,bool fixedSize=false);
//删除指针为band的Band
OFL_API void _stdcall Rebar_DeleteBand(void* pRebar,void* band);
//删除索引为index的Band
OFL_API void _stdcall Rebar_DeleteBandIndex(void* pRebar,int index);
//删除所有的Band
OFL_API void _stdcall Rebar_DeleteAllBand(void* pRebar);
//用程序代码来最大化索引为index的Band，用户也可用鼠标单击(或双击Band的抓取器来最大化/最小化Band)
OFL_API void _stdcall Rebar_MaximizeBand(void* pRebar,int index);
//用程序代码来最小化索引为index的Band
OFL_API void _stdcall Rebar_MinimizeBand(void* pRebar,int index);
//用程序代码来移动索引为iFrom的Band，使其索引位置为iTo
OFL_API void _stdcall Rebar_MoveBand(void* pRebar,int iFrom, int iTo);
//用程序代码来按下索引为index的Band的尖形按钮
OFL_API void _stdcall Rebar_PushChevron(void* pRebar,int index);
//用程序代码来开始拖拽索引为index的Band，此时会进入拖拽模式
OFL_API void _stdcall Rebar_BeginDrag(void* pRebar,int index);
//在拖拽模式下，鼠标位置移动到(x,y)
OFL_API void _stdcall Rebar_DragMove(void* pRebar,int x, int y);
//结束拖拽模式
OFL_API void _stdcall Rebar_EndDrag(void* pRebar);
//测试哪一个Band正好在坐标p(相对于控件客户区原点)之下
OFL_API void* _stdcall Rebar_IsOnBand(void* pRebar,const POINT& p);

OFL_API void _stdcall Rebar_DestroyControl(void* pRebar);
OFL_API char* _stdcall Rebar_GetClass(void* pRebar);
OFL_API void _stdcall Rebar_SetCaption(void* pRebar,char* string);
OFL_API char* _stdcall Rebar_GetCaption(void* pRebar);
OFL_API void _stdcall Rebar_Move(void* pRebar,int dx,int dy);
OFL_API void _stdcall Rebar_SetSize(void* pRebar,int width,int height);
OFL_API void _stdcall Rebar_SetPositionSize(void* pRebar,int left,int top,int width,int height);
OFL_API void _stdcall Rebar_RedrawControl(void* pRebar,bool redraw);

#endif //_OWI_REBAR_H_