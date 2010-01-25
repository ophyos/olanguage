#include "StdAfx.h"
#include "MemWatchHexEdit.h"
#include "UserWmMsg.h"

CMemWatchHexEdit::CMemWatchHexEdit(void)
{
}

CMemWatchHexEdit::~CMemWatchHexEdit(void)
{
}

UINT CMemWatchHexEdit::GetDataOffsetFromPoint(POINT point)
{
	bool bHightByte;
	UINT nAddr;
	GetAddressFromPoint(point,nAddr,bHightByte);

	return nAddr;
}

void CMemWatchHexEdit::MoveCaretPos(POINT point)
{
	CHexEditBase::MoveCaretPos(point);
	
	::SendMessage(GetParent()->GetSafeHwnd(),WM_MOVECARETPOS,(WPARAM)GetSafeHwnd(),(LPARAM)&point);
}