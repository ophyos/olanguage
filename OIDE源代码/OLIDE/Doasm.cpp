
#include "stdafx.h"
#include "Doasm.h"
#include "RunCommand.h"

bool CDoasm::DoDoasm(const CString& strDOASMPath,const CString& strPeFileName,const CString& strLanguageFileName,CString& strDoasmFileName)
{	
	//判断汇编器
	if(strDOASMPath.IsEmpty())
	{
		MainWndOutputMsg(_T("未指定反汇编器路径\n"));
		return false;
	}

	//判断汇编器是否存在
	if(!FileExist(strDOASMPath))
	{
		MainWndOutputMsg(_T("反汇编器 \"%s\" 不存在\n"),strDOASMPath);
		return false;
	}
	CString strDOASMTempPath;
	strDOASMTempPath = GetShortPath(strDOASMPath);

	if(strDoasmFileName.IsEmpty())
	{
		int nDotPos = strPeFileName.ReverseFind(_T('.'));
		strDoasmFileName = (nDotPos<0)?strPeFileName:strPeFileName.Left(nDotPos);		
		strDoasmFileName += _T(".doa");
	}	

	//删除原有的目标文件
	DeleteFile(strDoasmFileName);

	//组合参数
	CString strParam,strTemp;

	//设置源文件
	strParam += _T(" --in-pe-file ");
	strTemp = strPeFileName;
	AddPathSYH(strTemp);
	strParam += strTemp;

	//设置语言文件
	strParam += _T(" --in-language-file ");
	strTemp = strLanguageFileName;
	AddPathSYH(strTemp);
	strParam += strTemp;

	//设置目标文件
	if(!strDoasmFileName.IsEmpty())
	{
		strParam += _T(" --out-doasm-file ");
		strTemp = strDoasmFileName;
		AddPathSYH(strTemp);
		strParam += strTemp;
	}	

	TCHAR cmdLine[MAX_COMMAND_LINE];
	memset(cmdLine,0,MAX_COMMAND_LINE);
	wsprintf(cmdLine,_T("%s %s"),strDOASMTempPath,strParam);

	MainWndOutputMsg(_T("正在反汇编 \"%s\" 文件...\n"),strPeFileName);

	DWORD ddResult = RunCommand(cmdLine,RCT_DOASM);

	//如果没有生成目标文件则编译错误返回
	if(!FileExist(strDoasmFileName))
	{
		return false;
	}

	return (ddResult==0);
}