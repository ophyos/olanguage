
#ifndef _DEBUG_DATA_
#define _DEBUG_DATA_


#include "blackmagic.h"
#include "linkedlist.h"

#define EFLAGS_CARRY		0x00000001
#define EFLAGS_PARITY		0x00000004
#define EFLAGS_AUXCARRY		0x00000010
#define EFLAGS_ZERO			0x00000040
#define EFLAGS_SIGN			0x00000080
#define EFLAGS_TRAP			0x00000100
#define EFLAGS_INTENABLE	0x00000200
#define EFLAGS_DIRECTION	0x00000400
#define EFLAGS_OVERFLOW		0x00000800
#define EFLAGS_IOPL			0x00003000
#define EFLAGS_NESTEDTASK	0x00004000
#define EFLAGS_RESUME		0x00010000
#define EFLAGS_VIRT8086		0x00020000
#define EFLAGS_ALIGNMENT	0x00040000
#define EFLAGS_VIRTUALINT	0x00080000
#define EFLAGS_VIRTINTPEND	0x00100000
#define EFLAGS_IDFLAG		0x00200000

typedef struct DECLSPEC_ALIGN(16) _M128A
{
	ULONGLONG Low;
	LONGLONG High;
} M128A, *PM128A;


struct DEBUGGER_CPU 
{
	DWORD		EAX;
	DWORD		ECX;
	DWORD		EDX;
	DWORD		EBX;
	DWORD		ESI;
	DWORD		EDI;
	DWORD		ESP;
	DWORD		EBP;
	DWORD		EIP;
	DWORD		EFlags;

	WORD		CS;
	WORD		DS;
	WORD		ES;
	WORD		FS;
	WORD		GS;
	WORD		SS;

	BYTE        ST0[10];
	BYTE        ST1[10];
	BYTE        ST2[10];
	BYTE        ST3[10];
	BYTE        ST4[10];
	BYTE        ST5[10];
	BYTE        ST6[10];
	BYTE        ST7[10];

	M128A       XMM0;
	M128A       XMM1;
	M128A       XMM2;
	M128A       XMM3;
	M128A       XMM4;
	M128A       XMM5;
	M128A       XMM6;
	M128A       XMM7;
};

struct DEBUGGER_CPU_CONTEXT
{
	HANDLE m_hCurThread;
	unsigned int m_uiStackP;
	unsigned int m_uiDataSegmentAddr;	
	unsigned int m_uiDataSegmentLength;

	DEBUGGER_CPU m_debug_cpu;
};

//////////////////////////////////////////////////////////////////////////

//调试断点结构
struct DEBUGGER_BREAKPOINT
{
	TCHAR           m_tchFileName[256];       //断点所在文件的序号
	int             m_nLine;                  //断点所在的行

	unsigned int 	m_uiAddress;			  // 下断点的地址
	unsigned char   m_ucOriginalData;	      // 被替换成0xCC的原始字节数据 
	int 			m_bInstalled;			  // 断点被安装状态

	bool            m_bIsSingleLineBP;        //是否为单行跟踪断点
};

class CBreakPointList : public CLinkOper
{
public:

	CBreakPointList(){};
	virtual ~CBreakPointList(){DestroyList();};

protected:

	virtual void DeleteData(void* pData){if(pData) delete reinterpret_cast< DEBUGGER_BREAKPOINT* >(pData);};

public:

	DEBUGGER_BREAKPOINT* Add(const DEBUGGER_BREAKPOINT& breakPoint)
	{
		DEBUGGER_BREAKPOINT* pBreakPoint = new DEBUGGER_BREAKPOINT();
		if(pBreakPoint)
		{
			*pBreakPoint = breakPoint;
			PushData(pBreakPoint);
		}

		return pBreakPoint;
	}

	DEBUGGER_BREAKPOINT* GetCurBreakPoint()
	{
		return  reinterpret_cast< DEBUGGER_BREAKPOINT* >(GetCurElement()->GetData());
	}

	DEBUGGER_BREAKPOINT* Search(unsigned int uiAddress)
	{
		DEBUGGER_BREAKPOINT* pBreakPoint = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			pBreakPoint = GetCurBreakPoint();
			if(pBreakPoint->m_uiAddress == uiAddress)
			{
				return pBreakPoint;
			}
		}

		return NULL;
	}
};

//////////////////////////////////////////////////////////////////////////

//单步运行地址
struct DEBUGGER_SINGLE_STEP 
{
	unsigned int 	m_uiAddress;   //单步运行地址
	unsigned int    m_uiThreadID;  //线程ID
}; 

class CSingleStepList : public CLinkOper
{
public:

	CSingleStepList(){};
	virtual ~CSingleStepList(){DestroyList();};

protected:

	virtual void DeleteData(void* pData){if(pData) delete reinterpret_cast< DEBUGGER_SINGLE_STEP* >(pData);};

public:

	DEBUGGER_SINGLE_STEP* Add(const DEBUGGER_SINGLE_STEP& singleStep)
	{
		DEBUGGER_SINGLE_STEP* pSingleStep = new DEBUGGER_SINGLE_STEP();
		if(pSingleStep)
		{
			*pSingleStep = singleStep;
			PushData(pSingleStep);
		}

		return pSingleStep;
	}

	DEBUGGER_SINGLE_STEP* GetCurSingleStep()
	{
		return  reinterpret_cast< DEBUGGER_SINGLE_STEP* >(GetCurElement()->GetData());
	}

	DEBUGGER_SINGLE_STEP* SearchAddr(unsigned int uiAddress)
	{
		DEBUGGER_SINGLE_STEP* pSingleStep = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			pSingleStep = GetCurSingleStep();
			if(pSingleStep->m_uiAddress == uiAddress)
			{
				return pSingleStep;
			}
		}

		return NULL;
	}

	DEBUGGER_SINGLE_STEP* SearchThread(unsigned int uiThreadID)
	{
		DEBUGGER_SINGLE_STEP* pSingleStep = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			pSingleStep = GetCurSingleStep();
			if(pSingleStep->m_uiThreadID == uiThreadID)
			{
				return pSingleStep;
			}
		}

		return NULL;
	}
};


///////////////////////////////////////////////////////////////////////////////////////

struct DEBUGGER_THREAD 
{
	bool						m_bIsMainThread;				// 主线程标识
	unsigned int				m_uiThreadID;					// 线程ID
	HANDLE						m_hThread;                      // 线程句柄
	unsigned int				m_uiThreadLocalBase;			// ThreadLocalBase 
	unsigned int				m_uiStartAddress;				// 线程开始地址
	THREAD_BASIC_INFORMATION	m_tbiBasics;					// magic
	TEB							m_ThreadEnvironmentBlock;		// 线程环境块
	unsigned int				m_uiStackP;
};


class CDebuggerThread : public CLinkOper
{
public:

	CDebuggerThread(){};
	virtual ~CDebuggerThread(){DestroyList();};

protected:

	virtual void DeleteData(void* pData){if(pData) delete reinterpret_cast< DEBUGGER_THREAD* >(pData);};

public:

	DEBUGGER_THREAD* Add(const DEBUGGER_THREAD& debuggerThread)
	{
		DEBUGGER_THREAD* pDebuggerThread = new DEBUGGER_THREAD();
		if(pDebuggerThread)
		{
			*pDebuggerThread = debuggerThread;
			PushData(pDebuggerThread);
		}

		return pDebuggerThread;
	}

	DEBUGGER_THREAD* GetCurDebuggerThread()
	{
		return  reinterpret_cast< DEBUGGER_THREAD* >(GetCurElement()->GetData());
	}

	DEBUGGER_THREAD* Search(unsigned int uiThreadID)
	{
		DEBUGGER_THREAD* pDebuggerThread = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			pDebuggerThread = GetCurDebuggerThread();
			if(pDebuggerThread->m_uiThreadID == uiThreadID)
			{
				return pDebuggerThread;
			}
		}

		return NULL;
	}

	DEBUGGER_THREAD* Search(HANDLE	hThread)
	{
		DEBUGGER_THREAD* pDebuggerThread = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			pDebuggerThread = GetCurDebuggerThread();
			if(pDebuggerThread->m_hThread == hThread)
			{
				return pDebuggerThread;
			}
		}

		return NULL;
	}
};

//////////////////////////////////////////////////////////////////////////
//
struct DEBUG_DATA_ITEM_LINE
{
	unsigned short m_usFileIndex;   //文件序号
	long m_lLine;                   //行号
	unsigned long m_ulAddr;         //行号对应的代码地址
};

class CDebugDataItemLine : public CLinkOper
{
public:

	CDebugDataItemLine(){};
	virtual ~CDebugDataItemLine(){DestroyList();};

protected:

	virtual void DeleteData(void* pData){if(pData) delete reinterpret_cast< DEBUG_DATA_ITEM_LINE* >(pData);};

public:

	DEBUG_DATA_ITEM_LINE* Add(const DEBUG_DATA_ITEM_LINE& debug_data_item_line)
	{
		DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = new DEBUG_DATA_ITEM_LINE();
		if(p_debug_data_item_line)
		{
			*p_debug_data_item_line = debug_data_item_line;
			PushData(p_debug_data_item_line);
		}

		return p_debug_data_item_line;
	}

	DEBUG_DATA_ITEM_LINE* GetCurDebugDataItemLine()
	{
		return  reinterpret_cast< DEBUG_DATA_ITEM_LINE* >(GetCurElement()->GetData());
	}

	DEBUG_DATA_ITEM_LINE* Search(unsigned short usFileIndex,long lLine)
	{
		DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			p_debug_data_item_line = GetCurDebugDataItemLine();
			if( (p_debug_data_item_line->m_usFileIndex == usFileIndex) && 
				(p_debug_data_item_line->m_lLine == lLine))
			{
				return p_debug_data_item_line;
			}
		}

		return NULL;
	}

	DEBUG_DATA_ITEM_LINE* Search(unsigned long ulAddr)
	{
		DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = NULL;
		for(GetFirstElement();!isEnd();GetNextElement())
		{
			p_debug_data_item_line = GetCurDebugDataItemLine();
			if(p_debug_data_item_line->m_ulAddr == ulAddr)
			{
				return p_debug_data_item_line;
			}
		}

		return NULL;
	}
};

#endif //_DEBUG_DATA_