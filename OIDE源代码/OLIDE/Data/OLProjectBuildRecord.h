
#ifndef _OL_PROJECT_BUILD_RECORD_H_
#define _OL_PROJECT_BUILD_RECORD_H_

class COLProjectBuildRecord
{
public:

	COLProjectBuildRecord(){};
	~COLProjectBuildRecord(){};

private:

	CStringArray  m_strarrayFileName;
	CStringArray  m_strarrayFileTime;
	CStringArray  m_strarrayObjFileTime;

public:

	int GetCount();
	void AddRecord(const CString& strFileName,const CString& strFileTime,const CString& strObjFileTime = _T(""));
	void GetAt(int nIndex,CString& strFileName,CString& strFileTime,CString& strObjFileTime);
	const CString& GetAtFileName(int nIndex);
	const CString& GetAtFileTime(int nIndex);
	const CString& GetAtObjFileTime(int nIndex);
	void SetAtFileName(int nIndex,const CString& strFileName);
	void SetAtFileTime(int nIndex,const CString& strFileTime);
	void SetAtObjFileTime(int nIndex,const CString& strObjFileTime);
	int SearchRecord(const CString& strFileName);
};

#endif _OL_PROJECT_BUILD_RECORD_H_