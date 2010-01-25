#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CScintillaDemoApp : public CWinApp
{
public:
	CScintillaDemoApp();

	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()

  HINSTANCE m_hSciDLL;
};
