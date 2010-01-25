
#ifndef _UNICODE_COVERT_H_
#define _UNICODE_COVERT_H_

int CharToUnicode(char *pchIn, CString *pstrOut);
int UnicodeToChar(const CString &strIn, char *pchOut, int nCharLen);
void CopyStr(char* pchData,int nCharLen,const CString& strData);

#endif //_UNICODE_COVERT_H_