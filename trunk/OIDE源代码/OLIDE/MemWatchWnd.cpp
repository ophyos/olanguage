// MemWatchWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "MemWatchWnd.h"
#include "UserWmMsg.h"
#include "MainFrm.h"
#include "DebugThread.h"

// CMemWatchWnd 对话框

IMPLEMENT_DYNAMIC(CMemWatchWnd, CResizableDialog)

CMemWatchWnd::CMemWatchWnd(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CMemWatchWnd::IDD, pParent)
	, m_strDataAddr(_T(""))
	, m_strDataString(_T(""))
	, m_strDataUchar(_T(""))
    , m_strDataChar(_T(""))
    , m_strDataUShort(_T(""))
    , m_strDataShort(_T(""))
    , m_strDataUInt(_T(""))
    , m_strDataInt(_T(""))
	, m_strCodeDoasm(_T(""))
    , m_bShowDSViewOnly(FALSE)
{
	m_pCodeSegmentBuffer = NULL;
	m_nCodeSegmentBufferLength = 0;
	m_pStackSegmentBuffer = NULL;
	m_nStackSegmentBufferLength = 0;
	m_pDataSegmentBuffer = NULL;
	m_nDataSegmentBufferLength = 0;
}

CMemWatchWnd::~CMemWatchWnd()
{
	ClearSegmentBuffer(ST_ALL);
}

void CMemWatchWnd::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEM_ADDR, m_editMemAddr);	
	DDX_Control(pDX, IDC_EDIT_MEM_LENGTH, m_editMemLength);	
	DDX_Control(pDX, IDC_EDIT_HEX_VIEW_CODE_SEGMENT, m_editHexViewCodeSegment);	
	DDX_Text(pDX, IDC_EDIT_DATA_ADDR, m_strDataAddr);
	DDX_Text(pDX, IDC_EDIT_DATA_STRING, m_strDataString);
	DDX_Text(pDX, IDC_EDIT_DATA_UCHAR, m_strDataUchar);
	DDX_Text(pDX, IDC_EDIT_DATA_CHAR, m_strDataChar);
	DDX_Text(pDX, IDC_EDIT_DATA_USHORT, m_strDataUShort);
	DDX_Text(pDX, IDC_EDIT_DATA_SHORT, m_strDataShort);
	DDX_Text(pDX, IDC_EDIT_DATA_UINT, m_strDataUInt);
	DDX_Text(pDX, IDC_EDIT_DATA_INT, m_strDataInt);
	DDX_Control(pDX, IDC_EDIT_HEX_VIEW_DATA_SEGMENT, m_editHexViewDataSegment);
	DDX_Control(pDX, IDC_EDIT_HEX_VIEW_STACK_SEGMENT, m_editHexViewStackSegment);
	DDX_Text(pDX, IDC_EDIT_CODE_DOASM, m_strCodeDoasm);
	DDX_Control(pDX, IDC_EDIT_READ_CODE_LENGTH, m_editReadCodeLength);
}


BEGIN_MESSAGE_MAP(CMemWatchWnd, CResizableDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA, &CMemWatchWnd::OnBnClickedButtonGetData)
	ON_MESSAGE(WM_DEBUGGER_CLEAR_DEBUG_DATA,   &CMemWatchWnd::OnDebuggerClearDebugData)
	ON_MESSAGE(WM_MOVECARETPOS,&CMemWatchWnd::OnMoveCaretPos)
	ON_EN_CHANGE(IDC_EDIT_HEX_VIEW_CODE_SEGMENT, &CMemWatchWnd::OnEnChangeEditHexViewCodeSegment)
	ON_EN_CHANGE(IDC_EDIT_HEX_VIEW_DATA_SEGMENT, &CMemWatchWnd::OnEnChangeEditHexViewDataSegment)
	ON_EN_CHANGE(IDC_EDIT_HEX_VIEW_STACK_SEGMENT, &CMemWatchWnd::OnEnChangeEditHexViewStackSegment)
	ON_BN_CLICKED(IDC_BTN_SAVE_CODE_SEGMENT, &CMemWatchWnd::OnBnClickedBtnSaveCodeSegment)
	ON_BN_CLICKED(IDC_BTN_SAVE_DATA_SEGMENT, &CMemWatchWnd::OnBnClickedBtnSaveDataSegment)
	ON_BN_CLICKED(IDC_BTN_SAVE_STACK_SEGMENT, &CMemWatchWnd::OnBnClickedBtnSaveStackSegment)
	ON_BN_CLICKED(IDC_CHECK_SHOW_DS_VIEW_ONLY, &CMemWatchWnd::OnBnClickedCheckShowDsViewOnly)
	ON_BN_CLICKED(IDC_BTN_CODE_DOASM, &CMemWatchWnd::OnBnClickedBtnCodeDoasm)
	ON_MESSAGE(WM_DEBUGGER_SHOW_CPU_DATA,    &CMemWatchWnd::OnDebuggerShowCPUData)	
END_MESSAGE_MAP()


// CMemWatchWnd 消息处理程序


BOOL CMemWatchWnd::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_editMemLength.SetWindowText(_T("0x100"));	
	m_editReadCodeLength.SetWindowText(_T("0x100"));
	m_editHexViewCodeSegment.SetShowAddress(true,false);
	m_editHexViewCodeSegment.SetShowAscii(false,false); //不显示字符列
	m_editHexViewCodeSegment.SetBytesPerRow(4,false,false);

	m_editHexViewStackSegment.SetShowAddress(true,false);
	m_editHexViewStackSegment.SetShowAscii(false,false);
	m_editHexViewStackSegment.SetBytesPerRow(4,false,false);

	m_editHexViewDataSegment.SetShowAddress(true,false);
	m_editHexViewDataSegment.SetShowAscii(true,false);
	//m_editHexViewDataSegment.SetBytesPerRow(16,false,false);

	AddAnchor(IDC_EDIT_HEX_VIEW_CODE_SEGMENT, TOP_LEFT, BOTTOM_LEFT);	
	AddAnchor(IDC_EDIT_CODE_DOASM, TOP_LEFT, BOTTOM_LEFT);	
	AddAnchor(IDC_EDIT_HEX_VIEW_STACK_SEGMENT, TOP_LEFT, BOTTOM_LEFT);
	AddAnchor(IDC_EDIT_HEX_VIEW_DATA_SEGMENT, TOP_LEFT, BOTTOM_RIGHT);
	
	m_editHexViewDataSegment.GetClientRect(&m_rcHexViewDataSegment);
	m_editHexViewDataSegment.ClientToScreen(m_rcHexViewDataSegment);	
	ScreenToClient(m_rcHexViewDataSegment);
	
	m_bShowDSViewOnly = FALSE;
	ShowDataSegmentViewOnly(m_bShowDSViewOnly);

	//设置反汇编代码编辑框字体
	LOGFONT   lf;  
	memset(&lf,0,sizeof(LOGFONT));           //   zero   out   structure  
	lf.lfHeight = 12;                         //   request   a   12-pixel-heightfont  
	lf.lfPitchAndFamily = FIXED_PITCH;  
	wcscpy(lf.lfFaceName,_T("宋体"));        //   request   a   face   name   "宋体"  
	m_listFont.CreateFontIndirect(&lf);      //   create   the   font  	
	GetDlgItem(IDC_EDIT_CODE_DOASM)->SetFont(&m_listFont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMemWatchWnd::ClearSegmentBuffer(int nSegmentType)
{
	switch(nSegmentType)
	{
	case ST_CODE:
		{
			if(m_pCodeSegmentBuffer != NULL)
			{
				free(m_pCodeSegmentBuffer);
				m_pCodeSegmentBuffer = NULL;
				m_nCodeSegmentBufferLength = 0;
			}
			break;
		}
	case ST_STACK:
		{
			if(m_pStackSegmentBuffer != NULL)
			{
				free(m_pStackSegmentBuffer);
				m_pStackSegmentBuffer = NULL;
				m_nStackSegmentBufferLength = 0;
			}

			break;
		}
	case ST_DATA:
		{
			if(m_pDataSegmentBuffer != NULL)
			{
				free(m_pDataSegmentBuffer);
				m_pDataSegmentBuffer = NULL;
				m_nDataSegmentBufferLength = 0;
			}

			break;
		}
	case ST_ALL:
		{
			if(m_pCodeSegmentBuffer != NULL)
			{
				free(m_pCodeSegmentBuffer);
				m_pCodeSegmentBuffer = NULL;
				m_nCodeSegmentBufferLength = 0;
			}

			if(m_pStackSegmentBuffer != NULL)
			{
				free(m_pStackSegmentBuffer);
				m_pStackSegmentBuffer = NULL;
				m_nStackSegmentBufferLength = 0;
			}

			if(m_pDataSegmentBuffer != NULL)
			{
				free(m_pDataSegmentBuffer);
				m_pDataSegmentBuffer = NULL;
				m_nDataSegmentBufferLength = 0;
			}

			break;
		}
	}
}

BOOL CMemWatchWnd::MallocSegmentBuffer(int nSegmentType,UINT nLength)
{
	ASSERT((nSegmentType > ST_NULL) && (nSegmentType < ST_ALL));

	ClearSegmentBuffer(nSegmentType);

	switch(nSegmentType)
	{
	case ST_CODE:
		{
			m_pCodeSegmentBuffer = (LPBYTE)malloc(nLength);
			if(m_pCodeSegmentBuffer)
			{
				m_nCodeSegmentBufferLength = nLength;
				return TRUE;
			}

			break;
		}
	case ST_STACK:
		{
			m_pStackSegmentBuffer = (LPBYTE)malloc(nLength);
			if(m_pStackSegmentBuffer)
			{
				m_nStackSegmentBufferLength = nLength;
				return TRUE;
			}

			break;
		}
	case ST_DATA:
		{
			m_pDataSegmentBuffer = (LPBYTE)malloc(nLength);
			if(m_pDataSegmentBuffer)
			{
				m_nDataSegmentBufferLength = nLength;
				return TRUE;
			}

			break;
		}
	}

	return FALSE;
}

void CMemWatchWnd::OnBnClickedButtonGetData()
{
	// TODO: 在此添加控件通知处理程序代码

	unsigned int uiMemAddr = m_editMemAddr.GetValue();
	unsigned int uiMemLength = m_editMemLength.GetValue();

	if( MallocSegmentBuffer(ST_DATA,uiMemLength) && 		
		GetDebugMemData(uiMemAddr,uiMemLength,m_pDataSegmentBuffer,m_nDataSegmentBufferLength))
	{
		m_editHexViewDataSegment.SetData(m_pDataSegmentBuffer,m_nDataSegmentBufferLength);
	}
}

BOOL CMemWatchWnd::GetDebugMemData(unsigned int uiMemAddr,unsigned int uiLength,LPBYTE pDataBuffer,unsigned int& uiRead)
{
	uiRead = 0;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame->IsDebuging())
	{
		DEBUGGER_READ_WRITE_MEMORY drm;
		drm.m_nAddr = uiMemAddr;
		drm.m_nLength = uiLength;
		drm.m_pReadBuffer = pDataBuffer;
		SendThreadMessage(pMainFrame->m_dwDebugThreadID,WM_DEBUGGER_READ_MEMORY,(WPARAM)(&drm),NULL);
		if(drm.m_stReadOrWriteLength > 0)
		{
			uiRead = drm.m_stReadOrWriteLength;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMemWatchWnd::SaveDebugMemData(unsigned int uiMemAddr,LPBYTE pDataBuffer,unsigned int uiLength,BOOL bIsCodeSegment)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame->IsDebuging())
	{
		DEBUGGER_READ_WRITE_MEMORY drm;
		drm.m_nAddr = uiMemAddr;
		drm.m_nLength = uiLength;
		drm.m_pReadBuffer = pDataBuffer;
		SendThreadMessage(pMainFrame->m_dwDebugThreadID,WM_DEBUGGER_WRITE_MEMORY,(WPARAM)(&drm),(LPARAM)bIsCodeSegment);
		if(drm.m_stReadOrWriteLength > 0)
		{
			//uiWrite = drm.m_stReadOrWriteLength;
			return TRUE;
		}
	}

	return FALSE;
}

LRESULT CMemWatchWnd::OnDebuggerClearDebugData(WPARAM wParam,LPARAM lParam)
{
	m_editMemAddr.SetWindowText(_T(""));
	m_editMemLength.SetWindowText(_T("0x100"));	
	m_editReadCodeLength.SetWindowText(_T("0x100"));

	m_strDataAddr.Empty();
	m_strDataString.Empty();
	m_strDataUchar.Empty();
	m_strDataChar.Empty();
	m_strDataUShort.Empty();
	m_strDataShort.Empty();
	m_strDataUInt.Empty();
	m_strDataInt.Empty();

	ClearSegmentBuffer(ST_ALL);

	m_editHexViewCodeSegment.SetData(NULL,0,true);
	m_strCodeDoasm.Empty();

	m_editHexViewStackSegment.SetData(NULL,0,true);
	m_editHexViewDataSegment.SetData(NULL,0,true);
	
	UpdateData(FALSE);

	return 1;
}

LRESULT CMemWatchWnd::OnMoveCaretPos(WPARAM wParam,LPARAM lParam)
{
	HWND hwnd = (HWND)wParam;
	POINT* pPoint = (POINT*)lParam;

	//数据段
	if(m_editHexViewDataSegment.GetSafeHwnd() == hwnd)
	{		
		ShowEditHexViewData(m_editHexViewDataSegment,pPoint);		
	}
	//堆栈段
	else if(m_editHexViewStackSegment.GetSafeHwnd() == hwnd)
	{
		ShowEditHexViewData(m_editHexViewStackSegment,pPoint);
	}

	return 1;
}

void CMemWatchWnd::ShowEditHexViewData(CMemWatchHexEdit& memWatchHexEdit,POINT* pPoint)
{	
	UINT nOffset = 0;
	BYTE chData[5];
	unsigned int uiAddr = 0;		

	nOffset = memWatchHexEdit.GetDataOffsetFromPoint(*pPoint);		
	memset(chData,0,5);
	memWatchHexEdit.GetData(chData,4,nOffset);
	uiAddr = memWatchHexEdit.GetAddrOffset() + nOffset;		

	unsigned char ucString[3];
	ucString[0] = chData[0];
	ucString[1] = chData[1];
	ucString[2] = 0;
	unsigned short usData = *((unsigned short*)chData);
	short sData = *((short*)chData);
	unsigned int uiData = *((unsigned int*)chData);
	int iData = *((int*)chData);

	m_strDataAddr.Format(_T("0x%08X"),uiAddr);

	if(isascii(ucString[0]))
	{
		ucString[1] = 0;
	}
	m_strDataString = ucString;

	m_strDataUchar.Format(_T("0x%02X"),chData[0]);
	m_strDataChar.Format(_T("%d"),chData[0]);
	m_strDataUShort.Format(_T("0x%04X"),usData);
	m_strDataShort.Format(_T("%d"),sData);
	m_strDataUInt.Format(_T("0x%08X"),uiData);
	m_strDataInt.Format(_T("%d"),iData);

	UpdateData(FALSE);
}

void CMemWatchWnd::OnEnChangeEditHexViewCodeSegment()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_BTN_SAVE_CODE_SEGMENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CODE_DOASM)->EnableWindow(TRUE);
}

void CMemWatchWnd::OnEnChangeEditHexViewDataSegment()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_BTN_SAVE_DATA_SEGMENT)->EnableWindow(TRUE);
}

void CMemWatchWnd::OnEnChangeEditHexViewStackSegment()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_BTN_SAVE_STACK_SEGMENT)->EnableWindow(TRUE);
}

void CMemWatchWnd::OnBnClickedBtnSaveCodeSegment()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(SaveDebugMemData(
		m_editHexViewCodeSegment.GetAddrOffset(),
		m_editHexViewCodeSegment.GetDataPtr(),
		m_editHexViewCodeSegment.GetDataLength(),
		TRUE))
	{
		GetDlgItem(IDC_BTN_SAVE_CODE_SEGMENT)->EnableWindow(FALSE);		
	}
}

void CMemWatchWnd::OnBnClickedBtnSaveDataSegment()
{
	// TODO: 在此添加控件通知处理程序代码

	if(SaveDebugMemData(
		m_editHexViewDataSegment.GetAddrOffset(),
		m_editHexViewDataSegment.GetDataPtr(),
		m_editHexViewDataSegment.GetDataLength(),
		TRUE))
	{
		GetDlgItem(IDC_BTN_SAVE_DATA_SEGMENT)->EnableWindow(FALSE);
	}
}

void CMemWatchWnd::OnBnClickedBtnSaveStackSegment()
{
	// TODO: 在此添加控件通知处理程序代码

	if(SaveDebugMemData(
		m_editHexViewStackSegment.GetAddrOffset(),
		m_editHexViewStackSegment.GetDataPtr(),
		m_editHexViewStackSegment.GetDataLength(),
		TRUE))
	{
		GetDlgItem(IDC_BTN_SAVE_STACK_SEGMENT)->EnableWindow(FALSE);
	}
}

void CMemWatchWnd::OnBnClickedCheckShowDsViewOnly()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_bShowDSViewOnly = !m_bShowDSViewOnly;
	
	ShowDataSegmentViewOnly(m_bShowDSViewOnly);
}

void CMemWatchWnd::ShowDataSegmentViewOnly(BOOL bShowDSViewOnly)
{
	CRect rcClient;
	GetClientRect(rcClient);
	CRect rcHexViewDataSegment = m_rcHexViewDataSegment;
	rcHexViewDataSegment.right = rcClient.right - 5 ;
	rcHexViewDataSegment.bottom = rcClient.bottom;

	if(m_bShowDSViewOnly)
	{
		m_editHexViewCodeSegment.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CS)->ShowWindow(SW_HIDE);		
		GetDlgItem(IDC_EDIT_READ_CODE_LENGTH)->ShowWindow(SW_HIDE);		
		GetDlgItem(IDC_BTN_SAVE_CODE_SEGMENT)->ShowWindow(SW_HIDE);		
		GetDlgItem(IDC_EDIT_CODE_DOASM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CS_DOASM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_CODE_DOASM)->ShowWindow(SW_HIDE);		
		m_editHexViewStackSegment.ShowWindow(SW_HIDE);		
		GetDlgItem(IDC_STATIC_SS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SAVE_STACK_SEGMENT)->ShowWindow(SW_HIDE);		

		rcHexViewDataSegment.left = 5;
		m_editHexViewDataSegment.MoveWindow(rcHexViewDataSegment);		
	}
	else
	{
		m_editHexViewCodeSegment.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CS)->ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_EDIT_READ_CODE_LENGTH)->ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_BTN_SAVE_CODE_SEGMENT)->ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_EDIT_CODE_DOASM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CS_DOASM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_CODE_DOASM)->ShowWindow(SW_SHOW);		
		m_editHexViewStackSegment.ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_STATIC_SS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SAVE_STACK_SEGMENT)->ShowWindow(SW_SHOW);	

		m_editHexViewDataSegment.MoveWindow(rcHexViewDataSegment);	
	}

	CRect rcWnd;
	CWnd* pWnd = NULL;
	int nWidth = 0;
	pWnd = GetDlgItem(IDC_STATIC_DS);		
	pWnd->GetClientRect(rcWnd);
	nWidth = rcWnd.right - rcWnd.left;
	pWnd->ClientToScreen(rcWnd);
	ScreenToClient(rcWnd);
	rcWnd.left = rcHexViewDataSegment.left;
	rcWnd.right = rcWnd.left + nWidth;
	pWnd->MoveWindow(rcWnd);
	int nRight = rcWnd.right;

	pWnd = GetDlgItem(IDC_BTN_SAVE_DATA_SEGMENT);
	pWnd->GetClientRect(rcWnd);
	nWidth = rcWnd.right - rcWnd.left;
	pWnd->ClientToScreen(rcWnd);
	ScreenToClient(rcWnd);
	rcWnd.left = nRight + 10;
	rcWnd.right = rcWnd.left + nWidth;
	pWnd->MoveWindow(rcWnd);
	nRight = rcWnd.right;

	pWnd = GetDlgItem(IDC_BTN_GET_DATA_SEGMENT);
	pWnd->GetClientRect(rcWnd);
	nWidth = rcWnd.right - rcWnd.left;
	pWnd->ClientToScreen(rcWnd);
	ScreenToClient(rcWnd);
	rcWnd.left = nRight + 10;
	rcWnd.right = rcWnd.left + nWidth;
	pWnd->MoveWindow(rcWnd);

	RemoveAnchor(IDC_EDIT_HEX_VIEW_DATA_SEGMENT);
	AddAnchor(IDC_EDIT_HEX_VIEW_DATA_SEGMENT, TOP_LEFT, BOTTOM_RIGHT);
}

LRESULT CMemWatchWnd::OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam)
{
	DEBUGGER_CPU_CONTEXT* p_debugger_cpu_context = (DEBUGGER_CPU_CONTEXT*)wParam;
		
	UpdateData(TRUE);

	//显示代码段数据
	unsigned int uiAddr = p_debugger_cpu_context->m_debug_cpu.EIP - 1;
	m_nCodeSegmentBufferLength = m_editReadCodeLength.GetValue();
	if( MallocSegmentBuffer(ST_CODE,m_nCodeSegmentBufferLength) &&
		GetDebugMemData(uiAddr,m_nCodeSegmentBufferLength,m_pCodeSegmentBuffer,m_nCodeSegmentBufferLength))
	{
		m_editHexViewCodeSegment.SetAddrOffset(uiAddr);
		m_editHexViewCodeSegment.SetData(m_pCodeSegmentBuffer,m_nCodeSegmentBufferLength);
		ClearSegmentBuffer(ST_CODE);

		//代码段反汇编
		CodeSegmentDoasm();
		GetDlgItem(IDC_BTN_CODE_DOASM)->EnableWindow(FALSE);
	}	

	//显示堆栈段数据
	uiAddr = p_debugger_cpu_context->m_uiStackP;
	m_nStackSegmentBufferLength = uiAddr - p_debugger_cpu_context->m_debug_cpu.ESP + 4;
	if( MallocSegmentBuffer(ST_STACK,m_nStackSegmentBufferLength) && 
		GetDebugMemData(uiAddr,m_nStackSegmentBufferLength,m_pStackSegmentBuffer,m_nStackSegmentBufferLength))
	{
		m_editHexViewStackSegment.SetAddrOffset(uiAddr);
		m_editHexViewStackSegment.SetData(m_pStackSegmentBuffer,m_nStackSegmentBufferLength);
		ClearSegmentBuffer(ST_STACK);
	}

	//显示数据段
	uiAddr = p_debugger_cpu_context->m_uiDataSegmentAddr;
	if(uiAddr > 0)
	{
		m_nDataSegmentBufferLength = p_debugger_cpu_context->m_uiDataSegmentLength;
		if( MallocSegmentBuffer(ST_DATA,m_nDataSegmentBufferLength) && 
			GetDebugMemData(uiAddr,m_nDataSegmentBufferLength,m_pDataSegmentBuffer,m_nDataSegmentBufferLength))
		{
			m_editHexViewDataSegment.SetAddrOffset(uiAddr);
			m_editHexViewDataSegment.SetData(m_pDataSegmentBuffer,m_nDataSegmentBufferLength);
			ClearSegmentBuffer(ST_DATA);
		}
	}	

	return 1;
}

void CMemWatchWnd::OnBnClickedBtnCodeDoasm()
{
	// TODO: 在此添加控件通知处理程序代码

	CodeSegmentDoasm();
	GetDlgItem(IDC_BTN_CODE_DOASM)->EnableWindow(FALSE);
}

#include "./Common/UnicodeCovert.h"

//三个反汇编接口函数
//int   doi_DoasmBegin(char* pchLanguageFile,unsigned char* puchCode,unsigned int uiLength,unsigned int ui_image_base);
//bool  doi_DoasmData(char* pchInsnText);
//bool  doi_isEnd();

typedef int  (__cdecl *DOI_DOASMBEGIN)(char* ,unsigned char*,unsigned int,unsigned int);
typedef void (__cdecl *DOI_DOASMDATA)(char* pchInsnText);
typedef bool (__cdecl *DOI_ISEND)();

void CMemWatchWnd::CodeSegmentDoasm()
{
	BYTE* pData = m_editHexViewCodeSegment.GetDataPtr();
	if(pData == NULL)return;

	UINT uiDataLength = m_editHexViewCodeSegment.GetDataLength();

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString  strAppDir = pMainFrame->GetAppDirectory();
	CString strDoasmDllPath =  strAppDir + _T("\\oasm\\DoasmDll.dll");
	char chLanguagePath[MAX_PATH];
	CopyStr(chLanguagePath,MAX_PATH,strAppDir);
	strcat(chLanguagePath,"\\oasm\\language\\chinese.oic");

	HINSTANCE hDoasmDllInstance = LoadLibrary(strDoasmDllPath);
	if(hDoasmDllInstance)
	{
		int nResult = 0;
		//设置语言文件及初始化反汇编数据
		DOI_DOASMBEGIN doi_DoasmBegin = (DOI_DOASMBEGIN)GetProcAddress(hDoasmDllInstance,"doi_DoasmBegin");
		if(doi_DoasmBegin)
		{
			nResult = doi_DoasmBegin(chLanguagePath,pData,uiDataLength,m_editHexViewCodeSegment.GetAddrOffset());
		}

		//加载语言成功
		if(nResult >  0)
		{
			//得到反汇编函数
			DOI_DOASMDATA doi_DoasmData = (DOI_DOASMDATA)GetProcAddress(hDoasmDllInstance,"doi_DoasmData");
			DOI_ISEND doi_isEnd = (DOI_ISEND)GetProcAddress(hDoasmDllInstance,"doi_isEnd");
			if(doi_DoasmData && doi_isEnd)
			{
				m_strCodeDoasm.Empty();

				char chDoasmData[1024];				
				while(!doi_isEnd())
				{
					doi_DoasmData(chDoasmData);

					m_strCodeDoasm += chDoasmData;
					m_strCodeDoasm += _T("\r\n");
				}

				UpdateData(FALSE);
			}
		}			

		FreeLibrary(hDoasmDllInstance);
	}
}


