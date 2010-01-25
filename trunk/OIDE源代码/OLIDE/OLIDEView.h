
// OLIDEView.h : COLIDEView 类的接口
//

#pragma once

#ifdef _UNICODE
#endif

#include "./Controls/scintilla/ScintillaDocView.h"
#include "AutoCompleteListCtrl.h"
#include "./Data/HintString.h"

class COLIDEView : public CScintillaView
{
	friend class COLIDEDoc;

protected: // 仅从序列化创建
	COLIDEView();
	DECLARE_DYNCREATE(COLIDEView)

// 属性
public:
	COLIDEDoc* GetDocument() const;

private:

	CString m_strObjPath;
	CString m_strExeFileName;

	CAutoCompleteList m_autoCompleteList;	
	CHintString* m_pHintString;	

	int m_nDebuggerLine;

	int m_nSyntaxType;

	int m_nAutoSaveTimer;

private:
	
	void CloseAutoWnd();
	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(0xff, 0xff, 0xff), int size=-1, const char *face=0);
	void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
	void SetFlod(bool bShow,int nType);
	bool LineHasMarker(int line,int marker);
	BOOL GetCurLineBeginSpace(CString& strSpace);
	BOOL IsSeparatorWord(char chWord);
	void CharAdded();
	void AdjustAutoCompleteListSize();

// 操作
public:
	
	void UpdateAllStyle();
	void GotoPos(int nLine,int nRow = 0);
	void ShowLineNoMargin(bool bShow);
	int  GetLineCount();
	bool LineHasBreakPoint(int nLine);
	void SetBreakPoint(int nLine);
	void DeleteBreakPoint(int nLine);
	void DeleteAllBreakPoint();

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnCharAdded(SCNotification* pSCNotification);
	virtual void OnDwellStart(SCNotification* pSCNotification);
	virtual void OnDwellEnd(SCNotification* pSCNotification);
	virtual void OnChange();
	virtual void OnZoom(SCNotification* pSCNotification);

// 实现
public:
	virtual ~COLIDEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateDocPath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LONG OnAutoCompleteSelected(WPARAM wParam, LPARAM lParam);	
	afx_msg LONG OnAutoCompleteCancel(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnAutoCompleteAddChar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);		
	afx_msg void OnSyntaxWordOperator();	
	afx_msg void OnInsertRegister();
	afx_msg void OnAddSentence();
	afx_msg void OnIncludeFile();
	afx_msg void OnSetBreakPoint();	
	afx_msg void OnSyntaxHighLightType();
	afx_msg void OnTabAdd();
	afx_msg void OnTabSub();
	afx_msg void OnCommentAdd();
	afx_msg void OnCommentSub();
	afx_msg void OnFastInputList();
	afx_msg void OnFileTemplateList();
	afx_msg LRESULT OnDebuggerMoveTo(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDebuggerContinue(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDebuggerEnd(WPARAM wParam,LPARAM lParam);		
	afx_msg void OnUpdateHighLightOasm(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHighLightOml(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // OLIDEView.cpp 中的调试版本
inline COLIDEDoc* COLIDEView::GetDocument() const
   { return reinterpret_cast<COLIDEDoc*>(m_pDocument); }
#endif

