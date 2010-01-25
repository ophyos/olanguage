// DlgLinkOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgLinkOption.h"


// CDlgLinkOption 对话框

IMPLEMENT_DYNAMIC(CDlgLinkOption, CResizablePage)

CDlgLinkOption::CDlgLinkOption()
	: CResizablePage(CDlgLinkOption::IDD)
{
	SetTabIcon(IDI_OPTION_LINK );
}

CDlgLinkOption::~CDlgLinkOption()
{
}

void CDlgLinkOption::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLinkOption, CResizablePage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgLinkOption 消息处理程序

BOOL CDlgLinkOption::OnInitDialog()
{
	CResizablePage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if(m_wndPropertyGrid.GetSafeHwnd() == 0)
	{
		if (!m_wndPropertyGrid.Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 2))
		{
			TRACE0("未能创建属性网格\n");
			return FALSE;      // 未能创建
		}
		m_wndPropertyGrid.SetOwner(this);

		m_wndPropertyGrid.EnableHeaderCtrl(FALSE);
		m_wndPropertyGrid.EnableDescriptionArea();
		m_wndPropertyGrid.SetVSDotNetLook();
		m_wndPropertyGrid.MarkModifiedProperties();

		//设置链接器路径
		CMFCPropertyGridProperty* pPropertyLink = new CMFCPropertyGridProperty(_T("链接器"));
		static TCHAR BASED_CODE szFilter[] = _T("链接程序(*.exe)|*.exe|所有文件(*.*)|*.*||");
		CMFCPropertyGridFileProperty* pPropertyLinkFile = new CMFCPropertyGridFileProperty(_T("链接程序"), TRUE, _T(""), _T("exe"), 0, szFilter, _T("链接器应用程序"));
		pPropertyLinkFile->SetValue(COleVariant(m_strLinkerFileName));
		pPropertyLink->AddSubItem(pPropertyLinkFile);
		m_wndPropertyGrid.AddProperty(pPropertyLink);		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgLinkOption::OnSize(UINT nType, int cx, int cy)
{
	CResizablePage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0,0,cx,cy);
	}
}

void CDlgLinkOption::GetOption()
{
	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		//设置链接器路径
		CMFCPropertyGridProperty* pPropertyLink = m_wndPropertyGrid.GetProperty(0);
		CMFCPropertyGridFileProperty* pPropertyLinkFile = (CMFCPropertyGridFileProperty*)pPropertyLink->GetSubItem(0);
		m_strLinkerFileName = (CString)pPropertyLinkFile->GetValue();		
	}
}