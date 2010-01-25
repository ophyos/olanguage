#pragma once

#include "ScintillaCtrl.h"

// CSyntaxCtrl

class SCINTILLACTRL_EXT_CLASS CSyntaxCtrl : public CScintillaCtrl
{
	DECLARE_DYNAMIC(CSyntaxCtrl)

public:
	CSyntaxCtrl();
	virtual ~CSyntaxCtrl();
	
public:

	int GetCurrentLine();

protected:

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};


