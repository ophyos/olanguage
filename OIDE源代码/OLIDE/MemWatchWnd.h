#pragma once

#include "./Controls/TreePropSheet/ResizableDialog.h"

#include "./Controls/HexEdit/HexEdit.h"
#include "MemWatchHexEdit.h"

#include "afxwin.h"

// CMemWatchWnd 对话框

class CMemWatchWnd : public CResizableDialog
{
	DECLARE_DYNAMIC(CMemWatchWnd)

public:
	CMemWatchWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemWatchWnd();

// 对话框数据
	enum { IDD = IDD_MEM_WATCH_WND };

	enum SEBMENT_TYPE
	{
		ST_NULL,
		ST_CODE,
		ST_STACK,
		ST_DATA,
		ST_ALL,
	};

public:
	CHexEdit    m_editMemAddr;
	CHexEdit    m_editMemLength;
	CHexEdit    m_editReadCodeLength;
	CMemWatchHexEdit  m_editHexViewCodeSegment;	
	CMemWatchHexEdit m_editHexViewStackSegment;
	CMemWatchHexEdit m_editHexViewDataSegment;

	BOOL  m_bShowDSViewOnly;
	CRect m_rcHexViewDataSegment;

	CString m_strDataAddr;
	CString m_strDataString;
	CString m_strDataUchar;
	CString m_strDataChar;
	CString m_strDataUShort;
	CString m_strDataShort;
	CString m_strDataUInt;
	CString m_strDataInt;	
	CString m_strCodeDoasm;

	LPBYTE m_pCodeSegmentBuffer;
	UINT   m_nCodeSegmentBufferLength;
	LPBYTE m_pStackSegmentBuffer;
	UINT   m_nStackSegmentBufferLength;
	LPBYTE m_pDataSegmentBuffer;
	UINT   m_nDataSegmentBufferLength;

	void ShowDataSegmentViewOnly(BOOL bShowDSViewOnly);
	BOOL GetDebugMemData(unsigned int uiMemAddr,unsigned int uiLength,LPBYTE pDataBuffer,unsigned int& uiRead);	
	BOOL SaveDebugMemData(unsigned int uiMemAddr,LPBYTE pDataBuffer,unsigned int uiLength,BOOL bIsCodeSegment);
	void ClearSegmentBuffer(int nSegmentType);
	BOOL MallocSegmentBuffer(int nSegmentType,UINT nLength);
	void CodeSegmentDoasm();
	void ShowEditHexViewData(CMemWatchHexEdit& memWatchHexEdit,POINT* pPoint);

private:

	CFont m_listFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetData();
	afx_msg LRESULT OnDebuggerClearDebugData(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMoveCaretPos(WPARAM wParam,LPARAM lParam);	
	afx_msg void OnEnChangeEditHexViewCodeSegment();
	afx_msg void OnEnChangeEditHexViewDataSegment();
	afx_msg void OnEnChangeEditHexViewStackSegment();
	afx_msg void OnBnClickedBtnSaveCodeSegment();
	afx_msg void OnBnClickedBtnSaveDataSegment();
	afx_msg void OnBnClickedBtnSaveStackSegment();	
	afx_msg void OnBnClickedCheckShowDsViewOnly();
	afx_msg void OnBnClickedBtnCodeDoasm();
	afx_msg LRESULT OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam);
	
};
