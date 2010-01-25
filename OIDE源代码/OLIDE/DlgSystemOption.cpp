// DlgSystemOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgSystemOption.h"


// CDlgSystemOption 对话框

IMPLEMENT_DYNAMIC(CDlgSystemOption, CResizableDialog)

CDlgSystemOption::CDlgSystemOption(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CDlgSystemOption::IDD, pParent)
{

}

CDlgSystemOption::~CDlgSystemOption()
{
}

void CDlgSystemOption::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSystemOption, CResizableDialog)
	ON_BN_CLICKED(IDOK, &CDlgSystemOption::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSystemOption 消息处理程序

bool CDlgSystemOption::RegisterSheet(UINT nID, CPropertySheet& rSheet)
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
BOOL CDlgSystemOption::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//添加页	
	m_sheetItem.AddPage( &m_dlgCommonOption );
	m_sheetItem.AddPage( &m_dlgOMLOption );	
	m_sheetItem.AddPage( &m_dlgOasmOption );
	m_sheetItem.AddPage( &m_dlgLinkOption );
	m_sheetItem.AddPage( &m_dlgOMLEditOption );	
	m_sheetItem.AddPage( &m_dlgOasmEditOption );
	m_sheetItem.AddPage( &m_dlgDoasmOption );
		
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
void CDlgSystemOption::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	m_dlgCommonOption.GetOption();
	m_dlgOMLOption.GetOption();
	m_dlgOasmOption.GetOption();
	m_dlgLinkOption.GetOption();
	m_dlgOMLEditOption.GetOption();
	m_dlgOasmEditOption.GetOption();
	m_dlgDoasmOption.GetOption();

	CResizableDialog::OnOK();
}
