
#include "stdafx.h"
#include "OLProjectBuildRecord.h"

int COLProjectBuildRecord::GetCount()
{ 
	return m_strarrayFileName.GetCount(); 
}

void COLProjectBuildRecord::AddRecord(const CString& strFileName,const CString& strFileTime,const CString& strObjFileTime)
{
	m_strarrayFileName.Add(strFileName);
	m_strarrayFileTime.Add(strFileTime);
	m_strarrayObjFileTime.Add(strObjFileTime);	
}

void COLProjectBuildRecord::GetAt(int nIndex,CString& strFileName,CString& strFileTime,CString& strObjFileTime)
{
	strFileName = m_strarrayFileName.GetAt(nIndex);
	strFileTime = m_strarrayFileTime.GetAt(nIndex);
	strObjFileTime = m_strarrayObjFileTime.GetAt(nIndex);
}

const CString& COLProjectBuildRecord::GetAtFileName(int nIndex)
{		
	return m_strarrayFileName.GetAt(nIndex);
}

const CString& COLProjectBuildRecord::GetAtFileTime(int nIndex)
{		
	return m_strarrayFileTime.GetAt(nIndex);		
}

const CString& COLProjectBuildRecord::GetAtObjFileTime(int nIndex)
{		
	return m_strarrayObjFileTime.GetAt(nIndex);		
}

void COLProjectBuildRecord::SetAtFileName(int nIndex,const CString& strFileName)
{		
	m_strarrayFileName.SetAt(nIndex,strFileName);
}

void COLProjectBuildRecord::SetAtFileTime(int nIndex,const CString& strFileTime)
{		
	m_strarrayFileTime.SetAt(nIndex,strFileTime);
}

void COLProjectBuildRecord::SetAtObjFileTime(int nIndex,const CString& strObjFileTime)
{		
	m_strarrayObjFileTime.SetAt(nIndex,strObjFileTime);
}

int COLProjectBuildRecord::SearchRecord(const CString& strFileName)
{
	CString strFileNameTemp,strFileTimeTemp,strObjFileTimeTemp;
	int nCount = GetCount();
	for(int i=0;i< nCount;++i)
	{
		GetAt(i,strFileNameTemp,strFileTimeTemp,strObjFileTimeTemp);
		if(strFileNameTemp == strFileName)
		{				
			return i;
		}
	}

	return -1;
}
