
#include "OWI_ComboBox.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API int _stdcall ComboBox_GetCount(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetCount();
}

OFL_API int _stdcall ComboBox_GetItemHeight(void* pComboBox,int index)
{
	return ((WinComboBox*)pComboBox)->GetItemHeight(index);
}

OFL_API void _stdcall ComboBox_SetItemHeight(void* pComboBox,int index, int height)
{
	((WinComboBox*)pComboBox)->SetItemHeight(index,height);
}

OFL_API void _stdcall ComboBox_SetSelect(void* pComboBox,int index)
{
	((WinComboBox*)pComboBox)->SetSelect(index);
}

OFL_API int _stdcall ComboBox_GetSelect(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetSelect();
}

OFL_API void _stdcall ComboBox_SetSelectStart(void* pComboBox,int start)
{
	((WinComboBox*)pComboBox)->SetSelectStart(start);
}

OFL_API int _stdcall ComboBox_GetSelectStart(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetSelectStart();
}

OFL_API void _stdcall ComboBox_SetSelectEnd(void* pComboBox,int end)
{
	((WinComboBox*)pComboBox)->SetSelectEnd(end);
}

OFL_API int _stdcall ComboBox_GetSelectEnd(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetSelectEnd();
}

OFL_API void _stdcall ComboBox_SetTopIndex(void* pComboBox,int index)
{
	((WinComboBox*)pComboBox)->SetTopIndex(index);
}

OFL_API int _stdcall ComboBox_GetTopIndex(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetTopIndex();
}

OFL_API void _stdcall ComboBox_SetTextLimit(void* pComboBox,int length)
{
	((WinComboBox*)pComboBox)->SetTextLimit(length);
}

OFL_API int _stdcall ComboBox_GetItemTextLength(void* pComboBox,int index)
{
	return ((WinComboBox*)pComboBox)->GetItemTextLength(index);
}

OFL_API void _stdcall ComboBox_ShowDropdownList(void* pComboBox,bool show)
{
	((WinComboBox*)pComboBox)->ShowDropdownList(show);
}

OFL_API bool _stdcall ComboBox_IsDropdownListVisible(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->IsDropdownListVisible();
}

OFL_API int _stdcall ComboBox_GetDropdownListWidth(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetDropdownListWidth();
}

OFL_API void _stdcall ComboBox_SetDropdownListWidth(void* pComboBox,int width)
{
	((WinComboBox*)pComboBox)->SetDropdownListWidth(width);
}

OFL_API void _stdcall ComboBox_GetDropdownListRect(void* pComboBox,RECT& rc)
{
	Rect rect = ((WinComboBox*)pComboBox)->GetDropdownListRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}

OFL_API void _stdcall ComboBox_SetScrollWidth(void* pComboBox,int width)
{
	((WinComboBox*)pComboBox)->SetScrollWidth(width);
}

OFL_API int _stdcall ComboBox_GetScrollWidth(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetScrollWidth();
}

OFL_API void _stdcall ComboBox_SetExtendedUI(void* pComboBox,bool eui)
{
	((WinComboBox*)pComboBox)->SetExtendedUI(eui);
}

OFL_API bool _stdcall ComboBox_GetExtendedUI(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetExtendedUI();
}

OFL_API void _stdcall ComboBox_SetLocale(void* pComboBox,DWORD locale)
{
	((WinComboBox*)pComboBox)->SetLocale(locale);
}

OFL_API void _stdcall ComboBox_SetItemData(void* pComboBox,int index,void* data)
{
	((WinComboBox*)pComboBox)->SetItemData(index,data);
}

OFL_API void* _stdcall ComboBox_GetItemData(void* pComboBox,int index)
{
	return ((WinComboBox*)pComboBox)->GetItemData(index);
}

OFL_API DWORD _stdcall ComboBox_GetLocale(void* pComboBox)
{
	return ((WinComboBox*)pComboBox)->GetLocale();
}


//在ComboBox列表中指定的位置插入一个Item
OFL_API int _stdcall ComboBox_InsertItem(void* pComboBox,char* string,int index)
{
	return ((WinComboBox*)pComboBox)->InsertItem(string,index);
}

//在ComboBox列表的尾部追加一个Item
OFL_API int _stdcall ComboBox_AddItem(void* pComboBox,char* string)
{
	return ((WinComboBox*)pComboBox)->AddItem(string);
}

//删除指定的Item
OFL_API bool _stdcall ComboBox_DeleteItem(void* pComboBox,int index)
{
	return ((WinComboBox*)pComboBox)->DeleteItem(index);
}

//删除所有Item
OFL_API void _stdcall ComboBox_DeleteAllItems(void* pComboBox)
{
	((WinComboBox*)pComboBox)->DeleteAllItems();
}

//获取指定Item的文本
OFL_API char* _stdcall ComboBox_GetItemText(void* pComboBox,int index)
{
	return  (char*)((WinComboBox*)pComboBox)->GetItemText(index);
}

//如果某一项从第一个字符开始匹配string(注意：大小写不敏感)，将返回这个项的索引
OFL_API int _stdcall ComboBox_FindItem(void* pComboBox,char* string)
{
	return ((WinComboBox*)pComboBox)->FindItem(string);
}

//如果某一项完全相同于string(注意：大小写不敏感)，将返回这一项的索引，否则返回-1
OFL_API int _stdcall ComboBox_FindItemExact(void* pComboBox,char* string)
{
	return ((WinComboBox*)pComboBox)->FindItemExact(string);
}

//选择起始文本为string的Item，返回被选中Item的索引，若无法完成匹配，则返回-1
OFL_API int _stdcall ComboBox_SelectString(void* pComboBox,char* string)
{
	return ((WinComboBox*)pComboBox)->SelectString(string);
}

//对于风格为SimpleStyle和TextStyle的ComboBox，设置其编辑控件中文本的选择范围。
//若start为-1，会清除被选中文本的高亮选择状态；若end为-1，则编辑控件中所有文本都会被选中。
OFL_API void _stdcall ComboBox_SetEditSelect(void* pComboBox,int start, int end)
{
	((WinComboBox*)pComboBox)->SetEditSelect(start,end);
}

OFL_API void _stdcall ComboBox_DestroyControl(void* pComboBox)
{
	((WinComboBox*)pComboBox)->DestroyControl();
}

OFL_API char* _stdcall ComboBox_GetClass(void* pComboBox)
{
	return (char*)((WinComboBox*)pComboBox)->GetClass();
}

OFL_API void _stdcall ComboBox_SetCaption(void* pComboBox,char* string)
{
	((WinComboBox*)pComboBox)->SetCaption(string);
}

OFL_API char* _stdcall ComboBox_GetCaption(void* pComboBox)
{
	return (char*)((WinComboBox*)pComboBox)->GetCaption();
}
