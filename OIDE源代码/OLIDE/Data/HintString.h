
#ifndef _HINT_STRING_H_
#define _HINT_STRING_H_

struct HINT_STRING
{
	CString m_strInput;	
	CString m_strHint;
	char*  m_pInput;
};

enum HINT_STRING_TYPE
{
	HST_NULL,	
	HST_OASM_AUTO_COMPLETE,
	HST_OASM_TIP,	
	HST_OML_AUTO_COMPLETE,
	HST_OML_TIP,
	HST_END,
};

class CHintString
{
public:
	CHintString();
	~CHintString();

private:
	
	//OASM自动完成提示数组
	int m_nOASMAutoCompleteItemCount;
	HINT_STRING* m_phsOASMAutoComplete;
	CString m_strOASMAutoCompleteFileName;

	//OASM信息提示数组
	int m_nOASMTipDataCount;
	HINT_STRING* m_phsOASMTipData;
	CString m_strOASMTipFileName;

	//////////////////////////////////////////////////////////////////////////

	//OML自动完成提示数组
	int m_nOMLAutoCompleteItemCount;
	HINT_STRING* m_phsOMLAutoComplete;
	CString m_strOMLAutoCompleteFileName;

	//OML信息提示数组
	int m_nOMLTipDataCount;
	HINT_STRING* m_phsOMLTipData;
	CString m_strOMLTipFileName;

public:

	void LoadHintData();
	int GetItemCount(int nHintStringType);
	char* GetItemInput(int nHintStringType,int nItem);
	CString& GetItemHint(int nHintStringType,int nItem);

private:

	BOOL LoadConfigFile(const CString& strAutoFileName,CStringArray& strarrayData);
	BOOL LoadData(const CString& strAutoFileName,HINT_STRING*& phsData,int& nCount);
	void Convert2UTF8(HINT_STRING* phsData,int nItemCount);
	void ClearData(HINT_STRING*& phsData,int& nItemCount);

};

#endif //_HINT_STRING_H_