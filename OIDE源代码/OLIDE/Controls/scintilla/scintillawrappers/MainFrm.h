#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

protected:
  CString GetLongPathName(LPCTSTR pszPathName);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};
