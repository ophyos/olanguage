
#ifndef  _O_CODE_BUILD_H_
#define  _O_CODE_BUILD_H_

class COCodeBuild
{
public:

	COCodeBuild(){};
	~COCodeBuild(){};

	bool OML_BuildCode(const CString& strOMLPath,const CString& strSourceFileName,const CString& strLanguageFileName,CString& strObjFileName,bool bIsDebug);
	bool OASM_BuildCode(const CString& strOASMPath,const CString& strSourceFileName,const CString& strLanguageFileName,CString& strObjFileName,bool bIsDebug);
	bool LinkObjFile(const CString& strLinkerPath,const CString& strObjFile,CString& strExeFileName,const CString& strOtherLinkParam,bool bIsDLL = false);
	void GetObjAndResFile(const CString& strDir,CString& strObj,CString& strRes);
	bool LinkObjPath(const CString& strLinkerPath,const CString& strObjPath,CString& strExeFileName,const CString& strOtherLinkParam,bool bIsDLL,LPCTSTR pstrDefFileName = NULL);
	bool CompileResourceFile(const CString& strRcExePath,const CString& strResourceFile,LPCTSTR pstrOutputResFileName = NULL);

};

#endif  //_O_CODE_BUILD_H_