
#include "stdafx.h"
#include "HintString.h"
#include "./StdioFile/StdioFileEx.h"
#include "../Controls/scintilla/SyntaxCtrl.h"
#include "../MainFrm.h"
#include "../Common/Common.h"

CHintString::CHintString()
{
	//OASM自动完成提示数组
	m_nOASMAutoCompleteItemCount = 0;
	m_phsOASMAutoComplete = NULL;

	//OASM信息提示数组
	m_nOASMTipDataCount = 0;
	m_phsOASMTipData = NULL;	

	//OML自动完成提示数组
	m_nOMLAutoCompleteItemCount = 0;
	m_phsOMLAutoComplete = NULL;

	//OML信息提示数组
	m_nOMLTipDataCount = 0;
	m_phsOMLTipData = NULL;
}

CHintString::~CHintString()
{	
	ClearData(m_phsOASMAutoComplete,m_nOASMAutoCompleteItemCount);
	ClearData(m_phsOASMTipData,m_nOASMTipDataCount);	
	ClearData(m_phsOMLAutoComplete,m_nOMLAutoCompleteItemCount);
	ClearData(m_phsOMLTipData,m_nOMLTipDataCount);
}

void CHintString::LoadHintData()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString strOASMAutoCompleteFileName = pMainFrame->m_systemOption.m_strOASMAutoCompleteFileName;
	CString strOASMTipFileName = pMainFrame->m_systemOption.m_strOASMTipFileName;

	CString strAppDir = pMainFrame->GetAppDirectory();	
	if(!strOASMAutoCompleteFileName.IsEmpty() && strOASMAutoCompleteFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOASMAutoCompleteFileName,strAppDir);
	}
	if(!strOASMTipFileName.IsEmpty() && strOASMTipFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOASMTipFileName,strAppDir);
	}
	
	if(m_strOASMAutoCompleteFileName != strOASMAutoCompleteFileName)
	{
		m_strOASMAutoCompleteFileName = strOASMAutoCompleteFileName;
		ClearData(m_phsOASMAutoComplete,m_nOASMAutoCompleteItemCount);
		LoadData(m_strOASMAutoCompleteFileName,m_phsOASMAutoComplete,m_nOASMAutoCompleteItemCount);
	}	
	if(m_strOASMTipFileName != strOASMTipFileName)
	{
		m_strOASMTipFileName = strOASMTipFileName;
		ClearData(m_phsOASMTipData,m_nOASMTipDataCount);
		LoadData(m_strOASMTipFileName,m_phsOASMTipData,m_nOASMTipDataCount);	
	}

	//////////////////////////////////////////////////////////////////////////
	
	CString strOMLAutoCompleteFileName = pMainFrame->m_systemOption.m_strOMLAutoCompleteFileName;
	CString strOMLTipFileName = pMainFrame->m_systemOption.m_strOMLTipFileName;
	
	if(!strOMLAutoCompleteFileName.IsEmpty() && strOMLAutoCompleteFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOMLAutoCompleteFileName,strAppDir);
	}
	if(!strOMLTipFileName.IsEmpty() && strOMLTipFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOMLTipFileName,strAppDir);
	}
	
	if(m_strOMLAutoCompleteFileName != strOMLAutoCompleteFileName)
	{
		m_strOMLAutoCompleteFileName = strOMLAutoCompleteFileName;
		ClearData(m_phsOMLAutoComplete,m_nOMLAutoCompleteItemCount);
		LoadData(m_strOMLAutoCompleteFileName,m_phsOMLAutoComplete,m_nOMLAutoCompleteItemCount);
	}	
	if(m_strOMLTipFileName != strOMLTipFileName)
	{
		m_strOMLTipFileName = strOMLTipFileName;
		ClearData(m_phsOMLTipData,m_nOMLTipDataCount);
		LoadData(m_strOMLTipFileName,m_phsOMLTipData,m_nOMLTipDataCount);	
	}	
}

BOOL CHintString::LoadConfigFile(const CString& strAutoFileName,CStringArray& strarrayData)
{
	CStdioFileEx stdFile;
	if(stdFile.Open(strAutoFileName, CFile::modeRead|CFile::typeText)) 
	{		
		CString strLine;
		while(stdFile.ReadStringEx(strLine,TRUE,_T(';')))
		{
			while(strLine[strLine.GetLength()-1] == _T('\\'))
			{
				strLine.TrimRight(_T('\\'));

				CString strTemp;
				if(stdFile.ReadStringEx(strTemp,TRUE,_T(';')))
				{
					strLine += strTemp;
				}
			}

			strarrayData.Add(strLine);
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CHintString::LoadData(const CString& strAutoFileName,HINT_STRING*& phsData,int& nCount)
{	
	CStringArray strarrayAutoData;
	if(!LoadConfigFile(strAutoFileName,strarrayAutoData))
		return FALSE;

	nCount = strarrayAutoData.GetCount();
	if(nCount > 0)
	{
		phsData = new HINT_STRING[nCount];		
		int nPos = 0,nNextPos = 0;
		CString strLine;
		for(int i=0;i<nCount;++i)
		{		
			strLine = strarrayAutoData[i];

			nPos = strLine.Find(_T('\''));
			if(nPos >= 0)
			{
				nNextPos = strLine.Find(_T('\''),nPos+1);
				phsData[i].m_strInput = strLine.Mid(nPos+1,nNextPos-nPos-1);
			}			

			nPos = strarrayAutoData[i].Find(_T('"'));
			if(nPos >= 0)
			{
				nNextPos = strLine.Find(_T('"'),nPos+1);
				while((nNextPos > 1) && strLine.GetAt(nNextPos-1) == _T('\\'))
				{
					nNextPos = strLine.Find(_T('"'),nNextPos+1);
				}
				phsData[i].m_strHint = strLine.Mid(nPos+1,nNextPos-nPos-1);
				phsData[i].m_strHint.Replace(_T("\\\""),_T("\""));
				phsData[i].m_strHint.Replace(_T("\\n"),_T("\n"));
				phsData[i].m_strHint.Replace(_T("\\r"),_T("\r"));
			}
		}

		Convert2UTF8(phsData,nCount);

		return TRUE;
	}	

	return FALSE;
}

void CHintString::Convert2UTF8(HINT_STRING* phsData,int nItemCount)
{
#ifdef _UNICODE
	for(int i=0;i<nItemCount;++i)
	{
		CScintillaCtrl::W2UTF8(phsData[i].m_strInput,-1,phsData[i].m_pInput);
	}
#else
	for(int i=0;i<nItemCount;++i)
	{		
		phsData[i].m_pInput = (LPCTSTR)phsData[i].m_strInput;
	}
#endif
}

void CHintString::ClearData(HINT_STRING*& phsData,int& nItemCount)
{
	if(phsData)
	{
		for(int i=0;i<nItemCount;++i)
		{
			if(phsData[i].m_pInput)
			{
				delete[] phsData[i].m_pInput;
				phsData[i].m_pInput = NULL;
			}
		}

		nItemCount = 0;

		delete[] phsData;
		phsData = NULL;
	}	
}

int CHintString::GetItemCount(int nHintStringType)
{
	ASSERT(nHintStringType>HST_NULL && nHintStringType<HST_END);

	switch(nHintStringType)
	{	
	case HST_OASM_AUTO_COMPLETE:
		return m_nOASMAutoCompleteItemCount;
	case HST_OASM_TIP:
		return m_nOASMTipDataCount;	
	case HST_OML_AUTO_COMPLETE:
		return m_nOMLAutoCompleteItemCount;
	case HST_OML_TIP:
		return m_nOMLTipDataCount;
	}

	return 0;
}

char* CHintString::GetItemInput(int nHintStringType,int nItem)
{
	ASSERT(nHintStringType>HST_NULL && nHintStringType<HST_END);
	ASSERT(nItem>=0 && GetItemCount(nHintStringType));

	switch(nHintStringType)
	{	
	case HST_OASM_AUTO_COMPLETE:
		return m_phsOASMAutoComplete[nItem].m_pInput;
	case HST_OASM_TIP:
		return m_phsOASMTipData[nItem].m_pInput;	
	case HST_OML_AUTO_COMPLETE:
		return m_phsOMLAutoComplete[nItem].m_pInput;
	case HST_OML_TIP:
		return m_phsOMLTipData[nItem].m_pInput;
	}

	return NULL;
}

CString& CHintString::GetItemHint(int nHintStringType,int nItem)
{
	ASSERT(nHintStringType>HST_NULL && nHintStringType<HST_END);
	ASSERT(nItem>=0 && GetItemCount(nHintStringType));

	switch(nHintStringType)
	{	
	case HST_OASM_AUTO_COMPLETE:
		return m_phsOASMAutoComplete[nItem].m_strHint;
	case HST_OASM_TIP:
		return m_phsOASMTipData[nItem].m_strHint;	
	case HST_OML_AUTO_COMPLETE:
		return m_phsOMLAutoComplete[nItem].m_strHint;
	case HST_OML_TIP:
		return m_phsOMLTipData[nItem].m_strHint;
	}

	return *((CString*)NULL);
}