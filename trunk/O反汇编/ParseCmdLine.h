
#ifndef _PARSE_CMD_LINE_H_
#define _PARSE_CMD_LINE_H_

#include "anyoption.h"
#include "CmdLineOption.h"

class CParseCmdLine
{
public:
	CParseCmdLine();
	~CParseCmdLine();

	int parse_cmdline(int argc, char* argv[],CCmdLineOption& cmdLineOption);

private:

	AnyOption* m_pAnyOption;
};

#endif //_PARSE_CMD_LINE_H_