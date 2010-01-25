
#include "OWI_ImageList.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API int _stdcall OImageList_GetImageCount(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetImageCount();
}

OFL_API int _stdcall OImageList_GetImageWidth(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetImageWidth();
}

OFL_API int _stdcall OImageList_GetImageHeight(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetImageHeight();
}

OFL_API void _stdcall OImageList_SetBackColor(void* pImageList,unsigned int color)
{
	((WinImageList*)pImageList)->SetBackColor(color);
}

OFL_API unsigned int _stdcall OImageList_GetBackColor(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetBackColor();
}

OFL_API HIMAGELIST _stdcall OImageList_GetHandle(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetHandle();
}


//从位图文件或者可执行文件中装载位图																	 
OFL_API bool _stdcall OImageList_AddImageFromFile(void* pImageList,char* image)
{
	return ((WinImageList*)pImageList)->AddImageFromFile(image);
}

OFL_API bool _stdcall OImageList_AddImageFromFileMask(void* pImageList,char* image,char* maskImage)
{
	return ((WinImageList*)pImageList)->AddImageFromFile(image,maskImage);
}

OFL_API bool _stdcall OImageList_AddImageFromResource(void* pImageList,char* image,char* maskImage)
{
	return ((WinImageList*)pImageList)->AddImageFromResource(image,maskImage);
}

OFL_API bool _stdcall OImageList_AddImageFromResourceMask(void* pImageList,HMODULE module,char* image,char* maskImage)
{
	return ((WinImageList*)pImageList)->AddImageFromResource(module,image,maskImage);
}


//从图标文件或者可执行文件中装载图标
OFL_API bool _stdcall OImageList_AddIconFromFile(void* pImageList,char* icon)
{
	return ((WinImageList*)pImageList)->AddIconFromFile(icon);
}

OFL_API bool _stdcall OImageList_AddIconFromResourceName(void* pImageList,char* icon)
{
	return ((WinImageList*)pImageList)->AddIconFromResource(icon);
}

OFL_API bool _stdcall OImageList_AddIconFromResourceID(void* pImageList,int icon)
{
	return ((WinImageList*)pImageList)->AddIconFromResource(icon);
}

OFL_API bool _stdcall OImageList_AddIconFromModuleResourceName(void* pImageList,HMODULE module,char* icon)
{
	return ((WinImageList*)pImageList)->AddIconFromResource(module,icon);
}

OFL_API bool _stdcall OImageList_AddIconFromModuleResourceID(void* pImageList,HMODULE module,int icon)
{
	return ((WinImageList*)pImageList)->AddIconFromResource(module,icon);
}


//从光标文件或者可执行文件中装载光标
OFL_API bool _stdcall OImageList_AddCursorFromFile(void* pImageList,char* cursor)
{
	return ((WinImageList*)pImageList)->AddCursorFromFile(cursor);
}

OFL_API bool _stdcall OImageList_AddCursorFromResourceName(void* pImageList,char* cursor)
{
	return ((WinImageList*)pImageList)->AddCursorFromResource(cursor);
}

OFL_API bool _stdcall OImageList_AddCursorFromResourceID(void* pImageList,int cursor)
{
	return ((WinImageList*)pImageList)->AddCursorFromResource(cursor);
}

OFL_API bool _stdcall OImageList_AddCursorFromModuleResourceName(void* pImageList,HMODULE module,char* cursor)
{
	return ((WinImageList*)pImageList)->AddCursorFromResource(module,cursor);
}

OFL_API bool _stdcall OImageList_AddCursorFromModuleResourceID(void* pImageList,HMODULE module,int cursor)
{
	return ((WinImageList*)pImageList)->AddCursorFromResource(module,cursor);
}

//在ImageList中追加一个图标(ImageList维持图标句柄的副本，如果这个图标是通过调用LoadIcon得到，则图标不必调用者主动释放)
OFL_API int _stdcall OImageList_AddIcon(void* pImageList,HICON icon)
{
	return ((WinImageList*)pImageList)->AddIcon(icon);
}

OFL_API bool _stdcall OImageList_RemoveImage(void* pImageList,int index)
{
	return ((WinImageList*)pImageList)->RemoveImage(index);
}

OFL_API bool _stdcall OImageList_RemoveAll(void* pImageList)
{
	return ((WinImageList*)pImageList)->RemoveAll();
}

//提取位置为index的图标，用完之后，你需要调用DestroyIcon销毁它
OFL_API HICON _stdcall OImageList_CreateIcon(void* pImageList,int index)
{
	return ((WinImageList*)pImageList)->CreateIcon(index);
}

//设置指定的图标为覆盖图标。例如，可以指定索引为45的图标为覆盖图标，函数返回一个编号，这个编号
//在设置WinListView、WinTreeView的item覆盖图标时有用到
OFL_API int _stdcall OImageList_SetOverlay(void* pImageList,int image)
{
	return ((WinImageList*)pImageList)->SetOverlay(image);
}

OFL_API int _stdcall OImageList_GetLastOverlay(void* pImageList)
{
	return ((WinImageList*)pImageList)->GetLastOverlay();
}
