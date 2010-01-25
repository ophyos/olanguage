#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgLinkOption 对话框

class CDlgLinkOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgLinkOption)

public:
	CDlgLinkOption();   // 标准构造函数
	virtual ~CDlgLinkOption();

// 对话框数据
	enum { IDD = IDD_DLG_LINK_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//链接选项
	CString m_strLinkerFileName;
	
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
