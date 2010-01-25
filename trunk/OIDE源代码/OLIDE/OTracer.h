
#ifndef _O_TRACER_H_
#define _O_TRACER_H_

#include "./Debugger/ODebugger.h"
#include "UserWmMsg.h"
#include "./Debugger/ReadDebugData.h"

class COTracer : public CODebugger
{
public:
	COTracer();
	virtual ~COTracer();

private:

	CWnd*  m_pWndOwner;	
	HWND   m_hSuspendWnd;
	TCHAR  m_chDebugFileName[256];
	CReadDebugData  m_readDebugData;
	
	BOOL  m_bLoadAllLineBreakPoint;
	HANDLE m_hCurBreakPointThread;
	
public:

	bool  BeginDebug(TCHAR* pchDebugFileName);
	void  DebugEnd();
	int   DoMessage(MSG& msg);	
	void  SetWndOwner(CWnd* pWndOwner){ m_pWndOwner = pWndOwner;};
	CWnd* GetWndOwner(){ return m_pWndOwner; }
	void  ResumeBreakpoint();
	
	static CBreakPointList* GetSysBreakPointList();

private:
		
	void  ReSetAllBreakPoint(); //重置所有断点位置
	int   InstallBreakPointFromFile(const CString& strFileName,int nLine,BOOL bInstall);		
	BOOL  GetDebuggerBPInfo(unsigned long ulAddr,DEBUGGER_BREAKPOINT* pBP);
	void  InstallAllSingleLineBreakPoint();
	void  RestoreAllSingleLineBreakPoint();
	CWnd* SearchWnd(const CString& strFileName);	

protected:
	virtual BOOL E_Breakpoint(DEBUG_EVENT *d);
	virtual BOOL E_SingleStep(DEBUG_EVENT *d);
	virtual BOOL E_AccessViolation(DEBUG_EVENT *d);
	virtual BOOL E_DatatypeMisallignment(DEBUG_EVENT *d);

	virtual BOOL D_CreateThread(DEBUG_EVENT *d)			    { return TRUE; };
	virtual BOOL D_CreateProcess(DEBUG_EVENT *d)	        { return TRUE; };
	virtual BOOL D_ExitThread(DEBUG_EVENT *d)				{ return TRUE; };
	virtual BOOL D_ExitProcess(DEBUG_EVENT *d);
	virtual BOOL D_LoadDLL(DEBUG_EVENT *d)					{ return TRUE; };
	virtual BOOL D_UnloadDLL(DEBUG_EVENT *d)				{ return TRUE; };
	virtual BOOL D_OutputDebugString(DEBUG_EVENT *d)		{ return TRUE; };
};

#endif //_O_TRACER_H_