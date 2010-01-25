
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "CPUWatchPane.h"
#include "MemWatchPane.h"

#include "./Data/SystemOption.h"
#include "./Data/SyntaxWordList.h"
#include "./Data/AutoCompleteString.h"
#include "./Data/HintString.h"

#include "cgfiltyp.h"

#include "./Data/SolutionProperty.h"
#include "./OTracer.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:

	CSystemOption m_systemOption;
	CString m_strSystemOptionFileName;
	CString m_strAppPath;

	CSyntaxWordList m_syntaxWordList;
	CAutoCompleteString m_autoCompleteString;
	CHintString m_hintString;
	
	HANDLE   m_hDebugThread;
	DWORD    m_dwDebugThreadID;

	//下面这组变量只用在COLIDEView编辑窗口
	CRect m_rcAutoCompleteList;
	int m_nAutoCompleteList_Column0_Width;
	int m_nAutoCompleteList_Column1_Width;

// 操作
public:

	CString GetAppDirectory(){ return m_strAppPath.Left(m_strAppPath.ReverseFind(_T('\\')));}

	void OutPutMsg(TCHAR* format, ...);
	void ClearOutPut();

	void LoadConfigData();

	void ShowPaneWnd(int nPaneWnd);

	void OpenDocument(LPCTSTR lpFileName,int nGotoLine = -1,int nGotoRow = -1);

	void AssociateOFile(BOOL bSetAlways);	
	void DelAssociate();
	
	//打开方案
	bool OpenSolution(const CString& strSolutionFileName)
	{
		return m_wndSolutionPane.OpenSolution(strSolutionFileName);
	}

	CProjectProperty* GetCurProjectProperty()
	{
		return m_wndSolutionPane.GetCurProjectProperty();
	}

	BOOL GetCurProjectPropertyExeFileName(CString& strExeFileName);
	BOOL IsDebuging();
	void GetAllBreakPoint();   //得到当前所有的断点	
	
private:

	enum BUILD_CODE_TYPE
	{
		BCT_NULL,
		BCT_OML,   //中间语言文件
		BCT_OASM,  //汇编文件
	};

	int  BuildCode(CProjectProperty* pProjectProperty,const CString& strPathName,int nCodeFileType,BOOL bReBuild);
	int  BuildResource(CProjectProperty* pProjectProperty,const CString& strResourceName,BOOL bReBuild);
	
	BOOL m_bSaveProject;
	int  BuildProject(CProjectProperty* pProjectProperty,BOOL bReBuild = FALSE);
	BOOL BrowseBuildCodeFile(const CString& strDir,CProjectProperty* pProjectProperty,int& nCodeFileCount,BOOL bReBuild);		
	BOOL BrowseBuildResourceFile(const CString& strDir,CProjectProperty* pProjectProperty,int& nCodeFileCount,BOOL bReBuild);
	void LinkProject(CProjectProperty* pProjectProperty,BOOL bReLink = FALSE,BOOL bRunExeFile = FALSE);

	void CommandFinish();

	void SetBuildDebugOrRelease();

	BOOL CodeFileNeedBuild(CProjectProperty* pProjectProperty,const CString& strComplier,const CString& strFileName,const CString& strObjFileName,CStringArray& strarrayAssociateFile);
	void SetBuildRecord(CProjectProperty* pProjectProperty,const CString& strFileName,const CString& strObjFileName,CStringArray& strarrayAssociateFile);
	BOOL GetAssociateFile(const CString& strFileName,const CString& strComplier,CStringArray& strarrayAssociateFile);
	BOOL FileIsModified(COLProjectBuildRecord* pOLProjectBuildRecord,const CString& strFileName);

	void SetAssociate(TCHAR* szKeyExt,int nIconID,BOOL bSetAlways);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	virtual BOOL OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bTabDrop);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBar       m_wndToolBarBuild;
	CMFCToolBar       m_wndToolBarSyntaxWord;
	CMFCToolBar       m_wndToolBarOperator;
	CMFCToolBar       m_wndToolEditView;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndSolutionPane;
	//CClassView        m_wndClassView;
	COutputWnd        m_wndOutputPane;
	//CPropertiesWnd    m_wndProperties;	
	CCPUWatchPane     m_wndCPUWatchPane;
	CMemWatchPane     m_wndMemWatchPane;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);	
	afx_msg void OnUpdateDocPath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnAssociateOFile();
	afx_msg void OnResEditor();
	afx_msg void OnSystemOptions();	
	afx_msg void OnOASMHelp();
	afx_msg void OnOMLHelp();
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnCloseCurChildFrame();
	afx_msg void OnUpdateCloseCurChildFrame(CCmdUI *pCmdUI);
	afx_msg void OnSaveAllDocument();
	afx_msg void OnCloseAllChildFrame();
	afx_msg void OnUpdateCloseAllChildFrame(CCmdUI *pCmdUI);
	
	afx_msg void OnOpenOwnerFloder();
	afx_msg void OnUpdateOpenOwnerFloder(CCmdUI *pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBuildAll();
	afx_msg void OnBuildProject();
	afx_msg void OnLinkProject();
	afx_msg void OnBuildAndLink();	
	afx_msg void OnReBuildAndLink();
	afx_msg void OnBuildAndRun();
	afx_msg void OnUpdateLinkProject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildAndLink(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildAndRun(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildProject(CCmdUI *pCmdUI);	
	afx_msg void OnCheckNewVersion();
	afx_msg void OnNewSolution();
	afx_msg void OnOpenSolution();
	afx_msg void OnUpdateOpenSolution(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewSolution(CCmdUI *pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDasmPeFile();
	afx_msg void OnBeginDebugger();
	afx_msg void OnStopDebugger();
	afx_msg LRESULT OnOpenDocument(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnClearAllBreakPoint();	
	afx_msg LRESULT OnDebuggerEnd(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDebugSingleLine();
	afx_msg void OnDebugSingleSentence();
	afx_msg LRESULT OnDebuggerDeleteBreakPoint(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDebuggerSetBreakPoint(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam);	
	afx_msg void OnDummySelectActiveConfiguration();
	afx_msg void OnSelectGotoLine();
	afx_msg void OnOpenOlanguageWeb();
};


