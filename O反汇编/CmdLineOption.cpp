
#include "CmdLineOption.h"
#include <string.h>
#include <stdlib.h>

CCmdLineOption::CCmdLineOption()
{
	m_pchPeFile = 0;
	m_pchLanguageFile = 0;
	m_pchDoasmFile = 0;

	m_pchDoasmFileTemp = 0;
}
CCmdLineOption::~CCmdLineOption()
{
	if(m_pchDoasmFileTemp != 0)
	{
		free(m_pchDoasmFileTemp);
		m_pchDoasmFileTemp = 0;
	}
}

void CCmdLineOption::get_default_doasm_file()
{
	int nLen = (int)strlen(m_pchPeFile);
	if(m_pchDoasmFileTemp != 0)
	{
		free(m_pchDoasmFileTemp);
		m_pchDoasmFileTemp = 0;
	}
	m_pchDoasmFileTemp = (char*)malloc(nLen+5);

	strcpy(m_pchDoasmFileTemp,m_pchPeFile);
	if(m_pchPeFile[nLen-1] == '.')
	{
		m_pchDoasmFileTemp[nLen]   = 'd';
		m_pchDoasmFileTemp[nLen+1] = 'o';
		m_pchDoasmFileTemp[nLen+2] = 'a';
		m_pchDoasmFileTemp[nLen+3] = 0;
	}
	else if(m_pchPeFile[nLen-2] == '.')
	{
		m_pchDoasmFileTemp[nLen-1] = 'd';
		m_pchDoasmFileTemp[nLen]   = 'o';
		m_pchDoasmFileTemp[nLen+1] = 'a';
		m_pchDoasmFileTemp[nLen+2] = 0;
	}
	else if(m_pchPeFile[nLen-3] == '.')
	{
		m_pchDoasmFileTemp[nLen-2] = 'd';
		m_pchDoasmFileTemp[nLen-1] = 'o';
		m_pchDoasmFileTemp[nLen]   = 'a';
		m_pchDoasmFileTemp[nLen+1] = 0;
	}
	else if(m_pchPeFile[nLen-4] == '.')
	{
		m_pchDoasmFileTemp[nLen-3] = 'd';
		m_pchDoasmFileTemp[nLen-2] = 'o';
		m_pchDoasmFileTemp[nLen-1] = 'a';
		m_pchDoasmFileTemp[nLen] = 0;
	}
	else
	{
		m_pchDoasmFileTemp[nLen] = '.';
		m_pchDoasmFileTemp[nLen+1] = 'o';
		m_pchDoasmFileTemp[nLen+2] = 'b';
		m_pchDoasmFileTemp[nLen+3] = 'j';
		m_pchDoasmFileTemp[nLen+4] = 0;
	}

	m_pchDoasmFile = m_pchDoasmFileTemp;
}