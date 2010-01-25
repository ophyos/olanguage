
#include "stdafx.h"
#include "RunCommand.h"
#include "MainFrm.h"
#include "./Common/Common.h"

#ifndef MainWndOutputMsg
#define MainWndOutputMsg ((CMainFrame*)AfxGetMainWnd())->OutPutMsg
#endif

CString GetTitleFromPathName(const CString& strPathName)
{
	CString strTemp = strPathName;

	int index1 = strTemp.ReverseFind( _T('\\') );
	int index2 = strTemp.ReverseFind( _T('.') );

	if( index2 > -1 && index2 > index1 )
		strTemp = strTemp.Left(index2);

	return strTemp;
}

CString GetShortPath(const CString& strLongFileName) //用来将长路径名转化为短路径名
{ 
	TCHAR strBuffer[_MAX_PATH]; 

	GetShortPathName(strLongFileName,strBuffer,_MAX_PATH); 

	CString strTemp(strBuffer);

	return strTemp; 
} 

//执行CMD命令
DWORD RunCommand(TCHAR* pchCmdLine,int nCommandType,bool bHideWnd)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;

	//创建管道
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) 
	{
		return -1;
	} 

	//创建子进程
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si); 
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	if(bHideWnd)si.wShowWindow = SW_HIDE; //隐藏窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	if (!CreateProcess(NULL,pchCmdLine,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) 
	{			
		return -1;
	}

	//关闭写管道句柄
	CloseHandle(hWrite);

	//读取管道数据直到子程序结束
	char buffer[4097] = {0};
	DWORD bytesRead;
	CString strMessage;	
	while(true) 
	{
		//延迟80毫秒
		DelayNop(80);

		if((ReadFile(hRead,buffer,4096,&bytesRead,NULL) == NULL) || (bytesRead == 0))
			break;

		buffer[bytesRead] = 0;

#ifdef _UNICODE
		strMessage = buffer; //UNICODE版本这是必须的，会自动转化成宽字符
		MainWndOutputMsg(_T("%s"),strMessage);
#else
		MainWndOutputMsg(_T("%s"),buffer);
#endif
	}

	//获得程序返回值
	DWORD   dwExitCode = 0;
	GetExitCodeProcess(pi.hProcess,&dwExitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return dwExitCode;
}

void RunProgramme(const CString& strProgrammeName)
{
	if(!FileExist(strProgrammeName))
	{
		MainWndOutputMsg(_T("启动程序失败：程序 %s 不存在\n"),strProgrammeName);
		return ;
	}

	MainWndOutputMsg(_T("正在启动 %s 程序\n"),strProgrammeName);

	STARTUPINFO si={sizeof(si)};
	si.dwFlags =STARTF_USESHOWWINDOW;
	si.wShowWindow = (unsigned short)SW_SHOW;
	PROCESS_INFORMATION pi={0};

	CreateProcess(strProgrammeName,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

//添加路径双引号
void AddPathSYH(CString& strPath)
{
	CString strTemp;
	strTemp = _T('"');
	strTemp += strPath;
	strTemp += _T('"');

	strPath = strTemp;
}

//测试文件是否存在
bool FileExist(const CString& strFileName,bool bDirectory)
{
	bool bExist = false;
	WIN32_FIND_DATA fd; 
	HANDLE hFind = FindFirstFile(strFileName, &fd);
	//如果不存在
	if (hFind == INVALID_HANDLE_VALUE) 
	{ 
		bExist = false;
	}
	//如果是目录
	else if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if(bDirectory)
		{
			bExist = true;
		}
		else
		{
			bExist = false;
		}
	}
	else
	{
		bExist = true;
	}

	FindClose(hFind);

	return bExist;
}