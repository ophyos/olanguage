
#ifndef _OWI_TOOLBAR_H_
#define _OWI_TOOLBAR_H_

#include "../../ExportDefine.h"
#include <Windows.h>


//////////////////////////////////////////////////////////////////////////
//ToolbarButton

OFL_API int _stdcall ToolbarButton_GetIndex(void* pToolbarButton);
OFL_API int _stdcall ToolbarButton_GetId(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetImage(void* pToolbarButton,int image);
OFL_API int _stdcall ToolbarButton_GetImage(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetText(void* pToolbarButton,char* text);
OFL_API char* _stdcall ToolbarButton_GetText(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetEnabled(void* pToolbarButton,bool enable);
OFL_API bool _stdcall ToolbarButton_GetEnabled(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetVisible(void* pToolbarButton,bool visible);
OFL_API bool _stdcall ToolbarButton_GetVisible(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetChecked(void* pToolbarButton,bool check);
OFL_API bool _stdcall ToolbarButton_GetChecked(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetPressed(void* pToolbarButton,bool press);
OFL_API bool _stdcall ToolbarButton_GetPressed(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetHilited(void* pToolbarButton,bool high);
OFL_API bool _stdcall ToolbarButton_GetHilited(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetTipText(void* pToolbarButton,char* text);	
OFL_API char* _stdcall ToolbarButton_GetTipText(void* pToolbarButton);
OFL_API void _stdcall ToolbarButton_SetMenu(void* pToolbarButton,void* menu); 
OFL_API void _stdcall ToolbarButton_SetData(void* pToolbarButton,void* data);
OFL_API void _stdcall ToolbarButton_GetRect(void* pToolbarButton,RECT& rc);
OFL_API void* _stdcall ToolbarButton_GetData(void* pToolbarButton); 
OFL_API void* _stdcall ToolbarButton_GetMenu(void* pToolbarButton);
OFL_API void* _stdcall ToolbarButton_GetOwner(void* pToolbarButton);

//////////////////////////////////////////////////////////////////////////
//Toolbar

OFL_API int _stdcall Toolbar_GetButtonCount(void* pToolbar);
OFL_API void _stdcall Toolbar_SetButtonSize(void* pToolbar,const SIZE& size);
OFL_API void _stdcall Toolbar_SetBitmapSize(void* pToolbar,const SIZE& size);
OFL_API void _stdcall Toolbar_SetHotItem(void* pToolbar,int index);
OFL_API int _stdcall Toolbar_GetHotItem(void* pToolbar);			 
OFL_API void _stdcall Toolbar_SetPadding(void* pToolbar,const SIZE& size);
OFL_API void _stdcall Toolbar_SetRowCount(void* pToolbar,int rows);
OFL_API int _stdcall Toolbar_GetRowCount(void* pToolbar);		  
OFL_API void _stdcall Toolbar_SetToolTip(void* pToolbar,HWND tips);
OFL_API void _stdcall Toolbar_SetIndent(void* pToolbar,int indent);
OFL_API void _stdcall Toolbar_GetButtonSize(void* pToolbar,SIZE& size);
OFL_API void _stdcall Toolbar_GetBitmapSize(void* pToolbar,SIZE& size);
OFL_API void _stdcall Toolbar_GetPadding(void* pToolbar,SIZE& size);
OFL_API HWND _stdcall Toolbar_GetToolTip(void* pToolbar);	
OFL_API void _stdcall Toolbar_SetImageList(void* pToolbar,void* imageList);	    
OFL_API void _stdcall Toolbar_SetHotImageList(void* pToolbar,void* imageList);   
OFL_API void _stdcall Toolbar_SetDisabledImageList(void* pToolbar,void* imageList);
OFL_API void* _stdcall Toolbar_GetImageList(void* pToolbar);
OFL_API void* _stdcall Toolbar_GetHotImageList(void* pToolbar);
OFL_API void* _stdcall Toolbar_GetDisabledImageList(void* pToolbar);  
OFL_API void* _stdcall Toolbar_GetButton(void* pToolbar,int index);	

//以下4个函数为按钮插入函数，注意待插入按钮的id不能与本工具栏中的其他按钮id重复，也不要与其他工具栏中按钮id重复。
//在位置index之前插入一个普通按钮，用户必须指定按钮的id；showText指明是否显示文本，但此参数对于文字显示在图片下方
//的工具栏无效。
OFL_API void* _stdcall Toolbar_InsertButton(void* pToolbar,int index, int id, bool showText=true);//
//在位置index之前插入一个Check式按钮，用户按下这种按钮，它保持按下状态；再按一下，又恢复原状。
//如果group参数为true，则相邻的Check式按钮共属一组，其状态互斥，即其中只有一个能保持压下状态。
OFL_API void* _stdcall Toolbar_InsertCheck(void* pToolbar,bool group, int index, int id, bool showText=true);
//在位置index之前插入一个下拉式按钮，这种按钮右侧有一个小箭头。如果whole为false，则按钮本身与小箭头
//焊接在一起，否则是分开的。
OFL_API void* _stdcall Toolbar_InsertDropdown(void* pToolbar,bool whole, int index, int id, bool showText=true);
//在位置index之前插入一个分割按钮(这种分割按钮实际上是一种比较窄的豁口)
OFL_API void* _stdcall Toolbar_InsertSeperator(void* pToolbar,int index);		
//在工具栏尾部追加一个Button按钮，参数含义请参考InsertButton()的注释
OFL_API void* _stdcall Toolbar_AddButton(void* pToolbar,int id, bool showText = true);
//在工具栏尾部追加一个Check按钮，参数含义请参考InsertCheck()的注释
OFL_API void* _stdcall Toolbar_AddCheck(void* pToolbar,bool group, int id, bool showText=true);
//在工具栏尾部追加一个Dropdown按钮，参数含义请参考InsertDropdown()的注释
OFL_API void* _stdcall Toolbar_AddDropdown(void* pToolbar,bool whole, int id, bool showText=true);
//在工具栏尾部追加一个Seperator按钮
OFL_API void* _stdcall Toolbar_AddSeperator(void* pToolbar);
//删除指定索引的按钮
OFL_API void _stdcall Toolbar_DeleteButton(void* pToolbar,int index);
//删除所有按钮
OFL_API void _stdcall Toolbar_DeleteAllButtons(void* pToolbar);
//将一个按钮从iFrom位置移动到iTo位置
OFL_API void _stdcall Toolbar_MoveButton(void* pToolbar,int iFrom,int iTo);
//重新调整工具栏的尺寸(通常是用户改变了按钮大小或按钮图标大小时需要调用此函数)
OFL_API void _stdcall Toolbar_Resize(void* pToolbar);
//测试一个坐标为p(相对于工具客户区原点)的点是否在一个非Separator的按钮之上
OFL_API void* _stdcall Toolbar_IsOnButton(void* pToolbar,const POINT& p);
//找到指定id的按钮，若找不到，返回NULL
OFL_API void* _stdcall Toolbar_FindButton(void* pToolbar,int id);

OFL_API void _stdcall Toolbar_DestroyControl(void* pToolbar);	   
OFL_API char* _stdcall Toolbar_GetClass(void* pToolbar);
OFL_API void _stdcall Toolbar_SetCaption(void* pToolbar,char* string);
OFL_API char* _stdcall Toolbar_GetCaption(void* pToolbar);

#endif //_OWI_TOOLBAR_H_