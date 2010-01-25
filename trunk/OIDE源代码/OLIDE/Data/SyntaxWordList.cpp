
#include "stdafx.h"
#include "SyntaxWordList.h"
#include "./StdioFile/StdioFileEx.h"

CSyntaxWordList::CSyntaxWordList()
{

}

CSyntaxWordList::~CSyntaxWordList()
{

}

BOOL CSyntaxWordList::LoadOASMSyntaxWord(const CString& strSyntaxWordFileName)
{
	BOOL bResult = FALSE;
	int nCurIndex = -1;
	CStdioFileEx stdFile;
	if(stdFile.Open(strSyntaxWordFileName, CFile::modeRead|CFile::typeText)) 
	{		
		CString strLine;
		while(stdFile.ReadStringEx(strLine,TRUE,_T(';')))
		{
			if(strLine.Left(2) == _T("%%"))
			{
				strLine.TrimLeft(_T('%')); //去掉左边的百分号
				strLine.Trim(); //去掉两边空格

				if(!strLine.IsEmpty())
				{
					switch(strLine[0])
					{
					case _T('0'):bResult = TRUE;nCurIndex = 0;break;
					case _T('1'):bResult = TRUE;nCurIndex = 1;break;
					case _T('2'):bResult = TRUE;nCurIndex = 2;break;
					case _T('3'):bResult = TRUE;nCurIndex = 3;break;
					case _T('4'):bResult = TRUE;nCurIndex = 4;break;
					case _T('5'):bResult = TRUE;nCurIndex = 5;break;
					case _T('6'):bResult = TRUE;nCurIndex = 6;break;
					case _T('7'):bResult = TRUE;nCurIndex = 7;break;
					default:nCurIndex = -1;break;
					}
				}

				continue;
			}

			switch(nCurIndex)
			{
			case 0:
				m_strOasmWordListSymbol += strLine + _T(" ");
				break;
			case 1:
				m_strOasmWordListCPUInsns += strLine + _T(" ");
				break;
			case 2:
				m_strOasmWordListFPUInsns += strLine + _T(" ");
				break;
			case 3:
				m_strOasmWordListRegister += strLine + _T(" ");
				break;
			case 4:
				m_strOasmWordListDefineWord += strLine + _T(" ");
				break;
			case 5:
				m_strOasmWordListMacro += strLine + _T(" ");
				break;
			case 6:
				m_strOasmWordListOperatorTxt += strLine + _T(" ");
				break;
			case 7:
				m_strOasmWordListOperator += strLine + _T(" ");
				break;
			}
		}
	}

	return bResult;
}

BOOL CSyntaxWordList::LoadOMLSyntaxWord(const CString& strSyntaxWordFileName)
{
	BOOL bResult = FALSE;
	int nCurIndex = -1;
	CStdioFileEx stdFile;
	if(stdFile.Open(strSyntaxWordFileName, CFile::modeRead|CFile::typeText)) 
	{		
		CString strLine;
		while(stdFile.ReadStringEx(strLine,TRUE,_T(';')))
		{
			if(strLine.Left(2) == _T("%%"))
			{
				strLine.TrimLeft(_T('%')); //去掉左边的百分号
				strLine.Trim(); //去掉两边空格

				if(!strLine.IsEmpty())
				{
					switch(strLine[0])
					{
					case _T('0'):bResult = TRUE;nCurIndex = 0;break;
					case _T('1'):bResult = TRUE;nCurIndex = 1;break;
					case _T('2'):bResult = TRUE;nCurIndex = 2;break;
					case _T('3'):bResult = TRUE;nCurIndex = 3;break;					
					default:nCurIndex = -1;break;
					}
				}

				continue;
			}

			switch(nCurIndex)
			{
			case 0:
				m_strOMLWordListCommentSymbol += strLine + _T(" ");
				break;
			case 1:
				m_strOMLWordListKeyword += strLine + _T(" ");
				break;
			case 2:
				m_strOMLWordListOperator += strLine + _T(" ");
				break;
			case 3:
				m_strOMLWordListMacroTxt += strLine + _T(" ");
				break;			
			}
		}
	}

	return bResult;
}