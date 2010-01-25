// AutoCompleteListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoCompleteListCtrl.h"

// CAutoCompleteList

IMPLEMENT_DYNAMIC(CAutoCompleteList, CListCtrlEx)

CAutoCompleteList::CAutoCompleteList()
{
	m_psAutoCompleteShift = 0;
	m_pAutoCompleteString = 0;
	SetListType(ACLT_NULL);
}

CAutoCompleteList::~CAutoCompleteList()
{
}


BEGIN_MESSAGE_MAP(CAutoCompleteList, CListCtrlEx)
	ON_WM_CHAR()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CAutoCompleteList::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RETURN, &CAutoCompleteList::OnNMReturn)	
END_MESSAGE_MAP()



// CAutoCompleteList 消息处理程序

const CString CAutoCompleteList::GetToolTip(int nItem) 
{
	CString strTip;
	if(GetSafeHwnd())
	{
		strTip = GetItemText(nItem,1);
	}

	return strTip;
}

const CString CAutoCompleteList::GetToolTip(int nItem, int nSubItem,
								 UINT nFlags, BOOL& bAsLabel)
{
	CString strTip;
	if(GetSafeHwnd())
	{
		strTip = GetItemText(nItem,nSubItem);
	}

	return strTip;
}

BOOL CAutoCompleteList::CreateList(CWnd* pParent,const RECT& rect)
{
	if(GetSafeHwnd())
	{
		DestroyWindow();
	}

	if(IsHintList())
	{
		// Create
		if(!Create(WS_CHILD | WS_THICKFRAME | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_NOCOLUMNHEADER, rect, pParent, 0x10001))
			return FALSE;
	}
	else
	{
		// Create
		if(!Create(WS_CHILD | WS_THICKFRAME | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_OWNERDRAWFIXED | LVS_SINGLESEL , rect, pParent, 0x10001))
			return FALSE;
	}
	
	SetExtendedStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP |
		LVS_EX_INFOTIP       | LVS_EX_LABELTIP);

	return TRUE;
}

BOOL CAutoCompleteList::Show(CWnd* pParent,RECT& rect,CAutoCompleteString* pAutoCompleteString,int nSyntaxType,BOOL bIsTemplateFile)
{
	m_nSyntaxType = nSyntaxType;
	m_pAutoCompleteString = pAutoCompleteString;
	bIsTemplateFile?SetListType(ACLT_TEMPLATE_FILE):SetListType(ACLT_KEYWORD);

	if(!CreateList(pParent,rect))
		return FALSE;

	if(IsTemplateFileList())
	{
		InsertColumn(0,_T("模板文件"),0,300);
		TemplateFileAddString();
	}
	else
	{
		InsertColumn(0,_T("快捷输入项"),0,100);
		InsertColumn(1,_T("注释"),0,150);

		if(m_nSyntaxType == OVST_OASM)
		{		
			m_psAutoCompleteShift = m_pAutoCompleteString->GetHeadGroupPosition();
			AutoCompleteAddString(m_psAutoCompleteShift);
		}
		else if(m_nSyntaxType == OVST_OML)
		{
			AutoCompleteAddString(0);
		}
	}
	
	// Show listctrl
	if (GetItemCount() > 0)
	{		
		ShowWindow(SW_SHOW);		
		SetSelectionMark(0);
		SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,
			LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
		SetFocus();

		return TRUE;
	}
	
	SendMessage(WM_CLOSE);

	return FALSE;
}

BOOL CAutoCompleteList::Show(CWnd* pParent,RECT& rect,const CString& strText,int nSyntaxType,TCHAR chSeparator)
{
	m_nSyntaxType = nSyntaxType;
	SetListType(ACLT_HINT);

	if(!CreateList(pParent,rect))
		return FALSE;

	InsertColumn(0,_T("项目"),0,10);	

	CString strItems = strText;
	CString strItem;
	int nPos=0,i=0,nMaxLength = 0;
	do
	{
		nPos = strItems.Find(chSeparator);
		if(nPos>=0)
		{
			strItem = strItems.Left(nPos);
			strItems = strItems.Mid(nPos+1);
		}
		else
		{
			strItem = strItems;
		}

		InsertItem(GetItemCount(),strItem);

		++i;

	} while (nPos>=0 && nPos < strText.GetLength());	

	// Show listctrl
	if (GetItemCount() > 0)
	{		
		ShowWindow(SW_SHOW);		
		SetSelectionMark(0);
		SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, 
			LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
		SetFocus();

		return TRUE;
	}
	
	SendMessage(WM_CLOSE);

	return FALSE;
}

void CAutoCompleteList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//如果是ESC键
	if(nChar == VK_ESCAPE)
	{
		CompleteCancel();
		SendMessage(WM_CLOSE);
		return;
	}		

	//如果是输入提示列表
	if(IsHintList())
	{
		////输入1-9数字
		//if(nChar >= _T('1') && nChar <= _T('9'))
		//{
		//	int nItem = nChar - _T('1');
		//	if(GetItemCount() > nItem)
		//	{
		//		CompleteItem(nItem);
		//	}
		//}

		CWnd* pParent = GetParent();
		CompleteCancel();
		SendMessage(WM_CLOSE);	

		pParent->GetParent()->SendMessage(WM_AUTO_COMPLETE_ADD_CHAR,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));
		
		return;
	}

	//如果是TAB键
	if(nChar == VK_TAB)
	{
		GetParent()->SendMessage(WM_CHAR,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));
		return;
	}	

	if(m_nSyntaxType == OVST_OASM)
	{
		switch(nChar)
		{	
			//空格键
		case VK_SPACE:
			{
				if(m_psAutoCompleteShift == m_pAutoCompleteString->GetTailGroupPosition())
				{
					m_psAutoCompleteShift = m_pAutoCompleteString->GetHeadGroupPosition();
				}
				else
				{
					m_pAutoCompleteString->GetNextGroupPosition(m_psAutoCompleteShift);
				}
				AutoCompleteAddString(m_psAutoCompleteShift);
				SetSelectionMark(0);
				SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, 
					LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
				break;
			}
			//退格键
		case VK_BACK:
			{
				if(m_psAutoCompleteShift == m_pAutoCompleteString->GetHeadGroupPosition())
				{
					m_psAutoCompleteShift = m_pAutoCompleteString->GetTailGroupPosition();
				}
				else
				{
					m_pAutoCompleteString->GetPrevGroupPosition(m_psAutoCompleteShift);
				}			

				AutoCompleteAddString(m_psAutoCompleteShift);
				SetSelectionMark(0);
				SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, 
					LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);
				break;
			}
		default:		
			{	//快捷键
				for(int i=0;i<GetItemCount();++i)
				{
					if(GetItemData(i) == nChar)
					{				
						EnsureVisible(i, FALSE);
						SetSelectionMark(i);
						SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, 
							LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);

						break;
					}
				}
			}		
		}
	}			
	else if(m_nSyntaxType == OVST_OML)
	{
		//快捷键
		for(int i=0;i<GetItemCount();++i)
		{
			if(GetItemData(i) == nChar)
			{				
				EnsureVisible(i, FALSE);
				SetSelectionMark(i);
				SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, 
					LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);				

				break;
			}
		}
	}

	CListCtrlEx::OnChar(nChar, nRepCnt, nFlags);
}

void CAutoCompleteList::AutoCompleteAddString(POSITION psAutoCompleteShift)
{
	//清除原来所有项
	DeleteAllItems();
		
	if(m_nSyntaxType == OVST_OASM)
	{
		CString strText,strComment;
		char chKey = 0;
		int nItemCount = m_pAutoCompleteString->GetItemCount(psAutoCompleteShift);
		for(int i=1;i<nItemCount;++i)
		{
			m_pAutoCompleteString->GetItemData(psAutoCompleteShift,i,strText,strComment,chKey);		

			InsertItem(i-1,strText);
			SetItemText(i-1,1,strComment);
			if(chKey)
			{
				SetItemData(i-1,chKey);
			}		
		}
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		CStringArray& strarrayOMLSystemAutoComplete = m_pAutoCompleteString->GetOMLSystemAutoCompleteArray();
		int nItemCount = strarrayOMLSystemAutoComplete.GetCount();
		CString strText,strComment;
		char chKey = 0;		
		for(int i=0;i<nItemCount;++i)
		{
			m_pAutoCompleteString->GetItemData(strarrayOMLSystemAutoComplete.GetAt(i),strText,strComment,chKey);
			
			InsertItem(i,strText);
			SetItemText(i,1,strComment);
			if(chKey)
			{
				SetItemData(i,chKey);
			}
		}
	}	
}

void CAutoCompleteList::GetAutoCompleteItemText(int nItem,CString& strText)
{
	strText = GetItemText(nItem,0);

	/*if(IsHintList())
	{
		strText = GetItemText(nItem,0);
		return;
	}

	if(m_nSyntaxType == OVST_OASM)
	{
		strText = GetItemText(nItem,0);
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		strText = GetItemText(nItem,0);
	}*/		
}

void CAutoCompleteList::GetTemplateFileItemText(int nItem,CString& strText)
{
	if(m_nSyntaxType == OVST_OASM)
	{
		m_pAutoCompleteString->GetOASMTemplateFileText(strText,nItem);
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		m_pAutoCompleteString->GetOMLTemplateFileText(strText,nItem);
	}
}

void CAutoCompleteList::TemplateFileAddString()
{
	//删除所有原有项目
	DeleteAllItems();

	CStringArray* pstrarrayTemplateFile;
	int nItemCount = 0;

	if(m_nSyntaxType == OVST_OASM)
	{
		pstrarrayTemplateFile = &m_pAutoCompleteString->GetOASMTemplateFileArray();
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		pstrarrayTemplateFile = &m_pAutoCompleteString->GetOMLTemplateFileArray();
	}
	else
	{
		//assert(false);
		return;
	}

	nItemCount = pstrarrayTemplateFile->GetCount();
	for(int i=0;i<nItemCount;++i)
	{
		InsertItem(GetItemCount(),pstrarrayTemplateFile->GetAt(i));
	}
}

BOOL CAutoCompleteList::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	m_psAutoCompleteShift = 0;
	m_pAutoCompleteString = 0;

	return CListCtrlEx::DestroyWindow();
}

void CAutoCompleteList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;	

	CompleteItem(pNMItemActivate->iItem);	
}

void CAutoCompleteList::OnNMReturn(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CompleteItem(GetSelectionMark());
}
