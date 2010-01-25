
#include "ParseCmdLine.h"

CParseCmdLine::CParseCmdLine()
{
	m_pAnyOption = 0;
}

CParseCmdLine::~CParseCmdLine()
{
	if(m_pAnyOption)
	{
		delete m_pAnyOption;
		m_pAnyOption = 0;
	}
}

int CParseCmdLine::parse_cmdline(int argc, char* argv[],CCmdLineOption& cmdLineOption)
{
	//得到当前程序目录
	strcpy_s(cmdLineOption.m_chCurExeDir,256,argv[0]);
	int i = 0,n = 0;
	while(cmdLineOption.m_chCurExeDir[i] != 0)
	{
		if(cmdLineOption.m_chCurExeDir[i] == '\\')
		{
			n = i;
		}
		++i;
	}
	cmdLineOption.m_chCurExeDir[n] = 0;

	//////////////////////////////////////////////////////////////////////////
	//开始命令行解析

	if(m_pAnyOption == 0)
	{
		m_pAnyOption = new AnyOption();
		if(m_pAnyOption == 0)
			return -1;
	}	

	//设置命令行说明
	m_pAnyOption->addUsage(" O反汇编命令行说明：");
	m_pAnyOption->addUsage( " -?  -h  --help                 显示参数帮助" );
	m_pAnyOption->addUsage( " -p  --in-pe-file        必选   输入要反汇编的PE格式文件  如:c:\\source\\sample.exe" );
	m_pAnyOption->addUsage( " -l  --in-language-file  必选   输入O汇编的语言文件  如:c:\\source\\chinese.oic");
	m_pAnyOption->addUsage( " -d  --out-doasm-file    可选   输出反汇编后生成的文件 如:c:\\source\\sample.doa");

	char* pchHelp = "help";
	char chHelp = 'h';
	char chQuestion = '?';
	char* pchInPeFile = "in-pe-file";
	char chInPeFile = 'p';
	char* pchInLanguageFile = "in-language-file";
	char chInLanguageFile = 'l';
	char* pchOutDoasmFile = "out-doasm-file";
	char chOutDoasmFile = 'd';

	//添加参数选项
	m_pAnyOption->setFlag(chQuestion);
	m_pAnyOption->setFlag(pchHelp, chHelp);	
	m_pAnyOption->setOption(pchInPeFile,chInPeFile);
	m_pAnyOption->setOption(pchInLanguageFile,chInLanguageFile);
	m_pAnyOption->setOption(pchOutDoasmFile,chOutDoasmFile);

	//解析命令行
	m_pAnyOption->processCommandArgs( argc, argv );

	//如果没有参数
	if(!m_pAnyOption->hasOptions())
	{ 
		m_pAnyOption->printUsage();
		return 0;
	}

	/* 获得参数 */

	//获得帮助
	if( m_pAnyOption->getFlag( chQuestion ) || m_pAnyOption->getFlag( chHelp ) || m_pAnyOption->getFlag( pchHelp ) ) 
	{
		m_pAnyOption->printUsage();
		return 0;
	}

	//获得源代码文件
	if((m_pAnyOption->getValue(pchInPeFile) != 0) || (m_pAnyOption->getValue(chInPeFile) != 0))
	{
		cmdLineOption.m_pchPeFile = m_pAnyOption->getValue(chInPeFile);			
	}

	//获得语言文件
	if((m_pAnyOption->getValue(pchInLanguageFile) != 0) || (m_pAnyOption->getValue(chInLanguageFile) != 0))
	{
		cmdLineOption.m_pchLanguageFile = m_pAnyOption->getValue(chInLanguageFile);			
	}

	//获得输出目标文件
	if((m_pAnyOption->getValue(pchOutDoasmFile) != 0) || (m_pAnyOption->getValue(chOutDoasmFile) != 0))
	{
		cmdLineOption.m_pchDoasmFile = m_pAnyOption->getValue(chOutDoasmFile);
	}

	int iResult = 1;
	if(cmdLineOption.m_pchPeFile == 0)
	{
		printf("错误：没有要反汇编的PE文件\n");
		iResult = -3;
	}

	if(cmdLineOption.m_pchLanguageFile == 0)
	{
		printf("错误：没有语言文件\n");
		iResult = -4;
	}

	if(iResult > 0)
	{
		//如果没有输出文件则根据源文件得到默认输出文件
		if(cmdLineOption.m_pchDoasmFile == 0)
		{
			cmdLineOption.get_default_doasm_file();
		}
	}

	return iResult;
}