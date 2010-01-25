#include "StdAfx.h"
#include ".\solutionproperty.h"
#include "../Common/Global.h"

CSolutionProperty::CSolutionProperty(void)
{
}

CSolutionProperty::~CSolutionProperty(void)
{
}


CProjectProperty::CProjectProperty()
{	
	m_strProjectName.Empty();
	m_strProjectFilePath.Empty();

	m_strCodeDir.Empty();
	m_strResourceDir.Empty();
	m_nProgramType = PT_EXE; 
	m_nLinkSubSystem = 0;
	
	m_strDebugMiddleOutPutPath.Empty();
	m_strDebugOutPutFileName.Empty();

	m_strReleaseMiddleOutPutPath.Empty();
	m_strReleaseOutPutFileName.Empty();	

	m_strProjectFlag = _T("<工程>");

	m_pProjectBuildRecord = 0;
}

CProjectProperty::~CProjectProperty()
{

}

void CProjectProperty::SetDefaultProjectProperty(const CString& strProjectPath,const CString& strProjectName,int nProjectType)
{	
	m_strProjectName = strProjectName;
	m_strProjectFilePath = strProjectPath;
	m_strCodeDir = m_strProjectFlag + _T(".\\代码\\");
	m_strResourceDir = m_strProjectFlag + _T(".\\资源\\");
	m_nLinkSubSystem = 1;
	m_strDebugMiddleOutPutPath = m_strProjectFlag + _T(".\\输出\\调试\\");		
	m_strDebugOutPutFileName = m_strDebugMiddleOutPutPath + m_strProjectName;
	m_strReleaseMiddleOutPutPath = m_strProjectFlag + _T(".\\输出\\纯净\\");
	m_strReleaseOutPutFileName = m_strReleaseMiddleOutPutPath + m_strProjectName;

	switch(nProjectType)
	{
	case NEW_ITEM_TYPE_PROJECT_WIN32_WINDOWS:
		m_nProgramType = PT_EXE;		
		m_strDebugOutPutFileName += _T(".exe");
		m_strReleaseOutPutFileName += _T(".exe");
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_CONSOLE:
		m_nLinkSubSystem = 0;
		m_nProgramType = PT_EXE;
		m_strDebugOutPutFileName += _T(".exe");
		m_strReleaseOutPutFileName += _T(".exe");		
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_DLL:
		m_nProgramType = PT_DLL;
		m_strDebugOutPutFileName += _T(".dll");
		m_strReleaseOutPutFileName += _T(".dll");
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_LIB:
		m_nProgramType = PT_LIB;
		m_strDebugOutPutFileName += _T(".lib");
		m_strReleaseOutPutFileName += _T(".lib");
		break;
	}		

	if(m_pProjectBuildRecord)
	{
		delete m_pProjectBuildRecord;
	}

	m_pProjectBuildRecord = new COLProjectBuildRecord();
}

CString  CProjectProperty::GetProjectAbsolutePathCodeDir()
{
	return GetProjectAbsolutePath(m_strCodeDir);
}

CString  CProjectProperty::GetProjectAbsolutePathResourceDir()
{
	return GetProjectAbsolutePath(m_strResourceDir);
}

CString CProjectProperty::GetProjectAbsolutePathMiddleOutPut(bool bDebug)
{
	if(bDebug)
	{
		return GetProjectAbsolutePath(m_strDebugMiddleOutPutPath);
	}
	
	return GetProjectAbsolutePath(m_strReleaseMiddleOutPutPath);
}

CString CProjectProperty::GetProjectAbsolutePathOutPutFileName(bool bDebug)
{
	if(bDebug)
	{
		return GetProjectAbsolutePath(m_strDebugOutPutFileName);
	}
	
	return GetProjectAbsolutePath(m_strReleaseOutPutFileName);
}

CString CProjectProperty::GetProjectAbsolutePath(const CString& strPath)
{	
	CString strTemp;
	if(strPath.IsEmpty())
		return strTemp;

	if(strPath.Find(m_strProjectFlag) == 0)
	{
		strTemp = strPath.Right(strPath.GetLength()-m_strProjectFlag.GetLength());
	}	
	GetAbsolutePath(m_strProjectFilePath,strTemp);

	return strTemp;
}

void  CProjectProperty::DeleteBuildRecord()
{
	if(m_pProjectBuildRecord)
	{
		delete m_pProjectBuildRecord;
		m_pProjectBuildRecord = 0;
	}
}


