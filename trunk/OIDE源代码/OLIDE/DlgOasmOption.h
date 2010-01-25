#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgOasmOption 对话框

class CDlgOasmOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgOasmOption)

public:
	CDlgOasmOption();   // 标准构造函数
	virtual ~CDlgOasmOption();

// 对话框数据
	enum { IDD = IDD_DLG_OASM_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;

	//汇编选项
	CString m_strOasmPath;
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
