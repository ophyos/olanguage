// RichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEdit

CRichEdit::CRichEdit()
{
}

CRichEdit::~CRichEdit()
{
}


BEGIN_MESSAGE_MAP(CRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CRichEdit)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
    //ON_COMMAND(ID_OUTPUT_EDIT_COPY, OnOutputEditCopy)
	//ON_COMMAND(ID_OUTPUT_CLEAR, OnOutputClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEdit message handlers
int CRichEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetColor();	

	return 0;
}

void CRichEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRichEditCtrl::OnRButtonDown(nFlags, point);
	
	/*CRect Rect;
	GetClientRect(Rect);
	ClientToScreen(Rect);
	point.Offset( Rect.TopLeft() );

	CMenu menu;
	VERIFY( menu.LoadMenu( IDR_OUTPUT_RICHEDIT_POP) );
	CMenu* pPop = menu.GetSubMenu( 0 );
	ASSERT( pPop );
		
	pPop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,this);*/
}

void CRichEdit::SetColor(COLORREF colorBackGround,COLORREF colorText)
{
	SetBackgroundColor(FALSE, colorBackGround);

	// set richeditctrl default font
	CHARFORMAT cf;	
	GetDefaultCharFormat(cf);
	cf.crTextColor	= colorText; 	

	SetDefaultCharFormat(cf);
}

void CRichEdit::Clear()
{
	SetSel( 0, -1 );
	ReplaceSel( NULL );
}

void CRichEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRichEditCtrl::OnLButtonDblClk(nFlags, point);

	char buf[1024];
	long nStartChar, nEndChar;
	int line = 0;

	CRichEditCtrl::GetSel( nStartChar, nEndChar );
	CRichEditCtrl::GetLine( LineFromChar(nStartChar), (LPTSTR)buf, 1024 );
}

int CRichEdit::InsertText(LPCTSTR str, COLORREF color)
{
	int nOldLines = 0, nNewLines = 0, nScroll = 0;
	long nInsertionPoint = 0;
	CHARFORMAT cf;

	// Save number of lines before insertion of new text
	nOldLines		= GetLineCount();

	// Initialize character format structure
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR;
	cf.dwEffects	= 0;	// To disable CFE_AUTOCOLOR
	cf.crTextColor	= color;

	// Set insertion point to end of text
	nInsertionPoint = GetWindowTextLength();
	SetSel(nInsertionPoint, -1);

	//  Set the character format
	SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing selected, this will simply insert
	// the string at the current caret position.
	ReplaceSel(str);

	// Get new line count
	nNewLines		= GetLineCount();

	// Scroll by the number of lines just inserted
	nScroll			= nNewLines - nOldLines;
	LineScroll(nScroll);

	return 0;
}

//void CRichEdit::OnOutputEditCopy()
//{
//	// TODO: 在此添加命令处理程序代码
//
//	CRichEditCtrl::Copy();
//}

//void CRichEdit::OnOutputClear()
//{
//	// TODO: 在此添加命令处理程序代码
//
//	Clear();
//}
