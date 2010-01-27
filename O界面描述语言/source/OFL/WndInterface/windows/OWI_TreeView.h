
#ifndef _OWI_TREEVIEW_H_
#define _OWI_TREEVIEW_H_

#include "../../ExportDefine.h"
#include <Windows.h>
#include <CommCtrl.h>


//////////////////////////////////////////////////////////////////////////
//TreeItem
OFL_API char* _stdcall TreeItem_GetText(void* pTreeItem);			
OFL_API void _stdcall TreeItem_SetText(void* pTreeItem,char* string);
OFL_API bool _stdcall TreeItem_IsExpanded(void* pTreeItem);
OFL_API void _stdcall TreeItem_Expand(void* pTreeItem,bool expand);   
OFL_API bool _stdcall TreeItem_GetChecked(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetChecked(void* pTreeItem,bool check); 
OFL_API bool _stdcall TreeItem_IsSelected(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetSelected(void* pTreeItem,bool select);   
OFL_API bool _stdcall TreeItem_HasButton(void* pTreeItem);
OFL_API void _stdcall TreeItem_ShowButton(void* pTreeItem,bool showbtn);
OFL_API bool _stdcall TreeItem_IsCut(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetCut(void* pTreeItem,bool cut);   
OFL_API bool _stdcall TreeItem_IsBold(void* pTreeItem);    
OFL_API void _stdcall TreeItem_SetBold(void* pTreeItem,bool blod);
OFL_API void _stdcall TreeItem_SetDropHilited(void* pTreeItem,bool hilit);
OFL_API bool _stdcall TreeItem_GetDropHilited(void* pTreeItem);
OFL_API unsigned int _stdcall TreeItem_GetTextColor(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetTextColor(void* pTreeItem,unsigned int color);	  
OFL_API unsigned int _stdcall TreeItem_GetTextBackColor(void* pTreeItem); 
OFL_API void _stdcall TreeItem_SetTextBackColor(void* pTreeItem,unsigned int color);   
OFL_API int _stdcall TreeItem_GetImage(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetImage(void* pTreeItem,int image);		 
OFL_API int _stdcall TreeItem_GetSelectedImage(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetSelectedImage(void* pTreeItem,int image);
OFL_API int _stdcall TreeItem_GetStateImage(void* pTreeItem);
OFL_API void _stdcall TreeItem_SetStateImage(void* pTreeItem,int image);	 
OFL_API int _stdcall TreeItem_GetOverlayImage(void* pTreeItem);	
OFL_API void _stdcall TreeItem_SetOverlayImage(void* pTreeItem,int image);
OFL_API void _stdcall TreeItem_SetData(void* pTreeItem,void* data);
OFL_API void _stdcall TreeItem_GetRect(void* pTreeItem,RECT& rc);
OFL_API void* _stdcall TreeItem_GetData(void* pTreeItem);
OFL_API void* _stdcall TreeItem_GetParentItem(void* pTreeItem);   
OFL_API void* _stdcall TreeItem_GetPrevItem(void* pTreeItem);
OFL_API void* _stdcall TreeItem_GetNextItem(void* pTreeItem);
OFL_API void* _stdcall TreeItem_GetFirstChildItem(void* pTreeItem);
OFL_API HTREEITEM _stdcall TreeItem_GetHandle(void* pTreeItem);

//////////////////////////////////////////////////////////////////////////
//TreeView
OFL_API void _stdcall OTreeView_SetTextColor(void* pTreeView,unsigned int color);
OFL_API unsigned int _stdcall OTreeView_GetTextColor(void* pTreeView);
OFL_API void _stdcall OTreeView_SetLineColor(void* pTreeView,unsigned int color);
OFL_API unsigned int _stdcall OTreeView_GetLineColor(void* pTreeView);
OFL_API void _stdcall OTreeView_SetItemIndent(void* pTreeView,int indent);
OFL_API int _stdcall OTreeView_GetItemIndent(void* pTreeView);
OFL_API void _stdcall OTreeView_SetItemHeight(void* pTreeView,int height);
OFL_API int _stdcall OTreeView_GetItemHeight(void* pTreeView);
OFL_API void _stdcall OTreeView_SetToolTip(void* pTreeView,HWND tip);
OFL_API HWND _stdcall OTreeView_GetToolTip(void* pTreeView);
OFL_API HWND _stdcall OTreeView_GetEditControl(void* pTreeView);
OFL_API void* _stdcall OTreeView_GetTopItem(void* pTreeView);	 
OFL_API void* _stdcall OTreeView_GetRootItem(void* pTreeView); 
OFL_API void* _stdcall OTreeView_GetSelectedItem(void* pTreeView); 

//设置ImageList，可分为显示状态图标用的ImageList和显示正常图标用的ImageList两种
OFL_API void _stdcall OTreeView_SetImageList(void* pTreeView,int type,void* imageList);
//获取指定类型的ImageList
OFL_API void* _stdcall OTreeView_GetImageList(void* pTreeView,int type);	
//在指定的兄弟Item之后插入一个新的Item，after若为NULL则添加一个根Item，否则在其后加一个新Item
OFL_API void* _stdcall OTreeView_InsertSibling(void* pTreeView,void* after);
//在指定的父Item之下追加一个新的子Item，parent参数不能为NULL
OFL_API void* _stdcall OTreeView_InsertChild(void* pTreeView,void* parent);
//删除指定的Item
OFL_API void _stdcall OTreeView_DeleteItem(void* pTreeView,void* item);
//删除所有的Item
OFL_API void _stdcall OTreeView_DeleteAllItems(void* pTreeView); 
//获取指定句柄的Item
OFL_API void* _stdcall OTreeView_GetItem(void* pTreeView,HTREEITEM item);   
//给定相对于控件客户区原点的坐标x,y，返回坐标之下的Item
OFL_API void* _stdcall OTreeView_TestPoint(void* pTreeView,int x,int y);
//确保指定的Item可视，若不可视则自动滚动窗口使之可视
OFL_API void _stdcall OTreeView_EnsureVisible(void* pTreeView,void* item);
//开始编辑某个Item，返回值说明是否确实进入了编辑模式(要求控件有TreeViewDesc::mCanEdit风格)
OFL_API bool _stdcall OTreeView_BeginEdit(void* pTreeView,void* item);
//结束编辑模式，用户的输入生效
OFL_API void _stdcall OTreeView_EndEdit(void* pTreeView);
//取消编辑模式，用户的输入被丢弃，Item的文本不变
OFL_API void _stdcall OTreeView_CancelEdit(void* pTreeView);

OFL_API void _stdcall OTreeView_DestroyControl(void* pTreeView);
OFL_API char* _stdcall OTreeView_GetClass(void* pTreeView);
OFL_API void _stdcall OTreeView_SetCaption(void* pTreeView,char* string);
OFL_API char* _stdcall OTreeView_GetCaption(void* pTreeView);
OFL_API void _stdcall OTreeView_Move(void* pTreeView,int dx,int dy);
OFL_API void _stdcall OTreeView_SetSize(void* pTreeView,int width,int height);
OFL_API void _stdcall OTreeView_SetPositionSize(void* pTreeView,int letf,int top,int width,int height);

#endif //_OWI_TREEVIEW_H_