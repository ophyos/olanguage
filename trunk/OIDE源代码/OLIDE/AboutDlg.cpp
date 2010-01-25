
#include "stdafx.h"
#include "OLIDE.h"
#include "AboutDlg.h"


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	long lVersion1,lVersion2,lVersion3,lVersion4;
	theApp.GetCurVersion(lVersion1,lVersion2,lVersion3,lVersion4);

	CString strVersion;
	strVersion.Format(_T("O语言开发环境  %d.%d.%d.%d 测试版\r\n\r\n"),lVersion1,lVersion2,lVersion3,lVersion4);

	m_strText = strVersion;	
	m_strText += 
		_T("欢迎使用O汇编和中间语言套件\r\n\r\n")
		//_T("请按下面的邮箱地址留下你的宝贵建议\r\n\r\n")
		_T("访问主页：www.olanguage.org\r\n\r\n")
		_T("服务邮箱：olanguage@163.com\r\n\r\n")		
		//_T("参与开发：www.scover.cn/bbs/thread.php?fid=102\r\n\r\n")
		_T("特殊声明：本程序使用的资源编译器ResEdit和后台链接器polink都为免费软件\r\n")
		_T("　　　　　ResEdit下载地址为 http://www.resedit.net/\r\n")		
		_T("　　　　　polink下载地址为 www.smorgasbordet.com/pellesc/index.htm\r\n")
		_T("　　　　　版权归原作者所有\r\n\r\n")
		_T("版权所有(C) 2008-2009 O语言开发组 保留所有权利");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
}

