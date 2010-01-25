
#ifndef _STDIO_FILE_EX_H_
#define _STDIO_FILE_EX_H_

class CStdioFileEx : public CStdioFile
{
public:
	CStdioFileEx();
	~CStdioFileEx();

private:

	void Str2Unicode(CString &str);

public:

	//读取一行，如果chIgnoreLineStarChar不为0,则过滤到以chIgnoreLineStarChar开始的行
	BOOL ReadStringEx(CString& strText,BOOL bIgnoreEmptyLine = FALSE,TCHAR chIgnoreLineStarChar = 0);
};

#endif //_STDIO_FILE_EX_H_

