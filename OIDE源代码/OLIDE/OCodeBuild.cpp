
#include "stdafx.h"
#include "OCodeBuild.h"
#include "RunCommand.h"

bool COCodeBuild::OML_BuildCode(const CString& strOMLPath,const CString& strSourceFileName,const CString& strLanguageFileName,CString& strObjFileName,bool bIsDebug)
{
	return OASM_BuildCode(strOMLPath,strSourceFileName,strLanguageFileName,strObjFileName,bIsDebug);
}

bool COCodeBuild::OASM_BuildCode(const CString& strOASMPath,const CString& strSourceFileName,const CString& strLanguageFileName,CString& strObjFileName,bool bIsDebug)
{	
	//编译器
	if(strOASMPath.IsEmpty())
	{
		MainWndOutputMsg(_T("未指定编译器路径\n"));
		return false;
	}

	//判断汇编器是否存在
	if(!FileExist(strOASMPath))
	{
		MainWndOutputMsg(_T("编译器 \"%s\" 不存在\n"),strOASMPath);
		return false;
	}
	CString strOASMTempPath;
	strOASMTempPath = GetShortPath(strOASMPath);

	if(strObjFileName.IsEmpty())
	{
		int nDotPos = strSourceFileName.ReverseFind(_T('.'));
		strObjFileName = (nDotPos<0)?strSourceFileName:strSourceFileName.Left(nDotPos);		
		strObjFileName += _T(".obj");
	}	

	//删除原有的目标文件
	DeleteFile(strObjFileName);

	//组合参数
	CString strParam,strTemp;

	//设置源文件
	strParam += _T(" --in-source-file ");
	strTemp = strSourceFileName;
	AddPathSYH(strTemp);
	strParam += strTemp;

	//设置语言文件
	strParam += _T(" --in-language-file ");
	strTemp = strLanguageFileName;
	AddPathSYH(strTemp);
	strParam += strTemp;

	//设置目标文件
	if(!strObjFileName.IsEmpty())
	{
		strParam += _T(" --out-obj-file ");
		strTemp = strObjFileName;
		AddPathSYH(strTemp);
		strParam += strTemp;
	}	

	//如果是调试版本
	if(bIsDebug)
	{
		strParam += _T(" --debug");
	}

	TCHAR cmdLine[MAX_COMMAND_LINE];
	memset(cmdLine,0,MAX_COMMAND_LINE);
	wsprintf(cmdLine,_T("%s %s"),strOASMTempPath,strParam);

	DWORD ddResult = RunCommand(cmdLine,RCT_BUILD_CODE);
	
	//如果没有生成目标文件则编译错误返回
	if(!FileExist(strObjFileName))
	{
		return false;
	}

	return (ddResult==0);
}

//链接目标文件
bool COCodeBuild::LinkObjFile(const CString& strLinkerPath,const CString& strObjFile,CString& strExeFileName,const CString& strOtherLinkParam,bool bIsDLL)
{
	//判断链接器
	if(strLinkerPath.IsEmpty())
	{
		MainWndOutputMsg(_T("未指定链接器路径\n"));
		return false;
	}

	//判断链接器是否存在
	if(!FileExist(strLinkerPath))
	{
		MainWndOutputMsg(_T("链接器 \"%s\" 不存在\n"),strLinkerPath);
		return false;
	}
	CString strLinkerTempPath;
	strLinkerTempPath = GetShortPath(strLinkerPath);

	//判断要链接的目标文件是否存在
	if(!FileExist(strObjFile))
	{
		MainWndOutputMsg(_T("目标文件 \"%s\" 不存在\n"),strObjFile);
		return false;
	}

	CString strOtherLinkParamTemp;
	//如果是生成DLL文件，添加DLL链接参数
	if(bIsDLL)
	{ 
		strOtherLinkParamTemp += _T(" /DLL");
		//获取.def文件路径
		CString strDefFile = strObjFile;
		strDefFile = GetTitleFromPathName(strDefFile);
		strDefFile += _T(".DEF");
		if(FileExist(strDefFile))
		{
			AddPathSYH(strDefFile);
			strOtherLinkParamTemp += _T(" /DEF:");
			strOtherLinkParamTemp += strDefFile;
		}

		//设置生成执行文件路径
		if(strExeFileName.IsEmpty())
		{	
			strExeFileName = strObjFile;
			strExeFileName = GetTitleFromPathName(strExeFileName);
			strExeFileName += _T(".dll");
		}
	}
	else
	{
		//设置生成执行文件路径
		if(strExeFileName.IsEmpty())
		{			
			strExeFileName = strObjFile;
			strExeFileName = GetTitleFromPathName(strExeFileName);
			strExeFileName += _T(".exe");
		}
	}

	strOtherLinkParamTemp += strOtherLinkParam;	

	//删除原有的EXE文件
	if(!DeleteFile(strExeFileName))
	{
		DWORD ddError = GetLastError();
		//如果是拒绝访问
		if(ddError == 5)
		{
			MainWndOutputMsg(_T("%s 文件拒绝写入\n"),strExeFileName);
			return false;
		}
	}

	CString strTempObjFile,strTempResource,strTempExeFileName;

	//目标文件路径
	//strTempObjFile = strObjFile;
	//AddPathSYH(strTempObjFile);
	strTempObjFile = GetShortPath(strObjFile);

	//资源文件路径
	strTempResource = strObjFile;
	strTempResource = GetTitleFromPathName(strTempResource);
	strTempResource += _T(".RES");

	if(!FileExist(strTempResource))
	{
		strTempResource.Empty();
	}
	else
	{
		AddPathSYH(strTempResource);
		//strTempResource = GetShortPath(strTempResource);		
	}

	//输出执行文件路径
	strTempExeFileName = strExeFileName;
	AddPathSYH(strTempExeFileName);
	//strTempExeFileName = GetShortPath(strExeFileName);

	int nLength = 10 + strLinkerTempPath.GetLength() + strTempObjFile.GetLength() + 
		strTempResource.GetLength() + strTempExeFileName.GetLength() + strOtherLinkParamTemp.GetLength();

	if(nLength > MAX_COMMAND_LINE)
	{
		MainWndOutputMsg(_T("链接参数太长，请更改链接参数\n"));
		return false;
	}

	MainWndOutputMsg(_T("正在链接 %s 目标文件...\n"),strObjFile);

	TCHAR cmdLine[MAX_COMMAND_LINE];
	wsprintf(cmdLine,_T("%s %s %s /OUT:%s %s"),strLinkerTempPath,strTempObjFile,strTempResource,strTempExeFileName,strOtherLinkParamTemp); 

	RunCommand(cmdLine,RCT_LINK_OBJ);
	
	//判断执行文件是否存在
	if(!FileExist(strExeFileName))
	{	
		strExeFileName.Empty();

		MainWndOutputMsg(_T("程序链接失败\n"));
		return false;
	}

	MainWndOutputMsg(_T("生成 %s 执行文件\n"),strExeFileName);

	return true;
}

void COCodeBuild::GetObjAndResFile(const CString& strDir,CString& strObj,CString& strRes)
{
	CFileFind ff;
	CString szDir = strDir;

	if (szDir.Right(1) != _T("\\"))
	{
		szDir += _T("\\");
	}
	szDir += _T("*.*");

	bool bResult = false;
	BOOL res = ff.FindFile(szDir);
	while (res)
	{
		res = ff.FindNextFile();
		if (ff.IsDots() || ff.IsDirectory())continue;

		//否则是文件
		CString strFilePath = ff.GetFilePath();
		CString strFileName = ff.GetFileName();
		CString strExternName = strFileName;
		int nPos = strExternName.ReverseFind(_T('.'));
		if (nPos < 0)continue;

		strExternName = strExternName.Right(strExternName.GetLength()-nPos-1);
		strExternName.MakeLower();
		//目标文件
		if(strExternName == _T("obj"))
		{
			strObj += strFileName;
			strObj += _T(' ');
		}
		//资源文件
		else if(strExternName == _T("res"))
		{	
			strRes += strFileName;
			strRes += _T(' ');
		}
	}

	ff.Close();	
}

//链接目标路径
bool COCodeBuild::LinkObjPath(const CString& strLinkerPath,const CString& strObjPath,CString& strExeFileName,const CString& strOtherLinkParam,bool bIsDLL,LPCTSTR pstrDefFileName)
{
	//输出文件名不能为空
	ASSERT(!strExeFileName.IsEmpty());

	//判断链接器
	if(strLinkerPath.IsEmpty())
	{
		MainWndOutputMsg(_T("未指定链接器路径\n"));
		return false;
	}

	//判断链接器是否存在
	if(!FileExist(strLinkerPath))
	{
		MainWndOutputMsg(_T("链接器 \"%s\" 不存在\n"),strLinkerPath);
		return false;
	}
	CString strLinkerTempPath;
	strLinkerTempPath = GetShortPath(strLinkerPath);

	//判断要链接的目标目录是否存在
	CString strObjPathTemp = strObjPath;
	if(strObjPathTemp.Right(1) == _T("\\"))
	{
		strObjPathTemp.Delete(strObjPathTemp.GetLength()-1);
	}
	if(!FileExist(strObjPathTemp,true))
	{
		MainWndOutputMsg(_T("目录 \"%s\" 不存在\n"),strObjPathTemp);
		return false;
	}

	CString strOtherLinkParamTemp;
	//如果是生成DLL文件，添加DLL链接参数
	if(bIsDLL)
	{ 
		strOtherLinkParamTemp += _T(" /DLL");

		CString strDefFileList = pstrDefFileName;
		CString strDefFile;
		while(!strDefFileList.IsEmpty())
		{
			int nPos = strDefFileList.Find(_T('\n')); //多个def文件用回车符分隔
			strDefFile = strDefFileList.Left(nPos);

			AddPathSYH(strDefFile);
			strOtherLinkParamTemp += _T(" /DEF:");
			strOtherLinkParamTemp += strDefFile;
			
			strDefFileList = strDefFileList.Right(strDefFileList.GetLength()-nPos-1);
		}		
	}

	strOtherLinkParamTemp += strOtherLinkParam;	

	//删除原有的EXE文件
	if(!DeleteFile(strExeFileName))
	{
		DWORD ddError = GetLastError();
		//如果是拒绝访问
		if(ddError == 5)
		{
			MainWndOutputMsg(_T("%s 文件拒绝写入\n"),strExeFileName);
			return false;
		}
	}

	CString strTempExeFileName;
	//输出执行文件路径
	strTempExeFileName = strExeFileName;
	AddPathSYH(strTempExeFileName);
	//strTempExeFileName = GetShortPath(strExeFileName);

	CString strObjFile,strResFile;
	GetObjAndResFile(strObjPath,strObjFile,strResFile);

	int nLength = 8 + strLinkerTempPath.GetLength() + strObjFile.GetLength() + strResFile.GetLength() +
		strTempExeFileName.GetLength() + strOtherLinkParamTemp.GetLength();

	if(nLength > MAX_COMMAND_LINE)
	{
		MainWndOutputMsg(_T("链接参数太长，请更改链接参数\n"));
		return false;
	}

	MainWndOutputMsg(_T("正在链接...\n"));

	::SetCurrentDirectory(strObjPath);
	TCHAR cmdLine[MAX_COMMAND_LINE];
	wsprintf(cmdLine,_T("%s %s %s /OUT:%s %s"),strLinkerTempPath,strObjFile,strResFile,strTempExeFileName,strOtherLinkParamTemp); 
	RunCommand(cmdLine,RCT_LINK_OBJ);

	//判断执行文件是否存在
	if(!FileExist(strExeFileName))
	{	
		strExeFileName.Empty();

		MainWndOutputMsg(_T("程序链接失败\n"));
		return false;
	}

	//MainWndOutputMsg(_T("生成 %s 执行文件\n"),strExeFileName);

	return true;
}

//编译资源文件
bool COCodeBuild::CompileResourceFile(const CString& strRcExePath,const CString& strResourceFile,LPCTSTR pstrOutputResFileName)
{
	//首先判断要编译的资源文件是否存在
	if(!FileExist(strResourceFile))
	{
		MainWndOutputMsg(_T("没有 %s 资源文件，跳过资源编译\n"),strResourceFile);
		return false;
	}

	//资源编译器路径
	if(strRcExePath.IsEmpty())
	{
		MainWndOutputMsg(_T("未指定资源编译器路径\n"));
		return false;
	}

	//资源编译器是否存在
	if(!FileExist(strRcExePath))
	{
		MainWndOutputMsg(_T("资源编译器 \"%s\" 不存在\n"),strRcExePath);
		return false;
	}
	CString strRcExeTempPath;
	strRcExeTempPath = GetShortPath(strRcExePath);	

	//MainWndOutputMsg(_T("正在编译 %s 资源文件...\n"),strResourceFile);

	CString strResourceTempFile;
	strResourceTempFile = strResourceFile;
	AddPathSYH(strResourceTempFile);
	//strResourceTempFile = GetShortPath(strResourceFile);	

	CString strOutputResFileName = pstrOutputResFileName;

	TCHAR cmdLine[MAX_COMMAND_LINE];
	if(strOutputResFileName.IsEmpty())
	{
		strOutputResFileName = GetTitleFromPathName(strResourceFile);
		strOutputResFileName += _T(".res");
	}

	::DeleteFile(strOutputResFileName);

	CString strOutputResFileNameTemp = strOutputResFileName;
	AddPathSYH(strOutputResFileNameTemp);
	wsprintf(cmdLine,_T("%s -convert %s %s"),strRcExeTempPath,strResourceTempFile,strOutputResFileNameTemp);
		
	RunCommand(cmdLine,RCT_COMPILE_RES);
	
	//判断是否生成资源文件
	if(!FileExist(strOutputResFileName))
	{
		MainWndOutputMsg(_T("编译 %s 资源文件失败\n"),strOutputResFileName);
		return false;
	}

	//MainWndOutputMsg(_T("生成 %s 资源文件\n"),strOutputResFileName);	

	return true;
}

