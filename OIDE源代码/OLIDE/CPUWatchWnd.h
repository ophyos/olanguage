#pragma once

#include "Resource.h"
#include "afxcmn.h"

// CCPUWatchWnd 对话框

class CCPUWatchWnd : public CDialog
{
	DECLARE_DYNAMIC(CCPUWatchWnd)

public:
	CCPUWatchWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCPUWatchWnd();

// 对话框数据
	enum { IDD = IDD_CPU_WATCH_WND };

public:

	CString m_strEAX;
	CString m_strEBX;
	CString m_strECX;
	CString m_strEDX;
	CString m_strEBP;
	CString m_strESP;
	CString m_strESI;
	CString m_strEDI;
	CString m_strEIP;
	CString m_strCS;
	CString m_strDS;
	CString m_strES;
	CString m_strSS;
	CString m_strFS;
	CString m_strGS;
	CString m_strST0;
	CString m_strST1;
	CString m_strST2;
	CString m_strST3;
	CString m_strST4;
	CString m_strST5;
	CString m_strST6;
	CString m_strST7;
	CString m_strXMM0;
	CString m_strXMM1;
	CString m_strXMM2;
	CString m_strXMM3;
	CString m_strXMM4;
	CString m_strXMM5;
	CString m_strXMM6;
	CString m_strXMM7;

private:

	CFont m_listFont;  

	void InitEFlag32List();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnDebuggerClearDebugData(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam);	
	CListCtrl m_listEFlag32;
	virtual BOOL OnInitDialog();
};
