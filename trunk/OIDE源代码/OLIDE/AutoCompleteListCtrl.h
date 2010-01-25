#pragma once


// CAutoCompleteList

#include "./Controls/ListCtrl/ListViewCtrlEx.h"
#include "./Data/AutoCompleteString.h"

#include "UserWmMsg.h"

enum OLIDE_VIEW_SYNTAX_TYPE
{
	OVST_NULL,
	OVST_OASM,  //O汇编
	OVST_OML,   //O中间语言
};

enum AUTO_COMPLETE_LIST_TYPE
{
	ACLT_NULL,
	ACLT_KEYWORD,
	ACLT_TEMPLATE_FILE,
	ACLT_HINT,
};

class CAutoCompleteList : public CListCtrlEx
{
	DECLARE_DYNAMIC(CAutoCompleteList)

public:
	CAutoCompleteList();
	virtual ~CAutoCompleteList();	

private:

	int m_nSyntaxType;
	int m_nListType;
	POSITION m_psAutoCompleteShift;  //自动完成档的位置	
	CAutoCompleteString* m_pAutoCompleteString;

public:
	
	BOOL Show(CWnd* pParent,RECT& rect,const CString& strText,int nSyntaxType,TCHAR chSeparator);
	BOOL Show(CWnd* pParent,RECT& rect,CAutoCompleteString* pAutoCompleteString,int nSyntaxType,BOOL bIsTemplateFile);
	void GetAutoCompleteItemText(int nItem,CString& strText);
	void GetTemplateFileItemText(int nItem,CString& strText);
	void TemplateFileAddString();
	BOOL IsKeyWordList(){ return (m_nListType == ACLT_KEYWORD); }
	BOOL IsTemplateFileList(){ return (m_nListType == ACLT_TEMPLATE_FILE); }
	BOOL IsHintList(){ return (m_nListType == ACLT_HINT); };

private:

	BOOL CreateList(CWnd* pParent,const RECT& rect);	
	void SetListType(int nListType){ m_nListType = nListType; }
	void CompleteItem(int nItem){ ::SendMessage(GetParent()->GetParent()->GetSafeHwnd(),WM_AUTO_COMPLETE_SELECTED,NULL,(LPARAM)nItem);};
	void CompleteCancel(){ ::SendMessage(GetParent()->GetParent()->GetSafeHwnd(),WM_AUTO_COMPLETE_CANCEL,NULL,NULL);};
	void AutoCompleteAddString(POSITION psAutoCompleteShift);
	
protected:

	virtual const CString GetToolTip(int nItem);
	virtual const CString GetToolTip(int nItem, int nSubItem,UINT nFlags, BOOL& bAsLabel);
	virtual BOOL DestroyWindow();

protected:
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReturn(NMHDR *pNMHDR, LRESULT *pResult);	
};


