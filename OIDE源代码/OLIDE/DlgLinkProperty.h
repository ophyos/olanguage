#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgLinkProperty 对话框

class CDlgLinkProperty 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgLinkProperty)

public:
	CDlgLinkProperty();   // 标准构造函数
	virtual ~CDlgLinkProperty();

// 对话框数据
	enum { IDD = IDD_DLG_LINK_PROPERTY };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//链接选项	
	CString m_strCodeDir;
	CString m_strResourceDir;
	int m_nLinkProgrammType;
	int m_nLinkSubSystem;	
	CString m_strDebugMiddleFileDir;
	CString m_strDebugExeFileName;
	CString m_strReleaseMiddleFileDir;
	CString m_strReleaseExeFileName;

public:

	void GetOption();
	BOOL IsModify(){ return m_wndPropertyGrid.IsMarkModifiedProperties();};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
