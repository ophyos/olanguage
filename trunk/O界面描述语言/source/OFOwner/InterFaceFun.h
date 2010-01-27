
#ifndef _INTERFACE_FUN_H_
#define _INTERFACE_FUN_H_

int _stdcall 框架窗口关闭(void* pWnd,WPARAM wParam, LPARAM lParam);
int _stdcall 框架窗口销毁(void* pWnd,WPARAM wParam, LPARAM lParam);
int _stdcall 框架窗口创建(void* pWnd,WPARAM wParam, LPARAM lParam);

int _stdcall 框架窗口菜单处理(void* pWnd,WPARAM wParam, LPARAM lParam);

int _stdcall 关于对话框_关闭(void* pWnd,WPARAM wParam, LPARAM lParam);



#endif //_INTERFACE_FUN_H_