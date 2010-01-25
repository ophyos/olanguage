
#include "stdafx.h"
#include "UnicodeCovert.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 将Char型字符转换为Unicode字符
int CharToUnicode(char *pchIn, CString *pstrOut)
{
	int nLen;
	WCHAR *ptch;

	if(pchIn == NULL)
	{
		return 0;
	}

	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);
	ptch = new WCHAR[nLen];
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);
	pstrOut->Format(_T("%s"), ptch);

	delete [] ptch;

	return nLen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 将Unicode字符转换为Char型字符
int UnicodeToChar(const CString &strIn, char *pchOut, int nCharLen)
{
	if(pchOut == NULL)
	{
		return 0;
	}

	int nLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)strIn,-1, NULL, 0, NULL, NULL);
	nLen = min(nLen, nCharLen);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)strIn, -1, pchOut,
		nLen, NULL, NULL);

	if(nLen < nCharLen)
	{
		pchOut[nLen] = 0;
	}

	return nLen;
} 

void CopyStr(char* pchData,int nCharLen,const CString& strData)
{
#ifdef _UNICODE
	UnicodeToChar(strData,pchData,nCharLen);
#else
	strcpy_s(pchData,nCharLen,strData);
#endif

}