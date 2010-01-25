#pragma once

class CAutoCompleteString
{
public:

	CAutoCompleteString();
	~CAutoCompleteString();

private:

	//OASM系统自动完成使用的文件
	CString m_strOASMSystemFilePath;
	CPtrList m_listSystemAutoCompleteGroup;
	CString m_strOASMTempletDir;  //模板文件
	CStringArray m_strarrayOASMTemplateFile;

	//OML系统自动完成使用的文件
	CString m_strOMLSystemFilePath;
	CStringArray m_strarrayOMLSystemAutoComplete;	
	CString m_strOMLTempletDir;  //模板文件
	CStringArray m_strarrayOMLTemplateFile;

public:

	BOOL RefreshOASMSystemAutoCompleteGroup(LPCTSTR lpSystemTemplateFilePath = NULL);
	int GetItemCount(POSITION psAutoCompleteShift);	
	void  GetItemData(POSITION psAutoCompleteShift,int nIndex,CString& strText,CString& strComment,char& chKey);
	POSITION GetHeadGroupPosition(){ return m_listSystemAutoCompleteGroup.GetHeadPosition();};
	POSITION GetTailGroupPosition(){ return m_listSystemAutoCompleteGroup.GetTailPosition();};
	void GetNextGroupPosition(POSITION& ps){ m_listSystemAutoCompleteGroup.GetNext(ps);};
	void GetPrevGroupPosition(POSITION& ps){ m_listSystemAutoCompleteGroup.GetPrev(ps);};	
	void RefreshOASMTemplateFileList(LPCTSTR lpDirect = NULL);
	CStringArray& GetOASMTemplateFileArray(){ return m_strarrayOASMTemplateFile;}
	int GetOASMTemplateFileText(CString& strText,int nIndex);

	CStringArray& GetOMLSystemAutoCompleteArray(){ return m_strarrayOMLSystemAutoComplete; }
	BOOL RefreshOMLSystemAutoComplete(LPCTSTR lpSystemTemplateFilePath);
	void RefreshOMLTemplateFileList(LPCTSTR lpDirect = NULL);
	CStringArray& GetOMLTemplateFileArray(){ return m_strarrayOMLTemplateFile;}
	int GetOMLTemplateFileText(CString& strText,int nIndex);

	void  GetItemData(const CString& strItem,CString& strText,CString& strComment,char& chKey);

private:

	void GetTemplateFileList(LPCTSTR lpDirect,CStringArray& strarrayTemplateFile,int nRelativePathLength);
	BOOL ReadTemplateFile(const CString& strFileName,CString& strText);
};


