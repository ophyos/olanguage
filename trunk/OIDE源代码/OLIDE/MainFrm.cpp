
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "OLIDE.h"

#include "MainFrm.h"
#include "OLIDEView.h"
#include "OLIDEDoc.h"
#include "./Common/Common.h"
#include "./Common/Global.h"

#include <Dbghelp.h>
#pragma   comment(lib,"Dbghelp.lib")  //使用MakeSureDirectoryPathExists函数

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
    ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
    ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
    ON_COMMAND(ID_CLOSE_CUR_CHILD_FRAME, &CMainFrame::OnCloseCurChildFrame)
    ON_UPDATE_COMMAND_UI(ID_CLOSE_ALL_CHILD_FRAME, &CMainFrame::OnUpdateCloseAllChildFrame)
    ON_COMMAND(ID_FILE_SAVE_ALL, &CMainFrame::OnSaveAllDocument)
    ON_COMMAND(ID_CLOSE_ALL_CHILD_FRAME, &CMainFrame::OnCloseAllChildFrame)
    ON_UPDATE_COMMAND_UI(ID_CLOSE_CUR_CHILD_FRAME, &CMainFrame::OnUpdateCloseCurChildFrame)
    ON_COMMAND(ID_OPEN_OWNER_FLODER, &CMainFrame::OnOpenOwnerFloder)
    ON_UPDATE_COMMAND_UI(ID_OPEN_OWNER_FLODER, &CMainFrame::OnUpdateOpenOwnerFloder)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_DOC, OnUpdateDocPath)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
    ON_WM_SIZE()
    ON_COMMAND(ID_SYSTEM_OPTIONS, OnSystemOptions)	
	ON_COMMAND(ID_ASSOCIATE_O_FILE, OnAssociateOFile)
    ON_COMMAND(ID_RESEDITOR, OnResEditor)
	ON_MESSAGE(WM_OPEN_DOCUMENT, &CMainFrame::OnOpenDocument)

    ON_COMMAND(ID_BUILD_PROJECT, &CMainFrame::OnBuildProject)
    ON_COMMAND(ID_BUILD_ALL, &CMainFrame::OnBuildAll)
    ON_COMMAND(ID_LINK_PROJECT, &CMainFrame::OnLinkProject)
    ON_COMMAND(ID_BUILD_AND_LINK, &CMainFrame::OnBuildAndLink)
	ON_COMMAND(ID_REBUILD_AND_LINK, &CMainFrame::OnReBuildAndLink)	
    ON_COMMAND(ID_BUILD_AND_RUN, &CMainFrame::OnBuildAndRun)
    ON_UPDATE_COMMAND_UI(ID_BUILD_PROJECT, &CMainFrame::OnUpdateBuildProject)
    ON_UPDATE_COMMAND_UI(ID_BUILD_ALL, &CMainFrame::OnUpdateBuildAll)
    ON_UPDATE_COMMAND_UI(ID_LINK_PROJECT, &CMainFrame::OnUpdateLinkProject)
    ON_UPDATE_COMMAND_UI(ID_BUILD_AND_LINK, &CMainFrame::OnUpdateBuildAndLink)
    ON_UPDATE_COMMAND_UI(ID_BUILD_AND_RUN, &CMainFrame::OnUpdateBuildAndRun)

    ON_COMMAND(ID_OASM_HELP, &CMainFrame::OnOASMHelp)
	ON_COMMAND(ID_OML_HELP, &CMainFrame::OnOMLHelp)

    ON_COMMAND(ID_CHECK_NEW_VERSION, &CMainFrame::OnCheckNewVersion)
    ON_COMMAND(ID_NEW_SOLUTION, &CMainFrame::OnNewSolution)
    ON_COMMAND(ID_OPEN_SOLUTION, &CMainFrame::OnOpenSolution)
    ON_UPDATE_COMMAND_UI(ID_OPEN_SOLUTION, &CMainFrame::OnUpdateOpenSolution)
    ON_UPDATE_COMMAND_UI(ID_NEW_SOLUTION, &CMainFrame::OnUpdateNewSolution)
    ON_WM_DROPFILES()
	ON_COMMAND(ID_DASM_PE_FILE, &CMainFrame::OnDasmPeFile)
	ON_COMMAND(ID_BEGIN_DEBUGGER, &CMainFrame::OnBeginDebugger)
	ON_COMMAND(ID_STOP_DEBUGGER, &CMainFrame::OnStopDebugger)
	ON_COMMAND(ID_CLEAR_ALL_BREAK_POINT, &CMainFrame::OnClearAllBreakPoint)	
	ON_WM_DESTROY()
	ON_MESSAGE(WM_DEBUGGER_END,            &CMainFrame::OnDebuggerEnd)
	ON_COMMAND(ID_DEBUG_SINGLE_LINE, &CMainFrame::OnDebugSingleLine)
	ON_COMMAND(ID_DEBUG_SINGLE_SENTENCE, &CMainFrame::OnDebugSingleSentence)
	ON_MESSAGE(WM_DEBUGGER_DELETEBREAKPOINT,    &CMainFrame::OnDebuggerDeleteBreakPoint)
	ON_MESSAGE(WM_DEBUGGER_SETBREAKPOINT,    &CMainFrame::OnDebuggerSetBreakPoint)	
	ON_MESSAGE(WM_DEBUGGER_SHOW_CPU_DATA,    &CMainFrame::OnDebuggerShowCPUData)	
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, &CMainFrame::OnDummySelectActiveConfiguration)
	ON_CBN_SELENDOK(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, &CMainFrame::OnDummySelectActiveConfiguration)
	ON_COMMAND(ID_GOTO_LINE, &CMainFrame::OnSelectGotoLine)
	ON_CBN_SELENDOK(ID_GOTO_LINE, &CMainFrame::OnSelectGotoLine)
			
	ON_COMMAND(ID_OPEN_OLANGUAGE_WEB, &CMainFrame::OnOpenOlanguageWeb)
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,    // 状态行指示器
    ID_INDICATOR_DOC,
    ID_INDICATOR_LINE,
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_OVR,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
    // TODO: 在此添加成员初始化代码

    theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);

    //得到当前程序路径
    TCHAR szBuff[_MAX_PATH];
    VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));
    m_strAppPath = szBuff;

	m_hDebugThread = NULL;
	m_dwDebugThreadID = 0;	

	m_rcAutoCompleteList.left = 0;
	m_rcAutoCompleteList.right = 0;
	m_rcAutoCompleteList.top = 0;
	m_rcAutoCompleteList.bottom = 0;
	m_nAutoCompleteList_Column0_Width = 0;
	m_nAutoCompleteList_Column1_Width = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

	CMFCToolBarComboBoxButton::SetFlatMode();

    BOOL bNameValid;
    // 基于持久值设置视觉管理器和样式
    OnApplicationLook(theApp.m_nAppLook);

    CMDITabInfo mdiTabParams;
    mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
    mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
    mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
    mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
    mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
    EnableMDITabbedGroups(TRUE, mdiTabParams);

    if (!m_wndMenuBar.Create(this))
    {
        TRACE0("未能创建菜单栏\n");
        return -1;      // 未能创建
    }
    m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	
    // 防止菜单栏在激活时获得焦点
    CMFCPopupMenu::SetForceMenuFocus(FALSE);

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
            !m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
    {
        TRACE0("未能创建工具栏\n");
        return -1;      // 未能创建
    }

    if (!m_wndToolBarBuild.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),AFX_IDW_CONTROLBAR_FIRST+5) ||
            !m_wndToolBarBuild.LoadToolBar(IDR_BUILD_CODE1))
    {
        TRACE0("未能创建生成工具栏\n");
        return -1;      // 未能创建
    }

    if (!m_wndToolBarSyntaxWord.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),AFX_IDW_CONTROLBAR_FIRST+6) ||
            !m_wndToolBarSyntaxWord.LoadToolBar(IDR_SYNTAX_WORD))
    {
        TRACE0("未能创建生成工具栏\n");
        return -1;      // 未能创建
    }

    if (!m_wndToolBarOperator.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),AFX_IDW_CONTROLBAR_FIRST+7) ||
            !m_wndToolBarOperator.LoadToolBar(IDR_OPERATOR))
    {
        TRACE0("未能创建生成工具栏\n");
        return -1;      // 未能创建
    }

	if (!m_wndToolEditView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),AFX_IDW_CONTROLBAR_FIRST+8) ||
		!m_wndToolEditView.LoadToolBar(IDR_EDIT_VIEW))
	{
		TRACE0("未能创建生成工具栏\n");
		return -1;      // 未能创建
	}

    CString strToolBarName;
    bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
    ASSERT(bNameValid);
    m_wndToolBar.SetWindowText(strToolBarName);
    strToolBarName = _T("生成");
    m_wndToolBarBuild.SetWindowText(strToolBarName);
    strToolBarName = _T("语法字");
    m_wndToolBarSyntaxWord.SetWindowText(strToolBarName);
    strToolBarName = _T("操作符");
    m_wndToolBarOperator.SetWindowText(strToolBarName);
	strToolBarName = _T("编辑视图");
	m_wndToolEditView.SetWindowText(strToolBarName);

    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);
    m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    m_wndToolBarBuild.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    m_wndToolBarSyntaxWord.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    m_wndToolBarOperator.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);	
	m_wndToolEditView.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

    // 允许用户定义的工具栏操作:
    InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("未能创建状态栏\n");
        return -1;      // 未能创建
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    // TODO: 如果您不希望工具栏和菜单栏可停靠，请删除下面行
    m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndToolBarBuild.EnableDocking(CBRS_ALIGN_ANY);
    m_wndToolBarSyntaxWord.EnableDocking(CBRS_ALIGN_ANY);
    m_wndToolBarOperator.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolEditView.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockPane(&m_wndMenuBar);
    DockPane(&m_wndToolBar);
    DockPane(&m_wndToolBarBuild);
    DockPane(&m_wndToolBarSyntaxWord);
    DockPane(&m_wndToolBarOperator);
	DockPane(&m_wndToolEditView);

    // 启用 Visual Studio 2005 样式停靠窗口行为
    CDockingManager::SetDockingMode(DT_SMART);
    // 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
    EnableAutoHidePanes(CBRS_ALIGN_ANY);

    // 加载菜单项图像(不在任何标准工具栏上):
    //CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

    // 创建停靠窗口
    if (!CreateDockingWindows())
    {
        TRACE0("未能创建停靠窗口\n");
        return -1;
    }

    m_wndSolutionPane.EnableDocking(CBRS_ALIGN_ANY);
    DockPane(&m_wndSolutionPane);
    //m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
    CDockablePane* pTabbedBar = NULL;
    //m_wndClassView.AttachToTabWnd(&m_wndSolutionPane, DM_SHOW, TRUE, &pTabbedBar);
    //m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
    //DockPane(&m_wndProperties);

    m_wndOutputPane.EnableDocking(CBRS_ALIGN_ANY);
    DockPane(&m_wndOutputPane);

	m_wndCPUWatchPane.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndCPUWatchPane);
	m_wndCPUWatchPane.AttachToTabWnd(&m_wndSolutionPane, DM_SHOW, TRUE, &pTabbedBar);

	m_wndMemWatchPane.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndMemWatchPane);
	m_wndMemWatchPane.AttachToTabWnd(&m_wndOutputPane, DM_SHOW, TRUE, &pTabbedBar);

    // 启用增强的窗口管理对话框
    EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

    // 启用工具栏和停靠窗口菜单替换
    EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

    // 启用快速(按住 Alt 拖动)工具栏自定义
    CMFCToolBar::EnableQuickCustomization();

    //if (CMFCToolBar::GetUserImages() == NULL)
    //{
    //	// 加载用户定义的工具栏图像
    //	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
    //	{
    //		m_UserImages.SetImageSize(CSize(16, 16), FALSE);
    //		CMFCToolBar::SetUserImages(&m_UserImages);
    //	}
    //}

    // 启用菜单个性化(最近使用的命令)
    // TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
    CList<UINT, UINT> lstBasicCommands;

    lstBasicCommands.AddTail(ID_NEW_SOLUTION);
    lstBasicCommands.AddTail(ID_OPEN_SOLUTION);
    lstBasicCommands.AddTail(ID_CLOSE_SOLUTION);
    lstBasicCommands.AddTail(ID_FILE_SAVE);
    lstBasicCommands.AddTail(ID_FILE_SAVE_ALL);
    lstBasicCommands.AddTail(ID_FILE_SAVE_AS);
    lstBasicCommands.AddTail(ID_FILE_PRINT);
    lstBasicCommands.AddTail(ID_APP_EXIT);
    lstBasicCommands.AddTail(ID_EDIT_UNDO);
    lstBasicCommands.AddTail(ID_EDIT_REDO);
    lstBasicCommands.AddTail(ID_EDIT_CUT);
    lstBasicCommands.AddTail(ID_EDIT_COPY);
    lstBasicCommands.AddTail(ID_EDIT_PASTE);
    lstBasicCommands.AddTail(ID_EDIT_SELECT_ALL);
    lstBasicCommands.AddTail(ID_EDIT_FIND);
    lstBasicCommands.AddTail(ID_EDIT_REPEAT);
    lstBasicCommands.AddTail(ID_EDIT_REPLACE);
    lstBasicCommands.AddTail(ID_BUILD_PROJECT);
    lstBasicCommands.AddTail(ID_BUILD_ALL);
    lstBasicCommands.AddTail(ID_LINK_PROJECT);
    lstBasicCommands.AddTail(ID_BUILD_AND_LINK);
	lstBasicCommands.AddTail(ID_REBUILD_AND_LINK);	
    lstBasicCommands.AddTail(ID_BUILD_AND_RUN);
	lstBasicCommands.AddTail(ID_ASSOCIATE_O_FILE);	
    lstBasicCommands.AddTail(ID_RESEDITOR);
	lstBasicCommands.AddTail(ID_SET_BREAK_POINT);
	lstBasicCommands.AddTail(ID_BEGIN_DEBUGGER);
	lstBasicCommands.AddTail(ID_STOP_DEBUGGER);	
	lstBasicCommands.AddTail(ID_DEBUG_SINGLE_LINE);	
	lstBasicCommands.AddTail(ID_DEBUG_SINGLE_SENTENCE);	
	lstBasicCommands.AddTail(ID_CLEAR_ALL_BREAK_POINT);	
	lstBasicCommands.AddTail(ID_DASM_PE_FILE);
    lstBasicCommands.AddTail(ID_SYSTEM_OPTIONS);
    lstBasicCommands.AddTail(ID_OASM_HELP);
	lstBasicCommands.AddTail(ID_OML_HELP);
	lstBasicCommands.AddTail(ID_OPEN_OLANGUAGE_WEB);
    lstBasicCommands.AddTail(ID_APP_ABOUT);
    lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
    lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
    lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_HIGH_LIGHT_OASM);
	lstBasicCommands.AddTail(ID_HIGH_LIGHT_OML);
    lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
    lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
    lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
    lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);
    lstBasicCommands.AddTail(ID_CHECK_NEW_VERSION);
	lstBasicCommands.AddTail(ID_TAB_ADD);
	lstBasicCommands.AddTail(ID_TAB_SUB);
	lstBasicCommands.AddTail(ID_COMMENT_ADD);
	lstBasicCommands.AddTail(ID_COMMENT_SUB);
	lstBasicCommands.AddTail(ID_FAST_INPUT_LIST);
	lstBasicCommands.AddTail(ID_FILE_TEMPLATE_LIST);

    CMFCToolBar::SetBasicCommands(lstBasicCommands);

    CString strAppPath = GetAppDirectory();
    m_strSystemOptionFileName = strAppPath + _T("\\config\\option.xml");
    m_systemOption.Load(m_strSystemOptionFileName);

    //加载自动完成列表数据
    LoadConfigData();
    
	//关联O文件
	AssociateOFile(FALSE);

    //设置输出窗口背景色
    m_wndOutputPane.SetBackgroundColor(m_systemOption.m_colorOMLBackGround);

    return 0;
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_MAINFRAME:
		{
			//ASSERT(m_wndToolbarResource.GetSafeHwnd() != NULL);

			//// Replace dropdown resources button:
			//m_wndToolBar.ReplaceButton(ID_DUMMY_INSERT_RESOURCE, CMFCDropDownToolbarButton(_T("Add Resource"), &m_wndToolbarResource));

			//// Replace "Find..." button by combobox:
			//m_wndToolBar.ReplaceButton(ID_EDIT_FIND, CFindComboButton());

			//// Replace "Undo" button by menubutton:
			//m_wndToolBar.ReplaceButton(ID_EDIT_UNDO, CUndoButton(ID_EDIT_UNDO, _T("&Undo")));
			//m_wndToolBar.ReplaceButton(ID_EDIT_REDO, CUndoButton(ID_EDIT_REDO, _T("&Redo")));
		}
		break;

	case IDR_BUILD_CODE1:
		{
			// Replace "Confoguration..." button by combobox:
			CMFCToolBarComboBoxButton comboButton(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, GetCmdMgr()->GetCmdImage(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE), CBS_DROPDOWNLIST,120);
			comboButton.AddItem(_T("编译成调试版"));
			comboButton.AddItem(_T("编译成纯净版"));
			comboButton.SelectItem(0);			
			m_wndToolBarBuild.ReplaceButton(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, comboButton);

			break;
		}
	case IDR_EDIT_VIEW:
		{
			// Replace "Confoguration..." button by combobox:
			CMFCToolBarComboBoxButton comboGotoLine(ID_GOTO_LINE, GetCmdMgr()->GetCmdImage(ID_GOTO_LINE, FALSE), CBS_DROPDOWN,80);
			comboGotoLine.AddItem(_T("跳到首行"));
			comboGotoLine.AddItem(_T("跳到末行"));
			comboGotoLine.SelectItem(0);			
			m_wndToolEditView.ReplaceButton(ID_GOTO_LINE, comboGotoLine);

			break;
		}		
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if ( !CMDIFrameWndEx::PreCreateWindow(cs) )
        return FALSE;
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
    BOOL bNameValid;

    //// 创建类视图
    //CString strClassView;
    //bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
    //ASSERT(bNameValid);
    //if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
    //{
    //	TRACE0("未能创建“类视图”窗口\n");
    //	return FALSE; // 未能创建
    //}

    // 创建文件视图
    CString strFileView;
    bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
    ASSERT(bNameValid);
    if (!m_wndSolutionPane.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
    {
        TRACE0("未能创建“文件视图”窗口\n");
        return FALSE; // 未能创建
    }

    // 创建输出窗口
    CString strOutputWnd;
    bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
    ASSERT(bNameValid);
    if (!m_wndOutputPane.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
    {
        TRACE0("未能创建输出窗口\n");
        return FALSE; // 未能创建
    }

    //// 创建属性窗口
    //CString strPropertiesWnd;
    //bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
    //ASSERT(bNameValid);
    //if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
    //{
    //	TRACE0("未能创建“属性”窗口\n");
    //	return FALSE; // 未能创建
    //}

	//创建寄存器监视窗口	
	CString strCPUWatchWnd;
	bNameValid = strCPUWatchWnd.LoadString(IDS_CPUWATCH_WND);
	ASSERT(bNameValid);
	if (!m_wndCPUWatchPane.Create(strCPUWatchWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_CPUWATCHWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建CPU监视窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strMemWatchWnd;
	bNameValid = strMemWatchWnd.LoadString(IDS_MEM_WATCH_WND);
	ASSERT(bNameValid);
	if (!m_wndMemWatchPane.Create(strMemWatchWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_MEMWATCHWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}
	
    SetDockingWindowIcons(theApp.m_bHiColorIcons);
    return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
    HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_SOLUTION : IDI_SOLUTION), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndSolutionPane.SetIcon(hFileViewIcon, FALSE);

    /*HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndClassView.SetIcon(hClassViewIcon, FALSE);*/

    /*HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);*/


    HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndOutputPane.SetIcon(hOutputBarIcon, FALSE);

	HICON hCPUWatchWndIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndCPUWatchPane.SetIcon(hCPUWatchWndIcon, FALSE);

	HICON hMemWatchWndIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndMemWatchPane.SetIcon(hMemWatchWndIcon, FALSE);
	

    UpdateMDITabbedBarsIcons();
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
    ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	// Create a customize toolbars dialog:
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* Automatic menus scaning */, AFX_CUSTOMIZE_MENU_SHADOWS | AFX_CUSTOMIZE_TEXT_LABELS | AFX_CUSTOMIZE_MENU_ANIMATIONS);

	pDlgCust->EnableUserDefinedToolbars();

	// Setup combboxes:
	//pDlgCust->ReplaceButton(ID_EDIT_FIND, CFindComboButton());

	CMFCToolBarComboBoxButton comboButtonConfig(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, GetCmdMgr()->GetCmdImage(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE), CBS_DROPDOWNLIST,120);
	comboButtonConfig.AddItem(_T("编译成调试版"));
	comboButtonConfig.AddItem(_T("编译成纯净版"));
	comboButtonConfig.SelectItem(0);
	pDlgCust->ReplaceButton(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, comboButtonConfig);

	CMFCToolBarComboBoxButton comboGotoLine(ID_GOTO_LINE, GetCmdMgr()->GetCmdImage(ID_GOTO_LINE, FALSE), CBS_DROPDOWN,80);
	comboGotoLine.AddItem(_T("跳到首行"));
	comboGotoLine.AddItem(_T("跳到末行"));
	comboGotoLine.SelectItem(0);	
	pDlgCust->ReplaceButton(ID_GOTO_LINE, comboButtonConfig);

	// Add dropdown resources button:
	//pDlgCust->AddButton(_T("Build"), CMFCDropDownToolbarButton(_T("Add Resource"), &m_wndToolbarResource));

	//// Setup undo/redo buttons:
	//pDlgCust->ReplaceButton(ID_EDIT_UNDO, CUndoButton(ID_EDIT_UNDO, _T("&Undo")));
	//pDlgCust->ReplaceButton(ID_EDIT_REDO, CUndoButton(ID_EDIT_REDO, _T("&Redo")));

	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
    LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
    if (lres == 0)
    {
        return 0;
    }

    CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
    ASSERT_VALID(pUserToolbar);

    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
    CWaitCursor wait;

    theApp.m_nAppLook = id;

    switch (theApp.m_nAppLook)
    {
    case ID_VIEW_APPLOOK_WIN_2000:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
        break;

    case ID_VIEW_APPLOOK_OFF_XP:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
        break;

    case ID_VIEW_APPLOOK_WIN_XP:
        CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
        break;

    case ID_VIEW_APPLOOK_OFF_2003:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
        CDockingManager::SetDockingMode(DT_SMART);
        break;

    case ID_VIEW_APPLOOK_VS_2005:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
        CDockingManager::SetDockingMode(DT_SMART);
        break;

    default:
        switch (theApp.m_nAppLook)
        {
        case ID_VIEW_APPLOOK_OFF_2007_BLUE:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_BLACK:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_SILVER:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_AQUA:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
            break;
        }

        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
        CDockingManager::SetDockingMode(DT_SMART);
    }

    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

    theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
    pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
    // 基类将执行真正的工作

    if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
    {
        return FALSE;
    }

    // 为所有用户工具栏启用自定义按钮
    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    for (int i = 0; i < iMaxUserToolbars; i ++)
    {
        CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
        if (pUserToolbar != NULL)
        {
            pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
        }
    }

    return TRUE;
}

BOOL CMainFrame::OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bTabDrop)
{
    //不是拖动时显示菜单
    if (!bTabDrop)
    {
        CMenu menu;
        menu.LoadMenu(IDR_POPUP_TAB);

        CMenu* pSumMenu = menu.GetSubMenu(0);

        CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
        if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
        {
            delete pPopupMenu;
            return FALSE;
        }

        OnShowPopupMenu(pPopupMenu);
    }

    return TRUE;
}

void CMainFrame::OnCloseCurChildFrame()
{
    // TODO: 在此添加命令处理程序代码

    SendMessage(WM_COMMAND,ID_FILE_CLOSE,0);
}

void CMainFrame::OnUpdateCloseCurChildFrame(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnSaveAllDocument()
{
    CWinApp *pWinApp = AfxGetApp(); //得到应用程序指针
    POSITION p = pWinApp->GetFirstDocTemplatePosition();//得到第1个文档模板
    while (p != NULL) //遍历文档模板
    {
        CDocTemplate* pDocTemplate = pWinApp->GetNextDocTemplate(p);
        POSITION p1 = pDocTemplate->GetFirstDocPosition();//得到文档模板对应的第1个文档
        while (p1 != NULL) //遍历文档模板对应的文档
        {
            CDocument *pDocument = pDocTemplate->GetNextDoc(p1);
            if (!pDocument->GetPathName().IsEmpty())
            {
                pDocument->DoFileSave();
            }
        }
    }
}

void CMainFrame::OnCloseAllChildFrame()
{
    // TODO: 在此添加命令处理程序代码

    int nSaveType = AfxMessageBox(_T("关闭所有文档,保存所有修改过的文件?"), MB_YESNOCANCEL);
    if (nSaveType == IDCANCEL)
        return;

    CWinApp *pWinApp = AfxGetApp(); //得到应用程序指针
    POSITION p = pWinApp->GetFirstDocTemplatePosition();//得到第1个文档模板
    while (p != NULL) //遍历文档模板
    {
        CDocTemplate* pDocTemplate = pWinApp->GetNextDocTemplate(p);
        POSITION p1 = pDocTemplate->GetFirstDocPosition();//得到文档模板对应的第1个文档
        while (p1 != NULL) //遍历文档模板对应的文档
        {
            CDocument *pDocument = pDocTemplate->GetNextDoc(p1);
            //POSITION p2 = pDocument->GetFirstViewPosition(); //得到文档对应的第1个视图
            //while (p2 != NULL) //遍历文档对应的视图
            //{
            //CView *pView = pDocument->GetNextView(p2);
            //}

            if (nSaveType == IDYES)
            {
                pDocument->DoFileSave();
            }

            pDocument->OnCloseDocument();
        }
    }
}

void CMainFrame::OnUpdateCloseAllChildFrame(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnOpenOwnerFloder()
{
    // TODO: 在此添加命令处理程序代码

	CFrameWnd* pFrameWnd = GetActiveFrame();
	if(pFrameWnd == 0)
		return;
	
	CDocument* pDocument = pFrameWnd->GetActiveDocument();
	if (pDocument)
	{
		CString strPath = pDocument->GetPathName();
		strPath = strPath.Left(strPath.ReverseFind(_T('\\')));
		ShellExecute(NULL,NULL,strPath,NULL,NULL,SW_SHOW);
	}
}

void CMainFrame::OnUpdateOpenOwnerFloder(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

	CString strPath;
	CFrameWnd* pFrameWnd = GetActiveFrame();
	if(pFrameWnd)
	{
		CDocument* pDocument = pFrameWnd->GetActiveDocument();
		if(pDocument)
		{
			strPath = pDocument->GetPathName();
		}
	}    
    
    pCmdUI->Enable(!strPath.IsEmpty());
}

void CMainFrame::ClearOutPut()
{
    if (m_wndOutputPane.GetSafeHwnd())
    {
        m_wndOutputPane.Clear();

        //延迟50毫秒
        DelayNop(50);
    }
}

void CMainFrame::OutPutMsg(TCHAR* format, ...)
{
    if (m_wndOutputPane.GetSafeHwnd())
    {
        CString strMessage;

        va_list arglist;
        va_start(arglist,format);
        strMessage.FormatV(format, arglist);
        va_end(arglist);

		ShowPaneWnd(ID_VIEW_OUTPUTWND);
        m_wndOutputPane.InsertText(strMessage);
    }
}

void CMainFrame::OnUpdateDocPath(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
    pCmdUI->SetText(_T(""));
}

void CMainFrame::OnUpdateLine(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
    pCmdUI->SetText(_T(""));
}

void CMainFrame::OnUpdateInsert(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(FALSE);
    pCmdUI->SetText(_T(""));
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIFrameWndEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码

    if (m_wndStatusBar.GetSafeHwnd())
    {
        int nWidth = 0;
        for (int i=sizeof(indicators)/sizeof(UINT)-1;i>1;--i)
        {
            nWidth += m_wndStatusBar.GetPaneWidth(i);
        }
        m_wndStatusBar.SetPaneWidth(1,cx-nWidth-300);
    }
}

void CMainFrame::LoadConfigData()
{
    CString strAppDir = GetAppDirectory();

    //加载语法字
	//OASM语法字
    CString strOASMSyntaxWordFileName = m_systemOption.m_strOASMSyntaxWordFileName;
    if (!strOASMSyntaxWordFileName.IsEmpty() && strOASMSyntaxWordFileName[0] == _T('.'))
    {
        GetAbsolutePathByRelativePath(strOASMSyntaxWordFileName,strAppDir);
    }
    m_syntaxWordList.LoadOASMSyntaxWord(strOASMSyntaxWordFileName);
	
    //OASM添加选择框内容
    CString strOASMSelectionListFileName = m_systemOption.m_strOASMSelectionListFileName;
    if (!strOASMSelectionListFileName.IsEmpty() && strOASMSelectionListFileName[0] == _T('.'))
    {
        GetAbsolutePathByRelativePath(strOASMSelectionListFileName,strAppDir);
    }
    m_autoCompleteString.RefreshOASMSystemAutoCompleteGroup(strOASMSelectionListFileName);

    //OASM添加文件模板组
    CString strOASMTempletDir = m_systemOption.m_strOASMTempletDir;
    if (!strOASMTempletDir.IsEmpty() && strOASMTempletDir[0] == _T('.'))
    {
        GetAbsolutePathByRelativePath(strOASMTempletDir,strAppDir);
    }
    m_autoCompleteString.RefreshOASMTemplateFileList(strOASMTempletDir);

	//OML语法字
	CString strOMLSyntaxWordFileName = m_systemOption.m_strOMLSyntaxWordFileName;
	if (!strOMLSyntaxWordFileName.IsEmpty() && strOMLSyntaxWordFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOMLSyntaxWordFileName,strAppDir);
	}
	m_syntaxWordList.LoadOMLSyntaxWord(strOMLSyntaxWordFileName);

	
	//OML添加选择框内容
	CString strOMLSelectionListFileName = m_systemOption.m_strOMLSelectionListFileName;
	if (!strOMLSelectionListFileName.IsEmpty() && strOMLSelectionListFileName[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOMLSelectionListFileName,strAppDir);
	}
	m_autoCompleteString.RefreshOMLSystemAutoComplete(strOMLSelectionListFileName);

	//OML添加文件模板组
	CString strOMLTempletDir = m_systemOption.m_strOMLTempletDir;
	if (!strOMLTempletDir.IsEmpty() && strOMLTempletDir[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strOMLTempletDir,strAppDir);
	}
	m_autoCompleteString.RefreshOMLTemplateFileList(strOMLTempletDir);
	

    //加载提示数据
    m_hintString.LoadHintData();
}

void CMainFrame::AssociateOFile(BOOL bSetAlways)
{
	//关联程序，设置文档图标
	SetAssociate(_T("osl"),IDI_OSL_FILE,bSetAlways);
	SetAssociate(_T("opr"),IDI_OPR_FILE,bSetAlways);
	SetAssociate(_T("omp"),IDI_OMP_FILE,bSetAlways);
	SetAssociate(_T("omh"),IDI_OMH_FILE,bSetAlways);
	SetAssociate(_T("oam"),IDI_OAM_FILE,bSetAlways);
	SetAssociate(_T("oah"),IDI_OAH_FILE,bSetAlways);
}

void CMainFrame::OnAssociateOFile()
{
	AssociateOFile(TRUE);
}

void CMainFrame::OnResEditor()
{
    CString strResEditFileName = GetAppDirectory();
    strResEditFileName += _T("\\ResEdit\\ResEdit.exe");
    ShellExecute(NULL,NULL,strResEditFileName,NULL,NULL,SW_SHOW);
}

#include "DlgSystemOption.h"
void CMainFrame::OnSystemOptions()
{
    // TODO: 在此添加命令处理程序代码

    CDlgSystemOption dlgSystemOption;
    dlgSystemOption.m_dlgCommonOption.m_bUpdateEveryTime = m_systemOption.m_bUpdateEveryTime;

	dlgSystemOption.m_dlgOMLOption.m_strOMLPath = m_systemOption.m_strOMLPath;
	dlgSystemOption.m_dlgOMLOption.m_strOMLLanguagePath = m_systemOption.m_strOMLLanguagePath;

    dlgSystemOption.m_dlgOasmOption.m_strOasmPath = m_systemOption.m_strOasmPath;
    dlgSystemOption.m_dlgOasmOption.m_strOasmLanguagePath = m_systemOption.m_strOasmLanguagePath;

    dlgSystemOption.m_dlgLinkOption.m_strLinkerFileName = m_systemOption.m_strLinkerFileName;

	dlgSystemOption.m_dlgOMLEditOption.m_strOMLSyntaxWordFileName = m_systemOption.m_strOMLSyntaxWordFileName;
	dlgSystemOption.m_dlgOMLEditOption.m_strOMLSelectionListFileName = m_systemOption.m_strOMLSelectionListFileName;
	dlgSystemOption.m_dlgOMLEditOption.m_strOMLTempletDir = m_systemOption.m_strOMLTempletDir;	
	dlgSystemOption.m_dlgOMLEditOption.m_strOMLAutoCompleteFileName = m_systemOption.m_strOMLAutoCompleteFileName;
	dlgSystemOption.m_dlgOMLEditOption.m_strOMLTipFileName = m_systemOption.m_strOMLTipFileName;
	dlgSystemOption.m_dlgOMLEditOption.m_colorBackGround = m_systemOption.m_colorOMLBackGround;
	dlgSystemOption.m_dlgOMLEditOption.m_colorText = m_systemOption.m_colorOMLText;
	dlgSystemOption.m_dlgOMLEditOption.m_colorCommentLine = m_systemOption.m_colorOMLCommentLine;
	dlgSystemOption.m_dlgOMLEditOption.m_colorCommentBlock = m_systemOption.m_colorOMLCommentBlock;
	dlgSystemOption.m_dlgOMLEditOption.m_colorDigital = m_systemOption.m_colorOMLDigital;
	dlgSystemOption.m_dlgOMLEditOption.m_colorChar = m_systemOption.m_colorOMLChar;
	dlgSystemOption.m_dlgOMLEditOption.m_colorString = m_systemOption.m_colorOMLString;
	dlgSystemOption.m_dlgOMLEditOption.m_colorKeyWord = m_systemOption.m_colorOMLKeyWord;
	dlgSystemOption.m_dlgOMLEditOption.m_colorMacro = m_systemOption.m_colorOMLMacro;	
	dlgSystemOption.m_dlgOMLEditOption.m_colorOperator = m_systemOption.m_colorOMLOperator;
	dlgSystemOption.m_dlgOMLEditOption.m_lfTextFont = m_systemOption.m_lfOMLTextFont;
	dlgSystemOption.m_dlgOMLEditOption.m_bShowLineNumber = m_systemOption.m_bOMLShowLineNumber;
	dlgSystemOption.m_dlgOMLEditOption.m_bShowBookMarker = m_systemOption.m_bOMLShowBookMarker;
	dlgSystemOption.m_dlgOMLEditOption.m_bShowFold = m_systemOption.m_bOMLShowFold;
	dlgSystemOption.m_dlgOMLEditOption.m_bAutoSave = m_systemOption.m_bOMLAutoSave;

    dlgSystemOption.m_dlgOasmEditOption.m_strOASMSyntaxWordFileName = m_systemOption.m_strOASMSyntaxWordFileName;
    dlgSystemOption.m_dlgOasmEditOption.m_strSelectionListFileName = m_systemOption.m_strOASMSelectionListFileName;
    dlgSystemOption.m_dlgOasmEditOption.m_strOASMTempletDir = m_systemOption.m_strOASMTempletDir;
    dlgSystemOption.m_dlgOasmEditOption.m_strOASMAutoCompleteFileName = m_systemOption.m_strOASMAutoCompleteFileName;
    dlgSystemOption.m_dlgOasmEditOption.m_strOASMTipFileName = m_systemOption.m_strOASMTipFileName;
    dlgSystemOption.m_dlgOasmEditOption.m_colorBackGround = m_systemOption.m_colorOASMBackGround;
    dlgSystemOption.m_dlgOasmEditOption.m_colorText = m_systemOption.m_colorOASMText;
    dlgSystemOption.m_dlgOasmEditOption.m_colorCommentLine = m_systemOption.m_colorOASMCommentLine;
    dlgSystemOption.m_dlgOasmEditOption.m_colorCommentBlock = m_systemOption.m_colorOASMCommentBlock;
    dlgSystemOption.m_dlgOasmEditOption.m_colorIncludeText = m_systemOption.m_colorOASMIncludeText;
    dlgSystemOption.m_dlgOasmEditOption.m_colorIncludeLib = m_systemOption.m_colorOASMIncludeLib;
    dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentData = m_systemOption.m_colorOASMSegmentData;
    dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentRData = m_systemOption.m_colorOASMSegmentRData;
    dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentBSS = m_systemOption.m_colorOASMSegmentBSS;
    dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentExtern = m_systemOption.m_colorOASMSegmentExtern;
    dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentCode = m_systemOption.m_colorOASMSegmentCode;
    dlgSystemOption.m_dlgOasmEditOption.m_colorDigital = m_systemOption.m_colorOASMDigital;
    dlgSystemOption.m_dlgOasmEditOption.m_colorInstruction = m_systemOption.m_colorOASMInstruction;
    dlgSystemOption.m_dlgOasmEditOption.m_colorFInstruction = m_systemOption.m_colorOASMFInstruction;
    dlgSystemOption.m_dlgOasmEditOption.m_colorRegister = m_systemOption.m_colorOASMRegister;
    dlgSystemOption.m_dlgOasmEditOption.m_colorChar = m_systemOption.m_colorOASMChar;
    dlgSystemOption.m_dlgOasmEditOption.m_colorString = m_systemOption.m_colorOASMString;
    dlgSystemOption.m_dlgOasmEditOption.m_colorDefineWord = m_systemOption.m_colorOASMDefineWord;
    dlgSystemOption.m_dlgOasmEditOption.m_colorMacro = m_systemOption.m_colorOASMMacro;
    dlgSystemOption.m_dlgOasmEditOption.m_colorOperatorTxt = m_systemOption.m_colorOASMOperatorTxt;
    dlgSystemOption.m_dlgOasmEditOption.m_colorOperator = m_systemOption.m_colorOASMOperator;
    dlgSystemOption.m_dlgOasmEditOption.m_lfTextFont = m_systemOption.m_lfOASMTextFont;
    dlgSystemOption.m_dlgOasmEditOption.m_bShowLineNumber = m_systemOption.m_bOASMShowLineNumber;
    dlgSystemOption.m_dlgOasmEditOption.m_bShowBookMarker = m_systemOption.m_bOASMShowBookMarker;
    dlgSystemOption.m_dlgOasmEditOption.m_bShowFold = m_systemOption.m_bOASMShowFold;
	dlgSystemOption.m_dlgOasmEditOption.m_bAutoSave = m_systemOption.m_bOASMAutoSave;

	dlgSystemOption.m_dlgDoasmOption.m_strDoasmPath = m_systemOption.m_strDoasmPath;
	dlgSystemOption.m_dlgDoasmOption.m_strOasmLanguagePath = m_systemOption.m_strDoasmLanguagePath;

    if (dlgSystemOption.DoModal() == IDOK)
    {
        //没有修改直接返回
        if (!dlgSystemOption.IsModify())
            return;

        m_systemOption.m_bUpdateEveryTime = dlgSystemOption.m_dlgCommonOption.m_bUpdateEveryTime;

		m_systemOption.m_strOMLPath = dlgSystemOption.m_dlgOMLOption.m_strOMLPath;
		m_systemOption.m_strOMLLanguagePath = dlgSystemOption.m_dlgOMLOption.m_strOMLLanguagePath;

        m_systemOption.m_strOasmPath = dlgSystemOption.m_dlgOasmOption.m_strOasmPath;
        m_systemOption.m_strOasmLanguagePath = dlgSystemOption.m_dlgOasmOption.m_strOasmLanguagePath;

        m_systemOption.m_strLinkerFileName = dlgSystemOption.m_dlgLinkOption.m_strLinkerFileName;

		m_systemOption.m_strOMLSyntaxWordFileName = dlgSystemOption.m_dlgOMLEditOption.m_strOMLSyntaxWordFileName;
		m_systemOption.m_strOMLSelectionListFileName = dlgSystemOption.m_dlgOMLEditOption.m_strOMLSelectionListFileName;
		m_systemOption.m_strOMLTempletDir = dlgSystemOption.m_dlgOMLEditOption.m_strOMLTempletDir;		
		m_systemOption.m_strOMLAutoCompleteFileName = dlgSystemOption.m_dlgOMLEditOption.m_strOMLAutoCompleteFileName;
		m_systemOption.m_strOMLTipFileName = dlgSystemOption.m_dlgOMLEditOption.m_strOMLTipFileName;
		m_systemOption.m_colorOMLBackGround = dlgSystemOption.m_dlgOMLEditOption.m_colorBackGround;
		m_systemOption.m_colorOMLText = dlgSystemOption.m_dlgOMLEditOption.m_colorText;
		m_systemOption.m_colorOMLCommentLine = dlgSystemOption.m_dlgOMLEditOption.m_colorCommentLine;
		m_systemOption.m_colorOMLCommentBlock = dlgSystemOption.m_dlgOMLEditOption.m_colorCommentBlock;
		m_systemOption.m_colorOMLDigital = dlgSystemOption.m_dlgOMLEditOption.m_colorDigital;
		m_systemOption.m_colorOMLChar = dlgSystemOption.m_dlgOMLEditOption.m_colorChar;
		m_systemOption.m_colorOMLString = dlgSystemOption.m_dlgOMLEditOption.m_colorString;
		m_systemOption.m_colorOMLKeyWord = dlgSystemOption.m_dlgOMLEditOption.m_colorKeyWord;
		m_systemOption.m_colorOMLMacro = dlgSystemOption.m_dlgOMLEditOption.m_colorMacro;
		m_systemOption.m_colorOMLOperator = dlgSystemOption.m_dlgOMLEditOption.m_colorOperator;
		m_systemOption.m_lfOMLTextFont = dlgSystemOption.m_dlgOMLEditOption.m_lfTextFont;
		m_systemOption.m_bOMLShowLineNumber = dlgSystemOption.m_dlgOMLEditOption.m_bShowLineNumber;
		m_systemOption.m_bOMLShowBookMarker = dlgSystemOption.m_dlgOMLEditOption.m_bShowBookMarker;
		m_systemOption.m_bOMLShowFold = dlgSystemOption.m_dlgOMLEditOption.m_bShowFold;
		m_systemOption.m_bOMLAutoSave = dlgSystemOption.m_dlgOMLEditOption.m_bAutoSave;
        
        m_systemOption.m_strOASMSyntaxWordFileName = dlgSystemOption.m_dlgOasmEditOption.m_strOASMSyntaxWordFileName;		
        m_systemOption.m_strOASMSelectionListFileName = dlgSystemOption.m_dlgOasmEditOption.m_strSelectionListFileName;
        m_systemOption.m_strOASMTempletDir = dlgSystemOption.m_dlgOasmEditOption.m_strOASMTempletDir;
        m_systemOption.m_strOASMAutoCompleteFileName = dlgSystemOption.m_dlgOasmEditOption.m_strOASMAutoCompleteFileName;
        m_systemOption.m_strOASMTipFileName = dlgSystemOption.m_dlgOasmEditOption.m_strOASMTipFileName;
        m_systemOption.m_colorOASMBackGround = dlgSystemOption.m_dlgOasmEditOption.m_colorBackGround;
        m_systemOption.m_colorOASMText = dlgSystemOption.m_dlgOasmEditOption.m_colorText;
        m_systemOption.m_colorOASMCommentLine = dlgSystemOption.m_dlgOasmEditOption.m_colorCommentLine;
        m_systemOption.m_colorOASMCommentBlock = dlgSystemOption.m_dlgOasmEditOption.m_colorCommentBlock;
        m_systemOption.m_colorOASMIncludeText = dlgSystemOption.m_dlgOasmEditOption.m_colorIncludeText;
        m_systemOption.m_colorOASMIncludeLib = dlgSystemOption.m_dlgOasmEditOption.m_colorIncludeLib;
        m_systemOption.m_colorOASMSegmentData = dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentData;
        m_systemOption.m_colorOASMSegmentRData = dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentRData;
        m_systemOption.m_colorOASMSegmentBSS = dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentBSS;
        m_systemOption.m_colorOASMSegmentExtern = dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentExtern;
        m_systemOption.m_colorOASMSegmentCode = dlgSystemOption.m_dlgOasmEditOption.m_colorSegmentCode;
        m_systemOption.m_colorOASMDigital = dlgSystemOption.m_dlgOasmEditOption.m_colorDigital;
        m_systemOption.m_colorOASMInstruction = dlgSystemOption.m_dlgOasmEditOption.m_colorInstruction;
        m_systemOption.m_colorOASMFInstruction = dlgSystemOption.m_dlgOasmEditOption.m_colorFInstruction;
        m_systemOption.m_colorOASMRegister = dlgSystemOption.m_dlgOasmEditOption.m_colorRegister;
        m_systemOption.m_colorOASMChar = dlgSystemOption.m_dlgOasmEditOption.m_colorChar;
        m_systemOption.m_colorOASMString = dlgSystemOption.m_dlgOasmEditOption.m_colorString;
        m_systemOption.m_colorOASMDefineWord = dlgSystemOption.m_dlgOasmEditOption.m_colorDefineWord;
        m_systemOption.m_colorOASMMacro = dlgSystemOption.m_dlgOasmEditOption.m_colorMacro;
        m_systemOption.m_colorOASMOperatorTxt = dlgSystemOption.m_dlgOasmEditOption.m_colorOperatorTxt;
        m_systemOption.m_colorOASMOperator = dlgSystemOption.m_dlgOasmEditOption.m_colorOperator;
        m_systemOption.m_lfOASMTextFont = dlgSystemOption.m_dlgOasmEditOption.m_lfTextFont;
        m_systemOption.m_bOASMShowLineNumber = dlgSystemOption.m_dlgOasmEditOption.m_bShowLineNumber;
        m_systemOption.m_bOASMShowBookMarker = dlgSystemOption.m_dlgOasmEditOption.m_bShowBookMarker;
        m_systemOption.m_bOASMShowFold = dlgSystemOption.m_dlgOasmEditOption.m_bShowFold;
		m_systemOption.m_bOASMAutoSave = dlgSystemOption.m_dlgOasmEditOption.m_bAutoSave;

		m_systemOption.m_strDoasmPath = dlgSystemOption.m_dlgDoasmOption.m_strDoasmPath;
		m_systemOption.m_strDoasmLanguagePath = dlgSystemOption.m_dlgDoasmOption.m_strOasmLanguagePath;

        m_systemOption.Save(m_strSystemOptionFileName);

        //设置输出窗口背景色
        m_wndOutputPane.SetBackgroundColor(m_systemOption.m_colorOMLBackGround);

        //更新所有源代码编辑视图风格
        CWinApp *pWinApp = AfxGetApp(); //得到应用程序指针
        POSITION p = pWinApp->GetFirstDocTemplatePosition();//得到第1个文档模板
        while (p != NULL) //遍历文档模板
        {
            CDocTemplate* pDocTemplate = pWinApp->GetNextDocTemplate(p);
            POSITION p1 = pDocTemplate->GetFirstDocPosition();//得到文档模板对应的第1个文档
            while (p1 != NULL) //遍历文档模板对应的文档
            {
                CDocument *pDocument = pDocTemplate->GetNextDoc(p1);
                POSITION p2 = pDocument->GetFirstViewPosition(); //得到文档对应的第1个视图
                while (p2 != NULL) //遍历文档对应的视图
                {
                    CView *pView = pDocument->GetNextView(p2);
                    if (pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
                    {
                        ((COLIDEView*)pView)->UpdateAllStyle();
                    }
                }
            }
        }
    }
}
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_SYSKEYUP)
	{
		char nchar = pMsg->wParam;

		switch (nchar)
		{
		case VK_F10:
			{
				if(pMsg->message == WM_SYSKEYDOWN)
				{
					SendMessage(WM_COMMAND,ID_DEBUG_SINGLE_LINE,NULL);
					return TRUE;
				}
				
				return FALSE;
			}
		default:
			break;
		}
	}
    else if(pMsg->message == WM_KEYDOWN)
    {
        char nchar = pMsg->wParam;

        switch (nchar)
        {
        case VK_F1:
			SendMessage(WM_COMMAND,ID_OML_HELP,NULL);
            break;
        case VK_F3:
            SendMessage(WM_COMMAND,ID_EDIT_REPEAT,NULL);
            break;
        case VK_F5:
            SendMessage(WM_COMMAND,ID_BEGIN_DEBUGGER,NULL);
            break;
        case VK_F7:
            SendMessage(WM_COMMAND,ID_BUILD_PROJECT,NULL);
            break;
        case VK_F8:
            SendMessage(WM_COMMAND,ID_BUILD_AND_RUN,NULL);
            break;
		//case VK_F9:
		//	SendMessage(WM_COMMAND,ID_SET_BREAK_POINT,NULL);
		//	break;		
        //case VK_F11:
        //    SendMessage(WM_COMMAND,ID_BUILD_AND_LINK,NULL);
        //    break;
            //屏蔽下列快捷键
        case _T('B'):
        case _T('Q'):
        case _T('W'):
        case _T('E'):
        case _T('R'):        
			{
				if (GetKeyState(VK_CONTROL)&0x80)
				{
					CFrameWnd* pFrameWnd = GetActiveFrame();
					if(pFrameWnd)
					{
						CView* pView = pFrameWnd->GetActiveView();
						if(pView && pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
						{							
							if(pMsg->hwnd == ((COLIDEView*)pView)->GetCtrl().GetSafeHwnd())
							{
								return TRUE;
							}
						}						
					}
				}
				break;
			}
		case _T('T'):
			{
				//Ctrl+t
				if(GetKeyState(VK_CONTROL)&0x80)
				{
					CFrameWnd* pFrameWnd = GetActiveFrame();
					if(pFrameWnd)
					{
						CView* pView = pFrameWnd->GetActiveView();
						if(pView && pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
						{							
							if(pMsg->hwnd == ((COLIDEView*)pView)->GetCtrl().GetSafeHwnd())
							{
								::SendMessage(pView->GetSafeHwnd(),WM_COMMAND,ID_FILE_TEMPLATE_LIST,0);
								return TRUE;
							}
						}
					}
				}

				break;
			}
        case _T('C'):
			{
				//Ctrl+C
				if (GetKeyState(VK_CONTROL)&0x80)
				{
					//输出生成窗口
					if (pMsg->hwnd == m_wndOutputPane.GetOutputBuildWnd()->GetSafeHwnd())
					{
						::SendMessage(pMsg->hwnd,WM_COMMAND,ID_EDIT_COPY,0);
					}
				}
				break;
			}
        case _T('S'):
			{
				//Ctrl+Shift+S
				if((GetKeyState(VK_CONTROL)&0x80) && (GetKeyState(VK_SHIFT)&0x8000))
				{
					//OnSaveAllDocument();
					SendMessage(WM_COMMAND,ID_FILE_SAVE_ALL,0);					
				}

				break;
			}
        }
    }

    return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}

#include "OCodeBuild.h"
#include "./Common/Common.h"
#include "./Common/UnicodeCovert.h"
#include "RunCommand.h"

int CMainFrame::BuildCode(CProjectProperty* pProjectProperty,const CString& strPathName,int nCodeFileType,BOOL bReBuild)
{
    ASSERT(pProjectProperty);

    if (strPathName.IsEmpty())return false;

	CString strCompilerPath;
	CString strLanguagePath;

	switch(nCodeFileType)
	{
		//如果是中间文件
	case BCT_OML:
		{
			strCompilerPath = m_systemOption.m_strOMLPath;
			strLanguagePath = m_systemOption.m_strOMLLanguagePath;
			break;
		}
		//如果是汇编文件
	case BCT_OASM:
		{
			strCompilerPath = m_systemOption.m_strOasmPath;
			strLanguagePath = m_systemOption.m_strOasmLanguagePath;
			break;
		}
	default:
		{
			return false;
		}
	}
    
    if (pProjectProperty == NULL || strCompilerPath.IsEmpty() || strLanguagePath.IsEmpty())
    {
        return false;
    }

    //如果是相对路径
    if (strCompilerPath[0] == _T('.'))
    {
        GetAbsolutePathByRelativePath(strCompilerPath,GetAppDirectory());
    }
    if (strLanguagePath[0] == _T('.'))
    {
        GetAbsolutePathByRelativePath(strLanguagePath,GetAppDirectory());
    }

    CString strObjPath;
    strObjPath = pProjectProperty->GetProjectAbsolutePathMiddleOutPut(m_systemOption.m_bIsDebug);	
	char chPath[MAX_PATH];
	CopyStr(chPath,MAX_PATH,strObjPath);
	MakeSureDirectoryPathExists(chPath); //此函数不支持Unicode字符
    strObjPath += strPathName.Right(strPathName.GetLength()-strPathName.ReverseFind(_T('\\'))-1);
    strObjPath = strObjPath.Left(strObjPath.ReverseFind(_T('.')));
    strObjPath += _T(".obj");
	
	//判断文件是否有必要编译
	CStringArray strarrayAssociateFile;
	if(!CodeFileNeedBuild(pProjectProperty,strCompilerPath,strPathName,strObjPath,strarrayAssociateFile))
	{
		//不需要重新编译
		if(bReBuild == FALSE)		
			return -1;		
	}

	COCodeBuild OCodeBuild;
	switch(nCodeFileType)
	{
		//如果是中间文件
	case BCT_OML:
		{
			//编译代码文件
			if(!OCodeBuild.OML_BuildCode(strCompilerPath,strPathName,strLanguagePath,strObjPath,m_systemOption.m_bIsDebug))
			{
				return 0;
			}
			break;
		}
		//如果是汇编文件
	case BCT_OASM:
		{
			//编译代码文件
			if(!OCodeBuild.OASM_BuildCode(strCompilerPath,strPathName,strLanguagePath,strObjPath,m_systemOption.m_bIsDebug))
			{
				return 0;
			}
		}	
	}    

	//编译成功，修改编译记录
	SetBuildRecord(pProjectProperty,strPathName,strObjPath,strarrayAssociateFile);

    return 1;
}

int CMainFrame::BuildResource(CProjectProperty* pProjectProperty,const CString& strResourceName,BOOL bReBuild)
{
	ASSERT(pProjectProperty);

	if ((pProjectProperty == NULL) || strResourceName.IsEmpty())
		return false;

	CString strResEditFileName = GetAppDirectory();
	strResEditFileName += _T("\\ResEdit\\ResEdit.exe");

	CString strResPath;
	strResPath = pProjectProperty->GetProjectAbsolutePathMiddleOutPut(m_systemOption.m_bIsDebug);	
	char chPath[MAX_PATH];
	CopyStr(chPath,MAX_PATH,strResPath);
	MakeSureDirectoryPathExists(chPath); //此函数不支持Unicode字符
	strResPath += strResourceName.Right(strResourceName.GetLength()-strResourceName.ReverseFind(_T('\\'))-1);
	strResPath = strResPath.Left(strResPath.ReverseFind(_T('.')));
	strResPath += _T(".res");

	//判断文件是否有必要编译
	CStringArray strarrayAssociateFile;
	if(!CodeFileNeedBuild(pProjectProperty,strResEditFileName,strResourceName,strResPath,strarrayAssociateFile))
	{
		//不需要重新编译
		if(bReBuild == FALSE)		
			return -1;
	}

	COCodeBuild OCodeBuild;
	//编译代码文件
	if (!OCodeBuild.CompileResourceFile(strResEditFileName,strResourceName,strResPath))
	{
		return 0;
	}

	//编译成功，修改编译记录
	SetBuildRecord(pProjectProperty,strResourceName,strResPath,strarrayAssociateFile);

	return 1;
}

#include <io.h>
void CMainFrame::SetBuildRecord(CProjectProperty* pProjectProperty,const CString& strFileName,const CString& strObjFileName,CStringArray& strarrayAssociateFile)
{
	COLProjectBuildRecord* pOLProjectBuildRecord = pProjectProperty->m_pProjectBuildRecord;	

	CString strFileTime,strObjFileTime;
	_finddata_t fileinfo;
	char chTemp[MAX_PATH];	

	//得到文件信息
	CopyStr(chTemp,MAX_PATH,strFileName);
	_findfirst(chTemp,&fileinfo);	
	strFileTime = ctime(&fileinfo.time_write);

	//目标文件信息
	CopyStr(chTemp,MAX_PATH,strObjFileName);
	_findfirst(chTemp,&fileinfo);	
	strObjFileTime = ctime(&fileinfo.time_write);

	int nIndex = pOLProjectBuildRecord->SearchRecord(strFileName);
	if(nIndex >= 0)
	{
		pOLProjectBuildRecord->SetAtFileTime(nIndex,strFileTime);
		pOLProjectBuildRecord->SetAtObjFileTime(nIndex,strObjFileTime);
	}
	else
	{
		pOLProjectBuildRecord->AddRecord(strFileName,strFileTime,strObjFileTime);
	}

	CString strAssociateFileName;
	for(int i=0;i<strarrayAssociateFile.GetCount();++i)
	{
		strAssociateFileName = strarrayAssociateFile.GetAt(i);

		CopyStr(chTemp,MAX_PATH,strAssociateFileName);
		_findfirst(chTemp,&fileinfo);	
		strFileTime = ctime(&fileinfo.time_write);

		nIndex = pOLProjectBuildRecord->SearchRecord(strAssociateFileName);
		if(nIndex >= 0)
		{
			pOLProjectBuildRecord->SetAtFileTime(nIndex,strFileTime);			
		}
		else
		{
			pOLProjectBuildRecord->AddRecord(strAssociateFileName,strFileTime);
		}
	}
}

BOOL CMainFrame::CodeFileNeedBuild(CProjectProperty* pProjectProperty,const CString& strComplier,const CString& strFileName,const CString& strObjFileName,CStringArray& strarrayAssociateFile)
{
	//如果目标文件不存在
	if(!FileExist(strObjFileName))
		return TRUE;

	COLProjectBuildRecord* pOLProjectBuildRecord = pProjectProperty->m_pProjectBuildRecord;		
	int nIndex = pOLProjectBuildRecord->SearchRecord(strFileName);
	if(nIndex < 0)//没有找到文件记录
	{
		return TRUE;
	}

	//比较文件时间
	_finddata_t fileinfo;
	char chTemp[MAX_PATH];	

	//得到文件信息
	CopyStr(chTemp,MAX_PATH,strFileName);
	_findfirst(chTemp,&fileinfo);		
	CString strFileTime = pOLProjectBuildRecord->GetAtFileTime(nIndex);
	if(strFileTime != ctime(&fileinfo.time_write))  //比较文件修改时间
		return TRUE;

	//得到目标文件信息
	CopyStr(chTemp,MAX_PATH,strObjFileName);
	_findfirst(chTemp,&fileinfo);
	CString strObjFileTime = pOLProjectBuildRecord->GetAtObjFileTime(nIndex);
	if(strObjFileTime != ctime(&fileinfo.time_write)) //比较文件修改时间
		return TRUE;

	//得到关联文件列表
	if(!GetAssociateFile(strFileName,strComplier,strarrayAssociateFile))
		return TRUE;

	//判断关联文件是否被修改
	for(int i=0;i<strarrayAssociateFile.GetCount();++i)
	{
		if(FileIsModified(pOLProjectBuildRecord,strarrayAssociateFile.GetAt(i)))
			return TRUE;
	}

	return FALSE;
}

#include "./Data/StdioFile/StdioFileEx.h"
BOOL CMainFrame::GetAssociateFile(const CString& strFileName,const CString& strComplier,CStringArray& strarrayAssociateFile)
{
	CStdioFileEx stdioFile;
	if(!stdioFile.Open(strFileName,CFile::typeText|CFile::modeRead))
		return FALSE;

	CString strInclude = _T(".包含文");
	int nLength = strInclude.GetLength();
	CString strLine;
	while(stdioFile.ReadStringEx(strLine,TRUE))
	{		
		if(strLine.Left(nLength) == strInclude)
		{
			int nPos1 = strLine.Find(_T('<'));
			if(nPos1 < 0)break;
			int nPos2 = strLine.Find(_T('>'),nPos1);
			if(nPos2 < 0)break;
			
			CString strFilePath = strLine.Mid(nPos1+1,nPos2 - nPos1-1);
			strFilePath.Trim();
			if(strFilePath.GetLength() == 0)
				break;

			//如果第一个字符是星号*
			if(strFilePath[0] == _T('*'))
			{
				strFilePath = strFilePath.Right(strFilePath.GetLength()-1);
				
				CString strComplierPath = GetPathFromPathName(strComplier);
				CString strSysIncludePath;
				strSysIncludePath = strComplierPath + _T("include\\");
				if(!GetAbsolutePathByRelativePath(strFilePath,strSysIncludePath))
					break;
			}
			else if(strFilePath[0] == _T('.'))
			{
				CString strRelativePath = GetPathFromPathName(strFileName);
				if(!GetAbsolutePathByRelativePath(strFilePath,strRelativePath))
					break;
			}

			BOOL bHasAssociate = FALSE;
			//搜索是否已经加载到关联数组中
			for(int i=0;i<strarrayAssociateFile.GetCount();++i)
			{
				if(strarrayAssociateFile.GetAt(i) == strFilePath)
				{
					bHasAssociate = TRUE;
					break;
				}
			}

			//没有关联
			if(bHasAssociate == FALSE)
			{
				strarrayAssociateFile.Add(strFilePath);
				if(!GetAssociateFile(strFilePath,strComplier,strarrayAssociateFile))
					return FALSE;
			}
		}
	}	

	return TRUE;
}

BOOL CMainFrame::FileIsModified(COLProjectBuildRecord* pOLProjectBuildRecord,const CString& strFileName)
{		
	int nIndex = pOLProjectBuildRecord->SearchRecord(strFileName);
	if(nIndex < 0)
	{		
		return TRUE;
	}

	_finddata_t fileinfo;
	char chTemp[MAX_PATH];	

	//得到当前文件信息
	CopyStr(chTemp,MAX_PATH,strFileName);
	_findfirst(chTemp,&fileinfo);

	//文件被修改
	CString strFileTime = pOLProjectBuildRecord->GetAtFileTime(nIndex);
	if(strFileTime != ctime(&fileinfo.time_write))
		return TRUE;

	return FALSE;
}

void CMainFrame::LinkProject(CProjectProperty* pProjectProperty,BOOL bReLink,BOOL bRunExeFile)
{
    ASSERT(pProjectProperty);

    if (m_systemOption.m_strLinkerFileName.IsEmpty())
        return;

    CString strObjPath = pProjectProperty->GetProjectAbsolutePathMiddleOutPut(m_systemOption.m_bIsDebug);
    if (strObjPath.IsEmpty())
        return;

    CString strExeFileName = pProjectProperty->GetProjectAbsolutePathOutPutFileName(m_systemOption.m_bIsDebug);
    if (strExeFileName.IsEmpty())
        return;

	BOOL bNeedLink = TRUE;
	//比较文件时间
	_finddata_t fileinfo;
	char chTemp[MAX_PATH];	
	COLProjectBuildRecord* pOLProjectBuildRecord = pProjectProperty->m_pProjectBuildRecord;		
	int nIndex = pOLProjectBuildRecord->SearchRecord(strExeFileName);
	if(bReLink == FALSE)
	{
		//判断EXE文件是否需要重新链接
		if(nIndex >= 0)//有找到文件记录
		{
			CString strFileTime = pOLProjectBuildRecord->GetAtFileTime(nIndex);
			if(!strFileTime.IsEmpty()) //时间不为空
			{
				//得到文件信息
				CopyStr(chTemp,MAX_PATH,strExeFileName);
				_findfirst(chTemp,&fileinfo);			
				if(strFileTime == ctime(&fileinfo.time_write))  //文件时间没有修改就没必要重新链接
				{
					bNeedLink = FALSE;
				}	
			}								
		}		
	}	

	if(bNeedLink)
	{
		CString strExeFilePath = strExeFileName.Left(strExeFileName.ReverseFind('\\')+1);
		char chPath[MAX_PATH];
		CopyStr(chPath,MAX_PATH,strExeFilePath);
		MakeSureDirectoryPathExists(chPath); //此函数不支持Unicode字符

		CString strDefFileName = pProjectProperty->m_strDefFileName;

		CString strLinkerPath = m_systemOption.m_strLinkerFileName;
		//如果是相对路径
		if (strLinkerPath[0] == _T('.'))
		{
			GetAbsolutePathByRelativePath(strLinkerPath,GetAppDirectory());
		}

		//设置链接参数
		CString strOtherLinkParam;
		strOtherLinkParam += (pProjectProperty->m_nLinkSubSystem == 0)?_T(" /SUBSYSTEM:CONSOLE"):_T(" /SUBSYSTEM:WINDOWS");

		strExeFileName = pProjectProperty->GetProjectAbsolutePathOutPutFileName(m_systemOption.m_bIsDebug);
		COCodeBuild OASMBuild;
		if (!OASMBuild.LinkObjPath(strLinkerPath,strObjPath,strExeFileName,strOtherLinkParam,pProjectProperty->m_nProgramType == CProjectProperty::PT_DLL,strDefFileName))
		{
			//链接失败，则下一次需要重新链接
			if(nIndex < 0)//没有找到文件记录
			{
				pOLProjectBuildRecord->AddRecord(strExeFileName,_T(""));
			}
			else
			{
				pOLProjectBuildRecord->SetAtFileTime(nIndex,_T(""));
			}
			m_bSaveProject = TRUE;

			strExeFileName.Empty();
			return;
		}

		//记录EXE文件链接记录
		CopyStr(chTemp,MAX_PATH,strExeFileName);
		_findfirst(chTemp,&fileinfo);
		CString strFileTime;
		strFileTime = ctime(&fileinfo.time_write);
		if(nIndex < 0)//没有找到文件记录
		{
			pOLProjectBuildRecord->AddRecord(strExeFileName,strFileTime);
		}
		else
		{
			pOLProjectBuildRecord->SetAtFileTime(nIndex,strFileTime);
		}
		m_bSaveProject = TRUE;
	}	

    if (bRunExeFile && (pProjectProperty->m_nProgramType == CProjectProperty::PT_EXE))
    {
		CString strCurDir = GetPathFromPathName(strExeFileName);
		::SetCurrentDirectory(strCurDir);

        RunProgramme(strExeFileName);
    }
}

int CMainFrame::BuildProject(CProjectProperty* pProjectProperty,BOOL bReBuild)
{
    ASSERT(pProjectProperty);

	m_bSaveProject = FALSE;

	//设置调试版还是纯净版
	SetBuildDebugOrRelease();

    CString strCodeDir = pProjectProperty->GetProjectAbsolutePathCodeDir();
    if (strCodeDir.IsEmpty())
    {
        OutPutMsg(_T("未设置工程代码目录\n"));
        return FALSE;
    }

    //保存工程文件夹下的文件
    CString strProjectFilePath = pProjectProperty->m_strProjectFilePath;
    strProjectFilePath = strProjectFilePath.Left(strProjectFilePath.ReverseFind(_T('\\')));
    theApp.SaveDocument(strProjectFilePath,TRUE);

    OutPutMsg(_T("正在编译工程 %s...\n"),pProjectProperty->m_strProjectName);

    int nCodeFileCount = 0;
    pProjectProperty->m_strDefFileName.Empty();
    if(!BrowseBuildCodeFile(strCodeDir,pProjectProperty,nCodeFileCount,bReBuild ))
		return -1;
    
	//编译资源文件
	CString strResource = pProjectProperty->GetProjectAbsolutePathResourceDir();
	if(!strResource.IsEmpty())
	{
		if(!BrowseBuildResourceFile(strResource,pProjectProperty,nCodeFileCount,bReBuild ))
			return -1;
	}	

    return nCodeFileCount;
}

BOOL CMainFrame::BrowseBuildCodeFile(const CString& strDir,CProjectProperty* pProjectProperty,int& nCodeFileCount,BOOL bReBuild)
{
    CFileFind ff;
    CString szDir = strDir;

    if (szDir.Right(1) != _T("\\"))
    {
        szDir += _T("\\");
    }
    szDir += _T("*.*");

    BOOL bResult = TRUE;
    BOOL res = ff.FindFile(szDir);
    while (res)
    {
        res = ff.FindNextFile();
        if (ff.IsDots())continue;

        if (ff.IsDirectory())
        {
            if (!BrowseBuildCodeFile(ff.GetFilePath(),pProjectProperty,nCodeFileCount,bReBuild))
            {
                bResult = FALSE;
                break;
            }

            continue;
        }

        //否则是文件
        CString strFilePath = ff.GetFilePath();
        CString strExternName = ff.GetFileName();
        int nPos = strExternName.ReverseFind(_T('.'));
        if (nPos < 0)continue;

        strExternName = strExternName.Right(strExternName.GetLength()-nPos-1);
        strExternName.MakeLower();
        //中间语言代码文件
        if (strExternName == _T("omp"))
        {
			int nResult = BuildCode(pProjectProperty,strFilePath,BCT_OML,bReBuild );
			if(nResult == 0)
			{
				bResult = FALSE;
				break;
			}

			if(nResult > 0)
			{
				++nCodeFileCount;
				m_bSaveProject = TRUE;
				OutPutMsg(_T("%s\n"),ff.GetFileName());
			}
			//小于0为略过编译
			//else
			//{
			//}
        }
		//汇编代码文件
		else if (strExternName == _T("oam"))
		{			
			int nResult = BuildCode(pProjectProperty,strFilePath,BCT_OASM,bReBuild);
			if(nResult == 0)
			{
				bResult = FALSE;
				break;
			}

			if(nResult > 0)
			{
				++nCodeFileCount;
				m_bSaveProject = TRUE;
				OutPutMsg(_T("%s\n"),ff.GetFileName());
			}
			//小于0为略过编译
			//else
			//{
			//}			
		}
        //定义文件
        else if (strExternName == _T("def"))
        {
            pProjectProperty->m_strDefFileName += strFilePath;
			pProjectProperty->m_strDefFileName += _T("\n"); //有多个def文件用回车符分隔
        }
    }
    ff.Close();

    return bResult;
}

BOOL CMainFrame::BrowseBuildResourceFile(const CString& strDir,CProjectProperty* pProjectProperty,int& nCodeFileCount,BOOL bReBuild)
{
	CFileFind ff;
	CString szDir = strDir;

	if (szDir.Right(1) != _T("\\"))
	{
		szDir += _T("\\");
	}
	szDir += _T("*.*");

	BOOL bResult = TRUE;
	BOOL res = ff.FindFile(szDir);
	while (res)
	{
		res = ff.FindNextFile();
		if (ff.IsDots())continue;

		if (ff.IsDirectory())
		{
			if (!BrowseBuildResourceFile(ff.GetFilePath(),pProjectProperty,nCodeFileCount,bReBuild))
			{
				bResult = FALSE;
				break;
			}

			continue;
		}

		//否则是文件
		CString strFilePath = ff.GetFilePath();
		CString strExternName = ff.GetFileName();
		int nPos = strExternName.ReverseFind(_T('.'));
		if (nPos < 0)continue;

		strExternName = strExternName.Right(strExternName.GetLength()-nPos-1);
		strExternName.MakeLower();
		//代码文件
		if (strExternName == _T("rc"))
		{			
			int nResult = BuildResource(pProjectProperty,strFilePath,bReBuild);
			if(nResult == 0)
			{
				bResult = FALSE;
				break;
			}

			if(nResult > 0)
			{
				++nCodeFileCount;
				m_bSaveProject = TRUE;
				OutPutMsg(_T("%s\n"),ff.GetFileName());
			}
			//小于0为略过编译
			//else
			//{
			//}
		}		
	}
	ff.Close();

	return bResult;
}

void CMainFrame::OnBuildProject()
{
    // TODO: 在此添加命令处理程序代码

    ClearOutPut();

    CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
    if (pProjectPropertyCur)
    {
        BuildProject(pProjectPropertyCur);

		if(m_bSaveProject)
		{
			m_wndSolutionPane.SaveProjectProperty(pProjectPropertyCur,pProjectPropertyCur->m_strProjectFilePath);
		}
    }	

    CommandFinish();
}

void CMainFrame::OnLinkProject()
{
    // TODO: 在此添加命令处理程序代码

    ClearOutPut();

    CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
    if (pProjectPropertyCur)
    {
        LinkProject(pProjectPropertyCur,TRUE);
    }

    CommandFinish();
}

void CMainFrame::OnBuildAndLink()
{
    // TODO: 在此添加命令处理程序代码

    ClearOutPut();

    CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
    if (pProjectPropertyCur)
    {
        int nResult = BuildProject(pProjectPropertyCur);
		if(nResult > 0)
        {
            LinkProject(pProjectPropertyCur,TRUE);
        }
		//等于0表示没有重新编译的文件
		else if(nResult == 0)
		{
			LinkProject(pProjectPropertyCur,FALSE);
		}

		if(m_bSaveProject)
		{
			m_wndSolutionPane.SaveProjectProperty(pProjectPropertyCur,pProjectPropertyCur->m_strProjectFilePath);
		}
    }

    CommandFinish();
}

void CMainFrame::OnReBuildAndLink()
{
	ClearOutPut();

	CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
	if (pProjectPropertyCur)
	{
		if(BuildProject(pProjectPropertyCur,TRUE) >= 0)
		{
			LinkProject(pProjectPropertyCur,TRUE);
		}

		if(m_bSaveProject)
		{
			m_wndSolutionPane.SaveProjectProperty(pProjectPropertyCur,pProjectPropertyCur->m_strProjectFilePath);
		}
	}

	CommandFinish();
}

void CMainFrame::OnBuildAll()
{
    // TODO: 在此添加命令处理程序代码

    ClearOutPut();

    HTREEITEM hItemProject =  m_wndSolutionPane.GetFirstProject();
    while (hItemProject)
    {
        CProjectProperty* pProjectProperty = m_wndSolutionPane.GetProjectProperty(hItemProject);
        if (pProjectProperty)
        {
			int nResult = BuildProject(pProjectProperty);
			if(nResult > 0)
			{
				LinkProject(pProjectProperty,TRUE);
			}
			//等于0表示没有重新编译的文件
			else if(nResult == 0)
			{
				LinkProject(pProjectProperty,FALSE);
			}

            OutPutMsg(_T("\n"));
        }

		if(m_bSaveProject)
		{
			m_wndSolutionPane.SaveProjectProperty(pProjectProperty,pProjectProperty->m_strProjectFilePath);
		}

        hItemProject = m_wndSolutionPane.GetNextItem(hItemProject);
    }

    CommandFinish();
}

void CMainFrame::OnBuildAndRun()
{
    // TODO: 在此添加命令处理程序代码

    ClearOutPut();

    CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
    if (pProjectPropertyCur)
    {
		int nResult = BuildProject(pProjectPropertyCur);
		if(nResult > 0)
		{
			LinkProject(pProjectPropertyCur,TRUE,TRUE);
		}
		//等于0表示没有重新编译的文件
		else if(nResult == 0)
		{
			LinkProject(pProjectPropertyCur,FALSE,TRUE);
		}

		if(m_bSaveProject)
		{
			m_wndSolutionPane.SaveProjectProperty(pProjectPropertyCur,pProjectPropertyCur->m_strProjectFilePath);
		}
    }

	CommandFinish();
}

void CMainFrame::CommandFinish()
{
    OutPutMsg(_T("\n---------完成---------\n"));
}

LRESULT CMainFrame::OnOpenDocument(WPARAM wParam,LPARAM lParam)
{
	OpenDocument((LPCTSTR)wParam);

	return 1;
}

void CMainFrame::OnUpdateBuildProject(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(m_wndSolutionPane.HasProject());
}

void CMainFrame::OnUpdateLinkProject(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(m_wndSolutionPane.HasProject());
}

void CMainFrame::OnUpdateBuildAndLink(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(m_wndSolutionPane.HasProject());
}

void CMainFrame::OnUpdateBuildAndRun(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(m_wndSolutionPane.HasProject());
}

void CMainFrame::OnUpdateBuildAll(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(m_wndSolutionPane.HasProject());
}


void CMainFrame::OnOMLHelp()
{
	CString strOMLHelpFileName = GetAppDirectory();
	strOMLHelpFileName += _T("\\help\\oml.chm");
	ShellExecute(NULL,NULL,strOMLHelpFileName,NULL,NULL,SW_SHOW);
};

void CMainFrame::OnOASMHelp()
{
    CString strOasmHelpFileName = GetAppDirectory();
    strOasmHelpFileName += _T("\\help\\oasm.chm");
    ShellExecute(NULL,NULL,strOasmHelpFileName,NULL,NULL,SW_SHOW);
}

void CMainFrame::OpenDocument(LPCTSTR lpFileName,int nGotoLine,int nGotoRow)
{	
    CDocument *pDocument = 0;        
	pDocument = theApp.GetDocument(lpFileName);
    if(pDocument == NULL)
    {
        pDocument = theApp.OpenDocumentFile(lpFileName);
		if(nGotoLine < 0){nGotoLine = 0;}
		if(nGotoRow < 0){nGotoRow = 0;}		
    }

    POSITION p2 = pDocument->GetFirstViewPosition(); //得到文档对应的第1个视图
    while (p2 != NULL) //遍历文档对应的视图
    {
        CView *pView = pDocument->GetNextView(p2);
        if (pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
        {
            CMDIChildWndEx *pChild = (CMDIChildWndEx*)pView->GetParentFrame();//获得该view的父窗口
            pChild->MDIActivate();//激活该父窗口

			if(nGotoLine >= 0 && nGotoRow >= 0)
			{
				((COLIDEView*)pView)->GotoPos(nGotoLine,nGotoRow);
			}
            pView->SetFocus();

            return ;
        }
    }   
}

//设置文件关联
void CMainFrame::SetAssociate(TCHAR* szKeyExt,int nIconID,BOOL bSetAlways )
{
    CGCFileTypeAccess TheFTA;
    TheFTA.SetExtension(szKeyExt);

	if(!bSetAlways && TheFTA.IsAssociate())
	{
		return;
	}   

    TCHAR szProgPath[MAX_PATH * 2];
    ::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));

    CString csTempText;

    // just pass file path in quotes on command line	    
	csTempText =  szProgPath;
	csTempText += _T(" \"%1\"");
    TheFTA.SetShellOpenCommand(csTempText);
    TheFTA.SetDocumentShellOpenCommand(csTempText);

    csTempText = szKeyExt;
    csTempText += _T("file.Document");
    TheFTA.SetDocumentClassName(csTempText);

    // use first icon in program
    csTempText.Format(_T("%s,-%d"),szProgPath,nIconID);
    TheFTA.SetDocumentDefaultIcon(csTempText);

    TheFTA.RegSetAllInfo();
}

//删除文件关联
void CMainFrame::DelAssociate()
{

}

void CMainFrame::OnCheckNewVersion()
{
    // TODO: 在此添加命令处理程序代码

    theApp.CheckNewVersion();
}

void CMainFrame::OnNewSolution()
{
    // TODO: 在此添加命令处理程序代码

    m_wndSolutionPane.SendMessage(WM_COMMAND,ID_NEW_SOLUTION);
}

void CMainFrame::OnOpenSolution()
{
    if (m_wndSolutionPane.HasSolution())
        return;

    TCHAR szFilters[]= _T("O语言方案 (*.osl)|*.osl|");

    CFileDialog fileDlg (TRUE, _T("my"), _T("*.osl"),
                         OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, NULL);

    if ( fileDlg.DoModal ()!=IDOK )
        return ;

    if(OpenSolution(fileDlg.GetPathName()))
	{
		ShowPaneWnd(ID_VIEW_FILEVIEW);		
	}
}

void CMainFrame::OnUpdateOpenSolution(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(!m_wndSolutionPane.HasSolution());
}

void CMainFrame::OnUpdateNewSolution(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码

    pCmdUI->Enable(!m_wndSolutionPane.HasSolution());
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    int DropCount=DragQueryFile(hDropInfo,-1,NULL,0);
    //取得被拖动文件的数目
    for (int i=0;i< DropCount;i++)
    {
        int NameSize=DragQueryFile(hDropInfo,i,NULL,0);
        //取得第i个拖动文件名所占字节数
        HANDLE hHeap=GetProcessHeap();
		++NameSize;
        TCHAR *pName= new TCHAR[NameSize];//根据字节数分配缓冲区		
        if (pName==NULL)
        {
            MessageBox(_T("给文件名分配暂存空间时出错!"),_T("错误信息"),MB_ICONERROR);
            return;
        }		
		memset(pName,0,sizeof(TCHAR)*NameSize);
        DragQueryFile(hDropInfo,i,pName,NameSize);
		
		CString strFileName = pName;
		//释放缓冲区
		delete[] pName;

		CString strExternName = strFileName.Right(4);
		strExternName.MakeLower();
		//如果是方案文件
		if(strExternName == _T(".osl"))
		{	
			OpenSolution(strFileName);

			DragFinish(hDropInfo);
			return;
		}

		//如果是工程文件
		if(strExternName == _T(".opr"))
		{
			AfxMessageBox(_T("不能直接打开工程,请打开工程所在的方案文件"));
			DragFinish(hDropInfo);
			return;
		}
    }

    CMDIFrameWndEx::OnDropFiles(hDropInfo);
}

#include "./Doasm.h"

void CMainFrame::OnDasmPeFile()
{
	// TODO: 在此添加命令处理程序代码

	ClearOutPut();

	CString strDOASMPath = m_systemOption.m_strDoasmPath;
	CString strDoasmLanguagePath = m_systemOption.m_strDoasmLanguagePath;

	//如果是相对路径
	if (strDOASMPath[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strDOASMPath,GetAppDirectory());
	}
	if (strDoasmLanguagePath[0] == _T('.'))
	{
		GetAbsolutePathByRelativePath(strDoasmLanguagePath,GetAppDirectory());
	}

	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(ofn));
	TCHAR tchPeFile[MAX_PATH];
	tchPeFile[0] = 0;

	ofn.lStructSize      =sizeof(ofn);
	ofn.hwndOwner        =::GetActiveWindow();
	ofn.hInstance        =GetModuleHandle(NULL);
	ofn.nMaxFile         =MAX_PATH;
	ofn.lpstrInitialDir  =_T(".");
	ofn.lpstrFile        =tchPeFile;
	ofn.lpstrTitle       =_T("O语言反汇编");
	ofn.Flags            =OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter      = _T("执行文件(*.exe)\0*.exe\0动态库文件(*.dll)\0*.dll\0所有文件(*.*)\0*.*\0");

	if(!GetOpenFileName(&ofn))
		return;
	
	CString strPeFileName(tchPeFile);
	CString strOutDoasmFile;
	strOutDoasmFile = strPeFileName.Left(strPeFileName.ReverseFind(_T('.')));
	strOutDoasmFile += _T(".doa");

	theApp.CloseDocument(strOutDoasmFile);

	if(CDoasm::DoDoasm(strDOASMPath,strPeFileName,strDoasmLanguagePath,strOutDoasmFile))
	{		
		//反汇编成功则打开反汇编文件
		OpenDocument(strOutDoasmFile);
	}

	CommandFinish();
}

//获取工程内所有打开文档代码视图内的断点行，并保存在m_breakPointList列表中
void CMainFrame::GetAllBreakPoint()
{
	CBreakPointList* pSysBreakPointList = COTracer::GetSysBreakPointList();
	pSysBreakPointList->ClearList();
	CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
	if (pProjectPropertyCur)
	{
		CString strProjectPath = pProjectPropertyCur->m_strProjectFilePath;		
		strProjectPath = strProjectPath.Left(strProjectPath.ReverseFind('\\'));		
		POSITION pos1 = theApp.GetFirstDocTemplatePosition();
		while (pos1)
		{
			CDocTemplate* ptempl = (CDocTemplate*)theApp.GetNextDocTemplate(pos1);
			POSITION pos2 = ptempl->GetFirstDocPosition();
			CString strPathNameTemp;
			CDocument* pDocTemp;
			while (pos2) 
			{		
				pDocTemp = ptempl->GetNextDoc(pos2);
				strPathNameTemp = pDocTemp->GetPathName();
				
				if(strPathNameTemp.Find(strProjectPath) == 0)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						POSITION pos3 = pDocTemp->GetFirstViewPosition();
						while(pos3)
						{
							 CView* pView = pDocTemp->GetNextView(pos3);
							 if(pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
							 {
								 int nLineCount = ((COLIDEView*)pView)->GetLineCount();
								 for(int i=0;i<nLineCount;++i)
								 {
									 if(((COLIDEView*)pView)->LineHasBreakPoint(i))
									 {
										 DEBUGGER_BREAKPOINT bp;
										 bp.m_nLine = i;
										 wcscpy(bp.m_tchFileName,(LPTSTR)(LPCTSTR)strPathNameTemp);
										 bp.m_bIsSingleLineBP = false;
										 pSysBreakPointList->Add(bp);
									 }
								 }
							 }
						}
					}					
				}
			}
		}
	}
}

BOOL CMainFrame::GetCurProjectPropertyExeFileName(CString& strExeFileName)
{
	CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
	if (pProjectPropertyCur)
	{
		strExeFileName = pProjectPropertyCur->GetProjectAbsolutePathOutPutFileName(m_systemOption.m_bIsDebug);
		return TRUE;
	}

	return FALSE;
}

#include "DebugThread.h"
void CMainFrame::OnBeginDebugger()
{
	// TODO: 在此添加命令处理程序代码

	if(m_hDebugThread == NULL)
	{
		//设置调试版还是纯净版
		SetBuildDebugOrRelease();

		if(GetCurProjectProperty() == 0)
			return;

		//获取当前工程内的所有断点
		GetAllBreakPoint();

		//创建调试线程
		m_hDebugThread = ::CreateThread(
			NULL,              // default security attributes
			0,                 // use default stack size  
			DebugThread,          // thread function 
			(LPVOID)this,             // argument to thread function 
			0,                 // use default creation flags 
			&m_dwDebugThreadID);   // returns the thread identifier 
	}
	else
	{
		SendThreadMessage(m_dwDebugThreadID,WM_DEBUGGER_CONTINUE_FLOOD,NULL,NULL);
	}
}

void CMainFrame::OnStopDebugger()
{
	// TODO: 在此添加命令处理程序代码

	if(m_dwDebugThreadID)
	{
		////强制终止调试线程
		//::TerminateThread(m_hDebugThread,0);

		SendThreadMessage(m_dwDebugThreadID,WM_DEBUGGER_TERMINATE,NULL,NULL);
	}
}

LRESULT CMainFrame::OnDebuggerEnd(WPARAM wParam,LPARAM lParam)
{
	CloseHandle(m_hDebugThread);
	m_hDebugThread = 0;
	m_dwDebugThreadID = 0;

	::SendMessage(m_wndCPUWatchPane.GetWatchWnd()->GetSafeHwnd(),WM_DEBUGGER_CLEAR_DEBUG_DATA,NULL,NULL);
	::SendMessage(m_wndMemWatchPane.GetWatchWnd()->GetSafeHwnd(),WM_DEBUGGER_CLEAR_DEBUG_DATA,NULL,NULL);

	return 1;
}

LRESULT CMainFrame::OnDebuggerDeleteBreakPoint(WPARAM wParam,LPARAM lParam)
{
	DEBUGGER_BREAKPOINT* pDbp = (DEBUGGER_BREAKPOINT*)wParam;

	CDocument* pDoc = theApp.GetDocument(pDbp->m_tchFileName);
	if(pDoc)
	{
		POSITION pos = pDoc->GetFirstViewPosition();
		while(pos)
		{
			CView* pView = pDoc->GetNextView(pos);
			if(pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
			{					
				((COLIDEView*)pView)->DeleteBreakPoint(pDbp->m_nLine);
				break;
			}
		}
	}

	return 1;
}

LRESULT CMainFrame::OnDebuggerSetBreakPoint(WPARAM wParam,LPARAM lParam)
{
	DEBUGGER_BREAKPOINT* pDbp = (DEBUGGER_BREAKPOINT*)wParam;

	CDocument* pDoc = theApp.GetDocument(pDbp->m_tchFileName);
	if(pDoc)
	{
		POSITION pos = pDoc->GetFirstViewPosition();
		while(pos)
		{
			CView* pView = pDoc->GetNextView(pos);
			if(pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
			{					
				((COLIDEView*)pView)->SetBreakPoint(pDbp->m_nLine);
				break;
			}
		}
	}

	return 1;
}

void CMainFrame::OnDestroy()
{
	//如果还在调试程序状态则终止调试
	OnStopDebugger();

	CMDIFrameWndEx::OnDestroy();
}

void CMainFrame::OnClearAllBreakPoint()
{
	int nResult = ::MessageBox(GetSafeHwnd(),_T("确实要删除所有的断点吗?"),_T("警告"),MB_YESNO|MB_ICONQUESTION);
	if(nResult != IDYES)
		return;

	//正在处于调试状态
	if(IsDebuging())
	{		
		SendThreadMessage(m_dwDebugThreadID,WM_DEBUGGER_REMOVEALLBREAKPOINT,NULL,NULL);
	}

	CProjectProperty* pProjectPropertyCur = GetCurProjectProperty();
	if (pProjectPropertyCur)
	{
		CString strProjectPath = pProjectPropertyCur->m_strProjectFilePath;
		strProjectPath = strProjectPath.Left(strProjectPath.ReverseFind('\\'));
		POSITION pos1 = theApp.GetFirstDocTemplatePosition();
		while (pos1)
		{
			CDocTemplate* ptempl = (CDocTemplate*)theApp.GetNextDocTemplate(pos1);
			POSITION pos2 = ptempl->GetFirstDocPosition();
			CString strPathNameTemp;
			CDocument* pDocTemp;
			while (pos2) 
			{		
				pDocTemp = ptempl->GetNextDoc(pos2);
				strPathNameTemp = pDocTemp->GetPathName();

				if(strPathNameTemp.Find(strProjectPath) == 0)
				{
					if(pDocTemp->IsKindOf(RUNTIME_CLASS(COLIDEDoc)))
					{
						POSITION pos3 = pDocTemp->GetFirstViewPosition();
						while(pos3)
						{
							CView* pView = pDocTemp->GetNextView(pos3);
							if(pView->IsKindOf(RUNTIME_CLASS(COLIDEView)))
							{
								((COLIDEView*)pView)->DeleteAllBreakPoint();
							}
						}
					}					
				}
			}
		}
	}
}

void CMainFrame::OnDebugSingleLine()
{
	// TODO: 在此添加命令处理程序代码

	if(IsDebuging())
	{
		SendThreadMessage(m_dwDebugThreadID,WM_DEBUGGER_CONTINUE_SINGLE_LINE,NULL,NULL);		
	}
}

void CMainFrame::OnDebugSingleSentence()
{
	// TODO: 在此添加命令处理程序代码
}

BOOL CMainFrame::IsDebuging()
{
	if(m_hDebugThread)
	{
		DWORD dwThreadCode;
		GetExitCodeThread(m_hDebugThread,&dwThreadCode);
		if(dwThreadCode == STILL_ACTIVE)
			return true;
	}
	
	return false;
}

LRESULT CMainFrame::OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam)
{
	ShowPaneWnd(ID_VIEW_CPUWATCHWND);
	ShowPaneWnd(ID_VIEW_MEMWATCHWND);

	::SendMessage(m_wndCPUWatchPane.GetWatchWnd()->GetSafeHwnd(),WM_DEBUGGER_SHOW_CPU_DATA,wParam,lParam);
	::SendMessage(m_wndMemWatchPane.GetWatchWnd()->GetSafeHwnd(),WM_DEBUGGER_SHOW_CPU_DATA,wParam,lParam);

	return 1;
}

void CMainFrame::ShowPaneWnd(int nPaneWnd)
{
	HWND hActiveWnd = ::GetActiveWindow();
	HWND hFocusWnd = ::GetFocus();
	ShowPane(GetPane(nPaneWnd),TRUE,FALSE,TRUE);
	::SetActiveWindow(hActiveWnd);
	::SetFocus(hFocusWnd);
}

void CMainFrame::SetBuildDebugOrRelease()
{
	m_systemOption.m_bIsDebug = true; //默认为调试版

	CObList listButtons;
	if (CMFCToolBar::GetCommandButtons(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, listButtons) > 0)
	{
		for(POSITION posCombo = listButtons.GetHeadPosition();posCombo != NULL;)
		{
			CMFCToolBarComboBoxButton* pCombo = DYNAMIC_DOWNCAST(CMFCToolBarComboBoxButton, listButtons.GetNext(posCombo));

			if(pCombo != NULL && pCombo->GetHwnd())
			{				
				CString strText;
				strText = pCombo->GetText();
				
				if(strText == _T("编译成纯净版"))
				{
					m_systemOption.m_bIsDebug = false;
				}				
				/*else if(strText == _T("编译成调试版"))
				{
					m_systemOption.m_bIsDebug = true;
				}
				*/

				break;
			}
		}
	}	
}

void CMainFrame::OnDummySelectActiveConfiguration()
{
	
}

void CMainFrame::OnSelectGotoLine()
{
	CFrameWnd* pFrameWnd = GetActiveFrame();
	if(pFrameWnd == 0)
		return;

	CView* pView = pFrameWnd->GetActiveView();
	if((pView == NULL) || (!pView->IsKindOf(RUNTIME_CLASS(COLIDEView))))
		return;

	COLIDEView* pCurOLIDEView = (COLIDEView*)pView;
	
	CObList listButtons;
	if (CMFCToolBar::GetCommandButtons(ID_GOTO_LINE, listButtons) > 0)
	{		
		for(POSITION posCombo = listButtons.GetHeadPosition();posCombo != NULL;)
		{
			CMFCToolBarComboBoxButton* pCombo = DYNAMIC_DOWNCAST(CMFCToolBarComboBoxButton, listButtons.GetNext(posCombo));

			if(pCombo != NULL && pCombo->GetHwnd())
			{				
				CString strText;
				strText = pCombo->GetText();

				if(strText == _T("跳到首行"))
				{
					pCurOLIDEView->GotoPos(0);
				}				
				else if(strText == _T("跳到末行"))
				{
					int nLineCount = pCurOLIDEView->GetLineCount();
					pCurOLIDEView->GotoPos(nLineCount-1);
				}
				else
				{
					long lValue = 0;
#ifdef _UNICODE
					lValue = wcstol(strText,0,10);
#else
					lValue = strtol(strText,0,10);
#endif

					if(lValue == 0)
					{
						pCurOLIDEView->GotoPos(0);
					}
					else if(lValue > 0)
					{
						pCurOLIDEView->GotoPos(lValue - 1);
					}
				}

				pCurOLIDEView->SetFocus();

				break;
			}
		}
	}	
}

void CMainFrame::OnOpenOlanguageWeb()
{
	// TODO: 在此添加命令处理程序代码

	ShellExecute(NULL,_T("open"),_T("www.olanguage.org"),NULL,NULL,SW_SHOWNORMAL);
}