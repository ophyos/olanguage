
#ifndef _OWI_LISTVIEW_H_
#define _OWI_LISTVIEW_H_

#include "../../ExportDefine.h"
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
//ListItem
OFL_API int _stdcall ListItem_GetIndex(void* pListItem);
OFL_API void _stdcall ListItem_SetText(void* pListItem,int subindex,char* string);
OFL_API char* _stdcall ListItem_GetText(void* pListItem,int subindex);
OFL_API void _stdcall ListItem_SetImage(void* pListItem,int subindex,int image);
OFL_API int _stdcall ListItem_GetImage(void* pListItem,int subindex);
OFL_API void _stdcall ListItem_SetStateImage(void* pListItem,int subindex,int image);
OFL_API int _stdcall ListItem_GetStateImage(void* pListItem,int subindex);
OFL_API void _stdcall ListItem_SetOverlayImage(void* pListItem,int subindex,int image);
OFL_API int _stdcall ListItem_GetOverlayImage(void* pListItem,int subindex);   
OFL_API void _stdcall ListItem_SetGroup(void* pListItem,void* pListGroup);
OFL_API void _stdcall ListItem_SetIndent(void* pListItem,int indent);
OFL_API int _stdcall ListItem_GetIndent(void* pListItem);
OFL_API void _stdcall ListItem_SetChecked(void* pListItem,bool check);
OFL_API bool _stdcall ListItem_GetChecked(void* pListItem);
OFL_API void _stdcall ListItem_SetSelected(void* pListItem,bool select);
OFL_API bool _stdcall ListItem_IsSelected(void* pListItem);
OFL_API void _stdcall ListItem_SetCut(void* pListItem,bool cut);
OFL_API bool _stdcall ListItem_IsCut(void* pListItem); 
OFL_API void _stdcall ListItem_SetFocused(void* pListItem,bool focus);
OFL_API bool _stdcall ListItem_GetFocused(void* pListItem);
OFL_API void _stdcall ListItem_SetDropHilited(void* pListItem,bool hilite);
OFL_API bool _stdcall ListItem_GetDropHilited(void* pListItem);
OFL_API void _stdcall ListItem_SetTextColor(void* pListItem,int subindex,unsigned int color);
OFL_API unsigned int _stdcall ListItem_GetTextColor(void* pListItem,int subindex);
OFL_API void _stdcall ListItem_SetTextBackColor(void* pListItem,int subindex,unsigned int color);
OFL_API unsigned int _stdcall ListItem_GetTextBackColor(void* pListItem,int color);
OFL_API void _stdcall ListItem_GetRect(void* pListItem,RECT& rc);
OFL_API void _stdcall ListItem_GetSubRect(void* pListItem,int subIndex,RECT& rc);
OFL_API void _stdcall ListItem_SetData(void* pListItem,void* data);
OFL_API void* _stdcall ListItem_GetData(void* pListItem);
OFL_API void _stdcall ListItem_SetPosition(void* pListItem,const POINT& p);
OFL_API void _stdcall ListItem_GetPosition(void* pListItem,POINT& p);
OFL_API void* _stdcall ListItem_GetGroup(void* pListItem);
OFL_API void* _stdcall ListItem_GetOwner(void* pListItem);

//////////////////////////////////////////////////////////////////////////
//ListColumn
OFL_API int _stdcall ListColumn_GetIndex(void* pListColumn);
OFL_API void _stdcall ListColumn_SetText(void* pListColumn,char* name);
OFL_API char* _stdcall ListColumn_GetText(void* pListColumn);
OFL_API void _stdcall ListColumn_SetFormat(void* pListColumn,int format);
OFL_API int _stdcall ListColumn_GetFormat(void* pListColumn);
OFL_API void _stdcall ListColumn_SetWidth(void* pListColumn,int width);
OFL_API int _stdcall ListColumn_GetWidth(void* pListColumn);
OFL_API void _stdcall ListColumn_SetImage(void* pListColumn,int image);
OFL_API int _stdcall ListColumn_GetImage(void* pListColumn);
OFL_API void _stdcall ListColumn_SetOrder(void* pListColumn,int order);
OFL_API int _stdcall ListColumn_GetOrder(void* pListColumn);   
OFL_API void* _stdcall ListColumn_GetOwner(void* pListColumn);

//////////////////////////////////////////////////////////////////////////
//ListGroup
OFL_API int _stdcall ListGroup_GetId(void* pListGroup);
OFL_API void _stdcall ListGroup_SetFormat(void* pListGroup,unsigned int format);
OFL_API unsigned int _stdcall ListGroup_GetFormat(void* pListGroup);
OFL_API void _stdcall ListGroup_SetPosition(void* pListGroup,int pos);
OFL_API void _stdcall ListGroup_SetHeader(void* pListGroup,wchar_t* name);
OFL_API void _stdcall ListGroup_SetFooter(void* pListGroup,wchar_t* name);	
OFL_API wchar_t* _stdcall ListGroup_GetHeader(void* pListGroup);	  
OFL_API wchar_t* _stdcall ListGroup_GetFooter(void* pListGroup);
OFL_API void* _stdcall ListGroup_GetOwner(void* pListGroup);

//////////////////////////////////////////////////////////////////////////
//ListView

OFL_API void _stdcall OListView_SetToolTip(void* pListView,HWND hToolTip);
OFL_API int _stdcall OListView_GetColumnCount(void* pListView);
OFL_API int _stdcall OListView_GetItemCount(void* pListView);
OFL_API int _stdcall OListView_GetSelectedItemCount(void* pListView);
OFL_API void _stdcall OListView_SetTextColor(void* pListView,unsigned int color);
OFL_API unsigned int _stdcall OListView_GetTextColor(void* pListView);	
OFL_API void _stdcall OListView_SetTextBackColor(void* pListView,unsigned int color);
OFL_API unsigned int _stdcall OListView_GetTextBackColor(void* pListView);
OFL_API void _stdcall OListView_SetWorkAreaCount(void* pListView,int count);
OFL_API int _stdcall OListView_GetWorkAreaCount(void* pListView); 
OFL_API int _stdcall OListView_GetTopIndex(void* pListView);
OFL_API void _stdcall OListView_SetHoverTime(void* pListView,unsigned int time);
OFL_API unsigned int _stdcall OListView_GetHoverTime(void* pListView);
OFL_API void _stdcall OListView_SetSelectionMark(void* pListView,int mark);
OFL_API int _stdcall OListView_GetSelectionMark(void* pListView);
OFL_API void _stdcall OListView_SetHotItem(void* pListView,int item);
OFL_API int _stdcall OListView_GetHotItem(void* pListView);
OFL_API int _stdcall OListView_GetCountPerPage(void* pListView);
OFL_API void _stdcall OListView_SetGroupEnabled(void* pListView,bool enable); 
OFL_API bool _stdcall OListView_IsGroupEnabled(void* pListView);
OFL_API int _stdcall OListView_GetGroupCount(void* pListView);
OFL_API void _stdcall OListView_SetInsertMark(void* pListView,int mark);
OFL_API int _stdcall OListView_GetInsertMark(void* pListView);
OFL_API void _stdcall OListView_SetInsertMarkColor(void* pListView,unsigned int color);
OFL_API unsigned int _stdcall OListView_GetInsertMarkColor(void* pListView);	
OFL_API void _stdcall OListView_SetOutlineColor(void* pListView,unsigned int color);
OFL_API unsigned int _stdcall OListView_GetOutlineColor(void* pListView);
OFL_API void _stdcall OListView_SetSelectedColumn(void* pListView,unsigned int column);
OFL_API unsigned int _stdcall OListView_GetSelectedColumn(void* pListView); 
OFL_API void _stdcall OListView_SetWorkArea(void* pListView,int index,const RECT& rc);
OFL_API void _stdcall OListView_SetHotCursor(void* pListView,HCURSOR hCursor);
OFL_API void _stdcall OListView_SetViewMode(void* pListView,int mode);
OFL_API void _stdcall OListView_GetWorkArea(void* pListView,int index,RECT& rc);	
OFL_API void _stdcall OListView_GetViewRect(void* pListView,RECT& rc);
OFL_API void _stdcall OListView_GetInsertMarkRect(void* pListView,RECT& rc);   
OFL_API HWND _stdcall OListView_GetToolTip(void* pListView);
OFL_API HWND _stdcall OListView_GetHeader(void* pListView);  
OFL_API HWND _stdcall OListView_GetEditControl(void* pListView);	
OFL_API void _stdcall OListView_GetOrigin(void* pListView,POINT& p);	 
OFL_API HCURSOR _stdcall OListView_GetHotCursor(void* pListView);	
OFL_API void* _stdcall OListView_GetItem(void* pListView,int index);  
OFL_API void* _stdcall OListView_GetGroup(void* pListView,int index);	 
OFL_API void* _stdcall OListView_GetColumn(void* pListView,int index); 
OFL_API int _stdcall OListView_GetViewMode(void* pListView);	

//追加一列，默认格式为左对齐，列宽为50个像素，无列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumn(void* pListView);
//追加一列，默认格式为左对齐，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumnText(void* pListView,int width,char* text);
//追加一列，format为左对齐格式，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumnFormat(void* pListView,int format,int width,char* text);
//在索引index前插入一列，默认左对齐，列宽50个像素，无列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumn(void* pListView,int index);
//在索引index前插入一列，默认左对齐另外两个参数指定列宽和列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumnText(void* pListView,int index,int width,char* text);
//在索引index前插入一列，format为对齐格式，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumnFormat(void* pListView,int index,int format,int width,char* text);
//删除索引为index的列(注意：第一列不能删除，必须保留)，返回值表明删除操作是否成功
OFL_API bool _stdcall OListView_DeleteColumn(void* pListView,int index); 
//删除所有列
OFL_API void _stdcall OListView_DeleteAllColumns(void* pListView);
//设置ImageList，ListView可以设置包含3个ImageList：分别为大图标模式下所使用的ImageList、小图标模式
//下所使用的ImageList、用于显示状态的ImageList。
OFL_API void _stdcall OListView_SetImageList(void* pListView,int type,void* imagelist);
//获取相应的ImageList
OFL_API void* _stdcall OListView_GetImageList(void* pListView,int type);
//追加一个新的Item，返回新加的ListItem，如果控件具有某种排序风格，则此函数不一定是在控件尾部执行追加，而很可能在某个位置
//执行插入操作。返回值的含义请参考下面的InsertItem()注释。
OFL_API void* _stdcall OListView_AddItem(void* pListView);
//在第index个索引前插入一个新的Item。注意：返回值ListItem的成员mIndex只有临时意义。如果以后用户在此ListItem之前添加或
//删除其他的ListItem，则此ListItem的mIndex将失效，用户应当主动调用UpdateItemIndex刷新其mIndex值。如果控件有排序风格，
//则插入操作不一定发生在指定Item之前。
OFL_API void* _stdcall OListView_InsertItem(void* pListView,int index);
//删除指定的Item
OFL_API bool _stdcall OListView_DeleteItem(void* pListView,void* item);
//删除指定索引的Item
OFL_API bool _stdcall OListView_DeleteItemIndex(void* pListView,int index);
//删除所有的Item
OFL_API void _stdcall OListView_DeleteAllItems(void* pListView);
//获取Item在控件中的索引
OFL_API int _stdcall OListView_GetItemIndex(void* pListView,void* item);
//搜索其文本匹配text的Item，exact指定文本是否要精确匹配：true则要求文本完全相同，false只要求Item文本以text开始。搜索过程是
//大小写敏感的。找到符合要求的Item则返回其指针，否则返回NULL
OFL_API void* _stdcall OListView_FindItem(void* pListView,char* text, bool exact);
//在大图标或小图标模式，在direction方向找到离p点(相对控件客户区原点)最近的Item，方向可为VK_LEFT、VK_RIGHT、VK_UP、VK_DOWN
OFL_API void* _stdcall OListView_FindNearestItem(void* pListView,const POINT& p,unsigned int direction);
//开始编辑指定的Item，控件必须具有可编辑风格(ListViewDesc::mCanEdit必须设为true)，此时会创建一个Edit控件，
//其文本为Item的文本，并且全部高亮选中。返回值指明是否确实显示了Edit控件。
OFL_API bool _stdcall OListView_BeginEdit(void* pListView,int index);
//如果某个Item正处于编辑状态，此函数将取消其编辑状态，编辑控件自动隐藏并销毁(XP)
OFL_API void _stdcall OListView_CancelEdit(void* pListView);
//在大图标模式，重新安排所有的Item，确保对齐，参数align指明对齐方式(请参考枚举类型ListItemAlign{})
OFL_API void _stdcall OListView_Arrange(void* pListView,int align);
//确保指定的Item可视，若不可视，则滚动ListView使之可视
OFL_API void _stdcall OListView_EnsureVisible(void* pListView,int index);
//滚动客户区中的内容，两参数分别指定水平和垂直滚动的像素数(若控件模式为Report，只能垂直滚动，且dy会自动舍入成整行数)
OFL_API void _stdcall OListView_Scroll(void* pListView,int dx, int dy);
//设置在Icon模式下图标之间的间隔，注意cx和cy必须包括图标的宽高，不然会导致图标的重叠；两参数为-1，则恢复默认值
OFL_API void _stdcall OListView_SetIconSpacing(void* pListView,int cx,int cy);
//获取Item之间的间距，参数为true指明求小图标模式下的Item间距，否则求大图标模式下的Item间距
OFL_API unsigned int _stdcall OListView_GetItemSpacing(void* pListView,bool smallIcon);
//返回在控件当前字体下文本的像素宽度
OFL_API int _stdcall OListView_GetStringWidth(void* pListView,char* text);
//返回指定坐标之下的Item(p相对与控件客户区原点)
OFL_API void* _stdcall OListView_IsOnItem(void* pListView,const POINT& p);
//测试一个点是否在Item图标之上，p是相对控件客户区原点的坐标，返回Item(若坐标不在一个Item上则返回NULL)
OFL_API void* _stdcall OListView_IsOnIcon(void* pListView,const POINT& p,/*Out*/int* subItem = NULL);   
//测试一个点是否在Item状态图标之上，参数含义同IsOnIcon()说明
OFL_API void* _stdcall OListView_IsOnStateIcon(void* pListView,const POINT& p,/*Out*/int* subItem = NULL); 
//测试一个点是否在Item标签文本之上，参数含义同IsOnIcon()说明
OFL_API void* _stdcall OListView_IsOnLabel(void* pListView,const POINT& p,/*Out*/int* subItem = NULL);  
//追加一个新组，返回值指明了新加的组，用户以后可以通过此返回值操控组的各项属性(Vista)
OFL_API void* _stdcall OListView_AddGroup(void* pListView);
//获取相应ID的组(Vista)
OFL_API void* _stdcall OListView_GetGroupById(void* pListView,int id);
//删除指定的组，返回值指明操作是否成功(Vista)
OFL_API bool _stdcall OListView_DeleteGroup(void* pListView,void* group);
//删除所有的组(Vista)
OFL_API void _stdcall OListView_DeleteAllGroups(void* pListView);	

OFL_API void _stdcall OListView_DestroyControl(void* pListView);
OFL_API char* _stdcall OListView_GetClass(void* pListView);
OFL_API void _stdcall OListView_SetCaption(void* pListView,char* string);
OFL_API char* _stdcall OListView_GetCaption(void* pListView);
OFL_API void _stdcall OListView_RedrawControl(void* pListView,bool redraw);

#endif //_OWI_LISTVIEW_H_