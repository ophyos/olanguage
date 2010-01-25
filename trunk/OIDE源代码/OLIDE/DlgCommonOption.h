#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgCommonOption 对话框

class CDlgCommonOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgCommonOption)

public:
	CDlgCommonOption();   // 标准构造函数
	virtual ~CDlgCommonOption();

// 对话框数据
	enum { IDD = IDD_DLG_COMMON_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//常规选项
	BOOL m_bUpdateEveryTime;
	
	
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
