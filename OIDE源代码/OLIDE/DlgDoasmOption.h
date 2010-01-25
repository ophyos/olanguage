#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgDoasmOption 对话框

class CDlgDoasmOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgDoasmOption)

public:
	CDlgDoasmOption();   // 标准构造函数
	virtual ~CDlgDoasmOption();

// 对话框数据
	enum { IDD = IDD_DLG_DOASM_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//反汇编选项
	CString m_strDoasmPath;
	CString m_strOasmLanguagePath;

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
