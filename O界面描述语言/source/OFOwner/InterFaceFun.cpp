
#include "stdafx.h"
#include "InterFaceFun.h"
#include "../ofl/OFL.h"

//所有的事件处理函数都必须按如下格式定义
//int _stdcall 函数名(void*,WPARAM,LPARAM)

int _stdcall 框架窗口关闭(void* pWnd,WPARAM wParam, LPARAM lParam)
{
	int nResult = ::MessageBox(Ctrl_GetHandle(pWnd),"你真的要退出吗?","框架窗口",MB_YESNO);
	if(nResult == IDNO)
	{
		return false; //返回false,窗口将不会被关闭
	}

	return true; 
}

int _stdcall 框架窗口创建(void* pWnd,WPARAM wParam, LPARAM lParam)
{	
	void* pRightUpEdit =  OFGetControl("框架窗口.第一层.右栏面板.右上编辑框");
	if(pRightUpEdit)
	{		
		Edit_InsertText(pRightUpEdit,"\r\n这是窗口创建时增加的内容:)",true);
	}

	return 0;
}

int _stdcall 框架窗口菜单处理(void* pWnd,WPARAM wParam, LPARAM lParam)
{
	//wParam是菜单根指针
	//lParam是菜单子项指针

	unsigned short usID = MenuItem_GetId((void*)lParam);
	if(usID == 204) //退出菜单
	{
		void* pMainWnd = OFGetControl("框架窗口");
		if(pMainWnd)
		{
			SendMessage(Ctrl_GetHandle(pMainWnd),WM_CLOSE,0,0);
		}		
	}
	else if(usID == 401) //关于菜单
	{
		void* pMainWnd = OFGetControl("框架窗口");
		if(pMainWnd)
		{
			//显示关于窗口
			OFShowWnd("关于对话框",pMainWnd);
		}		
	}
	else
	{
		char* pchMenuText = MenuItem_GetText((void*)lParam);
		char chText[256];
		wsprintf(chText,"你点击了菜单:%s",pchMenuText);
		::MessageBox(0,chText,"OFL",0);
	}	

	return 0;
}

int _stdcall 关于对话框_关闭(void* pWnd,WPARAM wParam, LPARAM lParam)
{
	HWND hButton = Ctrl_GetHandle(pWnd);
	::SendMessage(::GetParent(hButton),WM_CLOSE,0,0); //向父窗口发送关闭消息

	return 0;
}