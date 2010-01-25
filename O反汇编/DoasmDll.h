
#ifndef _DOASM_DLL_H_
#define _DOASM_DLL_H_


// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DOASMDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DOASMDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DOASMDLL_EXPORTS
#define DOASMDLL_API extern "C"__declspec(dllexport)
#else
#define DOASMDLL_API extern "C" __declspec(dllimport)
#endif


DOASMDLL_API int   doi_LoadLanguageFile(char* pchLanguageFile);
DOASMDLL_API int   doi_GetLanguageType();
DOASMDLL_API void  doi_DoasmInit(unsigned char* puchCode,unsigned int uiLength,unsigned int ui_image_base);
DOASMDLL_API unsigned int doi_GetDoasmDataCurPos();
DOASMDLL_API void doi_GetDoasmExternAddr(unsigned int& unExternAddr,int& nExternAddrType);
DOASMDLL_API void doi_SetDoasmExternAddr(unsigned int unExternAddr,int nExternAddrType);

DOASMDLL_API int   doi_DoasmBegin(char* pchLanguageFile,unsigned char* puchCode,unsigned int uiLength,unsigned int ui_image_base);
DOASMDLL_API void  doi_DoasmData(char* pchInsnText);
DOASMDLL_API bool  doi_isEnd();


#endif //_DOASM_DLL_H_