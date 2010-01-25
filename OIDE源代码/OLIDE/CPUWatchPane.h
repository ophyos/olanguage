#pragma once

#include "CPUWatchWnd.h"

// CCPUWatchPane

class CCPUWatchPane : public CDockablePane
{
	DECLARE_DYNAMIC(CCPUWatchPane)

public:
	CCPUWatchPane();
	virtual ~CCPUWatchPane();

protected:

	CCPUWatchWnd  m_wndCPUWatch;

public:

	CWnd* GetWatchWnd(){ return &m_wndCPUWatch; };

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


