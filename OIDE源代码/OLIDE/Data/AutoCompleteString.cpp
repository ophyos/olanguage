
#include "stdafx.h"
#include "AutoCompleteString.h"

#include "./StdioFile/StdioFileEx.h"

CAutoCompleteString::CAutoCompleteString()
{

}

CAutoCompleteString::~CAutoCompleteString()
{
	while(!m_listSystemAutoCompleteGroup.IsEmpty())
	{
		CStringArray* pstrArray = (CStringArray*)m_listSystemAutoCompleteGroup.RemoveHead();
		if(pstrArray)
		{
			delete pstrArray;
		}
	}
	m_strarrayOASMTemplateFile.RemoveAll();

	m_strarrayOMLSystemAutoComplete.RemoveAll();
	m_strarrayOMLTemplateFile.RemoveAll();
}

//得到文件模板列表
void CAutoCompleteString::GetTemplateFileList(LPCTSTR lpDirect,CStringArray& strarrayTemplateFile,int nRelativePathLength)
{
	CString strRelativePath;
	CString strDir = lpDirect;
	if(strDir.GetLength() > nRelativePathLength)
	{
		strRelativePath = lpDirect;
		strRelativePath = strRelativePath.Mid(nRelativePathLength+1);
		strRelativePath += _T('\\');
	}

	TCHAR   szDirect[MAX_PATH];
	WIN32_FIND_DATA   winfd;
	_stprintf(szDirect,_T("%s\\*"),lpDirect);
	HANDLE   hFind   =   FindFirstFile(szDirect,&winfd);
	while(FindNextFile(hFind,&winfd))  
	{  
		//如果是目录不进行任何操作
		if(winfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)//搜子目录  
		{  
			if(_tcsicmp(winfd.cFileName,_T(".."))!=0&&_tcsicmp(winfd.cFileName,_T("."))!=0)  
			{  
				TCHAR  szNextDirect[MAX_PATH];
				_stprintf(szNextDirect,_T("%s\\%s"),lpDirect,winfd.cFileName);
				GetTemplateFileList(szNextDirect,strarrayTemplateFile,nRelativePathLength);
			}
		}  
		else  
		{  	
			CString strFileName = winfd.cFileName;
			//如果是模板文件
			if(strFileName.Right(4) == _T(".oat"))
			{
				//得到文件名
				strFileName = strFileName.Left(strFileName.GetLength()-4);
				
				//添加文件名
				strarrayTemplateFile.Add(strRelativePath + strFileName);
			}			
		}  
	}

	FindClose(hFind);
}

BOOL CAutoCompleteString::RefreshOASMSystemAutoCompleteGroup(LPCTSTR lpSystemTemplateFilePath)
{
	if(lpSystemTemplateFilePath != NULL)
	{
		m_strOASMSystemFilePath = lpSystemTemplateFilePath;
	}

	if(m_strOASMSystemFilePath.IsEmpty())
		return FALSE;

	CStdioFileEx stdFile;
	if(!stdFile.Open(m_strOASMSystemFilePath, CFile::modeRead|CFile::typeText)) 
		return FALSE;

	CStringArray* pstrArrayCurGroup = new CStringArray();
	if(pstrArrayCurGroup == 0)return FALSE;

	CString strLine;
	while(stdFile.ReadStringEx(strLine,TRUE,_T(';')))
	{		
		//如果是分段符号
		if(strLine == _T("%%"))
		{
			//添加一个Group
			if(!pstrArrayCurGroup->IsEmpty())
			{
				m_listSystemAutoCompleteGroup.AddTail(pstrArrayCurGroup);
				pstrArrayCurGroup = new CStringArray();
				if(pstrArrayCurGroup == 0)return FALSE;
			}

			continue;
		}

		pstrArrayCurGroup->Add(strLine);
	}
	
	if(!pstrArrayCurGroup->IsEmpty())
	{
		m_listSystemAutoCompleteGroup.AddTail(pstrArrayCurGroup);		
	}
	else
	{
		delete pstrArrayCurGroup;
	}
	
	return TRUE;
}

BOOL CAutoCompleteString::ReadTemplateFile(const CString& strFileName,CString& strText)
{
	CStdioFileEx stdFile;
	if(stdFile.Open(strFileName, CFile::modeRead|CFile::typeText)) 
	{
		BOOL bResult = FALSE;
	
		CString strLine;
		while(stdFile.ReadStringEx(strLine))
		{				
			if(bResult)
			{
				strText += _T("\r\n");
			}
			strText += strLine;
			bResult = TRUE;
		}

		return TRUE;
	}

	return FALSE;
}

int CAutoCompleteString::GetItemCount(POSITION psAutoCompleteShift)
{
	CStringArray* pstrArray = (CStringArray*)m_listSystemAutoCompleteGroup.GetAt(psAutoCompleteShift);
	ASSERT(pstrArray);

	return pstrArray->GetCount();
}

void  CAutoCompleteString::GetItemData(POSITION psAutoCompleteShift,int nIndex,CString& strText,CString& strComment,char& chKey)
{
	CStringArray* pstrArray = (CStringArray*)m_listSystemAutoCompleteGroup.GetAt(psAutoCompleteShift);		
	ASSERT(pstrArray);

	CString strItem = pstrArray->GetAt(nIndex);	
	GetItemData(strItem,strText,strComment,chKey);
}

void  CAutoCompleteString::GetItemData(const CString& strItem,CString& strText,CString& strComment,char& chKey)
{
	strText.Empty();
	strComment.Empty();
	chKey = 0;

	int nPos = strItem.Find(_T("∥"),1);//从第二个字符开始查找

	if(nPos>0)
	{
		strText = strItem.Left(nPos);
		strComment = strItem.Mid(nPos);
	}
	else
	{
		strText = strItem;
	}
	strText.Trim();

	//去掉快捷键字符
	if(strText.GetLength() >= 2)
	{	
		char chTemp = strText[1];
		if((strText[0] == '&') && (chTemp > 0x20 && chTemp <= 0x7E))
		{
			if(chTemp == '&')
			{
				strText = strText.Right(strText.GetLength()-1);
			}
			else
			{
				chKey = tolower(strText[1]);//转换成小写字母
				strText = strText.Right(strText.GetLength()-2);
			}
		}
	}
	strText.Replace(_T("\\r"),_T("\r"));
	strText.Replace(_T("\\n"),_T("\n"));
}

int CAutoCompleteString::GetOASMTemplateFileText(CString& strText,int nIndex)
{	
	//选中的是第一项则表示是刷新模板列表
	if(nIndex == 0)
	{
		RefreshOASMTemplateFileList();
		return -1;
	}

	CString strFileName = m_strOASMTempletDir + _T('\\') + GetOASMTemplateFileArray().GetAt(nIndex)+_T(".oat");
	ReadTemplateFile(strFileName,strText);
	return strText.GetLength();
}

void CAutoCompleteString::RefreshOASMTemplateFileList(LPCTSTR lpDirect)
{
	if(lpDirect)
	{
		m_strOASMTempletDir = lpDirect;
		if(m_strOASMTempletDir.Right(1) == _T('\\'))
		{
			m_strOASMTempletDir = m_strOASMTempletDir.Left(m_strOASMTempletDir.GetLength()-1);
		}
	}
	
	if(!m_strOASMTempletDir.IsEmpty())
	{
		GetOASMTemplateFileArray().RemoveAll();
		GetOASMTemplateFileArray().Add(_T("<刷新模板列表>"));

		GetTemplateFileList(m_strOASMTempletDir,GetOASMTemplateFileArray(),m_strOASMTempletDir.GetLength());
	}
}

BOOL CAutoCompleteString::RefreshOMLSystemAutoComplete(LPCTSTR lpSystemTemplateFilePath)
{
	if(lpSystemTemplateFilePath != NULL)
	{
		m_strOMLSystemFilePath = lpSystemTemplateFilePath;
	}

	if(m_strOMLSystemFilePath.IsEmpty())
		return FALSE;

	CStdioFileEx stdFile;
	if(!stdFile.Open(m_strOMLSystemFilePath, CFile::modeRead|CFile::typeText)) 
		return FALSE;

	CString strLine;
	while(stdFile.ReadStringEx(strLine,TRUE,_T(';')))
	{
		m_strarrayOMLSystemAutoComplete.Add(strLine);
	}

	return TRUE;
}

int CAutoCompleteString::GetOMLTemplateFileText(CString& strText,int nIndex)
{	
	//选中的是第一项则表示是刷新模板列表
	if(nIndex == 0)
	{
		RefreshOMLTemplateFileList();
		return -1;
	}

	CString strFileName = m_strOMLTempletDir + _T('\\') + GetOMLTemplateFileArray().GetAt(nIndex)+_T(".oat");
	ReadTemplateFile(strFileName,strText);
	return strText.GetLength();
}

void CAutoCompleteString::RefreshOMLTemplateFileList(LPCTSTR lpDirect)
{
	if(lpDirect)
	{
		m_strOMLTempletDir = lpDirect;
		if(m_strOMLTempletDir.Right(1) == _T('\\'))
		{
			m_strOMLTempletDir = m_strOMLTempletDir.Left(m_strOMLTempletDir.GetLength()-1);
		}
	}

	if(!m_strOMLTempletDir.IsEmpty())
	{
		GetOMLTemplateFileArray().RemoveAll();
		GetOMLTemplateFileArray().Add(_T("<刷新模板列表>"));

		GetTemplateFileList(m_strOMLTempletDir,GetOMLTemplateFileArray(),m_strOMLTempletDir.GetLength());
	}
}