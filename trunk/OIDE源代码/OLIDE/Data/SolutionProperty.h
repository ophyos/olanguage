
#ifndef _SOLUTION_PROPERTY_H_
#define _SOLUTION_PROPERTY_H_


#pragma once

#include "./OLXMLProjectData.h"

//方案属性
class CSolutionProperty
{
public:
	CSolutionProperty(void);
	~CSolutionProperty(void);
};


//工程属性
class CProjectProperty
{
public:

	CProjectProperty();
	~CProjectProperty();

public:

	enum PROGRAM_TYPE
	{		
		PT_EXE,
		PT_DLL,
		PT_LIB,
		PT_DRIVER,
	};

	CString m_strProjectName;
	CString m_strProjectFilePath;

	CString m_strCodeDir;     //代码目录
	CString m_strResourceDir; //资源目录
	int m_nProgramType;       //程序类型，EXE DLL
	int m_nLinkSubSystem;     //程序子系统 控制台 窗口程序
	CString m_strDebugMiddleOutPutPath;
	CString m_strDebugOutPutFileName;	
	CString m_strReleaseMiddleOutPutPath;
	CString m_strReleaseOutPutFileName;	
	CString m_strDefFileName;

	COLProjectBuildRecord* m_pProjectBuildRecord;
	
private:

	CString m_strProjectFlag;

public:

	void     SetDefaultProjectProperty(const CString& strProjectPath,const CString& strProjectName,int nProjectType);
	CString& GetProjectFlag(){ return m_strProjectFlag; };	
	CString  GetProjectAbsolutePathCodeDir();
	CString  GetProjectAbsolutePathResourceDir();
	CString  GetProjectAbsolutePathMiddleOutPut(bool bDebug);
	CString  GetProjectAbsolutePathOutPutFileName(bool bDebug);
	void     DeleteBuildRecord();
	
private:

	CString GetProjectAbsolutePath(const CString& strPath);

};

#endif //_SOLUTION_PROPERTY_H_