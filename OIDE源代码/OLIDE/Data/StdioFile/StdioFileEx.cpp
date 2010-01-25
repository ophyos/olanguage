
#include "stdafx.h"
#include "StdioFileEx.h"
#include "../../Common/UnicodeCovert.h"

CStdioFileEx::CStdioFileEx()
{

}

CStdioFileEx::~CStdioFileEx()
{

}

#ifdef _UNICODE

void CStdioFileEx::Str2Unicode(CString &str)
{
	char *szBuf = new char[str.GetLength()+1];

	for (int i = 0 ; i < str.GetLength()+1; i++)
	{
		szBuf[i] = str.GetAt(i); //如果提示 "wchar_t"转换到"char"，可能丢失数据 不用理会
	}
	CharToUnicode(szBuf , &str);

	delete []szBuf;
}
#endif

//读取一行，如果chIgnoreLineStarChar不为0,则过滤掉以chIgnoreLineStarChar开始的行
BOOL CStdioFileEx::ReadStringEx(CString& strText,BOOL bIgnoreEmptyLine,TCHAR chIgnoreLineStarChar)
{
	BOOL bResult = ReadString(strText);
	if(!bResult)return FALSE;

#ifdef _UNICODE
	Str2Unicode(strText);
#endif

	//忽略空行
	if(bIgnoreEmptyLine)
	{
		strText.Trim();
		if(strText.IsEmpty())
		{
			return ReadStringEx(strText,bIgnoreEmptyLine,chIgnoreLineStarChar);
		}
	}

	if(chIgnoreLineStarChar>0 && (!strText.IsEmpty()) && (strText[0] == chIgnoreLineStarChar))
	{
		return ReadStringEx(strText,bIgnoreEmptyLine,chIgnoreLineStarChar);
	}

	return TRUE;
}