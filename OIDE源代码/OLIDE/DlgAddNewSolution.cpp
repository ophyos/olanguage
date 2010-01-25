// DlgAddNewSolution.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgAddNewSolution.h"
#include ".\dlgaddnewsolution.h"
#include "./Common/Global.h"
#include "./Common/Global.h"

// CDlgAddNewSolution 对话框

IMPLEMENT_DYNAMIC(CDlgAddNewSolution, CResizablePage)
CDlgAddNewSolution::CDlgAddNewSolution()
	: CResizablePage(CDlgAddNewSolution::IDD)
{
	m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon( IDI_SOLUTION );
	m_psp.hIcon = hIconTab;
}

CDlgAddNewSolution::~CDlgAddNewSolution()
{
}

void CDlgAddNewSolution::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SOLUTION, m_listctrlSolution);
}


BEGIN_MESSAGE_MAP(CDlgAddNewSolution, CResizablePage)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgAddNewSolution 消息处理程序

BOOL CDlgAddNewSolution::OnInitDialog()
{
	CResizablePage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//用设置窗口大小的方法来隐藏IDC_LIST1控件
	((CListCtrl*)GetDlgItem(IDC_LIST1))->MoveWindow(0,0,1,1);

	CBitmap bm;	
	if (!m_ilSolutionList.Create(18,18,TRUE | ILC_COLOR24,8,0))
		return FALSE;

	bm.LoadBitmap(IDB_BITMAP_ADD_NEW_ITEM);    
	m_ilSolutionList.Add(&bm,(CBitmap*)NULL);
	bm.Detach();

	m_listctrlSolution.SetImageList( &m_ilSolutionList, LVSIL_NORMAL);

	m_listctrlSolution.InsertItem(m_listctrlSolution.GetItemCount(),_T("O语言方案"),0);
	//m_listctrlSolution.InsertItem(m_listctrlSolution.GetItemCount(),"空白方案2");
	//m_listctrlSolution.InsertItem(m_listctrlSolution.GetItemCount(),"空白方案3");

	AddAnchor(IDC_LIST_SOLUTION, TOP_LEFT, BOTTOM_RIGHT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CDlgAddNewSolution::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	//// TODO:  在此更改 DC 的任何属性

	//// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;

	if( HasWhiteBackground() )
	{
		pDC->SetBkMode(TRANSPARENT);
		return ::GetSysColorBrush( COLOR_WINDOW );
	}

	return  CResizablePage::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CDlgAddNewSolution::SetBeginNewItemType(int nNewItemType)
{
	int nItemIndex = -1;
	switch(nNewItemType)
	{
	case NEW_ITEM_TYPE_SOLUCTION:
		nItemIndex = LIST_ITEM_INDEX_SOLUTION;
		break;
	default:
		break;
	}

	if(nItemIndex < 0)
		return;

	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_listctrlSolution.SetItemState(nItemIndex,flag,flag);
	m_listctrlSolution.SetFocus();
}

int CDlgAddNewSolution::GetAddNewItemType()
{
	int nCurSelIndex = m_listctrlSolution.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
	//添加空白解决方案
	if(nCurSelIndex == LIST_ITEM_INDEX_SOLUTION)
	{
		return NEW_ITEM_TYPE_SOLUCTION;
	}

	return NEW_ITEM_TYPE_NULL;
}