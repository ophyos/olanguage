// SyntaxCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SyntaxCtrl.h"

// CSyntaxCtrl

IMPLEMENT_DYNAMIC(CSyntaxCtrl, CScintillaCtrl)

CSyntaxCtrl::CSyntaxCtrl()
{
	
}

CSyntaxCtrl::~CSyntaxCtrl()
{
}


BEGIN_MESSAGE_MAP(CSyntaxCtrl, CScintillaCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()	
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()	
	ON_WM_HELPINFO()
END_MESSAGE_MAP()



// CSyntaxCtrl 消息处理程序

void CSyntaxCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	GetParent()->SendMessage(WM_RBUTTONDOWN,(WPARAM)nFlags,MAKELPARAM(point.x,point.y));
}

void CSyntaxCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	GetParent()->SendMessage(WM_RBUTTONUP,(WPARAM)nFlags,MAKELPARAM(point.x,point.y));
}

void CSyntaxCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nChar)
	{	
	case VK_RETURN:	//如果是回车		
	case VK_TAB:    //TAB键	
		{
			//如果是SHIFT
			if(GetKeyState(VK_SHIFT)&0x8000)
				break;

			GetParent()->SendMessage(WM_CHAR,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));			
			return;
		}		
	}

	CScintillaCtrl::OnChar(nChar, nRepCnt, nFlags);

	//Back键
	if(nChar == VK_BACK)
	{
		GetParent()->SendMessage(WM_CHAR,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));	
	}
}

void CSyntaxCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	

	switch(nChar)
	{
	case VK_RETURN:	//如果是回车
	case VK_TAB:    //TAB键	
		return;
	}

	CScintillaCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSyntaxCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nChar)
	{	
	case VK_RETURN:	//如果是回车
	case VK_TAB:    //TAB键	
		return;
	}

	CScintillaCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CSyntaxCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	GetParent()->SendMessage(WM_LBUTTONDOWN,(WPARAM)nFlags,MAKELPARAM(point.x,point.y));

	CScintillaCtrl::OnLButtonDown(nFlags, point);
}

void CSyntaxCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	GetParent()->SendMessage(WM_LBUTTONUP,(WPARAM)nFlags,MAKELPARAM(point.x,point.y));

	CScintillaCtrl::OnLButtonUp(nFlags, point);
}

BOOL CSyntaxCtrl::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CScintillaCtrl::OnHelpInfo(pHelpInfo);
}

int CSyntaxCtrl::GetCurrentLine() 
{
	int line = LineFromPosition (GetCurrentPos());
	return line;
}