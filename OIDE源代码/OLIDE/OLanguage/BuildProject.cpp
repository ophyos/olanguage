#include "StdAfx.h"
#include ".\buildproject.h"
#include ".\olinterface.h"

#include "..\MainFrm.h"
#include "..\OLVisualStudioGlobal.h"

#define MAX_COMMAND_LINE 1024 //命令行最大长度

void OutPutMessage(LPCTSTR lpText)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame->GetSafeHwnd())
	{
		pMainFrame->OutPutMessage(lpText);
	}
}

CString& GetAppPathName()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMainFrame->GetSafeHwnd());

	return pMainFrame->GetAppPathName();
}

//执行CMD命令
void RunCommand(char* pchCmdLine,const CString& strMsgFileName,bool bHideWnd)
{
	//如果重定向输出文件名为空则按默认方式输出到控制台
	bool bOutputToFile = false;
	if(!strMsgFileName.IsEmpty())
	{
		bOutputToFile = true;
	}

	SECURITY_ATTRIBUTES sa={sizeof(sa),NULL,TRUE};
	SECURITY_ATTRIBUTES *psa=NULL;
	DWORD dwShareMode=FILE_SHARE_READ|FILE_SHARE_WRITE; 
	OSVERSIONINFO osVersion={0};
	osVersion.dwOSVersionInfoSize =sizeof(osVersion);
	if(GetVersionEx(&osVersion))
	{
		//根据版本设置共享模式和安全属性 
		if(osVersion.dwPlatformId >= VER_PLATFORM_WIN32_NT)
		{ 
			psa=&sa; 
			dwShareMode|=FILE_SHARE_DELETE;
		}
	}

	STARTUPINFO s={sizeof(s)}; 

	HANDLE hConsoleRedirect = NULL;
	if(bOutputToFile)
	{
		//创建临时文件
		hConsoleRedirect=CreateFile( 
			strMsgFileName, 
			GENERIC_WRITE, 
			dwShareMode, 
			psa, 
			OPEN_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL); 
		assert(hConsoleRedirect!=INVALID_HANDLE_VALUE);

		SetEndOfFile(hConsoleRedirect);

		s.hStdOutput =hConsoleRedirect;//将文件作为标准输出句柄 
	}

	//使用标准柄和显示窗口 
	s.dwFlags =STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES; 

	//隐藏控制台窗口
	if(bHideWnd)
	{
		s.wShowWindow =SW_HIDE; 
	}

	PROCESS_INFORMATION pi={0}; 
	//创建进程,执行程序
	if(CreateProcess(NULL,pchCmdLine,NULL,NULL,TRUE,NULL,NULL,NULL,&s,&pi))
	{ 
		//等待进程执行完毕 
		WaitForSingleObject(pi.hProcess ,INFINITE); 

		//关闭进程和主线程句柄 
		CloseHandle(pi.hProcess ); 
		CloseHandle(pi.hThread ); 
	}

	//关闭控制台定向输出文件句柄 
	if(bOutputToFile)
	{
		CloseHandle(hConsoleRedirect);
	}	
}

//编译目标代码生成obj文件
void BuildAsmToObjectCode(const CString& strAsmFileName,int nAssemblerType)
{
	//如果是MASM汇编
	if(nAssemblerType == OCT_MASM)
	{
		CString strBin,strAssemblerPathName,strIncludePath,strCmdOutPutFile;
		strBin = GetPathFromPathName(GetAppPathName());
		strBin += _T("bin\\MASM\\");
		strAssemblerPathName = strBin +  _T("ML.EXE");
		strIncludePath =  strBin +  _T("INCLUDE");

		//得到汇编文件路径
		CString strAssembleFilePath = GetPathFromPathName(strAsmFileName);
		strCmdOutPutFile = strAssembleFilePath + _T("~OLOUTPUT.TXT");

		CString strParam;
		strParam.Format("/Fo \"%s\\\" /coff /c /I \"%s\"",strAssembleFilePath,strIncludePath);

		char cmdLine[MAX_COMMAND_LINE];
		memset(cmdLine,0,MAX_COMMAND_LINE);
		wsprintf(cmdLine,"\"%s\" %s \"%s\"",strAssemblerPathName,strParam,strAsmFileName);

		//删除临时文件
		//DeleteFile(strTemp);

		RunCommand(cmdLine,strCmdOutPutFile,true);

		CStdioFile fileOutPut;
		CString strTemp;
		if(fileOutPut.Open(strCmdOutPutFile, CFile::modeRead | CFile::typeText))
		{
			while(fileOutPut.ReadString(strTemp))
			{
				//过滤掉汇编提示
				if(strTemp.Find(" Assembling: ") == 0)
					continue;

				OutPutMessage("\n");
				OutPutMessage(strTemp);
			}

			fileOutPut.Close();
		}

		return ;
	}

	//如果是NASM汇编
	if(nAssemblerType == OCT_NASM)
	{
		CString strBin,strAssemblerPathName,strIncludePath,strCmdOutPutFile;
		strBin = GetPathFromPathName(GetAppPathName());
		strBin += _T("bin\\NASM\\");

		strAssemblerPathName = strBin +  _T("nasmw.exe"); //NASM程序
		strIncludePath =  strBin +  _T("INCLUDE\\"); //包含文件路径
		strCmdOutPutFile = strBin + _T("~NLOUTPUT.TXT"); //错误输出文件

		//-f　参数输出目标文件类型
		//-i　包含路径
		//-E  错误输出文件
		CString strTemp;
		strTemp.Format("-f obj -i \"%s\" -E \"%s\"",strIncludePath,strCmdOutPutFile);

		char cmdLine[MAX_COMMAND_LINE];
		memset(cmdLine,0,MAX_COMMAND_LINE);
		wsprintf(cmdLine,"%s %s %s",strAssemblerPathName,strTemp,strAsmFileName);

		//删除临时文件
		//DeleteFile(strTemp);

		RunCommand(cmdLine,strCmdOutPutFile,true);

		CStdioFile fileOutPut;
		if(fileOutPut.Open(strCmdOutPutFile, CFile::modeRead | CFile::typeText) ) 
		{
			while(fileOutPut.ReadString(strTemp))
			{
				OutPutMessage("\n");
				OutPutMessage(strTemp);
			}

			fileOutPut.Close();
		}

		return;
	}    

	//如果是OASM汇编
	if(nAssemblerType == OCT_OASM)
	{
		return;
	}
}

void LinkObjectCode(const CString& strProjectFileName)
{
	//通过工程文件名称得到工程属性结点
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMainFrame->GetSafeHwnd());
	HTREEITEM hItemProject = pMainFrame->GetProjectItemFromProjectFileName(strProjectFileName);
	CProjectProperty* pProjectProperty = pMainFrame->GetProjectProperty(hItemProject);
	ASSERT(pProjectProperty);

	CString strOutPutFloder = pProjectProperty->GetProjectAbsolutePathOutPut();
	CString strProgramFileName = pProjectProperty->GetProjectAbsolutePathOutPutFileName();

	//如果是MASM汇编
	if(pProjectProperty->m_nAssemblerType == OCT_MASM)
	{
		CString strParamFile = strOutPutFloder + "ol.olp";
				
		CString strBin,strLinkerPathName,strLibPath,strSubSystem;
		strBin = GetPathFromPathName(GetAppPathName());
		strBin += _T("bin\\MASM\\");
		strLinkerPathName = strBin +  _T("LINK.EXE");
		strLibPath = strBin + _T("LIB");

		if(pProjectProperty->m_nProgramType == CProjectProperty::PROGRAM_TYPE::PT_CONSOL)
		{
			strSubSystem = _T("CONSOLE");
		}
		else
		{
			strSubSystem = _T("WINDOWS");
		}

		CString strParam;
		strParam.Format("/SUBSYSTEM:%s /LIBPATH:\"%s\" /OUT:\"%s\" /NOLOGO",strSubSystem,strLibPath,strProgramFileName);
		
		//删除原有的执行文件
		DeleteFile(strProgramFileName);

		//执行链接命令
		char cmdLine[MAX_COMMAND_LINE];
		memset(cmdLine,0,MAX_COMMAND_LINE);
		wsprintf(cmdLine,"\"%s\" %s @\"%s\"",strLinkerPathName,strParam,strParamFile);

		CString strCmdOutPutFile = strOutPutFloder + _T("~OLOUTPUT.TXT");

		//删除临时文件
		//DeleteFile(strCmdOutPutFile);

		RunCommand(cmdLine,strCmdOutPutFile,true);

		////如果执行文件存在则表示编译成功
		//FileExist(strProgramFileName);

		//输出链接信息
		CStdioFile fileOutPut;
		if(fileOutPut.Open( strCmdOutPutFile, CFile::modeRead | CFile::typeText) ) 
		{
			while(fileOutPut.ReadString(strCmdOutPutFile))
			{
				OutPutMessage("\n");
				OutPutMessage(strCmdOutPutFile);
			}

			fileOutPut.Close();
		}
	}

	//如果是NASM汇编
	if(pProjectProperty->m_nAssemblerType == OCT_NASM)
	{
		//return strProgramFileName;
	}

	//如果是OASM汇编
	if(pProjectProperty->m_nAssemblerType == OCT_OASM)
	{
		//return strProgramFileName;
	}
}

void BuildCmdInterface(int nCmdType,const char* pchValue,int nValue)
{
	switch(nCmdType)
	{
		//输出文本
	case BICT_OUTPUT:
		OutPutMessage(pchValue);
		break;
		//编译代码
	case BICT_BUILD_CODE:
		BuildAsmToObjectCode(pchValue,nValue);
		break;
		//链接生成执行文件
	case BICT_LINK_EXE:
		LinkObjectCode(pchValue);
		break;
	default:
		break;
	}
}

CBuildProject::CBuildProject(void)
{
}

CBuildProject::~CBuildProject(void)
{
}

void CBuildProject::BuildProject(CProjectProperty* pProjectProperty)
{	
	CString strMessage;
	strMessage.Format("\n开始编译工程：%s ...",pProjectProperty->m_strProjectName);
	OutPutMessage(strMessage);

	//创建工程输出目录
	CString strOutPutFloder = pProjectProperty->GetProjectAbsolutePathOutPut();
	CreateDepthDirectory(strOutPutFloder);

	//创建输出程序文件目录
	CString strProgramFileName = pProjectProperty->GetProjectAbsolutePathOutPutFileName();
	CreateDepthDirectory(strProgramFileName);

	//编译工程
	Build(pProjectProperty->m_strProjectFilePath);

	////如果代码解析有错误，则输出错误
	//if(CErrorTableOper::GetErrorCount() > 0)
	//{
	//	OutPutError();
	//}
	////否则链接生成可执行文件
	//else
	//{
	//	strMessage.Format("\n正在链接目标文件...",strProgramFileName);
	//	OutPutMessage(strMessage);

	//	//链接OBJ文件生成EXE执行文件
	//	if(LinkObjectCode(strOutPutFloder,strProgramFileName,pProjectProperty))
	//	{
	//		strMessage.Format("\n生成程序：%s",strProgramFileName);
	//		OutPutMessage(strMessage);
	//	}
	//	else
	//	{
	//		strMessage.Format("\n链接执行文件失败");
	//		OutPutMessage(strMessage);
	//	}
	//}	

	strMessage.Format("\n%s 工程编译结束",pProjectProperty->m_strProjectName);
	OutPutMessage(strMessage);
}

void CBuildProject::Build(const char* pchFileName)
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	BUILDPROJECT lpfnBuildProject = (BUILDPROJECT)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceBuildProject");
	if(lpfnBuildProject == NULL)
		return ;

	lpfnBuildProject(pchFileName,BuildCmdInterface);
}

//#include "./errortableoper.h"
//
//void CBuildProject::OutPutError()
//{
//	CSysErrorAttr* pSysErrorAttr = NULL;
//	for(SYS_ERROR_POSITION posSysError = CErrorTableOper::GetFirstSysError();posSysError != CErrorTableOper::GetEndSysError();++posSysError)
//	{
//		CErrorInfo errorInfo;
//		CErrorTableOper::GetSysErrorAttr(posSysError,errorInfo);
//
//		CString strMessage;
//		if(errorInfo.m_strErrorSymbol.IsEmpty())
//		{ 
//			strMessage.Format(_T("\n%s : 错误代码：%d 错误意义：%s"),errorInfo.m_strErrorFileName,errorInfo.m_nErrorCode,errorInfo.m_strErrorCodeInfo);
//		}
//		else
//		{
//			strMessage.Format(_T("\n%s : 错误代码：%d 错误符号：%s 错误意义：%s" ),errorInfo.m_strErrorFileName,errorInfo.m_nErrorCode,errorInfo.m_strErrorSymbol,errorInfo.m_strErrorCodeInfo);
//		}
//
//		OutPutMessage(strMessage);
//	}
//}
//
//
