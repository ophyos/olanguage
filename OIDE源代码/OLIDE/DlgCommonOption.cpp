// DlgOasmOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgCommonOption.h"


// CDlgCommonOption 对话框

IMPLEMENT_DYNAMIC(CDlgCommonOption, CResizablePage)

CDlgCommonOption::CDlgCommonOption()
	: CResizablePage(CDlgCommonOption::IDD)
{
	SetTabIcon(IDI_OPTION_COMMON);
}

CDlgCommonOption::~CDlgCommonOption()
{
}

void CDlgCommonOption::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCommonOption, CResizablePage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgCommonOption 消息处理程序

BOOL CDlgCommonOption::OnInitDialog()
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

		//设置升级类型
		CMFCPropertyGridProperty* pGroupUpdate = new CMFCPropertyGridProperty(_T("程序升级"));
		pGroupUpdate->AddSubItem(new CMFCPropertyGridProperty(_T("每次启动检测新版本"), (_variant_t)(m_bUpdateEveryTime?true:false), _T("程序每次启动都连接到服务检测新版本，有新版本就提示升级。")));
		m_wndPropertyGrid.AddProperty(pGroupUpdate);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCommonOption::OnSize(UINT nType, int cx, int cy)
{
	CResizablePage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0,0,cx,cy);
	}
}

void CDlgCommonOption::GetOption()
{
	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		//升级类型
		CMFCPropertyGridProperty* pPropertyUpdateType = m_wndPropertyGrid.GetProperty(0);
		m_bUpdateEveryTime = (_variant_t)pPropertyUpdateType->GetSubItem(0)->GetValue();
	}	
}