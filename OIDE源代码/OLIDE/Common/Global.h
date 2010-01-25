
#ifndef _OL_IDE_GLOBAL_H_
#define _OL_IDE_GLOBAL_H_

//自定义消息


//定义添加新项类型
enum NEW_ITEM_TYPE
{
	NEW_ITEM_TYPE_NULL                    =    NULL,
	NEW_ITEM_TYPE_SOLUCTION               =    100,
	NEW_ITEM_TYPE_PROJECT_WIN32_WINDOWS   =    101,
	NEW_ITEM_TYPE_PROJECT_WIN32_CONSOLE   =    102,
	NEW_ITEM_TYPE_PROJECT_WIN32_DLL       =    103,
	NEW_ITEM_TYPE_PROJECT_WIN32_LIB       =    104,
	NEW_ITEM_TYPE_PROJECT_OML_CODE_FILE   =    105,
	NEW_ITEM_TYPE_PROJECT_OML_HEAD_FILE   =    106,
	NEW_ITEM_TYPE_PROJECT_OASM_CODE_FILE  =    107,
	NEW_ITEM_TYPE_PROJECT_OASM_HEAD_FILE  =    108,
};


//错误代码定义
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_OPEN_FILE_NAME_EMPTY                               = -10000;  //打开O语言文件时文件名为空
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_OPEN_OPEN_FILE_FAIL                                = -10001;  //打开O语言文件时打开文件失败
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_OPEN_LOAD_XML_FILE_FAIL                            = -10002;  //打开O语言文件时加载XML文件失败
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_OPEN_OLANGUAGE_FILE_INVALID                        = -10003;  //打开O语言文件时O语言文件非法
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_ADD_PROJECT_TO_SOLUTION_GET_RELATIVE_PATH_FAIL     = -10004;  //添加工程到方案时得到工程文件相对于方案文件的相对路径失败
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_ADD_OBJECT_FILE_TO_PROJECT_GET_RELATIVE_PATH_FAIL  = -10005;  //添加对象文件到工程时得到对象文件相对于工程文件的相对路径失败
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_GET_OBJECT_FROM_SOLUTION_GET_ABSOLUTE_PATH_FAIL    = -10006;  //从方案文件中得到工程时将相对于方案文件名的工程文件名转换成绝对工程文件名时失败
const int ERROR_OVS_MANAGER_OLANGUAGE_FILE_GET_FILE_FROM_PROJECT_GET_ABSOLUTE_PATH_FAIL       = -10007;  //从工程文件中得到文件时将相对于工程文件名的文件名转换成绝对文件名时失败

//全局函数

bool FileExist(const TCHAR* pchFileName,bool bDirectory=false);
bool GetRelativePath(const CString& strFirstPath,CString& strSecondPath);
bool GetAbsolutePath(const CString& strFirstFileName,CString& strSecondFileName);
bool IsRelativePath(const CString& strPath);
//CString GetTitleFromPathName(const CString& strPathName);
CString GetPathFromPathName(const CString& strPathName);
CString GetFileExternName(const CString& strFileName);
CString GetFileNameFromPathName(const CString& strPathName,BOOL bContainExtendName=TRUE);
void CreateDepthDirectory(const CString& strDirectory);
bool FileRename(const TCHAR* pchOldName, const TCHAR* pchNewName);
BOOL DeleteFolderOrFile(LPCTSTR pszPath, BOOL bDelete/*=FALSE*/);
int  CopyFloderOrFile(LPCTSTR lpszPathFrom,LPCTSTR lpszPathTo,BOOL bMove = FALSE);

int  GetOSVersion(void);

#endif //_OL_IDE_GLOBAL_H_