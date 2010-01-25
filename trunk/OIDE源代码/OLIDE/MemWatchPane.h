#pragma once

#include "MemWatchWnd.h"

// CMemWatchPane

class CMemWatchPane : public CDockablePane
{
	DECLARE_DYNAMIC(CMemWatchPane)

public:
	CMemWatchPane();
	virtual ~CMemWatchPane();

protected:

	CMemWatchWnd  m_wndMemWatch;

public:

	CWnd* GetWatchWnd(){ return &m_wndMemWatch; };

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


