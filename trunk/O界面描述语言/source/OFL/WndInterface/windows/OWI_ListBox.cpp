
#include "OWI_ListBox.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall ListBox_SetSelect(void* pListBox,int index)
{
	((WinListBox*)pListBox)->SetSelect(index);
}

OFL_API int _stdcall ListBox_GetSelect(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetSelect();
}

OFL_API bool _stdcall ListBox_IsSelected(void* pListBox,int index)
{
	return ((WinListBox*)pListBox)->IsSelected(index);
}

OFL_API int _stdcall ListBox_GetSelectCount(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetSelectCount();
}

OFL_API char* _stdcall ListBox_GetItemText(void* pListBox,int index)
{
	return (char*)((WinListBox*)pListBox)->GetItemText(index);
}

OFL_API int _stdcall ListBox_GetItemCount(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetItemCount();
}

OFL_API void _stdcall ListBox_SetTextColor(void* pListBox,unsigned int color)
{
	((WinListBox*)pListBox)->SetTextColor(color);
}

OFL_API unsigned int _stdcall ListBox_GetTextColor(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetTextColor();
}

OFL_API void _stdcall ListBox_SetAnchorItem(void* pListBox,int index)
{
	((WinListBox*)pListBox)->SetAnchorItem(index);
}

OFL_API int _stdcall ListBox_GetAnchorItem(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetAnchorItem();
}

OFL_API void _stdcall ListBox_SetCaretItem(void* pListBox,int index)
{
	((WinListBox*)pListBox)->SetCaretItem(index);
}

OFL_API int _stdcall ListBox_GetCaretItem(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetCaretItem();
}

OFL_API void _stdcall ListBox_SetScrollWidth(void* pListBox,int width)
{
	((WinListBox*)pListBox)->SetScrollWidth(width);
}

OFL_API int _stdcall ListBox_GetScrollWidth(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetScrollWidth();
}

OFL_API void _stdcall ListBox_SetTopIndex(void* pListBox,int index)
{
	((WinListBox*)pListBox)->SetTopIndex(index);
}

OFL_API int _stdcall ListBox_GetTopIndex(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetTopIndex();
}

OFL_API void _stdcall ListBox_SetColumnWidth(void* pListBox,int width)
{
	((WinListBox*)pListBox)->SetColumnWidth(width);
}

OFL_API void _stdcall ListBox_SetItemHeight(void* pListBox,int index, int height)
{
	((WinListBox*)pListBox)->SetItemHeight(index,height);
}

OFL_API int _stdcall ListBox_GetItemHeight(void* pListBox,int index)
{
	return ((WinListBox*)pListBox)->GetItemHeight(index);
}

OFL_API void _stdcall ListBox_GetItemRect(void* pListBox,int index,RECT& rc)
{
	Rect rect = ((WinListBox*)pListBox)->GetItemRect(index);
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;
}

OFL_API void _stdcall ListBox_SetItemData(void* pListBox,int index,void* pData)
{
	((WinListBox*)pListBox)->SetItemData(index,pData);
}

OFL_API void _stdcall ListBox_SetLocale(void* pListBox,DWORD locale)
{
	((WinListBox*)pListBox)->SetLocale(locale);
}

OFL_API void* _stdcall ListBox_GetItemData(void* pListBox,int index)
{
	return ((WinListBox*)pListBox)->GetItemData(index);
}

OFL_API DWORD _stdcall ListBox_GetLocale(void* pListBox)
{
	return ((WinListBox*)pListBox)->GetLocale();
}


//在指定的Item索引之前插入一个新的Item，如果控件具有排序功能，则新加项不一定在指定位置插入，
//系统会进行排序
OFL_API int _stdcall ListBox_InsertItem(void* pListBox,char* string,int index)
{
	return ((WinListBox*)pListBox)->InsertItem(string,index);
}

//在尾部追加一个新的Item，函数返回新加项的索引，若发生错误，则返回-1。若控件有排序风格，Item
//不一定追加到尾部
OFL_API int _stdcall ListBox_AddItem(void* pListBox,char* string)
{
	return ((WinListBox*)pListBox)->AddItem(string);
}

//删除指定的Item
OFL_API void _stdcall ListBox_DeleteItem(void* pListBox,int index)
{
	((WinListBox*)pListBox)->DeleteItem(index);
}

//删除所有的Item
OFL_API void _stdcall ListBox_DeleteAllItems(void* pListBox)
{
	((WinListBox*)pListBox)->DeleteAllItems();
}

//找到文本以string开始的第一个Item，搜索操作从索引为index的item开始测试，直到尾部。若找不到匹配项，
//则从顶部开始继续搜索，直到索引为index之前Item。默认-1表示从第一个Item开始搜索。搜索失败，返回-1
OFL_API int _stdcall ListBox_FindItem(void* pListBox,char* string, int index)
{
	return ((WinListBox*)pListBox)->FindItem(string,index);
}

//找到文本正好为string的第一个Item，注意搜索操作不是大小写敏感的。index的含义以及返回值的含义可参考
//FindItem()的注释说明
OFL_API int _stdcall ListBox_FindItemExact(void* pListBox,char* string, int index)
{
	return ((WinListBox*)pListBox)->FindItemExact(string,index);
}

//对于单选风格的ListBox，选择文本以string开始的第一个Item，index的含义请参考FindItem()的注释说明。返
//回值说明了被选中的Item，若其值为-1，则没有找到匹配项；如果找到了有效匹配，控件还会滚动，使之可见。匹
//配过程是大小写无关的。
OFL_API int _stdcall ListBox_SelectString(void* pListBox,char* string, int index)
{
	return  ((WinListBox*)pListBox)->SelectString(string,index);
}

//对于多选风格的ListBox，若select为true，选择索引为index的Item；若select为false，则此Item被取消选择
OFL_API void _stdcall ListBox_SelectSingle(void* pListBox,int index, bool select)
{
	((WinListBox*)pListBox)->SelectSingle(index,select);
}

//对于多选风格的ListBox，若select为true，选中所有Item；若select为false，所有Item被取消选择
OFL_API void _stdcall ListBox_SelectAll(void* pListBox,bool select)
{
	((WinListBox*)pListBox)->SelectAll(select);
}

//对于多选风格的ListBox，此函数填充所有高亮选择的item的索引到buffer数组中，number指定数组的元素数目
//函数返回实际填充到数组中的元素数目		 
OFL_API int _stdcall ListBox_GetSelectArray(void* pListBox,int number,int* buffer)
{
	return ((WinListBox*)pListBox)->GetSelectArray(number,buffer);
}

//对于多选风格的ListBox，选择一组索引范围从first到last的Item，返回值指明操作是否成功
OFL_API bool _stdcall ListBox_SelectRange(void* pListBox,int first,int last)
{
	return ((WinListBox*)pListBox)->SelectRange(first,last);
}

//对于多选风格的ListBox，取消被选中的一组范围从first到last的Item，返回值指明操作是否成功
OFL_API bool _stdcall ListBox_CancelRange(void* pListBox,int first,int last)
{
	return ((WinListBox*)pListBox)->CancelRange(first,last);
}

//获取离坐标(x,y)最近的Item，坐标相对于ListBox的客户区原点
OFL_API int _stdcall ListBox_GetNearestItem(void* pListBox,int x,int y)
{
	return ((WinListBox*)pListBox)->GetNearestItem(x,y);
}

//获取坐标(x,y)之下的Item，坐标相对于ListBox的客户区原点
OFL_API int _stdcall ListBox_GetItemFromPoint(void* pListBox,int x,int y)
{
	return ((WinListBox*)pListBox)->GetItemFromPoint(x,y);
}


OFL_API void _stdcall ListBox_DestroyControl(void* pListBox)
{
	((WinListBox*)pListBox)->DestroyControl();
}

OFL_API char* _stdcall ListBox_GetClass(void* pListBox)
{
	return (char*)((WinListBox*)pListBox)->GetClass();
}

OFL_API char* _stdcall ListBox_GetCaption(void* pListBox)
{
	return (char*)((WinListBox*)pListBox)->GetCaption();
}

OFL_API void _stdcall ListBox_SetCaption(void* pListBox,char* string)
{
	((WinListBox*)pListBox)->SetCaption(string);
}
