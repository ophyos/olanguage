
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口

class COutputList : public CListBox
{
// 构造
public:
	COutputList();

// 实现
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

#include "./Controls/RichEdit/RichEdit.h"

class COutputBuild : public CRichEdit
{
	// 构造
public:
	COutputBuild();

	void Clear();

	// 实现
public:
	virtual ~COutputBuild();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();

// 属性
protected:
	CFont m_Font;
	
	COutputBuild m_wndOutputPaneBuild;

protected:	
	void AdjustHorzScroll(CListBox& wndListBox);

public:

	void Clear();
	void InsertText(const CString& strMsg);	

	COutputBuild* GetOutputBuildWnd(){ return &m_wndOutputPaneBuild;}

	void SetBackgroundColor(COLORREF colorBackGround)
	{
		m_wndOutputPaneBuild.SetBackgroundColor(FALSE,colorBackGround);
	}

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

