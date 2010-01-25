#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"
#include "afxcmn.h"

// CDlgAddNewFile 对话框

enum LIST_ITEM_INDEX_TYPE
{
	LIST_ITEM_INDEX_PROJECT_OML_CODE_FILE,
	LIST_ITEM_INDEX_PROJECT_OML_HEAD_FILE,
	LIST_ITEM_INDEX_PROJECT_OASM_CODE_FILE,
	LIST_ITEM_INDEX_PROJECT_OASM_HEAD_FILE,
};


class CDlgAddNewFile 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgAddNewFile)

public:
	CDlgAddNewFile();
	virtual ~CDlgAddNewFile();

// 对话框数据
	enum { IDD = IDD_DLG_NEW_FILE };

protected:

	CListCtrl   m_listctrlFile;
	CImageList  m_ilFileList;

	//函数
public:
	void SetBeginNewItemType(int nNewItemType);
	int  GetAddNewItemType();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
};
