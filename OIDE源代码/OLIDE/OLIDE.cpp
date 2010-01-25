
// OLIDE.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "OLIDE.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "OLIDEDoc.h"
#include "OLIDEView.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COLIDEApp

BEGIN_MESSAGE_MAP(COLIDEApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &COLIDEApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	
END_MESSAGE_MAP()


// COLIDEApp 构造

COLIDEApp::COLIDEApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中	
}

// 唯一的一个 COLIDEApp 对象

COLIDEApp theApp;


// COLIDEApp 初始化

BOOL COLIDEApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//Load the scintilla dll
	m_hSciDLL = LoadLibrary(_T("SciLexer.dll"));
	if (m_hSciDLL == NULL)
	{ 
		AfxMessageBox(_T("Scintilla 的动态链接库没有安装,请下载SciLexer.dll放到程序同一目录下"));
		return FALSE;
	}

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_OLIDETYPE,
		RUNTIME_CLASS(COLIDEDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(COLIDEView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生
	m_pMainWnd->DragAcceptFiles(TRUE);
	
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CString strExternName = cmdInfo.m_strFileName.Right(4);
	strExternName.MakeLower();
	if(strExternName == _T(".osl"))
	{		
		pMainFrame->OpenSolution(cmdInfo.m_strFileName);
	}
	else if(strExternName == _T(".opr"))
	{
		AfxMessageBox(_T("不能直接打开工程,请打开工程所在的方案文件"));
	}
	else
	{
		if((strExternName == _T(".omp")) || (strExternName == _T(".omh")) || 
			(strExternName == _T(".oam")) || (strExternName == _T(".oah")))
		{						
		}
		else
		{
			//如果不想开始就打开一个空文档添加下面一行代码
			cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
		}

		// 调度在命令行中指定的命令。如果
		// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}	

	// 主窗口已初始化，因此显示它并对其进行更新	
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();	

	SetCurVersion(1,0,0,5);

	//检测新版本
	if(pMainFrame->m_systemOption.m_bUpdateEveryTime)
	{
		CheckNewVersion();
	}

	return TRUE;
}

CDocument* COLIDEApp::GetDocument(const CString& strPath)
{
	POSITION pos1 = GetFirstDocTemplatePosition();
	while (pos1)
	{
		CDocTemplate* ptempl = (CDocTemplate*)GetNextDocTemplate(pos1);
		POSITION pos2 = ptempl->GetFirstDocPosition();
		while (pos2) 
		{
			CDocument *pDoc;
			if ((pDoc=ptempl->GetNextDoc(pos2)) != NULL)
			{
				if(pDoc->GetPathName() == strPath)
					return pDoc;
			}
		}
	}

	return NULL;
}

void COLIDEApp::SaveDocument(const CString& strPathName,BOOL bIsFloder)
{
	POSITION pos1 = GetFirstDocTemplatePosition();
	while (pos1)
	{
		CDocTemplate* ptempl = (CDocTemplate*)GetNextDocTemplate(pos1);
		POSITION pos2 = ptempl->GetFirstDocPosition();
		CString strPathNameTemp;
		CDocument* pDocTemp;
		while (pos2) 
		{		
			pDocTemp = ptempl->GetNextDoc(pos2);
			strPathNameTemp = pDocTemp->GetPathName();
			//如果是文件夹
			if(bIsFloder)
			{
				if(strPathNameTemp.Find(strPathName) == 0)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						((COLIDEDoc*)pDocTemp)->DoFileSave();
					}
					else
					{
						pDocTemp->DoFileSave();
					}
				}
			}
			//否则是文件
			else
			{
				if(strPathNameTemp == strPathName)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						((COLIDEDoc*)pDocTemp)->DoFileSave();
					}
					else
					{
						pDocTemp->DoFileSave();
					}
					break;
				}
			}						
		}
	}
}

void COLIDEApp::CloseDocument(const CString& strPathName,BOOL bIsFloder)
{
	POSITION pos1 = GetFirstDocTemplatePosition();
	while (pos1)
	{
		CDocTemplate* ptempl = (CDocTemplate*)GetNextDocTemplate(pos1);
		POSITION pos2 = ptempl->GetFirstDocPosition();
		CString strPathNameTemp;
		CDocument* pDocTemp;
		while (pos2) 
		{		
			pDocTemp = ptempl->GetNextDoc(pos2);
			strPathNameTemp = pDocTemp->GetPathName();
			//如果是文件夹
			if(bIsFloder)
			{
				if(strPathNameTemp.Find(strPathName) == 0)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						((COLIDEDoc*)pDocTemp)->OnCloseDocument();
					}
					else
					{
						pDocTemp->OnCloseDocument();
					}
				}
			}
			//否则是文件
			else
			{
				if(strPathNameTemp == strPathName)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						((COLIDEDoc*)pDocTemp)->OnCloseDocument();
					}
					else
					{
						pDocTemp->OnCloseDocument();
					}
					break;
				}
			}						
		}
	}
}


// COLIDEApp 自定义加载/保存方法

void COLIDEApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;

	bNameValid = strName.LoadString(IDS_OASM_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_OASM_EDIT);
	bNameValid = strName.LoadString(IDS_OML_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_OML_EDIT);

	bNameValid = strName.LoadString(IDS_SOLUTION);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_SOLUTION);
	bNameValid = strName.LoadString(IDS_PROJECT);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_PROJECT);
	bNameValid = strName.LoadString(IDS_FLODER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_FLODER);
	bNameValid = strName.LoadString(IDS_FILE);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_FILE);	
}

void COLIDEApp::LoadCustomState()
{
}

void COLIDEApp::SaveCustomState()
{
}

// COLIDEApp 消息处理程序

int COLIDEApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	//Free up the Scintilla DLL
	if (m_hSciDLL)
	{
		FreeLibrary(m_hSciDLL);
		m_hSciDLL = NULL;
	}

	return CWinAppEx::ExitInstance();
}

// 用于运行对话框的应用程序命令
void COLIDEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void COLIDEApp::SetCurVersion(long lVersion1,long lVersion2,long lVersion3,long lVersion4)
{
	m_lVersion1 = lVersion1;
	m_lVersion2 = lVersion2;
	m_lVersion3 = lVersion3;
	m_lVersion4 = lVersion4;
}

void COLIDEApp::GetCurVersion(long& lVersion1,long& lVersion2,long& lVersion3,long& lVersion4)
{
	lVersion1 = m_lVersion1;
	lVersion2 = m_lVersion2;
	lVersion3 = m_lVersion3;
	lVersion4 = m_lVersion4;
}

#include<wininet.h>  
#pragma comment(lib,"wininet.lib")  

void COLIDEApp::CheckNewVersion()
{
	CString strVersion;
	if(!ReadVersionInfo(strVersion))
		return;

	CString strVersion1,strVersion2,strVersion3,strVersion4;	

	int nPos = 0;
	nPos = strVersion.Find(_T('.'));
	strVersion1 = strVersion.Left(nPos);
	strVersion = strVersion.Right(strVersion.GetLength() - nPos - 1);

	nPos = strVersion.Find(_T('.'));
	strVersion2 = strVersion.Left(nPos);
	strVersion = strVersion.Right(strVersion.GetLength() - nPos - 1);

	nPos = strVersion.Find(_T('.'));
	strVersion3 = strVersion.Left(nPos);
	strVersion4 = strVersion.Right(strVersion.GetLength() - nPos - 1);	

	long lVersion1,lVersion2,lVersion3,lVersion4;
#ifdef _UNICODE
	lVersion1 = wcstol(strVersion1,0,10);
	lVersion2 = wcstol(strVersion2,0,10);
	lVersion3 = wcstol(strVersion3,0,10);
	lVersion4 = wcstol(strVersion4,0,10);
#else
	lVersion1 = strtol(strVersion1,0,10);
	lVersion2 = strtol(strVersion2,0,10);
	lVersion3 = strtol(strVersion3,0,10);
	lVersion4 = strtol(strVersion4,0,10);
#endif

	if( (lVersion1 > m_lVersion1) || 
		(lVersion2 > m_lVersion2) || 
		(lVersion3 > m_lVersion3) || 
		(lVersion4 > m_lVersion4))
	{
		CString strNewVersion;
		if(IDYES == ::MessageBox(NULL,_T("发现新版本，是否打开下载页面？"),_T("O语言升级"),MB_YESNO | MB_ICONQUESTION ))
		{
			ShellExecute(NULL,_T("open"),_T("http://www.olanguage.org/download/"),NULL,NULL,SW_SHOWNORMAL);
		}
	}
	else
	{
		::MessageBox(NULL,_T("当前版本已经是最新版了!"),_T("O语言升级"),0);
	}
}

BOOL COLIDEApp::ReadVersionInfo(CString& strVersion)
{	
	BOOL bResult = FALSE;
	CString strUpdateFile = _T("http://www.olanguage.org/download/update.txt");

	HINTERNET hSession  =  InternetOpen(_T("ol") , INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hSession  !=  NULL)
	{
		HINTERNET handle2  =  InternetOpenUrl(hSession,strUpdateFile, NULL,  0 , INTERNET_FLAG_DONT_CACHE,  0 );
		if(handle2  !=  NULL)
		{			
			char chTemp[1024];
			DWORD dwRead;
			InternetReadFile(handle2,chTemp,1023,&dwRead);
			if(dwRead > 0)
			{
				chTemp[dwRead] = 0;
				strVersion = chTemp;
				bResult = TRUE;
			}
			InternetCloseHandle(handle2);
			handle2 = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}

	return bResult;
} 