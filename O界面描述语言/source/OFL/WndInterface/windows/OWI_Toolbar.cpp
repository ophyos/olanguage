
#include "OWI_Toolbar.h"
#include "../../CreateWnd/windows/OFControl.h"

//////////////////////////////////////////////////////////////////////////
//ToolbarButton

OFL_API int _stdcall ToolbarButton_GetIndex(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetIndex();
}

OFL_API int _stdcall ToolbarButton_GetId(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetId();
}

OFL_API void _stdcall ToolbarButton_SetImage(void* pToolbarButton,int image)
{
	((ToolbarButton*)pToolbarButton)->SetImage(image);
}

OFL_API int _stdcall ToolbarButton_GetImage(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetImage();
}

OFL_API void _stdcall ToolbarButton_SetText(void* pToolbarButton,char* text)
{
	((ToolbarButton*)pToolbarButton)->SetText(text);
}

OFL_API char* _stdcall ToolbarButton_GetText(void* pToolbarButton)
{
	return (char*)((ToolbarButton*)pToolbarButton)->GetText();
}

OFL_API void _stdcall ToolbarButton_SetEnabled(void* pToolbarButton,bool enable)
{
	((ToolbarButton*)pToolbarButton)->SetEnabled(enable);
}

OFL_API bool _stdcall ToolbarButton_GetEnabled(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetEnabled();
}

OFL_API void _stdcall ToolbarButton_SetVisible(void* pToolbarButton,bool visible)
{
	((ToolbarButton*)pToolbarButton)->SetVisible(visible);
}

OFL_API bool _stdcall ToolbarButton_GetVisible(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetVisible();
}

OFL_API void _stdcall ToolbarButton_SetChecked(void* pToolbarButton,bool check)
{
	((ToolbarButton*)pToolbarButton)->SetChecked(check);
}

OFL_API bool _stdcall ToolbarButton_GetChecked(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetChecked();
}

OFL_API void _stdcall ToolbarButton_SetPressed(void* pToolbarButton,bool press)
{
	((ToolbarButton*)pToolbarButton)->SetPressed(press);
}

OFL_API bool _stdcall ToolbarButton_GetPressed(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetPressed();
}

OFL_API void _stdcall ToolbarButton_SetHilited(void* pToolbarButton,bool high)
{
	((ToolbarButton*)pToolbarButton)->SetHilited(high);
}

OFL_API bool _stdcall ToolbarButton_GetHilited(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetHilited();
}

OFL_API void _stdcall ToolbarButton_SetTipText(void* pToolbarButton,char* text)
{
	((ToolbarButton*)pToolbarButton)->SetTipText(text);
}

OFL_API char* _stdcall ToolbarButton_GetTipText(void* pToolbarButton)
{
	return (char*)((ToolbarButton*)pToolbarButton)->GetTipText();
}

OFL_API void _stdcall ToolbarButton_SetMenu(void* pToolbarButton,void* menu)
{
	((ToolbarButton*)pToolbarButton)->SetMenu((WinMenu*)menu);
}

OFL_API void _stdcall ToolbarButton_SetData(void* pToolbarButton,void* data)
{
	((ToolbarButton*)pToolbarButton)->SetData(data);
}

OFL_API void _stdcall ToolbarButton_GetRect(void* pToolbarButton,RECT& rc)
{
	Rect rect = ((ToolbarButton*)pToolbarButton)->GetRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void* _stdcall ToolbarButton_GetData(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetData();
}

OFL_API void* _stdcall ToolbarButton_GetMenu(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetMenu();
}

OFL_API void* _stdcall ToolbarButton_GetOwner(void* pToolbarButton)
{
	return ((ToolbarButton*)pToolbarButton)->GetOwner();
}


//////////////////////////////////////////////////////////////////////////
//Toolbar

OFL_API int _stdcall Toolbar_GetButtonCount(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetButtonCount();
}

OFL_API void _stdcall Toolbar_SetButtonSize(void* pToolbar,const SIZE& size)
{
	Size sz;
	sz.mWidth = size.cx;
	sz.mHeight = size.cy;
	((WinToolbar*)pToolbar)->SetButtonSize(sz);
}

OFL_API void _stdcall Toolbar_SetBitmapSize(void* pToolbar,const SIZE& size)
{
	Size sz;
	sz.mWidth = size.cx;
	sz.mHeight = size.cy;
	((WinToolbar*)pToolbar)->SetBitmapSize(sz);
}

OFL_API void _stdcall Toolbar_SetHotItem(void* pToolbar,int index)
{
	((WinToolbar*)pToolbar)->SetHotItem(index);
}

OFL_API int _stdcall Toolbar_GetHotItem(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetHotItem();
}

OFL_API void _stdcall Toolbar_SetPadding(void* pToolbar,const SIZE& size)
{
	Size sz;
	sz.mWidth = size.cx;
	sz.mHeight = size.cy;
	((WinToolbar*)pToolbar)->SetPadding(sz);
}

OFL_API void _stdcall Toolbar_SetRowCount(void* pToolbar,int rows)
{
	((WinToolbar*)pToolbar)->SetRowCount(rows);
}

OFL_API int _stdcall Toolbar_GetRowCount(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetRowCount();
}

OFL_API void _stdcall Toolbar_SetToolTip(void* pToolbar,HWND tips)
{
	((WinToolbar*)pToolbar)->SetToolTip(tips);
}

OFL_API void _stdcall Toolbar_SetIndent(void* pToolbar,int indent)
{
	((WinToolbar*)pToolbar)->SetIndent(indent);
}

OFL_API void _stdcall Toolbar_GetButtonSize(void* pToolbar,SIZE& size)
{
	Size sz = ((WinToolbar*)pToolbar)->GetButtonSize();
	size.cx = sz.mWidth;
	size.cy = sz.mHeight;
}

OFL_API void _stdcall Toolbar_GetBitmapSize(void* pToolbar,SIZE& size)
{
	Size sz = ((WinToolbar*)pToolbar)->GetBitmapSize();
	size.cx = sz.mWidth;
	size.cy = sz.mHeight;
}

OFL_API void _stdcall Toolbar_GetPadding(void* pToolbar,SIZE& size)
{
	Size sz = ((WinToolbar*)pToolbar)->GetPadding();
	size.cx = sz.mWidth;
	size.cy = sz.mHeight;
}

OFL_API HWND _stdcall Toolbar_GetToolTip(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetToolTip();
}

OFL_API void _stdcall Toolbar_SetImageList(void* pToolbar,void* imageList)
{
	((WinToolbar*)pToolbar)->SetImageList((WinImageList*)imageList);
}

OFL_API void _stdcall Toolbar_SetHotImageList(void* pToolbar,void* imageList)
{
	((WinToolbar*)pToolbar)->SetHotImageList((WinImageList*)imageList);
}

OFL_API void _stdcall Toolbar_SetDisabledImageList(void* pToolbar,void* imageList)
{
	((WinToolbar*)pToolbar)->SetDisabledImageList((WinImageList*)imageList);
}

OFL_API void* _stdcall Toolbar_GetImageList(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetImageList();
}

OFL_API void* _stdcall Toolbar_GetHotImageList(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetHotImageList();
}

OFL_API void* _stdcall Toolbar_GetDisabledImageList(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->GetDisabledImageList();
}

OFL_API void* _stdcall Toolbar_GetButton(void* pToolbar,int index)
{
	return ((WinToolbar*)pToolbar)->GetButton(index);
}


//以下4个函数为按钮插入函数，注意待插入按钮的id不能与本工具栏中的其他按钮id重复，也不要与其他工具栏中按钮id重复。
//在位置index之前插入一个普通按钮，用户必须指定按钮的id；showText指明是否显示文本，但此参数对于文字显示在图片下方
//的工具栏无效。
OFL_API void* _stdcall Toolbar_InsertButton(void* pToolbar,int index, int id, bool showText)
{
	return ((WinToolbar*)pToolbar)->InsertButton(index,id,showText);
}

//在位置index之前插入一个Check式按钮，用户按下这种按钮，它保持按下状态；再按一下，又恢复原状。
//如果group参数为true，则相邻的Check式按钮共属一组，其状态互斥，即其中只有一个能保持压下状态。
OFL_API void* _stdcall Toolbar_InsertCheck(void* pToolbar,bool group, int index, int id, bool showText)
{
	return ((WinToolbar*)pToolbar)->InsertCheck(group,index,id,showText);
}

//在位置index之前插入一个下拉式按钮，这种按钮右侧有一个小箭头。如果whole为false，则按钮本身与小箭头
//焊接在一起，否则是分开的。
OFL_API void* _stdcall Toolbar_InsertDropdown(void* pToolbar,bool whole, int index, int id, bool showText)
{
	return ((WinToolbar*)pToolbar)->InsertDropdown(whole,index,id,showText);
}

//在位置index之前插入一个分割按钮(这种分割按钮实际上是一种比较窄的豁口)
OFL_API void* _stdcall Toolbar_InsertSeperator(void* pToolbar,int index)
{
	return ((WinToolbar*)pToolbar)->InsertSeperator(index);
}
		
//在工具栏尾部追加一个Button按钮，参数含义请参考InsertButton()的注释
OFL_API void* _stdcall Toolbar_AddButton(void* pToolbar,int id, bool showText)
{
	return  ((WinToolbar*)pToolbar)->AddButton(id,showText);
}

//在工具栏尾部追加一个Check按钮，参数含义请参考InsertCheck()的注释
OFL_API void* _stdcall Toolbar_AddCheck(void* pToolbar,bool group, int id, bool showText)
{
	return ((WinToolbar*)pToolbar)->AddCheck(group,id,showText);
}

//在工具栏尾部追加一个Dropdown按钮，参数含义请参考InsertDropdown()的注释
OFL_API void* _stdcall Toolbar_AddDropdown(void* pToolbar,bool whole, int id, bool showText)
{
	return ((WinToolbar*)pToolbar)->AddDropdown(whole,id,showText);
}

//在工具栏尾部追加一个Seperator按钮
OFL_API void* _stdcall Toolbar_AddSeperator(void* pToolbar)
{
	return ((WinToolbar*)pToolbar)->AddSeperator();
}

//删除指定索引的按钮
OFL_API void _stdcall Toolbar_DeleteButton(void* pToolbar,int index)
{
	((WinToolbar*)pToolbar)->DeleteButton(index);
}

//删除所有按钮
OFL_API void _stdcall Toolbar_DeleteAllButtons(void* pToolbar)
{
	((WinToolbar*)pToolbar)->DeleteAllButtons();
}

//将一个按钮从iFrom位置移动到iTo位置
OFL_API void _stdcall Toolbar_MoveButton(void* pToolbar,int iFrom,int iTo)
{
	((WinToolbar*)pToolbar)->MoveButton(iFrom,iTo);
}

//重新调整工具栏的尺寸(通常是用户改变了按钮大小或按钮图标大小时需要调用此函数)
OFL_API void _stdcall Toolbar_Resize(void* pToolbar)
{
	((WinToolbar*)pToolbar)->Resize();
}

//测试一个坐标为p(相对于工具客户区原点)的点是否在一个非Separator的按钮之上
OFL_API void* _stdcall Toolbar_IsOnButton(void* pToolbar,const POINT& p)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinToolbar*)pToolbar)->IsOnButton(pt);
}

//找到指定id的按钮，若找不到，返回NULL
OFL_API void* _stdcall Toolbar_FindButton(void* pToolbar,int id)
{
	return ((WinToolbar*)pToolbar)->FindButton(id);
}


OFL_API void _stdcall Toolbar_DestroyControl(void* pToolbar)
{
	((WinToolbar*)pToolbar)->DestroyControl();
}

OFL_API char* _stdcall Toolbar_GetClass(void* pToolbar)
{
	return (char*)((WinToolbar*)pToolbar)->GetClass();
}

OFL_API void _stdcall Toolbar_SetCaption(void* pToolbar,char* string)
{
	((WinToolbar*)pToolbar)->SetCaption(string);
}

OFL_API char* _stdcall Toolbar_GetCaption(void* pToolbar)
{
	return (char*)((WinToolbar*)pToolbar)->GetCaption();
}
