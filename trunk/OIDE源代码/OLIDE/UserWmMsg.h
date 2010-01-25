
#ifndef _USER_WM_MSG_H_
#define _USER_WM_MSG_H_


#define WM_AUTO_COMPLETE_SELECTED  (WM_USER+100) 
#define WM_AUTO_COMPLETE_CANCEL    (WM_USER+101) 
#define WM_AUTO_COMPLETE_ADD_CHAR  (WM_USER+102) 
#define WM_OPEN_DOCUMENT           (WM_USER+110)

#define WM_DEBUGGER_RUN                         (WM_USER+120)
#define WM_DEBUGGER_CONTINUE_FLOOD              (WM_USER+121)
#define WM_DEBUGGER_CONTINUE_SINGLE_LINE        (WM_USER+122)
#define WM_DEBUGGER_TERMINATE                   (WM_USER+123)
#define WM_DEBUGGER_CONTINUE                    (WM_USER+124)
#define WM_DEBUGGER_REMOVEALLBREAKPOINT         (WM_USER+125)
#define WM_DEBUGGER_INSTALLBREAKPOINTFROMFILE   (WM_USER+126)
#define WM_DEBUGGER_READ_MEMORY                 (WM_USER+127)
#define WM_DEBUGGER_WRITE_MEMORY                (WM_USER+128)

#define WM_DEBUGGER_DELETEBREAKPOINT  (WM_USER+150)
#define WM_DEBUGGER_SETBREAKPOINT     (WM_USER+151)
#define WM_DEBUGGER_MOVE_TO           (WM_USER+152)
#define WM_DEBUGGER_CLEAR_DEBUG_DATA  (WM_USER+153)
#define WM_DEBUGGER_SHOW_CPU_DATA     (WM_USER+154)
#define WM_DEBUGGER_END               (WM_USER+155)

#define WM_MOVECARETPOS               (WM_USER+180)

struct  DEBUGGER_READ_WRITE_MEMORY
{
	UINT    m_nAddr;
	UINT    m_nLength;
	LPBYTE  m_pReadBuffer;
	SIZE_T  m_stReadOrWriteLength;
};

#endif //_USER_WM_MSG_H_