// CPUWatchWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "OLIDE.h"
#include "CPUWatchWnd.h"
#include "UserWmMsg.h"
#include "Debugger/DebugData.h"

// CCPUWatchWnd 对话框

IMPLEMENT_DYNAMIC(CCPUWatchWnd, CDialog)

CCPUWatchWnd::CCPUWatchWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CCPUWatchWnd::IDD, pParent)
	, m_strEAX(_T(""))
	, m_strEBX(_T(""))
	, m_strECX(_T(""))
	, m_strEDX(_T(""))
	, m_strEBP(_T(""))
	, m_strESP(_T(""))
	, m_strESI(_T(""))
	, m_strEDI(_T(""))
	, m_strEIP(_T(""))
	, m_strCS(_T(""))
	, m_strDS(_T(""))
	, m_strES(_T(""))
	, m_strSS(_T(""))
	, m_strFS(_T(""))
	, m_strGS(_T(""))
	,m_strST0(_T(""))
	,m_strST1(_T(""))
	,m_strST2(_T(""))
	,m_strST3(_T(""))
	,m_strST4(_T(""))
	,m_strST5(_T(""))
	,m_strST6(_T(""))
	,m_strST7(_T(""))
	,m_strXMM0(_T(""))
	,m_strXMM1(_T(""))
	,m_strXMM2(_T(""))
	,m_strXMM3(_T(""))
	,m_strXMM4(_T(""))
	,m_strXMM5(_T(""))
	,m_strXMM6(_T(""))
	,m_strXMM7(_T(""))
{

}

CCPUWatchWnd::~CCPUWatchWnd()
{
}

void CCPUWatchWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EAX, m_strEAX);
	DDX_Text(pDX, IDC_EDIT_EBX, m_strEBX);
	DDX_Text(pDX, IDC_EDIT_ECX, m_strECX);
	DDX_Text(pDX, IDC_EDIT_EDX, m_strEDX);
	DDX_Text(pDX, IDC_EDIT_EBP, m_strEBP);
	DDX_Text(pDX, IDC_EDIT_ESP, m_strESP);
	DDX_Text(pDX, IDC_EDIT_ESI, m_strESI);
	DDX_Text(pDX, IDC_EDIT_EDI, m_strEDI);
	DDX_Text(pDX, IDC_EDIT_EIP, m_strEIP);
	DDX_Control(pDX, IDC_LIST_EFLAG32, m_listEFlag32);
	DDX_Text(pDX, IDC_EDIT_CS, m_strCS);
	DDX_Text(pDX, IDC_EDIT_DS, m_strDS);
	DDX_Text(pDX, IDC_EDIT_ES, m_strES);
	DDX_Text(pDX, IDC_EDIT_SS, m_strSS);
	DDX_Text(pDX, IDC_EDIT_FS, m_strFS);
	DDX_Text(pDX, IDC_EDIT_GS, m_strGS);
	DDX_Text(pDX, IDC_EDIT_ST0_MMX0, m_strST0);
	DDX_Text(pDX, IDC_EDIT_ST1_MMX1, m_strST1);
	DDX_Text(pDX, IDC_EDIT_ST2_MMX2, m_strST2);
	DDX_Text(pDX, IDC_EDIT_ST3_MMX3, m_strST3);
	DDX_Text(pDX, IDC_EDIT_ST4_MMX4, m_strST4);
	DDX_Text(pDX, IDC_EDIT_ST5_MMX5, m_strST5);
	DDX_Text(pDX, IDC_EDIT_ST6_MMX6, m_strST6);
	DDX_Text(pDX, IDC_EDIT_ST7_MMX7, m_strST7);
	DDX_Text(pDX, IDC_EDIT_XMM0, m_strXMM0);
	DDX_Text(pDX, IDC_EDIT_XMM1, m_strXMM1);
	DDX_Text(pDX, IDC_EDIT_XMM2, m_strXMM2);
	DDX_Text(pDX, IDC_EDIT_XMM3, m_strXMM3);
	DDX_Text(pDX, IDC_EDIT_XMM4, m_strXMM4);
	DDX_Text(pDX, IDC_EDIT_XMM5, m_strXMM5);
	DDX_Text(pDX, IDC_EDIT_XMM6, m_strXMM6);
	DDX_Text(pDX, IDC_EDIT_XMM7, m_strXMM7);
}


BEGIN_MESSAGE_MAP(CCPUWatchWnd, CDialog)
	ON_MESSAGE(WM_DEBUGGER_CLEAR_DEBUG_DATA,   &CCPUWatchWnd::OnDebuggerClearDebugData)	
	ON_MESSAGE(WM_DEBUGGER_SHOW_CPU_DATA,    &CCPUWatchWnd::OnDebuggerShowCPUData)	
END_MESSAGE_MAP()


// CCPUWatchWnd 消息处理程序

LRESULT CCPUWatchWnd::OnDebuggerClearDebugData(WPARAM wParam,LPARAM lParam)
{
	m_strEAX.Empty();
	m_strEBX.Empty();
	m_strECX.Empty();
	m_strEDX.Empty();
	m_strEBP.Empty();
	m_strESP.Empty();
	m_strESI.Empty();
	m_strEDI.Empty();
	m_strEIP.Empty();

	int i;
	for(i=0;i<16;++i)
	{
		m_listEFlag32.SetItemText(2,i,m_strEAX);
	}
	for(i=0;i<16;++i)
	{		
		m_listEFlag32.SetItemText(5,i,m_strEAX);
	}

	m_strCS.Empty();
	m_strDS.Empty();
	m_strES.Empty();
	m_strSS.Empty();
	m_strFS.Empty();
	m_strGS.Empty();

	m_strST0.Empty();
	m_strST1.Empty();
	m_strST2.Empty();
	m_strST3.Empty();
	m_strST4.Empty();
	m_strST5.Empty();
	m_strST6.Empty();
	m_strST7.Empty();
	m_strXMM0.Empty();
	m_strXMM1.Empty();
	m_strXMM2.Empty();
	m_strXMM3.Empty();
	m_strXMM4.Empty();
	m_strXMM5.Empty();
	m_strXMM6.Empty();
	m_strXMM7.Empty();

	UpdateData(FALSE);

	return 1;
}

LRESULT CCPUWatchWnd::OnDebuggerShowCPUData(WPARAM wParam,LPARAM lParam)
{
	DEBUGGER_CPU_CONTEXT* p_debugger_cpu_context = (DEBUGGER_CPU_CONTEXT*)wParam;
	DEBUGGER_CPU* p_debugger_cpu = &p_debugger_cpu_context->m_debug_cpu;

	m_strEAX.Format(_T("%08X"),p_debugger_cpu->EAX);
	m_strEBX.Format(_T("%08X"),p_debugger_cpu->EBX);
	m_strECX.Format(_T("%08X"),p_debugger_cpu->ECX);
	m_strEDX.Format(_T("%08X"),p_debugger_cpu->EDX);
	m_strEBP.Format(_T("%08X"),p_debugger_cpu->EBP);
	m_strESP.Format(_T("%08X"),p_debugger_cpu->ESP);
	m_strESI.Format(_T("%08X"),p_debugger_cpu->ESI);
	m_strEDI.Format(_T("%08X"),p_debugger_cpu->EDI);
	m_strEIP.Format(_T("%08X"),p_debugger_cpu->EIP-1); //显示EIP寄存器值时退回一个0xCC字节

	p_debugger_cpu->EFlags;

	TCHAR* ptch0 = _T("0");
	TCHAR* ptch1 = _T("1");
	TCHAR* tchBitData[] = 
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};
	tchBitData[0]  = ((p_debugger_cpu->EFlags & 0x80000000) == 0x80000000)?ptch1:ptch0;
	tchBitData[1]  = ((p_debugger_cpu->EFlags & 0x40000000) == 0x40000000)?ptch1:ptch0;
	tchBitData[2]  = ((p_debugger_cpu->EFlags & 0x20000000) == 0x20000000)?ptch1:ptch0;
	tchBitData[3]  = ((p_debugger_cpu->EFlags & 0x10000000) == 0x10000000)?ptch1:ptch0;
	tchBitData[4]  = ((p_debugger_cpu->EFlags & 0x08000000) == 0x08000000)?ptch1:ptch0;
	tchBitData[5]  = ((p_debugger_cpu->EFlags & 0x04000000) == 0x04000000)?ptch1:ptch0;
	tchBitData[6]  = ((p_debugger_cpu->EFlags & 0x02000000) == 0x02000000)?ptch1:ptch0;
	tchBitData[7]  = ((p_debugger_cpu->EFlags & 0x01000000) == 0x01000000)?ptch1:ptch0;
	tchBitData[8]  = ((p_debugger_cpu->EFlags & 0x00800000) == 0x00800000)?ptch1:ptch0;
	tchBitData[9]  = ((p_debugger_cpu->EFlags & 0x00400000) == 0x00400000)?ptch1:ptch0;
	tchBitData[10] = ((p_debugger_cpu->EFlags & 0x00200000) == 0x00200000)?ptch1:ptch0;
	tchBitData[11] = ((p_debugger_cpu->EFlags & 0x00100000) == 0x00100000)?ptch1:ptch0;
	tchBitData[12] = ((p_debugger_cpu->EFlags & 0x00080000) == 0x00080000)?ptch1:ptch0;
	tchBitData[13] = ((p_debugger_cpu->EFlags & 0x00040000) == 0x00040000)?ptch1:ptch0;
	tchBitData[14] = ((p_debugger_cpu->EFlags & 0x00020000) == 0x00020000)?ptch1:ptch0;
	tchBitData[15] = ((p_debugger_cpu->EFlags & 0x00010000) == 0x00010000)?ptch1:ptch0;
	tchBitData[16] = ((p_debugger_cpu->EFlags & 0x00008000) == 0x00008000)?ptch1:ptch0;
	tchBitData[17] = ((p_debugger_cpu->EFlags & 0x00004000) == 0x00004000)?ptch1:ptch0;
	tchBitData[18] = ((p_debugger_cpu->EFlags & 0x00002000) == 0x00002000)?ptch1:ptch0;
	tchBitData[19] = ((p_debugger_cpu->EFlags & 0x00001000) == 0x00001000)?ptch1:ptch0;
	tchBitData[20] = ((p_debugger_cpu->EFlags & 0x00000800) == 0x00000800)?ptch1:ptch0;
	tchBitData[21] = ((p_debugger_cpu->EFlags & 0x00000400) == 0x00000400)?ptch1:ptch0;
	tchBitData[22] = ((p_debugger_cpu->EFlags & 0x00000200) == 0x00000200)?ptch1:ptch0;
	tchBitData[23] = ((p_debugger_cpu->EFlags & 0x00000100) == 0x00000100)?ptch1:ptch0;
	tchBitData[24] = ((p_debugger_cpu->EFlags & 0x00000080) == 0x00000080)?ptch1:ptch0;
	tchBitData[25] = ((p_debugger_cpu->EFlags & 0x00000040) == 0x00000040)?ptch1:ptch0;
	tchBitData[26] = ((p_debugger_cpu->EFlags & 0x00000020) == 0x00000020)?ptch1:ptch0;
	tchBitData[27] = ((p_debugger_cpu->EFlags & 0x00000010) == 0x00000010)?ptch1:ptch0;
	tchBitData[28] = ((p_debugger_cpu->EFlags & 0x00000008) == 0x00000008)?ptch1:ptch0;
	tchBitData[29] = ((p_debugger_cpu->EFlags & 0x00000004) == 0x00000004)?ptch1:ptch0;
	tchBitData[30] = ((p_debugger_cpu->EFlags & 0x00000002) == 0x00000002)?ptch1:ptch0;
	tchBitData[31] = ((p_debugger_cpu->EFlags & 0x00000001) == 0x00000001)?ptch1:ptch0;

	int i;
	for(i=0;i<16;++i)
	{		
		m_listEFlag32.SetItemText(2,i,tchBitData[i]);
	}
	for(i=0;i<16;++i)
	{		
		m_listEFlag32.SetItemText(5,i,tchBitData[16+i]);
	}

	//段寄存器
	m_strCS.Format(_T("%04X"),p_debugger_cpu->CS);
	m_strDS.Format(_T("%04X"),p_debugger_cpu->DS);
	m_strES.Format(_T("%04X"),p_debugger_cpu->ES);
	m_strSS.Format(_T("%04X"),p_debugger_cpu->SS);
	m_strFS.Format(_T("%04X"),p_debugger_cpu->FS);
	m_strGS.Format(_T("%04X"),p_debugger_cpu->GS);

	//浮点寄存器
    m_strST0.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST0[0],p_debugger_cpu->ST0[1],p_debugger_cpu->ST0[2],p_debugger_cpu->ST0[3],p_debugger_cpu->ST0[4],
	    p_debugger_cpu->ST0[5],p_debugger_cpu->ST0[6],p_debugger_cpu->ST0[7],p_debugger_cpu->ST0[8],p_debugger_cpu->ST0[9]);
	m_strST1.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST1[0],p_debugger_cpu->ST1[1],p_debugger_cpu->ST1[2],p_debugger_cpu->ST1[3],p_debugger_cpu->ST1[4],
	    p_debugger_cpu->ST1[5],p_debugger_cpu->ST1[6],p_debugger_cpu->ST1[7],p_debugger_cpu->ST1[8],p_debugger_cpu->ST1[9]);
	m_strST2.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST2[0],p_debugger_cpu->ST2[1],p_debugger_cpu->ST2[2],p_debugger_cpu->ST2[3],p_debugger_cpu->ST2[4],
	    p_debugger_cpu->ST2[5],p_debugger_cpu->ST2[6],p_debugger_cpu->ST2[7],p_debugger_cpu->ST2[8],p_debugger_cpu->ST2[9]);
	m_strST3.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST3[0],p_debugger_cpu->ST3[1],p_debugger_cpu->ST3[2],p_debugger_cpu->ST3[3],p_debugger_cpu->ST3[4],
	    p_debugger_cpu->ST3[5],p_debugger_cpu->ST3[6],p_debugger_cpu->ST3[7],p_debugger_cpu->ST3[8],p_debugger_cpu->ST3[9]);
	m_strST4.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST4[0],p_debugger_cpu->ST4[1],p_debugger_cpu->ST4[2],p_debugger_cpu->ST4[3],p_debugger_cpu->ST4[4],
	    p_debugger_cpu->ST4[5],p_debugger_cpu->ST4[6],p_debugger_cpu->ST4[7],p_debugger_cpu->ST4[8],p_debugger_cpu->ST4[9]);
	m_strST5.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST5[0],p_debugger_cpu->ST5[1],p_debugger_cpu->ST5[2],p_debugger_cpu->ST5[3],p_debugger_cpu->ST5[4],
	    p_debugger_cpu->ST5[5],p_debugger_cpu->ST5[6],p_debugger_cpu->ST5[7],p_debugger_cpu->ST5[8],p_debugger_cpu->ST5[9]);
	m_strST6.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST6[0],p_debugger_cpu->ST6[1],p_debugger_cpu->ST6[2],p_debugger_cpu->ST6[3],p_debugger_cpu->ST6[4],
	    p_debugger_cpu->ST6[5],p_debugger_cpu->ST6[6],p_debugger_cpu->ST6[7],p_debugger_cpu->ST6[8],p_debugger_cpu->ST6[9]);
	m_strST7.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
	    p_debugger_cpu->ST7[0],p_debugger_cpu->ST7[1],p_debugger_cpu->ST7[2],p_debugger_cpu->ST7[3],p_debugger_cpu->ST7[4],
	    p_debugger_cpu->ST7[5],p_debugger_cpu->ST7[6],p_debugger_cpu->ST7[7],p_debugger_cpu->ST7[8],p_debugger_cpu->ST7[9]);

	//XMM寄存器
	/*m_strXMM0.Format(_T("%016X%016X"),p_debugger_cpu->XMM0.High,p_debugger_cpu->XMM0.Low);
	m_strXMM1.Format(_T("%016X%016X"),p_debugger_cpu->XMM1.High,p_debugger_cpu->XMM1.Low);
	m_strXMM2.Format(_T("%016X%016X"),p_debugger_cpu->XMM2.High,p_debugger_cpu->XMM2.Low);
	m_strXMM3.Format(_T("%016X%016X"),p_debugger_cpu->XMM3.High,p_debugger_cpu->XMM3.Low);
	m_strXMM4.Format(_T("%016X%016X"),p_debugger_cpu->XMM4.High,p_debugger_cpu->XMM4.Low);
	m_strXMM5.Format(_T("%016X%016X"),p_debugger_cpu->XMM5.High,p_debugger_cpu->XMM5.Low);
	m_strXMM6.Format(_T("%016X%016X"),p_debugger_cpu->XMM6.High,p_debugger_cpu->XMM6.Low);
	m_strXMM7.Format(_T("%016X%016X"),p_debugger_cpu->XMM7.High,p_debugger_cpu->XMM7.Low);*/

	UpdateData(FALSE);

	return 1;
}

BOOL CCPUWatchWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	InitEFlag32List();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCPUWatchWnd::InitEFlag32List()
{
	int i;
	for(i=0;i<16;++i)
	{
		m_listEFlag32.InsertColumn(0,_T("a"),LVCFMT_CENTER,25);
	}

	m_listEFlag32.InsertItem(0,_T(""),0);
	m_listEFlag32.InsertItem(1,_T(""),0);
	m_listEFlag32.InsertItem(2,_T(""),0);
	m_listEFlag32.InsertItem(3,_T(""),0);
	m_listEFlag32.InsertItem(4,_T(""),0);
	m_listEFlag32.InsertItem(5,_T(""),0);
	
	LOGFONT   lf;  
	memset(&lf,0,sizeof(LOGFONT));           //   zero   out   structure  
	lf.lfHeight = 12;                         //   request   a   12-pixel-heightfont  
	wcscpy(lf.lfFaceName,_T("宋体"));        //   request   a   face   name   "Arial"  
	m_listFont.CreateFontIndirect(&lf);      //   create   the   font  
	m_listEFlag32.SetFont(&m_listFont, TRUE);   

	CString strText;
	for(i=0;i<16;++i)
	{
		strText.Format(_T("%02d"),31-i);
		m_listEFlag32.SetItemText(0,i,strText);
	}
	for(i=0;i<16;++i)
	{
		strText.Format(_T("%02d"),15-i);
		m_listEFlag32.SetItemText(3,i,strText);
	}
		
	TCHAR* tchBitName[] = 
	{ 
		//  31       30       29       28       27       26       25       24
		_T("－"),_T("－"),_T("－"),_T("－"),_T("－"),_T("－"),_T("－"),_T("－"),
		//  23       22       21       20       19       18       17       16
		_T("－"),_T("－"),_T("ID"),_T("VP"),_T("VI"),_T("AC"),_T("VM"),_T("RF"),
		//  15       14       13       12       11       10       09       08
		_T( "0"),_T("NT"),_T("IO"),_T("PL"),_T("OF"),_T("DF"),_T("IF"),_T("TF"),
		//  07       06       05       04       03       02       01       00
		_T("SF"),_T("ZF"), _T("0"),_T("AF"), _T("0"),_T("PF"), _T("1"),_T("CF")

	};

	for(i=0;i<16;++i)
	{		
		m_listEFlag32.SetItemText(1,i,tchBitName[i]);
	}
	for(i=0;i<16;++i)
	{		
		m_listEFlag32.SetItemText(4,i,tchBitName[16+i]);
	}

	//显示网格
	m_listEFlag32.SetExtendedStyle(m_listEFlag32.GetExtendedStyle()|LVS_EX_GRIDLINES);
}