
#include "OWI_ListView.h"
#include "../../CreateWnd/windows/OFControl.h"

//////////////////////////////////////////////////////////////////////////
//ListItem
OFL_API int _stdcall ListItem_GetIndex(void* pListItem)
{
	return ((ListItem*)pListItem)->GetIndex();
}

OFL_API void _stdcall ListItem_SetText(void* pListItem,int subindex,char* string)
{
	((ListItem*)pListItem)->SetText(subindex,string);
}

OFL_API char* _stdcall ListItem_GetText(void* pListItem,int subindex)
{
	return (char*)((ListItem*)pListItem)->GetText(subindex);
}

OFL_API void _stdcall ListItem_SetImage(void* pListItem,int subindex,int image)
{
	((ListItem*)pListItem)->SetImage(subindex,image);
}

OFL_API int _stdcall ListItem_GetImage(void* pListItem,int subindex)
{
	return ((ListItem*)pListItem)->GetImage(subindex);
}

OFL_API void _stdcall ListItem_SetStateImage(void* pListItem,int subindex,int image)
{
	((ListItem*)pListItem)->SetStateImage(subindex,image);
}

OFL_API int _stdcall ListItem_GetStateImage(void* pListItem,int subindex)
{
	return ((ListItem*)pListItem)->GetStateImage(subindex);
}

OFL_API void _stdcall ListItem_SetOverlayImage(void* pListItem,int subindex,int image)
{
	((ListItem*)pListItem)->SetOverlayImage(subindex,image);
}

OFL_API int _stdcall ListItem_GetOverlayImage(void* pListItem,int subindex)
{
	return ((ListItem*)pListItem)->GetOverlayImage(subindex);
}

OFL_API void _stdcall ListItem_SetGroup(void* pListItem,void* pListGroup)
{
	((ListItem*)pListItem)->SetGroup((ListGroup*)pListGroup);
}

OFL_API void _stdcall ListItem_SetIndent(void* pListItem,int indent)
{
	((ListItem*)pListItem)->SetIndent(indent);
}

OFL_API int _stdcall ListItem_GetIndent(void* pListItem)
{
	return ((ListItem*)pListItem)->GetIndent();
}

OFL_API void _stdcall ListItem_SetChecked(void* pListItem,bool check)
{
	((ListItem*)pListItem)->SetChecked(check);
}

OFL_API bool _stdcall ListItem_GetChecked(void* pListItem)
{
	return ((ListItem*)pListItem)->GetChecked();
}

OFL_API void _stdcall ListItem_SetSelected(void* pListItem,bool select)
{
	((ListItem*)pListItem)->SetSelected(select);
}

OFL_API bool _stdcall ListItem_IsSelected(void* pListItem)
{
	return ((ListItem*)pListItem)->IsSelected();
}

OFL_API void _stdcall ListItem_SetCut(void* pListItem,bool cut)
{
	((ListItem*)pListItem)->SetCut(cut);
}

OFL_API bool _stdcall ListItem_IsCut(void* pListItem)
{
	return ((ListItem*)pListItem)->IsCut();
}

OFL_API void _stdcall ListItem_SetFocused(void* pListItem,bool focus)
{
	((ListItem*)pListItem)->SetFocused(focus);
}

OFL_API bool _stdcall ListItem_GetFocused(void* pListItem)
{
	return ((ListItem*)pListItem)->GetFocused();
}

OFL_API void _stdcall ListItem_SetDropHilited(void* pListItem,bool hilite)
{
	((ListItem*)pListItem)->SetDropHilited(hilite);
}

OFL_API bool _stdcall ListItem_GetDropHilited(void* pListItem)
{
	return ((ListItem*)pListItem)->GetDropHilited();
}

OFL_API void _stdcall ListItem_SetTextColor(void* pListItem,int subindex,unsigned int color)
{
	((ListItem*)pListItem)->SetTextColor(subindex,color);
}

OFL_API unsigned int _stdcall ListItem_GetTextColor(void* pListItem,int subindex)
{
	return ((ListItem*)pListItem)->GetTextColor(subindex);
}

OFL_API void _stdcall ListItem_SetTextBackColor(void* pListItem,int subindex,unsigned int color)
{
	((ListItem*)pListItem)->SetTextBackColor(subindex,color);
}

OFL_API unsigned int _stdcall ListItem_GetTextBackColor(void* pListItem,int color)
{
	return ((ListItem*)pListItem)->GetTextBackColor(color);
}

OFL_API void _stdcall ListItem_GetRect(void* pListItem,RECT& rc)
{
	Rect rect = ((ListItem*)pListItem)->GetRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall ListItem_GetSubRect(void* pListItem,int subIndex,RECT& rc)
{
	Rect rect = ((ListItem*)pListItem)->GetSubRect(subIndex);
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall ListItem_SetData(void* pListItem,void* data)
{
	((ListItem*)pListItem)->SetData(data);
}

OFL_API void* _stdcall ListItem_GetData(void* pListItem)
{
	return ((ListItem*)pListItem)->GetData();
}

OFL_API void _stdcall ListItem_SetPosition(void* pListItem,const POINT& p)
{
	Point point;
	point.x = p.x;
	point.y = p.y;
	((ListItem*)pListItem)->SetPosition(point);
}

OFL_API void _stdcall ListItem_GetPosition(void* pListItem,POINT& p)
{
	Point point = ((ListItem*)pListItem)->GetPosition();
	p.x = point.x;
	p.y = point.y;
}

OFL_API void* _stdcall ListItem_GetGroup(void* pListItem)
{
	return ((ListItem*)pListItem)->GetGroup();
}

OFL_API void* _stdcall ListItem_GetOwner(void* pListItem)
{
	return ((ListItem*)pListItem)->GetOwner();
}

//////////////////////////////////////////////////////////////////////////
//ListColumn

OFL_API int _stdcall ListColumn_GetIndex(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetIndex();
}

OFL_API void _stdcall ListColumn_SetText(void* pListColumn,char* name)
{
	((ListColumn*)pListColumn)->SetText(name);
}

OFL_API char* _stdcall ListColumn_GetText(void* pListColumn)
{
	return (char*)((ListColumn*)pListColumn)->GetText();
}

OFL_API void _stdcall ListColumn_SetFormat(void* pListColumn,int format)
{
	((ListColumn*)pListColumn)->SetFormat(format);
}

OFL_API int _stdcall ListColumn_GetFormat(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetFormat();
}

OFL_API void _stdcall ListColumn_SetWidth(void* pListColumn,int width)
{
	((ListColumn*)pListColumn)->SetWidth(width);
}

OFL_API int _stdcall ListColumn_GetWidth(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetWidth();
}

OFL_API void _stdcall ListColumn_SetImage(void* pListColumn,int image)
{
	((ListColumn*)pListColumn)->SetImage(image);
}

OFL_API int _stdcall ListColumn_GetImage(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetImage();
}

OFL_API void _stdcall ListColumn_SetOrder(void* pListColumn,int order)
{
	((ListColumn*)pListColumn)->SetOrder(order);
}

OFL_API int _stdcall ListColumn_GetOrder(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetOrder();
}

OFL_API void* _stdcall ListColumn_GetOwner(void* pListColumn)
{
	return ((ListColumn*)pListColumn)->GetOwner();
}

//////////////////////////////////////////////////////////////////////////
//ListGroup

OFL_API int _stdcall ListGroup_GetId(void* pListGroup)
{
	return ((ListGroup*)pListGroup)->GetId();
}

OFL_API void _stdcall ListGroup_SetFormat(void* pListGroup,unsigned int format)
{
	((ListGroup*)pListGroup)->SetFormat(format);
}

OFL_API unsigned int _stdcall ListGroup_GetFormat(void* pListGroup)
{
	return ((ListGroup*)pListGroup)->GetFormat();
}

OFL_API void _stdcall ListGroup_SetPosition(void* pListGroup,int pos)
{
	((ListGroup*)pListGroup)->SetPosition(pos);
}

OFL_API void _stdcall ListGroup_SetHeader(void* pListGroup,wchar_t* name)
{
	((ListGroup*)pListGroup)->SetHeader(name);
}

OFL_API void _stdcall ListGroup_SetFooter(void* pListGroup,wchar_t* name)
{
	((ListGroup*)pListGroup)->SetFooter(name);
}

OFL_API wchar_t* _stdcall ListGroup_GetHeader(void* pListGroup)
{
	return (wchar_t*)((ListGroup*)pListGroup)->GetHeader();
}

OFL_API wchar_t* _stdcall ListGroup_GetFooter(void* pListGroup)
{
	return (wchar_t*)((ListGroup*)pListGroup)->GetFooter();
}

OFL_API void* _stdcall ListGroup_GetOwner(void* pListGroup)
{
	return ((ListGroup*)pListGroup)->GetOwner();
}

//////////////////////////////////////////////////////////////////////////
//ListView

OFL_API void _stdcall OListView_SetToolTip(void* pListView,HWND hToolTip)
{
	((WinListView*)pListView)->SetToolTip(hToolTip);
}

OFL_API int _stdcall OListView_GetColumnCount(void* pListView)
{
	return ((WinListView*)pListView)->GetColumnCount();
}

OFL_API int _stdcall OListView_GetItemCount(void* pListView)
{
	return ((WinListView*)pListView)->GetItemCount();
}

OFL_API int _stdcall OListView_GetSelectedItemCount(void* pListView)
{
	return ((WinListView*)pListView)->GetSelectedItemCount();
}

OFL_API void _stdcall OListView_SetTextColor(void* pListView,unsigned int color)
{
	((WinListView*)pListView)->SetTextColor(color);
}

OFL_API unsigned int _stdcall OListView_GetTextColor(void* pListView)
{
	return ((WinListView*)pListView)->GetTextColor();
}

OFL_API void _stdcall OListView_SetTextBackColor(void* pListView,unsigned int color)
{
	((WinListView*)pListView)->SetTextBackColor(color);
}

OFL_API unsigned int _stdcall OListView_GetTextBackColor(void* pListView)
{
	return ((WinListView*)pListView)->GetTextBackColor();
}

OFL_API void _stdcall OListView_SetWorkAreaCount(void* pListView,int count)
{
	((WinListView*)pListView)->SetWorkAreaCount(count);
}

OFL_API int _stdcall OListView_GetWorkAreaCount(void* pListView)
{
	return ((WinListView*)pListView)->GetWorkAreaCount();
}

OFL_API int _stdcall OListView_GetTopIndex(void* pListView)
{
	return ((WinListView*)pListView)->GetTopIndex();
}

OFL_API void _stdcall OListView_SetHoverTime(void* pListView,unsigned int time)
{
	((WinListView*)pListView)->SetHoverTime(time);
}

OFL_API unsigned int _stdcall OListView_GetHoverTime(void* pListView)
{
	return ((WinListView*)pListView)->GetHoverTime();
}

OFL_API void _stdcall OListView_SetSelectionMark(void* pListView,int mark)
{
	((WinListView*)pListView)->SetSelectionMark(mark);
}

OFL_API int _stdcall OListView_GetSelectionMark(void* pListView)
{
	return ((WinListView*)pListView)->GetSelectionMark();
}

OFL_API void _stdcall OListView_SetHotItem(void* pListView,int item)
{
	((WinListView*)pListView)->SetHotItem(item);
}

OFL_API int _stdcall OListView_GetHotItem(void* pListView)
{
	return ((WinListView*)pListView)->GetHotItem();
}

OFL_API int _stdcall OListView_GetCountPerPage(void* pListView)
{
	return ((WinListView*)pListView)->GetCountPerPage();
}

OFL_API void _stdcall OListView_SetGroupEnabled(void* pListView,bool enable)
{
	((WinListView*)pListView)->SetGroupEnabled(enable);
}

OFL_API bool _stdcall OListView_IsGroupEnabled(void* pListView)
{
	return ((WinListView*)pListView)->IsGroupEnabled();
}

OFL_API int _stdcall OListView_GetGroupCount(void* pListView)
{
	return ((WinListView*)pListView)->GetGroupCount();
}

OFL_API void _stdcall OListView_SetInsertMark(void* pListView,int mark)
{
	((WinListView*)pListView)->SetInsertMark(mark);
}

OFL_API int _stdcall OListView_GetInsertMark(void* pListView)
{
	return ((WinListView*)pListView)->GetInsertMark();
}

OFL_API void _stdcall OListView_SetInsertMarkColor(void* pListView,unsigned int color)
{
	((WinListView*)pListView)->SetInsertMarkColor(color);
}

OFL_API unsigned int _stdcall OListView_GetInsertMarkColor(void* pListView)
{
	return ((WinListView*)pListView)->GetInsertMarkColor();
}

OFL_API void _stdcall OListView_SetOutlineColor(void* pListView,unsigned int color)
{
	((WinListView*)pListView)->SetOutlineColor(color);
}

OFL_API unsigned int _stdcall OListView_GetOutlineColor(void* pListView)
{
	return ((WinListView*)pListView)->GetOutlineColor();
}

OFL_API void _stdcall OListView_SetSelectedColumn(void* pListView,unsigned int column)
{
	((WinListView*)pListView)->SetSelectedColumn(column);
}

OFL_API unsigned int _stdcall OListView_GetSelectedColumn(void* pListView)
{
	return ((WinListView*)pListView)->GetSelectedColumn();
}

OFL_API void _stdcall OListView_SetWorkArea(void* pListView,int index,const RECT& rc)
{
	Rect rect;
	rect.mLeft = rc.left;
	rect.mTop = rc.top;
	rect.mRight = rc.right;
	rect.mBottom = rc.bottom;	
	((WinListView*)pListView)->SetWorkArea(index,rect);	
}

OFL_API void _stdcall OListView_SetHotCursor(void* pListView,HCURSOR hCursor)
{
	((WinListView*)pListView)->SetHotCursor(hCursor);
}

OFL_API void _stdcall OListView_SetViewMode(void* pListView,int mode)
{
	((WinListView*)pListView)->SetViewMode((ListViewMode)mode);
}

OFL_API void _stdcall OListView_GetWorkArea(void* pListView,int index,RECT& rc)
{
	Rect rect = ((WinListView*)pListView)->GetWorkArea();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;
}

OFL_API void _stdcall OListView_GetViewRect(void* pListView,RECT& rc)
{
	Rect rect = ((WinListView*)pListView)->GetViewRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;
}

OFL_API void _stdcall OListView_GetInsertMarkRect(void* pListView,RECT& rc)
{
	Rect rect = ((WinListView*)pListView)->GetInsertMarkRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;
}

OFL_API HWND _stdcall OListView_GetToolTip(void* pListView)
{
	return ((WinListView*)pListView)->GetToolTip();
}

OFL_API HWND _stdcall OListView_GetHeader(void* pListView)
{
	return ((WinListView*)pListView)->GetHeader();
}

OFL_API HWND _stdcall OListView_GetEditControl(void* pListView)
{
	return ((WinListView*)pListView)->GetEditControl();
}

OFL_API void _stdcall OListView_GetOrigin(void* pListView,POINT& p)
{
	Point pt = ((WinListView*)pListView)->GetOrigin();
	p.x = pt.x;
	p.y = pt.y;
}

OFL_API HCURSOR _stdcall OListView_GetHotCursor(void* pListView)
{
	return ((WinListView*)pListView)->GetHotCursor();
}

OFL_API void* _stdcall OListView_GetItem(void* pListView,int index)
{
	return ((WinListView*)pListView)->GetItem(index);
}

OFL_API void* _stdcall OListView_GetGroup(void* pListView,int index)
{
	return ((WinListView*)pListView)->GetGroup(index);
}

OFL_API void* _stdcall OListView_GetColumn(void* pListView,int index)
{
	return ((WinListView*)pListView)->GetColumn(index);
}

OFL_API int _stdcall OListView_GetViewMode(void* pListView)
{
	return ((WinListView*)pListView)->GetViewMode();
}


//追加一列，默认格式为左对齐，列宽为50个像素，无列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumn(void* pListView)
{
	return ((WinListView*)pListView)->AddColumn();
}

//追加一列，默认格式为左对齐，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumnText(void* pListView,int width,char* text)
{
	return ((WinListView*)pListView)->AddColumn(width,text);
}

//追加一列，format为左对齐格式，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_AddColumnFormat(void* pListView,int format,int width,char* text)
{
	return ((WinListView*)pListView)->AddColumn(format,width,text);
}

//在索引index前插入一列，默认左对齐，列宽50个像素，无列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumn(void* pListView,int index)
{
	return ((WinListView*)pListView)->InsertColumn(index);
}

//在索引index前插入一列，默认左对齐另外两个参数指定列宽和列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumnText(void* pListView,int index,int width,char* text)
{
	return ((WinListView*)pListView)->InsertColumn(index,width,text);
}

//在索引index前插入一列，format为对齐格式，width为列宽，text为列文本，操作成功返回一个列结构，否则返回NULL
OFL_API void* _stdcall OListView_InsertColumnFormat(void* pListView,int index,int format,int width,char* text)
{
	return ((WinListView*)pListView)->InsertColumn(index,format,width,text);
}

//删除索引为index的列(注意：第一列不能删除，必须保留)，返回值表明删除操作是否成功
OFL_API bool _stdcall OListView_DeleteColumn(void* pListView,int index)
{
	return ((WinListView*)pListView)->DeleteColumn(index);
}

//删除所有列
OFL_API void _stdcall OListView_DeleteAllColumns(void* pListView)
{
	((WinListView*)pListView)->DeleteAllColumns();
}

//设置ImageList，ListView可以设置包含3个ImageList：分别为大图标模式下所使用的ImageList、小图标模式
//下所使用的ImageList、用于显示状态的ImageList。
OFL_API void _stdcall OListView_SetImageList(void* pListView,int type,void* imagelist)
{
	((WinListView*)pListView)->SetImageList((ImageListType)type,(WinImageList*)imagelist);
}

//获取相应的ImageList
OFL_API void* _stdcall OListView_GetImageList(void* pListView,int type)
{
	return ((WinListView*)pListView)->GetImageList((ImageListType)type);
}

//追加一个新的Item，返回新加的ListItem，如果控件具有某种排序风格，则此函数不一定是在控件尾部执行追加，而很可能在某个位置
//执行插入操作。返回值的含义请参考下面的InsertItem()注释。
OFL_API void* _stdcall OListView_AddItem(void* pListView)
{
	return ((WinListView*)pListView)->AddItem();
}

//在第index个索引前插入一个新的Item。注意：返回值ListItem的成员mIndex只有临时意义。如果以后用户在此ListItem之前添加或
//删除其他的ListItem，则此ListItem的mIndex将失效，用户应当主动调用UpdateItemIndex刷新其mIndex值。如果控件有排序风格，
//则插入操作不一定发生在指定Item之前。
OFL_API void* _stdcall OListView_InsertItem(void* pListView,int index)
{
	return ((WinListView*)pListView)->InsertItem(index);
}

//删除指定的Item
OFL_API bool _stdcall OListView_DeleteItem(void* pListView,void* item)
{
	return ((WinListView*)pListView)->DeleteItem((ListItem*)item);
}

//删除指定索引的Item
OFL_API bool _stdcall OListView_DeleteItemIndex(void* pListView,int index)
{
	return ((WinListView*)pListView)->DeleteItem(index);
}

//删除所有的Item
OFL_API void _stdcall OListView_DeleteAllItems(void* pListView)
{
	((WinListView*)pListView)->DeleteAllItems();
}

//获取Item在控件中的索引
OFL_API int _stdcall OListView_GetItemIndex(void* pListView,void* item)
{
	return ((WinListView*)pListView)->GetItemIndex((ListItem*)item);
}

//搜索其文本匹配text的Item，exact指定文本是否要精确匹配：true则要求文本完全相同，false只要求Item文本以text开始。搜索过程是
//大小写敏感的。找到符合要求的Item则返回其指针，否则返回NULL
OFL_API void* _stdcall OListView_FindItem(void* pListView,char* text, bool exact)
{
	return ((WinListView*)pListView)->FindItem(text,exact);
}

//在大图标或小图标模式，在direction方向找到离p点(相对控件客户区原点)最近的Item，方向可为VK_LEFT、VK_RIGHT、VK_UP、VK_DOWN
OFL_API void* _stdcall OListView_FindNearestItem(void* pListView,const POINT& p,unsigned int direction)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinListView*)pListView)->FindNearestItem(pt,direction);
}

//开始编辑指定的Item，控件必须具有可编辑风格(ListViewDesc::mCanEdit必须设为true)，此时会创建一个Edit控件，
//其文本为Item的文本，并且全部高亮选中。返回值指明是否确实显示了Edit控件。
OFL_API bool _stdcall OListView_BeginEdit(void* pListView,int index)
{
	return ((WinListView*)pListView)->BeginEdit(index);
}

//如果某个Item正处于编辑状态，此函数将取消其编辑状态，编辑控件自动隐藏并销毁(XP)
OFL_API void _stdcall OListView_CancelEdit(void* pListView)
{
	((WinListView*)pListView)->CancelEdit();
}

//在大图标模式，重新安排所有的Item，确保对齐，参数align指明对齐方式(请参考枚举类型ListItemAlign{})
OFL_API void _stdcall OListView_Arrange(void* pListView,int align)
{
	((WinListView*)pListView)->Arrange(align);
}

//确保指定的Item可视，若不可视，则滚动ListView使之可视
OFL_API void _stdcall OListView_EnsureVisible(void* pListView,int index)
{
	((WinListView*)pListView)->EnsureVisible(index);
}

//滚动客户区中的内容，两参数分别指定水平和垂直滚动的像素数(若控件模式为Report，只能垂直滚动，且dy会自动舍入成整行数)
OFL_API void _stdcall OListView_Scroll(void* pListView,int dx, int dy)
{
	((WinListView*)pListView)->Scroll(dx,dy);
}

//设置在Icon模式下图标之间的间隔，注意cx和cy必须包括图标的宽高，不然会导致图标的重叠；两参数为-1，则恢复默认值
OFL_API void _stdcall OListView_SetIconSpacing(void* pListView,int cx,int cy)
{
	((WinListView*)pListView)->SetIconSpacing(cx,cy);
}

//获取Item之间的间距，参数为true指明求小图标模式下的Item间距，否则求大图标模式下的Item间距
OFL_API unsigned int _stdcall OListView_GetItemSpacing(void* pListView,bool smallIcon)
{
	return ((WinListView*)pListView)->GetItemSpacing(smallIcon);
}

//返回在控件当前字体下文本的像素宽度
OFL_API int _stdcall OListView_GetStringWidth(void* pListView,char* text)
{
	return ((WinListView*)pListView)->GetStringWidth(text);
}

//返回指定坐标之下的Item(p相对与控件客户区原点)
OFL_API void* _stdcall OListView_IsOnItem(void* pListView,const POINT& p)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinListView*)pListView)->IsOnItem(pt);
}

//测试一个点是否在Item图标之上，p是相对控件客户区原点的坐标，返回Item(若坐标不在一个Item上则返回NULL)
OFL_API void* _stdcall OListView_IsOnIcon(void* pListView,const POINT& p,/*Out*/int* subItem)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinListView*)pListView)->IsOnIcon(pt,subItem);
}

//测试一个点是否在Item状态图标之上，参数含义同IsOnIcon()说明
OFL_API void* _stdcall OListView_IsOnStateIcon(void* pListView,const POINT& p,/*Out*/int* subItem)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinListView*)pListView)->IsOnStateIcon(pt,subItem);
}

//测试一个点是否在Item标签文本之上，参数含义同IsOnIcon()说明
OFL_API void* _stdcall OListView_IsOnLabel(void* pListView,const POINT& p,/*Out*/int* subItem)
{
	Point pt;
	pt.x = p.x;
	pt.y = p.y;
	return ((WinListView*)pListView)->IsOnLabel(pt,subItem);
}

//追加一个新组，返回值指明了新加的组，用户以后可以通过此返回值操控组的各项属性(Vista)
OFL_API void* _stdcall OListView_AddGroup(void* pListView)
{
	return ((WinListView*)pListView)->AddGroup();
}

//获取相应ID的组(Vista)
OFL_API void* _stdcall OListView_GetGroupById(void* pListView,int id)
{
	return ((WinListView*)pListView)->GetGroupById(id);
}

//删除指定的组，返回值指明操作是否成功(Vista)
OFL_API bool _stdcall OListView_DeleteGroup(void* pListView,void* group)
{
	return ((WinListView*)pListView)->DeleteGroup((ListGroup*)group);
}

//删除所有的组(Vista)
OFL_API void _stdcall OListView_DeleteAllGroups(void* pListView)
{
	((WinListView*)pListView)->DeleteAllGroups();
}


OFL_API void _stdcall OListView_DestroyControl(void* pListView)
{
	((WinListView*)pListView)->DestroyControl();
}

OFL_API char* _stdcall OListView_GetClass(void* pListView)
{
	return (char*)((WinListView*)pListView)->GetClass();
}

OFL_API void _stdcall OListView_SetCaption(void* pListView,char* string)
{
	((WinListView*)pListView)->SetCaption(string);
}

OFL_API char* _stdcall OListView_GetCaption(void* pListView)
{
	return (char*)((WinListView*)pListView)->GetCaption();
}

OFL_API void _stdcall OListView_RedrawControl(void* pListView,bool redraw)
{
	((WinListView*)pListView)->RedrawControl(redraw);
}
