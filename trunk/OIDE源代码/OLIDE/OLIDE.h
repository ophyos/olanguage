
// OLIDE.h : OLIDE 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// COLIDEApp:
// 有关此类的实现，请参阅 OLIDE.cpp
//

class COLIDEApp : public CWinAppEx
{
public:
	COLIDEApp();

private:

	long m_lVersion1;
	long m_lVersion2;
	long m_lVersion3;
	long m_lVersion4;

	BOOL ReadVersionInfo(CString& strVersion);

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	HINSTANCE m_hSciDLL;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	void CheckNewVersion();
	void SetCurVersion(long lVersion1,long lVersion2,long lVersion3,long lVersion4);
	void GetCurVersion(long& lVersion1,long& lVersion2,long& lVersion3,long& lVersion4);

	CDocument* GetDocument(const CString& strPath);
	void SaveDocument(const CString& strPathName,BOOL bIsFloder = FALSE);
	void CloseDocument(const CString& strPathName,BOOL bIsFloder = FALSE);
	
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();	
};

extern COLIDEApp theApp;
