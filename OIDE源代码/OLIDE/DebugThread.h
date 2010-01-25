
#ifndef _DEBUG_THREAD_H_
#define _DEBUG_THREAD_H_

#include "./Debugger/DebugData.h"

void CreateSynchroSignal();
void ClearSynchroSignal();
void WaitSynchroSignal();
void SendThreadMessage(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam);
DWORD WINAPI DebugThread( LPVOID lpParam );

#endif //_DEBUG_THREAD_H_