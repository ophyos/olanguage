// DlgDoasmOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgDoasmOption.h"


// CDlgDoasmOption 对话框

IMPLEMENT_DYNAMIC(CDlgDoasmOption, CResizablePage)

CDlgDoasmOption::CDlgDoasmOption()
	: CResizablePage(CDlgDoasmOption::IDD)
{
	SetTabIcon(IDI_OPTION_OASM);
}

CDlgDoasmOption::~CDlgDoasmOption()
{
}

void CDlgDoasmOption::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDoasmOption, CResizablePage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgDoasmOption 消息处理程序

BOOL CDlgDoasmOption::OnInitDialog()
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

		//设置反汇编器路径
		CMFCPropertyGridProperty* pPropertyOasm = new CMFCPropertyGridProperty(_T("反汇编器"));
		static TCHAR BASED_CODE szFilter[] = _T("O反汇编程序(*.exe)|*.exe|所有文件(*.*)|*.*||");
		CMFCPropertyGridFileProperty* pPropertyOasmFile = new CMFCPropertyGridFileProperty(_T("O反汇编程序"), TRUE, _T(""), _T("exe"), 0, szFilter, _T("O反汇编应用程序"));
		pPropertyOasmFile->SetValue(COleVariant(m_strDoasmPath));
		pPropertyOasm->AddSubItem(pPropertyOasmFile);		
		m_wndPropertyGrid.AddProperty(pPropertyOasm);

		//设置语言文件路径
		CMFCPropertyGridProperty* pPropertyLanguage = new CMFCPropertyGridProperty(_T("语言文件"));
		static TCHAR BASED_CODE szFilterLanguage[] = _T("O反汇编语言文件(*.oic)|*.oic|所有文件(*.*)|*.*||");
		CMFCPropertyGridFileProperty* pPropertyLanguageFile = new CMFCPropertyGridFileProperty(_T("O反汇编语言文件"), TRUE, _T(""), _T("exe"), 0, szFilterLanguage, _T("O反汇编语言内码文件"));
		pPropertyLanguageFile->SetValue(COleVariant(m_strOasmLanguagePath));
		pPropertyLanguage->AddSubItem(pPropertyLanguageFile);
		m_wndPropertyGrid.AddProperty(pPropertyLanguage);		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgDoasmOption::OnSize(UINT nType, int cx, int cy)
{
	CResizablePage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0,0,cx,cy);
	}
}

void CDlgDoasmOption::GetOption()
{
	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		CMFCPropertyGridProperty* pPropertyOasm = m_wndPropertyGrid.GetProperty(0);
		CMFCPropertyGridFileProperty* pPropertyOasmFile = (CMFCPropertyGridFileProperty*)pPropertyOasm->GetSubItem(0);
		m_strDoasmPath = (CString)pPropertyOasmFile->GetValue();

		CMFCPropertyGridProperty* pPropertyLanguage = m_wndPropertyGrid.GetProperty(1);
		CMFCPropertyGridFileProperty* pPropertyLanguageFile = (CMFCPropertyGridFileProperty*)pPropertyLanguage->GetSubItem(0);
		m_strOasmLanguagePath = (CString)pPropertyLanguageFile->GetValue();		
	}	
}