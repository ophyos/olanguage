#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgOMLEditOption 对话框

class CDlgOMLEditOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgOMLEditOption)

public:
	CDlgOMLEditOption();   // 标准构造函数
	virtual ~CDlgOMLEditOption();

// 对话框数据
	enum { IDD = IDD_DLG_OML_EDIT_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;
		
	//编辑器选项
	CString m_strOMLSyntaxWordFileName;
	CString m_strOMLSelectionListFileName;
	CString m_strOMLTempletDir;	
	CString m_strOMLAutoCompleteFileName;
	CString m_strOMLTipFileName;

	COLORREF m_colorBackGround;
	COLORREF m_colorText;
	COLORREF m_colorCommentLine;
	COLORREF m_colorCommentBlock;
	COLORREF m_colorDigital;
	COLORREF m_colorChar;
	COLORREF m_colorString;
	COLORREF m_colorKeyWord;
	COLORREF m_colorMacro;
	COLORREF m_colorOperator;
	LOGFONT m_lfTextFont;	
	BOOL m_bShowLineNumber;
	BOOL m_bShowBookMarker;
	BOOL m_bShowFold;
	BOOL m_bAutoSave;

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
