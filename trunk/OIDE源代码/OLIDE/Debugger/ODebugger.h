
#ifndef _O_DEBUGGER_H_
#define _O_DEBUGGER_H_

#include "DebugData.h"

enum BREAK_POINT_TYPE
{
	BPT_NULL,
	BPT_BREAK_POINT_ALL,
	BPT_BREAK_POINT_ALL_SHOW,
	BPT_BREAK_POINT_ALL_NOT_SHOW,
};

class CODebugger
{
public:
	CODebugger();
	virtual ~CODebugger();

protected:

	CBreakPointList m_breakPointListUser;
	CDebuggerThread  m_debuggerThread;   //线程列表

	TCHAR           m_chFileName[256];
	unsigned int	m_uiProcessID;	// 当前被调试进程的ID
	HANDLE			m_hProcess;	    // 进程句柄
	unsigned int	m_uiThreadID;   // 主线程ID
	HANDLE			m_hThread;	    // 主线程句柄

	bool			m_bActive;		// 活动状态
	unsigned long   m_ulCurBreakPointAddr; // 当前断点地址
	
	CSingleStepList m_singleStepList; //设置单步运行时的地址列表

public:

	bool load(TCHAR *filename);
	bool load(TCHAR *filename, TCHAR *commandline);
	void TerminateDebug();
	bool DebugProcessIsRuning();

	bool run(unsigned int msec = INFINITE);
	bool IsDebuging();
	void SetStopDebug(){ m_bActive = false;}
	void SuspendAllThread(DWORD dwThreadId);
	void SuspendAllThread(HANDLE hThread);
	void ResumeAllThread(DWORD dwThreadId);
	bool ReadTEB(HANDLE th);
	unsigned long GetCurBreakPointAddr(){ return m_ulCurBreakPointAddr;}
	
	bool InstallBreakPoint(DEBUGGER_BREAKPOINT& bp,bool bNoSearch = false);	
	bool DisableBreakPoint(DWORD addr);
	bool RemoveBreakPoint(DWORD addr);
	void RemoveAllBreakPoint();
	void InstallAllSingleLineBreakPoint();
	void RestoreAllSingleLineBreakPoint();
	bool GetCPUContext(HANDLE hhThread, DEBUGGER_CPU *cpu);
	bool SetCPUContext(HANDLE hhThread, DEBUGGER_CPU *cpu);
	bool SetEIP(HANDLE hThread,unsigned int uiNewEIP);

	//设置回调函数句柄
	void set_breakpoint_handler(void (*handler)(DEBUG_EVENT*)){bpfunc = handler;}
	void set_exit_handler(void (*handler)(DEBUG_EVENT*)){exitfunc = handler;}
	void set_unhandled_handler(void (*handler)(DEBUG_EVENT*)){unhfunc = handler;}
	void set_inital_breakpoint_handler(void (*handler)(DEBUG_EVENT*)){fbpfunc = handler;}

protected:

	bool SetBreakPoint(DEBUGGER_BREAKPOINT *bp);
	bool RestoreBreakPoint(DEBUGGER_BREAKPOINT *bp);
	bool SetSingleStep(HANDLE hThread);

	void (*fbpfunc)(DEBUG_EVENT*);	// function to be called when initial BP is hit
	void (*bpfunc)(DEBUG_EVENT*);	// function to be called when BP is hit
	void (*exitfunc)(DEBUG_EVENT*);	// function to be called when debugee exits
	void (*unhfunc)(DEBUG_EVENT*);	// function to be called when debugee failed

	virtual BOOL E_FirstBreakpoint(DEBUG_EVENT *d)			{ return FALSE; };
	virtual BOOL E_Breakpoint(DEBUG_EVENT *d)				{ return FALSE; };
	virtual BOOL E_SingleStep(DEBUG_EVENT *d)				{ return FALSE; };
	virtual BOOL E_AccessViolation(DEBUG_EVENT *d)			{ return FALSE; };
	virtual BOOL E_DatatypeMisallignment(DEBUG_EVENT *d)	{ return FALSE; };
	//....
	virtual BOOL D_CreateThread(DEBUG_EVENT *d)			    { return TRUE; };
	virtual BOOL D_CreateProcess(DEBUG_EVENT *d)			{ return TRUE; };
	virtual BOOL D_ExitThread(DEBUG_EVENT *d)				{ return TRUE; };
	virtual BOOL D_ExitProcess(DEBUG_EVENT *d)				{ return TRUE; };
	virtual BOOL D_LoadDLL(DEBUG_EVENT *d)					{ return TRUE; };
	virtual BOOL D_UnloadDLL(DEBUG_EVENT *d)				{ return TRUE; };
	virtual BOOL D_OutputDebugString(DEBUG_EVENT *d)		{ return TRUE; };

	BOOL OnDebugException(DEBUG_EVENT& pEvent);

private:

	bool SetDebugPrivilege( HANDLE hProcess );
	void default_unhandled(DEBUG_EVENT *d);
	DEBUGGER_THREAD* AddThread(DWORD threadID, HANDLE ht, DWORD lpStartAddress, DWORD lpThreadLocalBase);
	void RemoveThread(DWORD threadID);

};

#endif //_O_DEBUGGER_H_