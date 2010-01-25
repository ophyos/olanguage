
#include "stdafx.h"
#include "DebugThread.h"
#include "OTracer.h"
#include "MainFrm.h"

int g_nSynchroSignal = 0;  //同步信号量

void CreateSynchroSignal()
{
	g_nSynchroSignal = 1;
}

void ClearSynchroSignal()
{
	g_nSynchroSignal = 0;
}

void WaitSynchroSignal()
{
	//只要信号存在就一直等待
	while(g_nSynchroSignal)
	{
		MSG msg;
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);  
			DispatchMessage(&msg);   
		}
	}
}

void SendThreadMessage(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CreateSynchroSignal();
	::PostThreadMessage(idThread,Msg,wParam,lParam);
	WaitSynchroSignal();
}

DWORD WINAPI DebugThread( LPVOID lpParam ) 
{
	CMainFrame* pMainFrame = (CMainFrame*)lpParam;

	int nResult = -1; //小于0表示调试失败

	COTracer debugTracer;
	debugTracer.SetWndOwner(pMainFrame);

	CString strExeFileName;
	if(pMainFrame->GetCurProjectPropertyExeFileName(strExeFileName))
	{					
		if(debugTracer.BeginDebug((LPTSTR)(LPCTSTR)strExeFileName))
		{
			MSG msg;
			while(debugTracer.IsDebuging())
			{
				if(::PeekMessage(&msg,0,0,0,PM_REMOVE) && (msg.message > 0))
				{
					int nMsg = debugTracer.DoMessage(msg);

					//消息处理结束，清除同步信号
					ClearSynchroSignal();

					//如果消息处理结束返回小于0表示调试正常结束
					if(nMsg < 0)
					{
						nResult = 1;
						break;
					}
				}

				debugTracer.run(100);
			}
		}
	}
	
	debugTracer.DebugEnd();

	return nResult;
}
