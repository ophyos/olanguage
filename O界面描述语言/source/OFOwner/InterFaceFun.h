
#ifndef _INTERFACE_FUN_H_
#define _INTERFACE_FUN_H_

int _stdcall InterFaceFun(void* pWnd,WPARAM wParam, LPARAM lParam);
int _stdcall 主窗口关闭(void* pWnd,WPARAM wParam, LPARAM lParam);
int _stdcall 主窗口创建(void* pWnd,WPARAM wParam, LPARAM lParam);
int _stdcall 菜单处理(void* pWnd,WPARAM wParam, LPARAM lParam);

#endif //_INTERFACE_FUN_H_