// DlgOMLOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgOMLOption.h"


// CDlgOMLOption 对话框

IMPLEMENT_DYNAMIC(CDlgOMLOption, CResizablePage)

CDlgOMLOption::CDlgOMLOption()
	: CResizablePage(CDlgOMLOption::IDD)
{
	SetTabIcon(IDI_OPTION_OASM);
}

CDlgOMLOption::~CDlgOMLOption()
{
}

void CDlgOMLOption::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOMLOption, CResizablePage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgOMLOption 消息处理程序

BOOL CDlgOMLOption::OnInitDialog()
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

		//设置汇编器路径
		CMFCPropertyGridProperty* pPropertyOML = new CMFCPropertyGridProperty(_T("O中间语言"));
		static TCHAR BASED_CODE szFilter[] = _T("O中间语言编译器(*.exe)|*.exe|所有文件(*.*)|*.*||");
		CMFCPropertyGridFileProperty* pPropertyOMLFile = new CMFCPropertyGridFileProperty(_T("O中间语言编译程序"), TRUE, _T(""), _T("exe"), 0, szFilter, _T("O中间语言编译应用程序"));
		pPropertyOMLFile->SetValue(COleVariant(m_strOMLPath));
		pPropertyOML->AddSubItem(pPropertyOMLFile);		
		m_wndPropertyGrid.AddProperty(pPropertyOML);

		//设置语言文件路径
		CMFCPropertyGridProperty* pPropertyLanguage = new CMFCPropertyGridProperty(_T("语言文件"));
		static TCHAR BASED_CODE szFilterLanguage[] = _T("O中间语言内码文件(*.oic)|*.oic|所有文件(*.*)|*.*||");
		CMFCPropertyGridFileProperty* pPropertyLanguageFile = new CMFCPropertyGridFileProperty(_T("O中间语言内码文件"), TRUE, _T(""), _T("exe"), 0, szFilterLanguage, _T("O中间语言内码文件"));
		pPropertyLanguageFile->SetValue(COleVariant(m_strOMLLanguagePath));
		pPropertyLanguage->AddSubItem(pPropertyLanguageFile);
		m_wndPropertyGrid.AddProperty(pPropertyLanguage);		
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgOMLOption::OnSize(UINT nType, int cx, int cy)
{
	CResizablePage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0,0,cx,cy);
	}
}

void CDlgOMLOption::GetOption()
{
	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		CMFCPropertyGridProperty* pPropertyOML = m_wndPropertyGrid.GetProperty(0);
		CMFCPropertyGridFileProperty* pPropertyOMLFile = (CMFCPropertyGridFileProperty*)pPropertyOML->GetSubItem(0);
		m_strOMLPath = (CString)pPropertyOMLFile->GetValue();

		CMFCPropertyGridProperty* pPropertyLanguage = m_wndPropertyGrid.GetProperty(1);
		CMFCPropertyGridFileProperty* pPropertyLanguageFile = (CMFCPropertyGridFileProperty*)pPropertyLanguage->GetSubItem(0);
		m_strOMLLanguagePath = (CString)pPropertyLanguageFile->GetValue();		
	}	
}