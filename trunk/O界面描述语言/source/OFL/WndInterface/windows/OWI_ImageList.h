
#ifndef _OWI_IMAGELIST_H_
#define _OWI_IMAGELIST_H_

#include "../../ExportDefine.h"
#include <Windows.h>
#include <CommCtrl.h>

//bool CreateImageList(ImageBitType type,bool useMask,int width,int height);
//bool CreateLargeImageList(ImageBitType type,bool useMask);
//bool CreateSmallImageList(ImageBitType type,bool useMask);
//void DestroyImageList();

OFL_API int _stdcall OImageList_GetImageCount(void* pImageList);   
OFL_API int _stdcall OImageList_GetImageWidth(void* pImageList);
OFL_API int _stdcall OImageList_GetImageHeight(void* pImageList);   
OFL_API void _stdcall OImageList_SetBackColor(void* pImageList,unsigned int color);
OFL_API unsigned int _stdcall OImageList_GetBackColor(void* pImageList); 
OFL_API HIMAGELIST _stdcall OImageList_GetHandle(void* pImageList);

//从位图文件或者可执行文件中装载位图																	 
OFL_API bool _stdcall OImageList_AddImageFromFile(void* pImageList,char* image);
OFL_API bool _stdcall OImageList_AddImageFromFileMask(void* pImageList,char* image,char* maskImage);
OFL_API bool _stdcall OImageList_AddImageFromResource(void* pImageList,char* image,char* maskImage = NULL);
OFL_API bool _stdcall OImageList_AddImageFromResourceMask(void* pImageList,HMODULE module,char* image,char* maskImage = NULL);

//从图标文件或者可执行文件中装载图标
OFL_API bool _stdcall OImageList_AddIconFromFile(void* pImageList,char* icon);
OFL_API bool _stdcall OImageList_AddIconFromResourceName(void* pImageList,char* icon);
OFL_API bool _stdcall OImageList_AddIconFromResourceID(void* pImageList,int icon);
OFL_API bool _stdcall OImageList_AddIconFromModuleResourceName(void* pImageList,HMODULE module,char* icon);
OFL_API bool _stdcall OImageList_AddIconFromModuleResourceID(void* pImageList,HMODULE module,int icon);

//从光标文件或者可执行文件中装载光标
OFL_API bool _stdcall OImageList_AddCursorFromFile(void* pImageList,char* cursor);
OFL_API bool _stdcall OImageList_AddCursorFromResourceName(void* pImageList,char* cursor);
OFL_API bool _stdcall OImageList_AddCursorFromResourceID(void* pImageList,int cursor);
OFL_API bool _stdcall OImageList_AddCursorFromModuleResourceName(void* pImageList,HMODULE module,char* cursor);
OFL_API bool _stdcall OImageList_AddCursorFromModuleResourceID(void* pImageList,HMODULE module,int cursor);
//在ImageList中追加一个图标(ImageList维持图标句柄的副本，如果这个图标是通过调用LoadIcon得到，则图标不必调用者主动释放)
OFL_API int _stdcall OImageList_AddIcon(void* pImageList,HICON icon);
OFL_API bool _stdcall OImageList_RemoveImage(void* pImageList,int index);
OFL_API bool _stdcall OImageList_RemoveAll(void* pImageList);
//提取位置为index的图标，用完之后，你需要调用DestroyIcon销毁它
OFL_API HICON _stdcall OImageList_CreateIcon(void* pImageList,int index);
//设置指定的图标为覆盖图标。例如，可以指定索引为45的图标为覆盖图标，函数返回一个编号，这个编号
//在设置WinListView、WinTreeView的item覆盖图标时有用到
OFL_API int _stdcall OImageList_SetOverlay(void* pImageList,int image);
OFL_API int _stdcall OImageList_GetLastOverlay(void* pImageList);

#endif //_OWI_IMAGELIST_H_