#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgOMLOption 对话框

class CDlgOMLOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgOMLOption)

public:
	CDlgOMLOption();   // 标准构造函数
	virtual ~CDlgOMLOption();

// 对话框数据
	enum { IDD = IDD_DLG_OML_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//汇编选项
	CString m_strOMLPath;
	CString m_strOMLLanguagePath;
	
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
