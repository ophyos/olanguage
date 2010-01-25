
#pragma once

#include "ViewTree.h"
#include "SolutionTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 构造
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	void AddNewItem(TCHAR* pchPath,TCHAR* pchName,int nNewItemType,BOOL bBrowsePath = TRUE);
	void AddNewSolution(CString& strSolutionFilePath,CString& strSolutionName);
	bool OpenSolution(const CString& strSolutionFileName);
	void CloseSolution();
	HTREEITEM InsertSolutionNode(const TCHAR* pchSolutionFileName,const TCHAR* pchSolutionName);
	void SaveSolutionTreeNode();
	void AddNewProject(CString& strProjectFilePath,CString& strProjectName,int nProjectType);
	void OpenProjectTreeNode(const TCHAR* pchFileName,BOOL bIsExpand);
	HTREEITEM InsertProjectNode(const TCHAR* pchProjectFilePath,const TCHAR* pchProjectName);	
	void SaveProjectProperty(CProjectProperty* pProjectProperty,const CString& strProjectFileName);
	void SaveProjectTreeNode(HTREEITEM hProjectTreeItem);
	void SetProjectProperty(CProjectProperty* pProjectProperty,const CString& strProjectFileName);
	void AddNewInProjectFile(CString& strFilePath,CString& strFileName,char* lpText = NULL);

	void LoadProjectFile(HTREEITEM hProjectItem,const CString& strProjectPath);
	void BrowseFile(const CString& strDir,HTREEITEM hTreeParent,BOOL bIsProjectDir);

	BOOL HasSolution(){	return (m_wndSolutionTree.GetSolutionNode() != NULL); }
	BOOL HasProject()
	{	
		COLFileNode* pOLFileNode = m_wndSolutionTree.GetSolutionNode();
		if(pOLFileNode)
		{
			return m_wndSolutionTree.ItemHasChildren(pOLFileNode->m_hItemTree); 
		}
		
		return FALSE;
	}

	HTREEITEM GetFirstProject()
	{
		return  m_wndSolutionTree.GetFirstProject();
	}	

	HTREEITEM GetNextItem(HTREEITEM hItem)
	{
		return m_wndSolutionTree.GetNextItem(hItem,TVGN_NEXT);
	}

	CProjectProperty* GetCurProjectProperty()
	{		
		return m_wndSolutionTree.GetCurProjectProperty();
	}

	CProjectProperty* GetProjectProperty(HTREEITEM hItemProject)
	{		
		return m_wndSolutionTree.GetProjectProperty(hItemProject);
	}

// 属性
protected:

	CSolutionTree m_wndSolutionTree;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

// 实现
public:
	virtual ~CFileView();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();	
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();	
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewSolution();
	afx_msg void OnNewProject();	
	afx_msg void OnCloseSolution();
	afx_msg void OnAddProject();
	afx_msg void OnRemoveProject();
	afx_msg void OnClose();
	afx_msg void OnDeleteFile();
	afx_msg void OnAddFloder();
	afx_msg void OnOpenCurFloder();
	afx_msg void OnReName();
	afx_msg void OnNewInProjectFile();
	afx_msg void OnRefresh();
	afx_msg void OnDestroy();
	afx_msg void OnOpenInProjectFile();
	afx_msg void OnBuildCurProject();
	afx_msg void OnReBuildCurProject();
};

