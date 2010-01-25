#pragma once

#include "./Controls/TreePropSheet/ResizableDialog.h"
#include "./Controls/TreePropSheet/TreePropSheetEx.h"
#include "./Controls/TreePropSheet/TreePropSheetSplitter.h"
#include "./Controls/TreePropSheet/TreePropSheetBordered.h"

#include "./Controls/XFolderDialog/XFolderDialog.h"
#include "./Controls/XFolderDialog/XHistoryCombo.h"

#include "DlgAddNewSolution.h"
#include "DlgAddNewProject.h"
#include "DlgAddNewFile.h"
#include "afxwin.h"

// CDlgAddNewItemManager 对话框

#define NEW_ITEM_PAGE_INDEX_SOLUTION  0
#define NEW_ITEM_PAGE_INDEX_PROJECT   1
#define NEW_ITEM_PAGE_INDEX_FILE      2

class CDlgAddNewItemManager : public CResizableDialog
{
	DECLARE_DYNAMIC(CDlgAddNewItemManager)

public:
	CDlgAddNewItemManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddNewItemManager();

// 对话框数据
	enum { IDD = IDD_DLG_NEW_ITEM_MANAGER };

	//属性
public:

	CHistoryCombo m_comboxItemPath;
	CString m_strItemPath;
	CString m_strItemFileName;
	CString m_strItemName;

private:

	int m_nAddItemType;
	TreePropSheet::CTreePropSheetEx m_sheetItem;
	CDlgAddNewSolution  m_pageNewSolution;
	CDlgAddNewProject   m_pageNewProject;
	CDlgAddNewFile      m_pageNewFile;

	BOOL   m_bBrowsePath;
	//函数
public:

	void SetAddNewItem(int nAddItemType,TCHAR* pchPath=NULL,TCHAR* pchName=NULL,BOOL bBrowsePath = TRUE);
	int  GetAddNewItemType();
	

private:
	bool RegisterSheet(UINT nID,CPropertySheet& rSheet);
	void SetBeginActivePage();
	bool InitNewItem();
	bool InitNewSolution();
	bool InitNewProject();
	bool InitNewProjectFile(int nFileType);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual INT_PTR DoModal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonGetPath();
};
