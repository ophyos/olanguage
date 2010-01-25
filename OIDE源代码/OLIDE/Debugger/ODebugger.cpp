
#include "stdafx.h"
#include "ODebugger.h"

CODebugger::CODebugger()
{
	m_chFileName[0] = 0;
	m_uiProcessID = 0;	// 当前被调试进程的ID
	m_uiThreadID = 0;   // 主线程ID
	m_hProcess = NULL;	// 进程句柄
	m_hThread = NULL;	// 主线程句柄
	
	m_bActive = false;	// 活动状态
	m_ulCurBreakPointAddr = 0;
	
	fbpfunc=NULL;
	bpfunc=NULL;
	exitfunc=NULL;
	unhfunc=NULL;

	SetDebugPrivilege(GetCurrentProcess());
	InitBlackmagic();
}

CODebugger::~CODebugger()
{
	Exorcism();
}

bool CODebugger::load(TCHAR *filename) 
{
	return load(filename,NULL);
}

bool CODebugger::load(TCHAR *filename,TCHAR *commandline) 
{
	PROCESS_INFORMATION		pi;
	STARTUPINFO				si;
	
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if(!CreateProcess(filename , // 文件名
		commandline,             // 命令行
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		DEBUG_ONLY_THIS_PROCESS, // 进程调试模式, 但不调试子进程
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		return false;
	} 

	//
	// CreateProcess worked
	//
	m_uiThreadID = pi.dwThreadId;
	m_hThread = pi.hThread;	
	m_uiProcessID = pi.dwProcessId;
	m_hProcess = pi.hProcess;
	
	m_bActive = true;

#ifdef _UNICODE
	wcscpy(m_chFileName,filename);
#else
	strcpy(m_chFileName,filename);
#endif	

	m_debuggerThread.ClearList();
	m_singleStepList.ClearList();

	return true;
}

void CODebugger::TerminateDebug()
{
	if(IsDebuging())
	{
		SetStopDebug();

		//强制终止被调试的进程
		TerminateProcess(m_hProcess,0);
	}
}

bool CODebugger::DebugProcessIsRuning()
{
	DWORD dwProcessCode;
	::GetExitCodeProcess(m_hProcess,&dwProcessCode);
	if(dwProcessCode == STILL_ACTIVE)
		return true;

	return false;
}

bool CODebugger::IsDebuging()
{
	if(!DebugProcessIsRuning())
	{
		m_bActive = false;
	}

	return m_bActive;
}

bool CODebugger::run(unsigned int msec)
{
	DEBUG_EVENT	deDebugEvent;	//调试事件信息
	bool bResult = true;

	// 等待调试事件
	if(m_bActive && WaitForDebugEvent(&deDebugEvent, msec)) 
	{
		//处理调试事件
		switch(deDebugEvent.dwDebugEventCode)
		{ 
			//调试异常事件
		case EXCEPTION_DEBUG_EVENT:
			{
				bResult = OnDebugException(deDebugEvent);
				break;
			}

			//创建线程
		case CREATE_THREAD_DEBUG_EVENT: 	
			{
				AddThread(deDebugEvent.dwThreadId,
					deDebugEvent.u.CreateThread.hThread,
					(DWORD)deDebugEvent.u.CreateThread.lpStartAddress,
					(DWORD)deDebugEvent.u.CreateThread.lpThreadLocalBase);

				// call overloady
				D_CreateThread(&deDebugEvent);

				break;
			}

			//创建进程
		case CREATE_PROCESS_DEBUG_EVENT:
			{
				//m_hProcess = deDebugEvent.u.CreateProcessInfo.hProcess;
				//m_hThread = deDebugEvent.u.CreateProcessInfo.hThread;				

				//将主线程添加到线程链表
				DEBUGGER_THREAD* pDebuggerThread = AddThread(deDebugEvent.dwThreadId,deDebugEvent.u.CreateProcessInfo.hThread,0,0);
				pDebuggerThread->m_bIsMainThread = true;

				// call overloady
				D_CreateProcess(&deDebugEvent);

				// 关闭进程文件句柄
				if(deDebugEvent.u.CreateProcessInfo.hFile)
				{
					CloseHandle(deDebugEvent.u.CreateProcessInfo.hFile);
				}

				break;
			}

			//结束线程
		case EXIT_THREAD_DEBUG_EVENT: 		
			{
				RemoveThread(deDebugEvent.dwThreadId);

				// call overloady
				D_ExitThread(&deDebugEvent);

				break;
			}			

			//结束进程
		case EXIT_PROCESS_DEBUG_EVENT:	
			{
				if(exitfunc != NULL) 
				{					
					(*exitfunc)(&deDebugEvent);
				}				

				// call overloady
				D_ExitProcess(&deDebugEvent);

				break;
			}			

			//加载DLL
		case LOAD_DLL_DEBUG_EVENT: 		
			{				
				break;
			}			

			//卸载DLL
		case UNLOAD_DLL_DEBUG_EVENT: 		
			break;

			//输出调试字符串
		case OUTPUT_DEBUG_STRING_EVENT: 
			{
				// call overloady
				D_OutputDebugString(&deDebugEvent);

				break;
			}
		default:
			{
				bResult = false;
			}
		}

		DWORD dwContinueStatus;
		dwContinueStatus = bResult?DBG_CONTINUE:DBG_EXCEPTION_NOT_HANDLED;
		ContinueDebugEvent(deDebugEvent.dwProcessId, deDebugEvent.dwThreadId,dwContinueStatus);
	}
	else
	{
		return false;
	}

	return true;
}

// 中断处理程序
BOOL CODebugger::OnDebugException(DEBUG_EVENT& deDebugEvent)
{
	unsigned long ulAddress = (unsigned long)deDebugEvent.u.Exception.ExceptionRecord.ExceptionAddress;

	//处理异常
	switch (deDebugEvent.u.Exception.ExceptionRecord.ExceptionCode) 
	{ 
		//断点异常
	case EXCEPTION_BREAKPOINT:
		{			
			//发生断点异常的地址			
			DEBUGGER_BREAKPOINT* pBreakPoint = m_breakPointListUser.Search(ulAddress); //搜索断点
			if(pBreakPoint == NULL) //断点不在断点列表内
			{
				break;
			}

			m_ulCurBreakPointAddr = ulAddress;

			//断点发生
			E_Breakpoint(&deDebugEvent);
			if(bpfunc != NULL)
			{
				(*bpfunc)(&deDebugEvent);
			}

			//得到线程
			HANDLE hThread = m_debuggerThread.Search(deDebugEvent.dwThreadId)->m_hThread;

			CONTEXT ct;
			//得到线程上下文
			ct.ContextFlags = CONTEXT_FULL;
			if(hThread && GetThreadContext(hThread, &ct))
			{
				//将原来的代码写回
				RestoreBreakPoint(pBreakPoint);
				
				//暂停所有其他线程，保证单步执行不被其他线程中断
				SuspendAllThread(hThread);

				//Eip指针减1，指向原来代码的运行处
				ct.Eip--;

				//设置单步运行
				ct.EFlags |= EFLAGS_TRAP;

				//添加单步执行
				if(pBreakPoint->m_bIsSingleLineBP == false)
				{
					DEBUGGER_SINGLE_STEP singleStep;
					singleStep.m_uiAddress = ulAddress;
					singleStep.m_uiThreadID = deDebugEvent.dwThreadId;
					m_singleStepList.Add(singleStep);
				}
				
				//设置线程的上下文信息
				SetThreadContext(hThread, &ct);

				return true;
			}
			
			break;
		}

		//单步异常
	case EXCEPTION_SINGLE_STEP:
		{
			E_SingleStep(&deDebugEvent);

			//得到单步断点的指针
			DEBUGGER_SINGLE_STEP* pSingleStep = NULL;
			pSingleStep = m_singleStepList.SearchThread(deDebugEvent.dwThreadId);
			if(pSingleStep)
			{
				//重新设置断点
				DEBUGGER_BREAKPOINT* pDbp = m_breakPointListUser.Search(pSingleStep->m_uiAddress);
				if(pDbp && (pDbp->m_bIsSingleLineBP == false))
				{
					SetBreakPoint(pDbp);
				}

				m_singleStepList.RemoveData(pSingleStep);

				ResumeAllThread(deDebugEvent.dwThreadId);
			}

			break;
		}

		//
		//下面的异常事件不关心,按默认处理
		//

		//违规访问
	case EXCEPTION_ACCESS_VIOLATION:
		{
			E_AccessViolation(&deDebugEvent);
			if (deDebugEvent.u.Exception.dwFirstChance) 
			{
				if(unhfunc != NULL)
				{
					(*unhfunc)(&deDebugEvent); 
				}
				else
				{
					default_unhandled(&deDebugEvent);
				}
			}

			break;
		}

	case EXCEPTION_PRIV_INSTRUCTION: 				
		{
			if ((deDebugEvent.u.Exception.dwFirstChance == 0) || 
				(deDebugEvent.u.Exception.ExceptionRecord.ExceptionFlags == EXCEPTION_NONCONTINUABLE) ) 
			{						
				if(unhfunc != NULL)
				{
					(*unhfunc)(&deDebugEvent); 
				}
				else
				{
					default_unhandled(&deDebugEvent);
				}
			}

			break;
		}

		/*
		case EXCEPTION_DATATYPE_MISALIGNMENT: 	
		//按Ctrl+C 键
		case DBG_CONTROL_C:
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		case EXCEPTION_ILLEGAL_INSTRUCTION:
		case EXCEPTION_IN_PAGE_ERROR:
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
		case EXCEPTION_INT_OVERFLOW:			
		case EXCEPTION_STACK_OVERFLOW:
		*/
	default:
		{
			if(deDebugEvent.u.Exception.dwFirstChance == 0) 
			{				
				if(unhfunc != NULL)
				{
					(*unhfunc)(&deDebugEvent); 
				}
				else
				{
					default_unhandled(&deDebugEvent);
				}
			}
			
			return FALSE;
		}
	} 

	return TRUE;
}

//设置指令单步异常
bool CODebugger::SetSingleStep(HANDLE hThread)
{
	CONTEXT ct;
	//得到线程上下文
	ct.ContextFlags = CONTEXT_FULL;
	if(hThread && GetThreadContext(hThread, &ct))
	{
		//暂停所有其他线程，保证单步执行不被其他线程中断
		SuspendAllThread(hThread);

		//设置单步运行
		ct.EFlags |= EFLAGS_TRAP;
		
		//设置线程的上下文信息
		SetThreadContext(hThread, &ct);

		return true;
	}

	return false;
}

DEBUGGER_THREAD* CODebugger::AddThread(DWORD threadID, HANDLE ht, DWORD lpStartAddress, DWORD lpThreadLocalBase) 
{
	DEBUGGER_THREAD	debuggerThread;
	DEBUGGER_CPU	cpu;

	debuggerThread.m_uiThreadID = threadID;
	debuggerThread.m_hThread = ht;
	debuggerThread.m_uiStartAddress = (DWORD)lpStartAddress;
	debuggerThread.m_uiThreadLocalBase = (DWORD)lpThreadLocalBase;

	ReadThreadBasicInformation(debuggerThread.m_hThread, &(debuggerThread.m_tbiBasics));
	ReadTEB(debuggerThread.m_hThread);	
	GetCPUContext(debuggerThread.m_hThread,&cpu);
	debuggerThread.m_uiStackP = cpu.ESP;
	
	return m_debuggerThread.Add(debuggerThread);
}

void CODebugger::RemoveThread(DWORD threadID) 
{
	DEBUGGER_THREAD* pDebuggerThread = m_debuggerThread.Search(threadID);
	if(pDebuggerThread)
	{
		m_debuggerThread.RemoveData(pDebuggerThread);
	}
}

void CODebugger::default_unhandled(DEBUG_EVENT *d) 
{
	
}

// 暂停其他线程
void CODebugger::SuspendAllThread(DWORD dwThreadId)
{	
	DEBUGGER_THREAD* pDebuggerThread = NULL;
	for(m_debuggerThread.GetFirstElement();!m_debuggerThread.isEnd();m_debuggerThread.GetNextElement())	
	{
		pDebuggerThread = m_debuggerThread.GetCurDebuggerThread();
		// 自身以外所有的线程都暂停
		if (pDebuggerThread->m_uiThreadID != dwThreadId)
		{
			::SuspendThread(pDebuggerThread->m_hThread);
		}
	}
}

void CODebugger::SuspendAllThread(HANDLE hThread)
{
	DEBUGGER_THREAD* pDebuggerThread = NULL;
	for(m_debuggerThread.GetFirstElement();!m_debuggerThread.isEnd();m_debuggerThread.GetNextElement())	
	{
		pDebuggerThread = m_debuggerThread.GetCurDebuggerThread();
		// 自身以外所有的线程都暂停
		if (pDebuggerThread->m_hThread != hThread)
		{
			::SuspendThread(pDebuggerThread->m_hThread);
		}
	}
}

//  恢复其他线程
void CODebugger::ResumeAllThread(DWORD dwThreadId)
{
	DEBUGGER_THREAD* pDebuggerThread = NULL;
	for(m_debuggerThread.GetFirstElement();!m_debuggerThread.isEnd();m_debuggerThread.GetNextElement())	
	{
		pDebuggerThread = m_debuggerThread.GetCurDebuggerThread();
		// 自身以外所有的线程都恢复
		if (pDebuggerThread->m_uiThreadID != dwThreadId)
		{
			::ResumeThread(pDebuggerThread->m_hThread);
		}
	}
}

bool CODebugger::ReadTEB(HANDLE th) 
{	
	bool	rv = false;
	DWORD	dwLength = 0;

	DEBUGGER_THREAD* pDebuggerThread = NULL;
	pDebuggerThread = m_debuggerThread.Search(th);
	if(pDebuggerThread != NULL)
	{
		rv = ReadProcessMemory(
			m_hProcess,
			pDebuggerThread->m_tbiBasics.TebBaseAddress,
			&pDebuggerThread->m_ThreadEnvironmentBlock,
			sizeof(TEB),
			&dwLength);
	}

	return rv;
}

bool CODebugger::SetBreakPoint(DEBUGGER_BREAKPOINT *bp)
{
	DWORD	oldprot, oldprot2;
	BYTE	ccByte = 0xCC;

	//
	// Make the page in question writable 
	//
	if ( ! VirtualProtectEx(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		sizeof(BYTE),
		PAGE_EXECUTE_READWRITE,
		&oldprot) )
	{			
		return false;
	}

	//
	// Read original opcode
	//
	if (!ReadProcessMemory(
		m_hProcess,
		(LPCVOID)bp->m_uiAddress,
		&(bp->m_ucOriginalData),
		sizeof(BYTE),
		NULL) )
	{
		return false;
	}

	//
	// replace with 0xCC
	//
	if (!WriteProcessMemory(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		&ccByte,
		sizeof(ccByte),
		NULL) )
	{
			
		return false;
	}

	//
	// restore original permissions
	//
	if ( ! VirtualProtectEx(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		sizeof(BYTE),
		oldprot,
		&oldprot2) )
	{
		return false;
	}

	FlushInstructionCache(m_hProcess,NULL,0);

	bp->m_bInstalled = true;

	return true;
}


bool CODebugger::RestoreBreakPoint(DEBUGGER_BREAKPOINT *bp) 
{
	DWORD						oldprot, oldprot2;

	//
	// Make the page in question writable 
	//
	if ( ! VirtualProtectEx(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		sizeof(BYTE),
		PAGE_EXECUTE_READWRITE,
		&oldprot) )
	{
		return false;
	}

	//
	// replace with original byte
	//
	if (!WriteProcessMemory(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		&(bp->m_ucOriginalData),
		sizeof(bp->m_ucOriginalData),
		NULL) )
	{
		return false;
	}

	//
	// restore original permissions
	//
	if ( ! VirtualProtectEx(
		m_hProcess,
		(LPVOID)bp->m_uiAddress,
		sizeof(BYTE),
		oldprot,
		&oldprot2) )
	{
		return false;
	}

	FlushInstructionCache(m_hProcess,NULL,0);	

	bp->m_bInstalled = false;

	return true;
}

bool CODebugger::InstallBreakPoint(DEBUGGER_BREAKPOINT& bp,bool bNoSearch)
{
	DEBUGGER_BREAKPOINT* p_debugger_breakpoint = 0;
	if(bNoSearch)
	{
		//添加一个新断点
		p_debugger_breakpoint = m_breakPointListUser.Add(bp);
	}
	else
	{
		p_debugger_breakpoint = m_breakPointListUser.Search(bp.m_uiAddress);
		if(p_debugger_breakpoint)
		{
			p_debugger_breakpoint->m_bIsSingleLineBP = bp.m_bIsSingleLineBP;

			//断点已经被安装
			if(p_debugger_breakpoint->m_bInstalled)
			{
				return true;	
			}
		}
		else
		{
			//没有找到指定地址的断点就添加一个断点
			p_debugger_breakpoint = m_breakPointListUser.Add(bp);
		}	
	}	

	return SetBreakPoint(p_debugger_breakpoint);
}

bool CODebugger::DisableBreakPoint(DWORD addr)
{
	DEBUGGER_BREAKPOINT* pDebuggerBreakpoint = NULL; 
	pDebuggerBreakpoint = m_breakPointListUser.Search(addr);

	if(pDebuggerBreakpoint == NULL) 
	{	
		return false;
	}

	return RestoreBreakPoint(pDebuggerBreakpoint);
}

bool CODebugger::RemoveBreakPoint(DWORD addr)
{
	DEBUGGER_BREAKPOINT* pDebuggerBreakpoint = NULL;
	pDebuggerBreakpoint = m_breakPointListUser.Search(addr);

	if(pDebuggerBreakpoint == NULL)
	{
		return false;
	}

	if(pDebuggerBreakpoint->m_bInstalled)
	{
		RestoreBreakPoint(pDebuggerBreakpoint);
	}	

	m_breakPointListUser.RemoveData(pDebuggerBreakpoint);

	return true;
}

void CODebugger::InstallAllSingleLineBreakPoint()
{
	DEBUGGER_BREAKPOINT* p_debugger_breakpoint = 0;
	for(m_breakPointListUser.GetFirstElement();!m_breakPointListUser.isEnd();m_breakPointListUser.GetNextElement())
	{
		p_debugger_breakpoint = m_breakPointListUser.GetCurBreakPoint();
		if( (p_debugger_breakpoint->m_bIsSingleLineBP)    && 
			(p_debugger_breakpoint->m_bInstalled == false) && 
			(p_debugger_breakpoint->m_uiAddress != GetCurBreakPointAddr()))
		{
			SetBreakPoint(p_debugger_breakpoint);
		}
	}
}

void CODebugger::RestoreAllSingleLineBreakPoint()
{
	DEBUGGER_BREAKPOINT* p_debugger_breakpoint = 0;
	for(m_breakPointListUser.GetFirstElement();!m_breakPointListUser.isEnd();m_breakPointListUser.GetNextElement())
	{
		p_debugger_breakpoint = m_breakPointListUser.GetCurBreakPoint();
		if((p_debugger_breakpoint->m_bIsSingleLineBP) && (p_debugger_breakpoint->m_bInstalled))
		{
			RestoreBreakPoint(p_debugger_breakpoint);
		}		
	}
}

void CODebugger::RemoveAllBreakPoint()
{
	m_breakPointListUser.ClearList();
}

bool CODebugger::SetEIP(HANDLE hThread,unsigned int uiNewEIP) 
{
	CONTEXT	ctx;

	ctx.ContextFlags = CONTEXT_CONTROL;
	if(!GetThreadContext(hThread, &ctx)) 
	{		
		return false;
	}

	ctx.Eip = uiNewEIP;

	if(!SetThreadContext(hThread, &ctx)) 
	{		
		return false;
	}

	return true;
}

bool CODebugger::GetCPUContext(HANDLE hhThread, DEBUGGER_CPU *cpu)
{
	CONTEXT		ctx;

	ctx.ContextFlags = CONTEXT_FULL;
	if (!GetThreadContext(hhThread, &ctx)) 
	{
		return false;
	}

	cpu->EAX = ctx.Eax;
	cpu->ECX = ctx.Ecx;
	cpu->EDX = ctx.Edx;
	cpu->EBX = ctx.Ebx;
	cpu->ESI = ctx.Esi;
	cpu->EDI = ctx.Edi;
	cpu->EBP = ctx.Ebp;
	cpu->ESP = ctx.Esp;
	cpu->EIP = ctx.Eip;
	cpu->CS = ctx.SegCs;
	cpu->DS = ctx.SegDs;
	cpu->ES = ctx.SegEs;
	cpu->FS = ctx.SegFs;
	cpu->GS = ctx.SegGs;
	cpu->SS = ctx.SegSs;
	cpu->EFlags = ctx.EFlags;

	memcpy(cpu->ST0,&ctx.FloatSave.RegisterArea[00],10);
	memcpy(cpu->ST1,&ctx.FloatSave.RegisterArea[10],10);
	memcpy(cpu->ST2,&ctx.FloatSave.RegisterArea[20],10);
	memcpy(cpu->ST3,&ctx.FloatSave.RegisterArea[30],10);
	memcpy(cpu->ST4,&ctx.FloatSave.RegisterArea[40],10);
	memcpy(cpu->ST5,&ctx.FloatSave.RegisterArea[50],10);
	memcpy(cpu->ST6,&ctx.FloatSave.RegisterArea[60],10);
	memcpy(cpu->ST7,&ctx.FloatSave.RegisterArea[70],10);
	
	/*cpu->XMM1 = ctx.Xmm1;
	cpu->XMM2 = ctx.Xmm2;
	cpu->XMM3 = ctx.Xmm3;
	cpu->XMM4 = ctx.Xmm4;
	cpu->XMM5 = ctx.Xmm5;
	cpu->XMM6 = ctx.Xmm6;
	cpu->XMM7 = ctx.Xmm7;*/

	return true;
}


bool CODebugger::SetCPUContext(HANDLE hhThread, DEBUGGER_CPU* cpu) 
{
	CONTEXT		ctx;

	ctx.Eax = cpu->EAX;
	ctx.Ecx = cpu->ECX;
	ctx.Edx = cpu->EDX;
	ctx.Ebx = cpu->EBX;
	ctx.Esi = cpu->ESI;
	ctx.Edi = cpu->EDI;
	ctx.Ebp = cpu->EBP;
	ctx.Esp = cpu->ESP;
	ctx.Eip = cpu->EIP;
	ctx.SegCs = cpu->CS;
	ctx.SegDs = cpu->DS;
	ctx.SegEs = cpu->ES;
	ctx.SegFs = cpu->FS;
	ctx.SegGs = cpu->GS;
	ctx.SegSs = cpu->SS;
	ctx.EFlags = cpu->EFlags;

	memcpy(&ctx.FloatSave.RegisterArea[00],cpu->ST0,10);
	memcpy(&ctx.FloatSave.RegisterArea[10],cpu->ST1,10);
	memcpy(&ctx.FloatSave.RegisterArea[20],cpu->ST2,10);
	memcpy(&ctx.FloatSave.RegisterArea[30],cpu->ST3,10);
	memcpy(&ctx.FloatSave.RegisterArea[40],cpu->ST4,10);
	memcpy(&ctx.FloatSave.RegisterArea[50],cpu->ST5,10);
	memcpy(&ctx.FloatSave.RegisterArea[60],cpu->ST6,10);
	memcpy(&ctx.FloatSave.RegisterArea[70],cpu->ST7,10);

	/*ctx.Xmm0 = cpu->XMM0;
	ctx.Xmm1 = cpu->XMM1;
	ctx.Xmm2 = cpu->XMM2;
	ctx.Xmm3 = cpu->XMM3;
	ctx.Xmm4 = cpu->XMM4;
	ctx.Xmm5 = cpu->XMM5;
	ctx.Xmm6 = cpu->XMM6;
	ctx.Xmm7 = cpu->XMM7;*/

	ctx.ContextFlags = CONTEXT_FULL;
	if (!SetThreadContext(hhThread, &ctx)) 
	{		
		return false;
	}
	
	return true;
}

// Function to set priviledges stolen from Dan Kurc by Halvar, 
// in turn stolen from him by FX
bool CODebugger::SetDebugPrivilege( HANDLE hProcess ) 
{
	LUID luid ;
	TOKEN_PRIVILEGES privs ;
	HANDLE hToken = NULL ;
	DWORD dwBufLen = 0 ;
	char buf[1024] ;

	ZeroMemory( &luid,sizeof(luid) ) ;

	if(!LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &luid ))
		return false ;

	privs.PrivilegeCount = 1 ;
	privs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED ;
	memcpy( &privs.Privileges[0].Luid, &luid, sizeof(privs.Privileges[0].Luid )
		) ;


	if(!OpenProcessToken( hProcess, TOKEN_ALL_ACCESS,&hToken))
		return false ;

	if(!AdjustTokenPrivileges( hToken, FALSE, &privs,
		sizeof(buf),(PTOKEN_PRIVILEGES)buf, &dwBufLen ) )
		return false ;

	return true ;
}