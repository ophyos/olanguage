
#ifndef _OL_FILE_NODE_H_
#define _OL_FILE_NODE_H_


#pragma once


// CSolutionTree

#include "./Controls/XTreeCtrl/XTreeCtrl.h"
#include "./Data/SolutionProperty.h"

//O语言文件结点
class COLFileNode
{
public:

	COLFileNode()
	{
		m_enumType = ONT_UNKNOW;
		m_hItemTree = NULL;
		m_strName.Empty();
		m_strPathName.Empty();

		m_pProperty = NULL;
	}
	~COLFileNode(){};

public:

	enum OLFILE_NODE_TYPE
	{
		ONT_UNKNOW,
		ONT_SOLUTION,
		ONT_PROJECT,			
		ONT_FLODER,
		ONT_FILE,		
	};

	OLFILE_NODE_TYPE m_enumType;
	HTREEITEM  m_hItemTree;
	CString    m_strName;
	CString    m_strPathName;	

	//结点属性
	void*      m_pProperty;

public:
	
	bool IsSolutionNode(){ return (m_enumType == ONT_SOLUTION);};
	bool IsProjectNode(){ return (m_enumType == ONT_PROJECT);};	
	bool IsFloderNode(){ return (m_enumType == ONT_FLODER);};
	bool IsFileNode(){ return (m_enumType == ONT_FILE);};	
};

class CSolutionTree : public CXTreeCtrl
{
public:
	CSolutionTree();
	virtual ~CSolutionTree();

	//属性
private:

	HTREEITEM m_hCurItem;

	CString m_strBeforeChangeItemText;

	enum
	{
		GET_OBJECT_NODE_TYPE_OBJECTNAME,
		GET_OBJECT_NODE_TYPE_OBJECTFILEPATH
	};

	//函数
public:

	HTREEITEM GetCurItem(){ return m_hCurItem; }
	
	COLFileNode* GetSolutionNode();
	HTREEITEM GetFirstProject();
	
	HTREEITEM GetProjectItemFromProjectFileName(const CString& strProjectFileName);
	HTREEITEM GetProjectItemFromChildItem(HTREEITEM hTreeItem);
		
	COLFileNode* GetItemNode(HTREEITEM hTreeItem);
	COLFileNode* GetCurItemNode()
	{
		return GetItemNode(m_hCurItem);
	}	
	
	void DeleteItem(HTREEITEM hTreeItem);
	void DelChild(HTREEITEM hItem); //递归删除子项

	HTREEITEM InsertSolution(const TCHAR* pchSolutionFileName,const TCHAR* pchSolutionName);
	HTREEITEM InsertProject(const TCHAR* pchProjectFilePath,const TCHAR* pchProjectName);
	HTREEITEM InsertFloder(HTREEITEM hTreeItem,const TCHAR* pchFloderName,BOOL bCreateDirectory,BOOL bSelected);
	HTREEITEM InsertFile(HTREEITEM hTreeItemParent,const CString& strFileName,const CString& strFilePath,BOOL bSelected = false);
	
	void SetProjectProperty(HTREEITEM hProjectTreeItem,CProjectProperty& projectProperty);
	CProjectProperty* GetProjectProperty(HTREEITEM hTreeItemProject);
	CProjectProperty* GetCurProjectProperty();

	void OpenProjectFile(HTREEITEM hItemFile);
	void DeleteFloadOrFile(HTREEITEM hItem);
	void SaveProjectTreeNode(HTREEITEM hProjectTreeItem);	
	void SaveAllProject();
	void CloseSolution();	

	void AddProjectFloder();	

protected:
	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);	
	
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);				
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	
};


#endif //_OL_FILE_NODE_H_