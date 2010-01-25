#pragma once

#ifdef new
#undef new
#endif

#include "./Controls/TreePropSheet/ResizableDialog.h"
#include "./Controls/TreePropSheet/TreePropSheetEx.h"
#include "./Controls/TreePropSheet/TreePropSheetSplitter.h"
#include "./Controls/TreePropSheet/TreePropSheetBordered.h"

#include "DlgOMLOption.h"
#include "DlgOasmOption.h"
#include "DlgLinkOption.h"
#include "DlgOMLEditOption.h"
#include "DlgOasmEditOption.h"
#include "DlgCommonOption.h"
#include "DlgDoasmOption.h"

// CDlgSystemOption 对话框

class CDlgSystemOption : public CResizableDialog
{
	DECLARE_DYNAMIC(CDlgSystemOption)

public:
	CDlgSystemOption(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSystemOption();

// 对话框数据
	enum { IDD = IDD_DLG_SYSTEM_OPTION };

private:

	TreePropSheet::CTreePropSheetEx m_sheetItem;

public:

	CDlgCommonOption     m_dlgCommonOption;
	CDlgOMLOption        m_dlgOMLOption;
	CDlgOasmOption       m_dlgOasmOption;
	CDlgLinkOption       m_dlgLinkOption;
	CDlgOMLEditOption    m_dlgOMLEditOption;
	CDlgOasmEditOption   m_dlgOasmEditOption;
	CDlgDoasmOption      m_dlgDoasmOption;

private:

	bool RegisterSheet(UINT nID, CPropertySheet& rSheet);

public:

	BOOL IsModify()
	{ 
		return (m_dlgCommonOption.IsModify()     || 
			    m_dlgOMLOption.IsModify()        ||
			    m_dlgOasmOption.IsModify()       || 
				m_dlgLinkOption.IsModify()       || 
				m_dlgOMLEditOption.IsModify()    ||
				m_dlgOasmEditOption.IsModify()   ||
				m_dlgDoasmOption.IsModify());
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();
};
