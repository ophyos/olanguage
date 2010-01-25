
#ifndef _D_OASM_H_
#define _D_OASM_H_

class CDoasm
{
public:
	CDoasm(){}
	~CDoasm(){}

public:

	static bool DoDoasm(const CString& strDOASMPath,const CString& strPeFileName,const CString& strLanguageFileName,CString& strDoasmFileName);
};
#endif //_D_OASM_H_