// DlgProjectProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include ".\dlgprojectproperty.h"


// CDlgProjectProperty 对话框

IMPLEMENT_DYNAMIC(CDlgProjectProperty, CResizableDialog)
CDlgProjectProperty::CDlgProjectProperty(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CDlgProjectProperty::IDD, pParent)
{
	
}

CDlgProjectProperty::~CDlgProjectProperty()
{
}

void CDlgProjectProperty::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProjectProperty, CResizableDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgProjectProperty 消息处理程序

bool CDlgProjectProperty::RegisterSheet(UINT nID, CPropertySheet& rSheet)
{
	CWnd* pWnd = GetDlgItem( nID );
	if( !pWnd )
	{
		ASSERT( FALSE );
		return false;
	}

	rSheet.Create( this, WS_CHILD | WS_VISIBLE , 0 );

	if( 0 != rSheet.GetPageCount() )
	{
		rSheet.ModifyStyleEx( 0, WS_EX_CONTROLPARENT );
		rSheet.ModifyStyle( 0, WS_TABSTOP );

		//CRect rcSheet;
		//pWnd->GetWindowRect( &rcSheet );
		//ScreenToClient( &rcSheet );
		//		rSheet.SetWindowPos( NULL, rcSheet.left, rcSheet.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE );
		//rSheet.SetWindowPos( NULL, 0, 0, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE );

		CRect rect;
		//GetClientRect( &rect );
		GetDlgItem( nID )->GetWindowRect( rect );
		ScreenToClient( rect );
		rect.right += 5;
		rSheet.MoveWindow(rect);
	}

	return true;
}


BOOL CDlgProjectProperty::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//添加页
	m_sheetItem.AddPage( &m_dlgLinkProperty );

	m_sheetItem.SetTreeViewMode( TRUE, TRUE, TRUE );
	m_sheetItem.SetIsResizable( true );
	RegisterSheet( IDC_PROJCET_PROPERTY_ITEM_RECT, m_sheetItem );

	// 设置控件锚点
	AddAnchor( m_sheetItem, TOP_LEFT, BOTTOM_RIGHT );

	AddAnchor( IDOK, BOTTOM_RIGHT );
	AddAnchor( IDCANCEL, BOTTOM_RIGHT );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

INT_PTR CDlgProjectProperty::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CResizableDialog::DoModal();
}

void CDlgProjectProperty::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	m_dlgLinkProperty.GetOption();

	CResizableDialog::OnOK();
}
