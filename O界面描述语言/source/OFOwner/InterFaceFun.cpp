
#include "stdafx.h"
#include "InterFaceFun.h"
#include "../ofl/OFL.h"

//所有的事件处理函数都必须按如下格式定义
//int _stdcall 函数名(void*,WPARAM,LPARAM)

int _stdcall InterFaceFun(void* pWnd,WPARAM wParam, LPARAM lParam)
{
	::MessageBox(0,"界面语言测试","OFL",0);

	return 0;
}

int _stdcall 主窗口关闭(void* pWnd,WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);

	return 0;
}

int _stdcall 主窗口创建(void* pWnd,WPARAM wParam, LPARAM lParam)
{	
	void* pControl =  OFGetControl("主窗口.第一层.TreeView1");

	return 0;
}

int _stdcall 菜单处理(void* pWnd,WPARAM wParam, LPARAM lParam)
{	
	//wParam是菜单根指针
	//lParam是菜单子项指针

	char* pchMenuText = MenuItem_GetText((void*)lParam);
	char chText[256];
	wsprintf(chText,"你点击了菜单:%s",pchMenuText);
	::MessageBox(0,chText,"OFL",0);

	return 0;
}

