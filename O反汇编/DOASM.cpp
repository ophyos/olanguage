// DOASM.cpp : 定义控制台应用程序的入口点。
//

#include "DOASM.h"
#include "ParseCmdLine.h"
#include "DoasmPeFile.h"

int main(int argc, char* argv[])
{
	CCmdLineOption cmdLineOption;

	//命令行解析
	CParseCmdLine parseCmdLine;
	if(parseCmdLine.parse_cmdline(argc,argv,cmdLineOption) <= 0) //小于0表示命令行错误，等于0表示输出命令行帮助信息
	{
		//return -DOASM_MSG_COMMAND_LINE_ERROR;
		return -1;
	}

	////测试时使用
	//parseCmdLine.parse_cmdline(argc,argv,cmdLineOption);
	////cmdLineOption.m_pchLanguageFile = "F:\\Myprogram\\OL\\OL\\release\\oasm\\language\\english.oic";
	//cmdLineOption.m_pchLanguageFile = "F:\\Myprogram\\OL\\OL\\release\\oasm\\language\\chinese.oic";
	//cmdLineOption.m_pchPeFile = "f:\\第一个窗口程序.exe";
	//if(cmdLineOption.m_pchDoasmFile == 0)cmdLineOption.get_default_doasm_file();

	int nRetCode = 0;

	//调用DoasmDLL函数进行反汇编
	nRetCode = DoasmPeFile(cmdLineOption.m_pchPeFile,cmdLineOption.m_pchLanguageFile,cmdLineOption.m_pchDoasmFile);
	
	return nRetCode;
}

