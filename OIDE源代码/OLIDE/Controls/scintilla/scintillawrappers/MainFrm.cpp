#include "stdafx.h"
#include "ScintillaDemo.h"
#include "ScintillaDocView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETTINGCHANGE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, OnUpdateStyle) 
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, OnUpdateFold) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_FOLD,
  ID_INDICATOR_STYLE,
  ID_INDICATOR_LINE,
  ID_INDICATOR_OVR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  //Let the base class do its thing
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  //Create the toolbar  
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE(_T("Failed to create toolbar\n"));
		return -1;      // fail to create
	}

	//Set the title of the toolbar.
	CString sTitle;
	VERIFY(sTitle.LoadString(IDS_TOOLBAR));
	m_wndToolBar.SetWindowText(sTitle);

  //Create the status bar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE(_T("Failed to create status bar\n"));
		return -1;      // fail to create
	}

	//Setup docing an tooltips for the toolbar
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  //Let the base class do its thing
	if (!CMDIFrameWnd::PreCreateWindow(cs))
		return FALSE;
		
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
  CWinApp* pApp = AfxGetApp();
  AFXASSUME(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_SETTINGCHANGE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
  CMDIFrameWnd::OnSettingChange(uFlags, lpszSection);
}

void CMainFrame::OnSysColorChange() 
{
  CWinApp* pApp = AfxGetApp();
  AFXASSUME(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_SYSCOLORCHANGE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
  CMDIFrameWnd::OnSysColorChange();
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
  CWinApp* pApp = AfxGetApp();
  AFXASSUME(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_PALETTECHANGED, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
  CMDIFrameWnd::OnPaletteChanged(pFocusWnd);
}

BOOL CMainFrame::OnQueryNewPalette() 
{
  CWinApp* pApp = AfxGetApp();
  AFXASSUME(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_QUERYNEWPALETTE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
	return CMDIFrameWnd::OnQueryNewPalette();
}

void CMainFrame::OnUpdateInsert(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(_T(""));
}

void CMainFrame::OnUpdateStyle(CCmdUI* pCmdUI)
{
   pCmdUI->SetText(_T(""));
} 

void CMainFrame::OnUpdateFold(CCmdUI* pCmdUI)
{
  pCmdUI->SetText(_T(""));
} 

void CMainFrame::OnUpdateLine(CCmdUI* pCmdUI)
{
  pCmdUI->SetText(_T(""));
} 

