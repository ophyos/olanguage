#ifndef _O_FACE_LANGUAGE_H_
#define _O_FACE_LANGUAGE_H_

#include "ExportDefine.h"

//用默认语种进行初始化 nLanguageType < 0时不加载语言内码 
//nLanguageType == 0 时使用默认语言文件进行初始化
OFL_API bool _stdcall  OFDefaultInit(int nLanguageType);
OFL_API bool _stdcall  OFLoadDefaultLanguage(int nLanguageType); //加载默认语言内码
OFL_API bool _stdcall  OFInit(char* pchAppDir,char* pchLanguageFile); //使用指定的语言文件进行初始化
OFL_API void _stdcall  OFClear(); //解析完进行清理
OFL_API bool _stdcall  OFAddFunction(char* pchFunctionName,void* pfun); //添加函数
OFL_API bool _stdcall  OFParse(char* pchScriptFileName,int nShowError); //解析代码文件
//解析字符串pchFileName是字符串所在的文件或者是块名称,nRelativeLine字符串在文件中的行起始行,用于提示错误行号
OFL_API bool _stdcall  OFParseString(char* pchScriptString,char* pchFileName,int nShowError,int nRelativeLine,bool bNoSearchFunction); 
OFL_API char* _stdcall OFGetParseText();
OFL_API void _stdcall  OFFreeMem(char* p);

OFL_API void* _stdcall OFShowMainWnd(char* pchWndName); //显示主窗口,窗口显示后会调用消息循环
OFL_API void* _stdcall OFShowWnd(char* pchWndName,void* pParentWnd); //显示一般窗口,pParentWnd为父窗口指针
OFL_API void* _stdcall OFGetControl(char* pchControlName); //使用名称来获取控件(包括窗口)

#define AddInterfaceFunction(fun_name) OFAddFunction(#fun_name,fun_name);

//控件接口
#include "./WndInterface/WndInterface.h"

#endif //_O_FACE_LANGUAGE_H_