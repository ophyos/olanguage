// DlgLinkOption.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "DlgLinkProperty.h"


// CDlgLinkProperty 对话框

IMPLEMENT_DYNAMIC(CDlgLinkProperty, CResizablePage)

CDlgLinkProperty::CDlgLinkProperty()
	: CResizablePage(CDlgLinkProperty::IDD)
{
	SetTabIcon(IDI_OPTION_LINK );
}

CDlgLinkProperty::~CDlgLinkProperty()
{
}

void CDlgLinkProperty::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLinkProperty, CResizablePage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgLinkProperty 消息处理程序

TCHAR* g_pchLinkSubSystemOption[] = 
{
	_T("控制台程序(/SUBSYSTEM:CONSOLE)"),
	_T("WINDOWS程序(/SUBSYSTEM:WINDOWS)"),
};

TCHAR* g_pchLinkProgrammTypeOption[] = 
{
	_T("运行程序(.EXE)"),
	_T("动态链接库(.DLL)"),
	_T("库文件(.LIB)"),
};

BOOL CDlgLinkProperty::OnInitDialog()
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
		
		//设置代码目录
		CMFCPropertyGridProperty* pPropertyCodeDir = new CMFCPropertyGridProperty(_T("代码目录"));
		pPropertyCodeDir->AddSubItem(new CMFCPropertyGridFileProperty(_T("代码目录"), m_strCodeDir,0,_T("工程中需要编译的代码目录")));
		pPropertyCodeDir->AddSubItem(new CMFCPropertyGridFileProperty(_T("资源目录"), m_strResourceDir,0,_T("工程中需要编译的资源目录")));
		m_wndPropertyGrid.AddProperty(pPropertyCodeDir);

		//设置链接生成的程序类型
		int nLinkProgrammTypeOptionCount = sizeof(g_pchLinkProgrammTypeOption)/sizeof(g_pchLinkProgrammTypeOption[0]);
		if(m_nLinkProgrammType<0 || m_nLinkProgrammType>nLinkProgrammTypeOptionCount)
		{
			m_nLinkProgrammType = 0;
		}
		CMFCPropertyGridProperty* pPropertyProgrammType = new CMFCPropertyGridProperty(_T("程序类型"));
		CMFCPropertyGridProperty* pPropertyProgrammTypeItem = new CMFCPropertyGridProperty(_T("生成程序类型"), g_pchLinkSubSystemOption[m_nLinkSubSystem], _T("设置程序生成程序类型为执行程序(.EXE)、动态链接库(.DLL)、库文件(.LIB)"));
		for(int i=0;i<nLinkProgrammTypeOptionCount;++i)
		{
			pPropertyProgrammTypeItem->AddOption(g_pchLinkProgrammTypeOption[i]);
		}
		pPropertyProgrammTypeItem->AllowEdit(FALSE);
		pPropertyProgrammTypeItem->SetValue(g_pchLinkProgrammTypeOption[m_nLinkProgrammType]);

		pPropertyProgrammType->AddSubItem(pPropertyProgrammTypeItem);
		m_wndPropertyGrid.AddProperty(pPropertyProgrammType);

		//设置子系统
		int nLinkSubSystemOptionCount = sizeof(g_pchLinkSubSystemOption)/sizeof(g_pchLinkSubSystemOption[0]);
		if(m_nLinkSubSystem<0 || m_nLinkSubSystem>nLinkSubSystemOptionCount)
		{
			m_nLinkSubSystem = 0;
		}
		CMFCPropertyGridProperty* pPropertySubSystem = new CMFCPropertyGridProperty(_T("系统设置"));
		CMFCPropertyGridProperty* pPropertySubSystemItem = new CMFCPropertyGridProperty(_T("生成文件运行系统"), g_pchLinkSubSystemOption[m_nLinkSubSystem], _T("设置程序生成类型:/SUBSYSTEM:CONSOLE生成控制台程序 /SUBSYSTEM:WINDOWS生成WINDOWS程序"));
		for(int i=0;i<nLinkSubSystemOptionCount;++i)
		{
			pPropertySubSystemItem->AddOption(g_pchLinkSubSystemOption[i]);
		}
		pPropertySubSystemItem->AllowEdit(FALSE);
		pPropertySubSystemItem->SetValue(g_pchLinkSubSystemOption[m_nLinkSubSystem]);

		pPropertySubSystem->AddSubItem(pPropertySubSystemItem);
		m_wndPropertyGrid.AddProperty(pPropertySubSystem);
		
		//设置调试版输出
		CMFCPropertyGridProperty* pPropertyOutputDebug = new CMFCPropertyGridProperty(_T("调试版输出"));		
		pPropertyOutputDebug->AddSubItem(new CMFCPropertyGridFileProperty(_T("中间文件目录"), m_strDebugMiddleFileDir,0,_T("编译过程中生成的中间文件的目录")));
		pPropertyOutputDebug->AddSubItem(new CMFCPropertyGridProperty(_T("生成文件名"), (_variant_t)m_strDebugExeFileName, _T("生成执行文件的路径名称")));
		m_wndPropertyGrid.AddProperty(pPropertyOutputDebug);

		//设置纯净版输出
		CMFCPropertyGridProperty* pPropertyOutputRelease = new CMFCPropertyGridProperty(_T("纯净版输出"));		
		pPropertyOutputRelease->AddSubItem(new CMFCPropertyGridFileProperty(_T("中间文件目录"), m_strReleaseMiddleFileDir,0,_T("编译过程中生成的中间文件的目录")));
		pPropertyOutputRelease->AddSubItem(new CMFCPropertyGridProperty(_T("生成文件名"), (_variant_t)m_strReleaseExeFileName, _T("生成执行文件的路径名称")));
		m_wndPropertyGrid.AddProperty(pPropertyOutputRelease);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgLinkProperty::OnSize(UINT nType, int cx, int cy)
{
	CResizablePage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0,0,cx,cy);
	}
}

void CDlgLinkProperty::GetOption()
{
	if(m_wndPropertyGrid.GetSafeHwnd())
	{
		//设置代码目录		
		CMFCPropertyGridProperty* pPropertyCodeDir = m_wndPropertyGrid.GetProperty(0);
		m_strCodeDir = (CString)pPropertyCodeDir->GetSubItem(0)->GetValue();
		m_strResourceDir = (CString)pPropertyCodeDir->GetSubItem(1)->GetValue();
		
		//设置程序类型
		CMFCPropertyGridProperty* pPropertyProgrammType = m_wndPropertyGrid.GetProperty(1);
		CMFCPropertyGridProperty* pPropertyProgrammTypeItem = pPropertyProgrammType->GetSubItem(0);
		m_nLinkProgrammType = 0;
		CString strProgrammTypeItemName = (CString)pPropertyProgrammTypeItem->GetValue();
		int nLinkProgrammTypeOptionCount = sizeof(g_pchLinkProgrammTypeOption)/sizeof(g_pchLinkProgrammTypeOption[0]);		
		for(int i=0;i<nLinkProgrammTypeOptionCount;++i)
		{
			if(strProgrammTypeItemName == g_pchLinkProgrammTypeOption[i])
			{
				m_nLinkProgrammType = i;
				break;
			}
		}

		//设置子系统
		CMFCPropertyGridProperty* pPropertySubSystem = m_wndPropertyGrid.GetProperty(2);
		CMFCPropertyGridProperty* pPropertySubSystemItem = pPropertySubSystem->GetSubItem(0);
		m_nLinkSubSystem = 0;
		CString strSubSystemItemName = (CString)pPropertySubSystemItem->GetValue();
		int nLinkSubSystemOptionCount = sizeof(g_pchLinkSubSystemOption)/sizeof(g_pchLinkSubSystemOption[0]);		
		for(int i=0;i<nLinkSubSystemOptionCount;++i)
		{
			if(strSubSystemItemName == g_pchLinkSubSystemOption[i])
			{
				m_nLinkSubSystem = i;
				break;
			}
		}		

		//设置调试版输出
		CMFCPropertyGridProperty* pPropertyOutputDebug = m_wndPropertyGrid.GetProperty(3);
		m_strDebugMiddleFileDir = (CString)pPropertyOutputDebug->GetSubItem(0)->GetValue();
		m_strDebugExeFileName = (CString)pPropertyOutputDebug->GetSubItem(1)->GetValue();

		//设置纯净版输出
		CMFCPropertyGridProperty* pPropertyOutputRelease = m_wndPropertyGrid.GetProperty(4);
		m_strReleaseMiddleFileDir = (CString)pPropertyOutputRelease->GetSubItem(0)->GetValue();
		m_strReleaseExeFileName = (CString)pPropertyOutputRelease->GetSubItem(1)->GetValue();
	}
}