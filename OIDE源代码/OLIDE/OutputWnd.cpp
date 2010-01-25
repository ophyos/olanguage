
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);
	
	if( !m_wndOutputPaneBuild.Create( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL |  ES_MULTILINE | ES_LEFT  , CRect(0,0,0,0), this ,0xF3 ) )
	{
		TRACE0("Failed to create view for OutputBuild\n");
		return NULL;
	}
	m_wndOutputPaneBuild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	
	
	m_wndOutputPaneBuild.SetFont(&m_Font);
	
	Clear();	

	m_wndOutputPaneBuild.SetReadOnly(TRUE);

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	m_wndOutputPaneBuild.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_Font);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::InsertText(const CString& strMsg)
{	
	if(m_wndOutputPaneBuild.GetSafeHwnd())
	{
		m_wndOutputPaneBuild.InsertText(strMsg);
	}
}

void COutputWnd::Clear()
{	
	if(m_wndOutputPaneBuild.GetSafeHwnd())
	{
		m_wndOutputPaneBuild.Clear();			
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("复制输出"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("清除输出"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}



/////////////////////////////////////////////////////////////////////////////
// COutputBuild

COutputBuild::COutputBuild()
{
}

COutputBuild::~COutputBuild()
{
}

BEGIN_MESSAGE_MAP(COutputBuild, CRichEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

void COutputBuild::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputBuild::OnEditCopy()
{
	Copy();
}

void COutputBuild::OnEditClear()
{
	Clear();
}

void COutputBuild::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();
	}
}

void COutputBuild::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	//CRichEdit::OnLButtonDblClk(nFlags, point);

	TCHAR buf[1024];
	long nStartChar, nEndChar;
	int nline = 0;

	CRichEditCtrl::GetSel( nStartChar, nEndChar );
	nline = LineFromChar(nStartChar);
	int nLength = CRichEditCtrl::GetLine( nline, buf, 1024 );
	buf[nLength] = 0;

	CString strLine = buf;	
	CString strFindWord = _T("错误 ");
	int nPos = strLine.Find(strFindWord);
	if(nPos < 0)
	{
		strFindWord = _T("警告 ");
		nPos = strLine.Find(strFindWord);
	}
	if(nPos < 0)
	{
		CRichEdit::OnLButtonDblClk(nFlags, point);
		return;
	}
	
	CString strFileName;
	int nLine = 1;	
	int nRow = 1;

	//得到所在文件名称
	strLine = strLine.Right(strLine.GetLength() - nPos - strFindWord.GetLength());
	strLine.TrimLeft();
	strFindWord = _T(" 行: ");
	nPos = strLine.Find(strFindWord);
	if(nPos < 0)
		return;
	strFileName = strLine.Left(nPos);
	strFileName.Trim();

	//得到所在行
	strLine = strLine.Right(strLine.GetLength() - nPos - strFindWord.GetLength());
	strLine.TrimLeft();
	strFindWord = _T(" 列: ");
	nPos = strLine.Find(strFindWord);
	if(nPos > 0)
	{		
		CString strLineNo = strLine.Left(nPos);
		strLineNo.Trim();	
		#ifdef _UNICODE
			nLine = wcstol(strLineNo,NULL,10);
		#else
			nLine = strtol(strLineNo,NULL,10);
		#endif			

		//得到所在列
		strLine = strLine.Right(strLine.GetLength() - nPos - strFindWord.GetLength());
		strLine.TrimLeft();
		strFindWord = _T(" ");
		nPos = strLine.Find(strFindWord);
		if(nPos > 0)
		{
			CString strRowNo = strLine.Left(nPos);
			strRowNo.Trim();	
			#ifdef _UNICODE
				nRow = wcstol(strRowNo,NULL,10);
			#else
				nRow = strtol(strRowNo,NULL,10);
			#endif	
		}
	}	

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();	
	pMainFrame->OpenDocument(strFileName,nLine-1,nRow-1);
}

void COutputBuild::Clear()
{
	CRichEdit::Clear();

	InsertText(_T("--------------------------------- O语言编译报告 ---------------------------------\n"));
}