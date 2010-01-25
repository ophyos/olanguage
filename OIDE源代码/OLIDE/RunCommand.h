
#ifndef _RUN_COMMAND_H_
#define _RUN_COMMAND_H_

#ifndef MAX_COMMAND_LINE
#define MAX_COMMAND_LINE 1024
#endif

#ifndef MainWndOutputMsg
#include "MainFrm.h"
#define MainWndOutputMsg ((CMainFrame*)AfxGetMainWnd())->OutPutMsg
#endif

enum RUN_COMMAND_TYPE
{
	RCT_NULL,
	RCT_BUILD_CODE,
	RCT_LINK_OBJ,
	RCT_COMPILE_RES,
	RCT_DOASM,
};

CString GetTitleFromPathName(const CString& strPathName);
CString GetShortPath(const CString& strLongFileName); //用来将长路径名转化为短路径名
DWORD RunCommand(TCHAR* pchCmdLine,int nCommandType = 0,bool bHideWnd = true);	
void RunProgramme(const CString& strProgrammeName);
void AddPathSYH(CString& strPath);
bool FileExist(const CString& strFileName,bool bDirectory = false);

#endif //_RUN_COMMAND_H_