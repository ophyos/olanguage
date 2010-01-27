
#include "OWI_Rebar.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API unsigned int _stdcall RebarBand_GetId(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetId();
}

OFL_API int _stdcall RebarBand_GetIndex(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetIndex();
}

OFL_API void _stdcall RebarBand_SetText(void* pRebarBand,char* text)
{
	((RebarBand*)pRebarBand)->SetText(text);
}

OFL_API char* _stdcall RebarBand_GetText(void* pRebarBand)
{
	return (char*)((RebarBand*)pRebarBand)->GetText();
}

OFL_API void _stdcall RebarBand_SetImage(void* pRebarBand,int index)
{
	((RebarBand*)pRebarBand)->SetImage(index);
}

OFL_API int _stdcall RebarBand_GetImage(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetImage();
}

OFL_API void _stdcall RebarBand_SetWidth(void* pRebarBand,int width)
{
	((RebarBand*)pRebarBand)->SetWidth(width);
}

OFL_API int _stdcall RebarBand_GetWidth(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetWidth();
}

OFL_API void _stdcall RebarBand_SetVisible(void* pRebarBand,bool visible)
{
	((RebarBand*)pRebarBand)->SetVisible(visible);
}

OFL_API bool _stdcall RebarBand_GetVisible(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetVisible();
}

OFL_API bool _stdcall RebarBand_HasChevron(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->HasChevron();
}

OFL_API void _stdcall RebarBand_SetTextColor(void* pRebarBand,unsigned int color)
{
	((RebarBand*)pRebarBand)->SetTextColor(color);
}

OFL_API unsigned int _stdcall RebarBand_GetTextColor(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetTextColor();
}

OFL_API void _stdcall RebarBand_SetBackColor(void* pRebarBand,unsigned int color)
{
	((RebarBand*)pRebarBand)->SetBackColor(color);
}

OFL_API unsigned int _stdcall RebarBand_GetBackColor(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetBackColor();
}

OFL_API void _stdcall RebarBand_SetLeftMargin(void* pRebarBand,int margin)
{
	((RebarBand*)pRebarBand)->SetLeftMargin(margin);
}

OFL_API int _stdcall RebarBand_GetLeftMargin(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetLeftMargin();
}

OFL_API void _stdcall RebarBand_SetChevronLimit(void* pRebarBand,int limit)
{
	((RebarBand*)pRebarBand)->SetChevronLimit(limit);
}

OFL_API int _stdcall RebarBand_GetChevronLimit(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetChevronLimit();
}

OFL_API void _stdcall RebarBand_SetMinChildWidth(void* pRebarBand,int width)
{
	((RebarBand*)pRebarBand)->SetMinChildWidth(width);
}

OFL_API int _stdcall RebarBand_GetMinChildWidth(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetMinChildWidth();
}

OFL_API void _stdcall RebarBand_SetMinHeight(void* pRebarBand,int height)
{
	((RebarBand*)pRebarBand)->SetMinHeight(height);
}

OFL_API int _stdcall RebarBand_GetMinHeight(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetMinHeight();
}

OFL_API void _stdcall RebarBand_GetRect(void* pRebarBand,RECT& rc)
{
	Rect rect = ((RebarBand*)pRebarBand)->GetRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall RebarBand_SetBackBitmap(void* pRebarBand,HBITMAP bitmap)
{
	((RebarBand*)pRebarBand)->SetBackBitmap(bitmap);
}

OFL_API HBITMAP _stdcall RebarBand_GetBackBitmap(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetBackBitmap();
}

OFL_API void* _stdcall RebarBand_GetParent(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetParent();
}

OFL_API void* _stdcall RebarBand_GetChild(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetChild();
}


OFL_API void* _stdcall RebarBand_GetOwner(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->GetOwner();
}

OFL_API bool _stdcall RebarBand_IsClientEmpty(void* pRebarBand)
{
	return ((RebarBand*)pRebarBand)->IsClientEmpty();
}

OFL_API void _stdcall RebarBand_AddControl(void* pRebarBand,void* pControl)
{
	((RebarBand*)pRebarBand)->AddControl((WinControl*)pControl);
}

OFL_API void _stdcall RebarBand_RemoveControl(void* pRebarBand,void* pControl)
{
	((RebarBand*)pRebarBand)->RemoveControl((WinControl*)pControl);
}


OFL_API void _stdcall RebarBand_SetColor(void* pRebarBand,unsigned int foreColor,unsigned int backColor)
{
	((RebarBand*)pRebarBand)->SetColor(foreColor,backColor);
}

OFL_API void _stdcall RebarBand_GetColor(void* pRebarBand,unsigned int& foreColor,unsigned int& backColor)
{
	((RebarBand*)pRebarBand)->GetColor(foreColor,backColor);
}

OFL_API void _stdcall RebarBand_SetMinChildSize(void* pRebarBand,int minWidth,int minHeight)
{
	((RebarBand*)pRebarBand)->SetMinChildSize(minWidth,minHeight);
}

OFL_API void _stdcall RebarBand_GetMinChildSize(void* pRebarBand,int& minWidth,int& minHeight)
{
	((RebarBand*)pRebarBand)->GetMinChildSize(minWidth,minHeight);
}

//////////////////////////////////////////////////////////////////////////
//Rebar

OFL_API int _stdcall Rebar_GetBandCount(void* pRebar)
{
	return ((WinRebar*)pRebar)->GetBandCount();
}

OFL_API int _stdcall Rebar_GetRowCount(void* pRebar)
{
	return ((WinRebar*)pRebar)->GetRowCount();
}

OFL_API int _stdcall Rebar_GetRowHeight(void* pRebar,int index)
{
	return ((WinRebar*)pRebar)->GetRowHeight(index);
}

OFL_API void _stdcall Rebar_SetTextColor(void* pRebar,unsigned int color)
{
	((WinRebar*)pRebar)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Rebar_GetTextColor(void* pRebar)
{
	return ((WinRebar*)pRebar)->GetTextColor();
}

OFL_API void _stdcall Rebar_GetBandRect(void* pRebar,int pos,RECT& rc)
{
	Rect rect = ((WinRebar*)pRebar)->GetBandRect(pos);
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall Rebar_SetImageList(void* pRebar,void* imageList)
{
	((WinRebar*)pRebar)->SetImageList((WinImageList*)imageList);
}

OFL_API void* _stdcall Rebar_GetBand(void* pRebar,int index)
{
	return ((WinRebar*)pRebar)->GetBand(index);
}

OFL_API void* _stdcall Rebar_GetImageList(void* pRebar)
{
	return ((WinRebar*)pRebar)->GetImageList();
}


//添加一个Band，参数1指明Band的宽度，参数2指明Band的最小高度，参数3表明是否要把Band放在新的一行，参数4指明是否Band的尺寸要固定下来
OFL_API void* _stdcall Rebar_AddBand(void* pRebar,int width,int height,bool newLine,bool fixedSize)
{
	return ((WinRebar*)pRebar)->AddBand(width,height,newLine,fixedSize);
}

//在索引为index的Band之前插入一个新的Band，其他参数可参考AddBand()的注释说明
OFL_API void* _stdcall Rebar_InsertBand(void* pRebar,int index,int width,int height,bool newLine,bool fixedSize)
{
	return ((WinRebar*)pRebar)->InsertBand(width,height,newLine,fixedSize);
}

//删除指针为band的Band
OFL_API void _stdcall Rebar_DeleteBand(void* pRebar,void* band)
{
	((WinRebar*)pRebar)->DeleteBand((RebarBand*)band);
}

//删除索引为index的Band
OFL_API void _stdcall Rebar_DeleteBandIndex(void* pRebar,int index)
{
	((WinRebar*)pRebar)->DeleteBand(index);
}

//删除所有的Band
OFL_API void _stdcall Rebar_DeleteAllBand(void* pRebar)
{
	((WinRebar*)pRebar)->DeleteAllBand();
}

//用程序代码来最大化索引为index的Band，用户也可用鼠标单击(或双击Band的抓取器来最大化/最小化Band)
OFL_API void _stdcall Rebar_MaximizeBand(void* pRebar,int index)
{
	((WinRebar*)pRebar)->MaximizeBand(index);
}

//用程序代码来最小化索引为index的Band
OFL_API void _stdcall Rebar_MinimizeBand(void* pRebar,int index)
{
	((WinRebar*)pRebar)->MinimizeBand(index);
}

//用程序代码来移动索引为iFrom的Band，使其索引位置为iTo
OFL_API void _stdcall Rebar_MoveBand(void* pRebar,int iFrom, int iTo)
{
	((WinRebar*)pRebar)->MoveBand(iFrom,iTo);
}

//用程序代码来按下索引为index的Band的尖形按钮
OFL_API void _stdcall Rebar_PushChevron(void* pRebar,int index)
{
	((WinRebar*)pRebar)->PushChevron(index);
}

//用程序代码来开始拖拽索引为index的Band，此时会进入拖拽模式
OFL_API void _stdcall Rebar_BeginDrag(void* pRebar,int index)
{
	((WinRebar*)pRebar)->BeginDrag(index);
}

//在拖拽模式下，鼠标位置移动到(x,y)
OFL_API void _stdcall Rebar_DragMove(void* pRebar,int x, int y)
{
	((WinRebar*)pRebar)->DragMove(x,y);
}

//结束拖拽模式
OFL_API void _stdcall Rebar_EndDrag(void* pRebar)
{
	((WinRebar*)pRebar)->EndDrag();
}

//测试哪一个Band正好在坐标p(相对于控件客户区原点)之下
OFL_API void* _stdcall Rebar_IsOnBand(void* pRebar,const POINT& p)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinRebar*)pRebar)->IsOnBand(pt);
}


OFL_API void _stdcall Rebar_DestroyControl(void* pRebar)
{
	((WinRebar*)pRebar)->DestroyControl();
}

OFL_API char* _stdcall Rebar_GetClass(void* pRebar)
{
	return (char*)((WinRebar*)pRebar)->GetClass();
}

OFL_API void _stdcall Rebar_SetCaption(void* pRebar,char* string)
{
	((WinRebar*)pRebar)->SetCaption(string);
}

OFL_API char* _stdcall Rebar_GetCaption(void* pRebar)
{
	return (char*)((WinRebar*)pRebar)->GetCaption();
}

OFL_API void _stdcall Rebar_Move(void* pRebar,int dx,int dy)
{
	((WinRebar*)pRebar)->Move(dx,dy);
}

OFL_API void _stdcall Rebar_SetSize(void* pRebar,int width,int height)
{
	((WinRebar*)pRebar)->SetSize(width,height);
}

OFL_API void _stdcall Rebar_SetPositionSize(void* pRebar,int left,int top,int width,int height)
{
	((WinRebar*)pRebar)->SetPositionSize(left,top,width,height);
}

OFL_API void _stdcall Rebar_RedrawControl(void* pRebar,bool redraw)
{
	((WinRebar*)pRebar)->RedrawControl(redraw);
}
