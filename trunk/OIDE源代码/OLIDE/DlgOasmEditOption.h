#pragma once

#include "./Controls/TreePropSheet/ResizablePage.h"
#include "./Controls/TreePropSheet/TreePropSheetUtil.hpp"

// CDlgOasmEditOption 对话框

class CDlgOasmEditOption 
: public CResizablePage,
  public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDlgOasmEditOption)

public:
	CDlgOasmEditOption();   // 标准构造函数
	virtual ~CDlgOasmEditOption();

// 对话框数据
	enum { IDD = IDD_DLG_OASM_EDIT_OPTION };

	CMFCPropertyGridCtrl m_wndPropertyGrid;
	
	//OASM编辑器选项
	CString m_strOASMSyntaxWordFileName;
	CString m_strSelectionListFileName;
	CString m_strOASMTempletDir;	
	CString m_strOASMAutoCompleteFileName;
	CString m_strOASMTipFileName;

	COLORREF m_colorBackGround;
	COLORREF m_colorText;
	COLORREF m_colorCommentLine;
	COLORREF m_colorCommentBlock;
	COLORREF m_colorIncludeText;
	COLORREF m_colorIncludeLib;
	COLORREF m_colorSegmentData;
	COLORREF m_colorSegmentRData;
	COLORREF m_colorSegmentBSS;
	COLORREF m_colorSegmentExtern;
	COLORREF m_colorSegmentCode;
	COLORREF m_colorDigital;
	COLORREF m_colorInstruction;
	COLORREF m_colorFInstruction;
	COLORREF m_colorRegister;
	COLORREF m_colorChar;
	COLORREF m_colorString;
	COLORREF m_colorDefineWord;
	COLORREF m_colorMacro;
	COLORREF m_colorOperatorTxt;
	COLORREF m_colorOperator;
	LOGFONT m_lfTextFont;	
	BOOL m_bShowLineNumber;
	BOOL m_bShowBookMarker;
	BOOL m_bShowFold;
	BOOL m_bAutoSave;

	//OML编辑器选项
	CString m_strOMLSyntaxWordFileName;

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
