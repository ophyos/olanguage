// DlgAddNewProject.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgAddNewProject.h"
#include ".\dlgaddnewproject.h"
#include "./Common/Global.h"


// CDlgAddNewProject 对话框

IMPLEMENT_DYNAMIC(CDlgAddNewProject, CResizablePage)
CDlgAddNewProject::CDlgAddNewProject()
	: CResizablePage(CDlgAddNewProject::IDD)
{
	m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon( IDI_PROJECT );
	m_psp.hIcon = hIconTab;
}

CDlgAddNewProject::~CDlgAddNewProject()
{
}

void CDlgAddNewProject::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROJECT, m_listctrlProject);
}


BEGIN_MESSAGE_MAP(CDlgAddNewProject, CResizablePage)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgAddNewProject 消息处理程序

BOOL CDlgAddNewProject::OnInitDialog()
{
	CResizablePage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//用设置窗口大小的方法来隐藏IDC_LIST1控件
	((CListCtrl*)GetDlgItem(IDC_LIST1))->MoveWindow(0,0,1,1);

	CBitmap bm;	
	if (!m_ilProjectList.Create(18,18,TRUE | ILC_COLOR24,8,0))
		return FALSE;

	bm.LoadBitmap(IDB_BITMAP_ADD_NEW_ITEM);    
	m_ilProjectList.Add(&bm,(CBitmap*)NULL);
	bm.Detach();

	m_listctrlProject.SetImageList( &m_ilProjectList, LVSIL_NORMAL);

	m_listctrlProject.InsertItem(m_listctrlProject.GetItemCount(),_T("Win32 应用程序"),1);
	m_listctrlProject.InsertItem(m_listctrlProject.GetItemCount(),_T("Win32 控制台程序"),1);
	m_listctrlProject.InsertItem(m_listctrlProject.GetItemCount(),_T("Win32 动态链接库"),1);
	//m_listctrlProject.InsertItem(m_listctrlProject.GetItemCount(),_T("Win32 静态库"),1);
	
	AddAnchor(IDC_LIST_PROJECT, TOP_LEFT, BOTTOM_RIGHT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CDlgAddNewProject::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CDlgAddNewProject::SetBeginNewItemType(int nNewItemType)
{
	int nItemIndex = -1;
	switch(nNewItemType)
	{
	case NEW_ITEM_TYPE_PROJECT_WIN32_WINDOWS:
		nItemIndex = LIST_ITEM_INDEX_PROJECT_WIN32_WINDOWS;
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_CONSOLE:
		nItemIndex = LIST_ITEM_INDEX_PROJECT_WIN32_CONSOLE;
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_DLL:
		nItemIndex = LIST_ITEM_INDEX_PROJECT_WIN32_DLL;
		break;
	case NEW_ITEM_TYPE_PROJECT_WIN32_LIB:
		nItemIndex = LIST_ITEM_INDEX_PROJECT_WIN32_LIB;
		break;
	default:
		break;
	}

	if(nItemIndex < 0)
		return;

	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_listctrlProject.SetItemState(nItemIndex,flag,flag);
	m_listctrlProject.SetFocus();
}

int CDlgAddNewProject::GetAddNewItemType()
{
	int nCurSelIndex = m_listctrlProject.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
	//添加工程
	switch(nCurSelIndex)
	{
	case LIST_ITEM_INDEX_PROJECT_WIN32_WINDOWS:
		return NEW_ITEM_TYPE_PROJECT_WIN32_WINDOWS;
	case LIST_ITEM_INDEX_PROJECT_WIN32_CONSOLE:
		return NEW_ITEM_TYPE_PROJECT_WIN32_CONSOLE;
	case LIST_ITEM_INDEX_PROJECT_WIN32_DLL:
		return NEW_ITEM_TYPE_PROJECT_WIN32_DLL;
	case LIST_ITEM_INDEX_PROJECT_WIN32_LIB:
		return NEW_ITEM_TYPE_PROJECT_WIN32_LIB;
	}

	return NEW_ITEM_TYPE_NULL;
}

