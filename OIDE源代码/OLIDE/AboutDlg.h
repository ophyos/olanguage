
#ifndef _ABOUT_DLG_H_ 
#define _ABOUT_DLG_H_ 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

#include "resource.h"       // 主符号

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
};

#endif //_ABOUT_DLG_H_ 