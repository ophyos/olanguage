
// OLIDEView.cpp : COLIDEView 类的实现
//

#include "stdafx.h"
#include "OLIDE.h"

#include "OLIDEDoc.h"
#include "OLIDEView.h"

#include "MainFrm.h"
#include "OTracer.h"
#include "DebugThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BREAKPOINT_MARKER         3
#define BREAKPOINT_STYLE          SC_MARK_CIRCLE
#define DEBUGGER_CUR_LINE         4
#define DEBUGGER_CUR_LINE_STYLE   SC_MARK_ARROW

// COLIDEView

IMPLEMENT_DYNCREATE(COLIDEView, CScintillaView)

BEGIN_MESSAGE_MAP(COLIDEView, CScintillaView)
    // 标准打印命令
    ON_COMMAND(ID_FILE_PRINT, &CScintillaView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScintillaView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COLIDEView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()    
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_DOC, OnUpdateDocPath)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
    ON_WM_CHAR()
    ON_WM_LBUTTONDOWN()
    ON_MESSAGE(WM_AUTO_COMPLETE_SELECTED,OnAutoCompleteSelected)
	ON_MESSAGE(WM_AUTO_COMPLETE_CANCEL,OnAutoCompleteCancel)
	ON_MESSAGE(WM_AUTO_COMPLETE_ADD_CHAR,OnAutoCompleteAddChar)	
	ON_WM_ACTIVATE()	

	ON_COMMAND(ID_SET_BREAK_POINT,         &COLIDEView::OnSetBreakPoint)	
	ON_MESSAGE(WM_DEBUGGER_MOVE_TO,        &COLIDEView::OnDebuggerMoveTo)	
	ON_MESSAGE(WM_DEBUGGER_CONTINUE,       &COLIDEView::OnDebuggerContinue)	
	ON_MESSAGE(WM_DEBUGGER_END,            &COLIDEView::OnDebuggerEnd)
		
	ON_COMMAND(ID_SYNTAX_WORD_COMMENT_LINE     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_COMMENT_BLOCK    , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_INCLUDE_TEXT     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_INCLUDE_LIB      , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_SEGMENT_EXTERN   , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_SEGMENT_DATA     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_SEGMENT_RDATA    , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_SEGMENT_BSS      , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_SEGMENT_CODE     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_STRUCT           , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_UNION            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_ENUM             , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_TYPE_DEFINE      , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_MACRO_DEFINE     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_DEGREE           , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_HDOB             , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_START            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_FUNCTION         , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_LABLE            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_ADDR             , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_ARRAY_DEFINE     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_ARRAY_MEMBER     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_WCHAR            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_WSTRING          , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_BLOCK_CONNECT    , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_LINE_CONNECT     , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_SYNTAX_WORD_INSN_JOIN        , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_IF                  , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ELSE                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_OR                  , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ALSO                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_NEG                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_CALL                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_RET                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_JMP                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_EXIT                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_BREAK               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_CONTINUE            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_INTERRUPT           , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_HLT                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_PUSH                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_POP                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_FLAGR               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_SET                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ENTER               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_LEAVE               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_CMP                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_XCHG                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_STRING              , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_WAIT                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_NOP                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ABOVE               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_BELOW               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_GT_ASSIGN           , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_LT_ASSIGN           , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_OVERFLOW            , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ODD                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_ZERO                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_FWAIT               , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_FNOP                , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_DIVISOR             , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_SQUARE_ROOT         , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_PI                  , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_LOG                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_LN                  , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_POWER               , &COLIDEView::OnSyntaxWordOperator)	
	ON_COMMAND(ID_OPERATOR_MUL                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_DIV                 , &COLIDEView::OnSyntaxWordOperator)
	ON_COMMAND(ID_OPERATOR_SIGN                , &COLIDEView::OnSyntaxWordOperator)
	
	ON_COMMAND(ID_INSERT_REG_AL                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_AH                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_BL                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_BH                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CL                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CH                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DL                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DH                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_AX                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_BX                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CX                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DX                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_BP                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_SP                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_SI                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DI                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_EAX               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_EBX               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ECX               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_EDX               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_EBP               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ESP               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ESI               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_EDI               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CS                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DS                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ES                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_SS                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_FS                , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_GS                , &COLIDEView::OnInsertRegister)	
	ON_COMMAND(ID_INSERT_REG_CR0               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CR2               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CR3               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_CR4               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR0               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR1               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR2               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR3               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR6               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_DR7               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR0               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR1               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR2               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR3               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR4               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR5               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR6               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_TR7               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST0               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST1               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST2               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST3               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST4               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST5               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST6               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_ST7               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM0               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM1               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM2               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM3               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM4               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM5               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM6               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_MM7               , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM0              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM1              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM2              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM3              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM4              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM5              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM6              , &COLIDEView::OnInsertRegister)
	ON_COMMAND(ID_INSERT_REG_XMM7              , &COLIDEView::OnInsertRegister)

	ON_COMMAND(ID_INCLUDE_OASM_HEAD, &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_INCLUDE_CUR_TEXT,  &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_INCLUDE_SYS_TEXT,  &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_INCLUDE_CUR_LIB,   &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_INCLUDE_SYS_LIB,   &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_INCLUDE_GENERAL,   &COLIDEView::OnIncludeFile)
	
	ON_COMMAND(ID_SENTENCE_SEGMENT_DATA,   &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_SEGMENT_RDATA,  &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_SEGMENT_BSS,    &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_SEGMENT_EXTERN, &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_SEGMENT_CODE,   &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_FUNCTION,       &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_IF,             &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_IF_ELSE,        &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_IF_ELSEIF_ELSE, &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_SENTENCE_WHILE,          &COLIDEView::OnAddSentence)		
	
	ON_COMMAND(ID_OML_INCLUDE_CUR_TEXT,  &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_OML_INCLUDE_SYS_TEXT,  &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_OML_INCLUDE_CUR_LIB,   &COLIDEView::OnIncludeFile)
	ON_COMMAND(ID_OML_INCLUDE_SYS_LIB,   &COLIDEView::OnIncludeFile)

	ON_COMMAND(ID_OML_SENTENCE_FUNCTION,       &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_OML_SENTENCE_IF,             &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_OML_SENTENCE_IF_ELSE,        &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_OML_SENTENCE_IF_ELSEIF_ELSE, &COLIDEView::OnAddSentence)
	ON_COMMAND(ID_OML_SENTENCE_WHILE,          &COLIDEView::OnAddSentence)		

	ON_COMMAND(ID_HIGH_LIGHT_OASM,         &COLIDEView::OnSyntaxHighLightType)
	ON_COMMAND(ID_HIGH_LIGHT_OML,          &COLIDEView::OnSyntaxHighLightType)

	ON_UPDATE_COMMAND_UI(ID_HIGH_LIGHT_OASM, &COLIDEView::OnUpdateHighLightOasm)
	ON_UPDATE_COMMAND_UI(ID_HIGH_LIGHT_OML, &COLIDEView::OnUpdateHighLightOml)

	ON_COMMAND(ID_TAB_ADD, &COLIDEView::OnTabAdd)
	ON_COMMAND(ID_TAB_SUB, &COLIDEView::OnTabSub)
	ON_COMMAND(ID_COMMENT_ADD, &COLIDEView::OnCommentAdd)
	ON_COMMAND(ID_COMMENT_SUB, &COLIDEView::OnCommentSub)
	ON_COMMAND(ID_FAST_INPUT_LIST, &COLIDEView::OnFastInputList)	
	ON_COMMAND(ID_FILE_TEMPLATE_LIST, &COLIDEView::OnFileTemplateList)	

	ON_WM_TIMER()
	ON_WM_DESTROY()
	END_MESSAGE_MAP()

// COLIDEView 构造/析构

COLIDEView::COLIDEView()
{
    // TODO: 在此处添加构造代码

	m_nSyntaxType = OVST_NULL;
	m_nAutoSaveTimer = 0;	
}

COLIDEView::~COLIDEView()
{
	
}

BOOL COLIDEView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CScintillaView::PreCreateWindow(cs);
}

// COLIDEView 绘制

void COLIDEView::OnDraw(CDC* /*pDC*/)
{
    COLIDEDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    /*if (!pDoc)
    	return;*/

    // TODO: 在此处为本机数据添加绘制代码
}


// COLIDEView 打印


void COLIDEView::OnFilePrintPreview()
{
    AFXPrintPreview(this);
}

BOOL COLIDEView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void COLIDEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: 添加额外的打印前进行的初始化过程
}

void COLIDEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: 添加打印后进行的清理过程
}

void COLIDEView::OnContextMenu(CWnd* pWnd, CPoint point)
{	
	if(m_nSyntaxType == OVST_OASM)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_OASM_EDIT, point.x, point.y, this, TRUE);
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_OML_EDIT, point.x, point.y, this, TRUE);		
	}
    
	CMFCMenuBar::SetShowAllCommands(TRUE);
}


// COLIDEView 诊断

#ifdef _DEBUG
void COLIDEView::AssertValid() const
{
    CScintillaView::AssertValid();
}

void COLIDEView::Dump(CDumpContext& dc) const
{
    CScintillaView::Dump(dc);
}

COLIDEDoc* COLIDEView::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COLIDEDoc)));
    return (COLIDEDoc*)m_pDocument;
}
#endif //_DEBUG


// COLIDEView 消息处理程序

void COLIDEView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CloseAutoWnd();

	CScintillaView::OnRButtonDown(nFlags, point);
}

void COLIDEView::OnRButtonUp(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    ClientToScreen(&point);
    OnContextMenu(this, point);

    CScintillaView::OnRButtonUp(nFlags, point);
}

void COLIDEView::OnInitialUpdate()
{
    CScintillaView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
		
	CString strExternName = GetDocument()->GetPathName();
	int nPos = strExternName.ReverseFind(_T('.'));
	if(nPos > 0)
	{
		strExternName = strExternName.Right(strExternName.GetLength()-nPos-1);
		strExternName.MakeLower();
		//如果是O汇编或者O反汇编
		if( (strExternName == _T("oam")) || 
			(strExternName == _T("oah")) ||
			(strExternName == _T("doa")))
		{
			m_nSyntaxType = OVST_OASM;
		}
		//如果是O汇编
		else if((strExternName == _T("omp")) || (strExternName == _T("omh")))
		{
			m_nSyntaxType = OVST_OML;
		}
	}

	UpdateAllStyle();	
}

void COLIDEView::UpdateAllStyle()
{
	CSyntaxCtrl& rCtrl = GetCtrl();	

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CSystemOption* pSystemOption = &pMainFrame->m_systemOption;
	m_pHintString = &pMainFrame->m_hintString;
	
	if(m_nSyntaxType == OVST_OASM) //O汇编
	{
		rCtrl.SetLexer(SCLEX_OASM);
		rCtrl.SetKeyWords(0, pMainFrame->m_syntaxWordList.m_strOasmWordListSymbol);
		rCtrl.SetKeyWords(1, pMainFrame->m_syntaxWordList.m_strOasmWordListCPUInsns);
		rCtrl.SetKeyWords(2, pMainFrame->m_syntaxWordList.m_strOasmWordListFPUInsns);
		rCtrl.SetKeyWords(3, pMainFrame->m_syntaxWordList.m_strOasmWordListRegister);
		rCtrl.SetKeyWords(4, pMainFrame->m_syntaxWordList.m_strOasmWordListDefineWord);
		rCtrl.SetKeyWords(5, pMainFrame->m_syntaxWordList.m_strOasmWordListMacro);
		rCtrl.SetKeyWords(6, pMainFrame->m_syntaxWordList.m_strOasmWordListOperatorTxt);
		rCtrl.SetKeyWords(7, pMainFrame->m_syntaxWordList.m_strOasmWordListOperator);
		//SetKeyWords 不能超过9

		//Setup styles			
		COLORREF colorBack = pSystemOption->m_colorOASMBackGround;

		//得到字体大小
		CDC* pDC = GetDC();  
		int nFontSize;
		nFontSize = -pSystemOption->m_lfOASMTextFont.lfHeight*72 / pDC->GetDeviceCaps(LOGPIXELSY);
		pDC->ReleaseOutputDC();

		rCtrl.StyleClearAll();

		rCtrl.StyleSetBack(STYLE_DEFAULT, colorBack); //设置背景色

		SetAStyle(SCE_OASM_DEFAULT, pSystemOption->m_colorOASMText,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);

		SetAStyle(SCE_OASM_COMMENTLINE, pSystemOption->m_colorOASMCommentLine,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_COMMENT, pSystemOption->m_colorOASMCommentBlock,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);

		SetAStyle(SCE_OASM_INCLUDE_TEXT, pSystemOption->m_colorOASMIncludeText,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_INCLUDE_LIB, pSystemOption->m_colorOASMIncludeLib,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		//SetAStyle(SCE_OASM_INCLUDE_BIN, pSystemOption->);

		//SetAStyle(SCE_OASM_SEGMENT_FLAG, pSystemOption->);
		SetAStyle(SCE_OASM_SEGMENT_DATA_FLAG, pSystemOption->m_colorOASMSegmentData,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_SEGMENT_RDATA_FLAG, pSystemOption->m_colorOASMSegmentRData,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_SEGMENT_BSS_FLAG, pSystemOption->m_colorOASMSegmentBSS,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		//SetAStyle(SCE_OASM_SEGMENT_EXTRA_FLAG, pSystemOption->);
		//SetAStyle(SCE_OASM_SEGMENT_STACK_FLAG, pSystemOption->);
		SetAStyle(SCE_OASM_SEGMENT_EXTERN_FLAG, pSystemOption->m_colorOASMSegmentExtern,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_SEGMENT_CODE_FLAG, pSystemOption->m_colorOASMSegmentCode,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);

		SetAStyle(SCE_OASM_NUMBER, pSystemOption->m_colorOASMDigital,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);

		SetAStyle(SCE_OASM_CPU_INSTRUCTIONS, pSystemOption->m_colorOASMInstruction,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		//rCtrl.StyleSetBold(SCE_OASM_CPU_INSTRUCTIONS, 1);
		SetAStyle(SCE_OASM_FPU_INSTRUCTIONS, pSystemOption->m_colorOASMFInstruction,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		//rCtrl.StyleSetBold(SCE_OASM_FPU_INSTRUCTIONS, 1);
		SetAStyle(SCE_OASM_REGISTER, pSystemOption->m_colorOASMRegister,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		//rCtrl.StyleSetBold(SCE_OASM_REGISTER, 1);
		SetAStyle(SCE_OASM_CHARACTER, pSystemOption->m_colorOASMChar,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_WCHARACTER, pSystemOption->m_colorOASMChar,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_STRING, pSystemOption->m_colorOASMString,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_WSTRING, pSystemOption->m_colorOASMString,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_DEFINE_WORD, pSystemOption->m_colorOASMDefineWord,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_MACRO, pSystemOption->m_colorOASMMacro,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_OPERATOR_TXT, pSystemOption->m_colorOASMOperatorTxt,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);
		SetAStyle(SCE_OASM_OPERATOR, pSystemOption->m_colorOASMOperator,colorBack,nFontSize,pSystemOption->m_pchOASMFontName);	

		//行号
		ShowLineNoMargin(pSystemOption->m_bOASMShowLineNumber);	
		//书签
		pSystemOption->m_bOASMShowBookMarker?rCtrl.SetMarginWidthN(1, 16):rCtrl.SetMarginWidthN(1, 0);

		//折叠
		SetFlod(pSystemOption->m_bOASMShowFold,0);
	}
	else if(m_nSyntaxType == OVST_OML) //O中间语言
	{
		rCtrl.SetLexer(SCLEX_OML);
		rCtrl.SetKeyWords(0, pMainFrame->m_syntaxWordList.m_strOMLWordListCommentSymbol);
		rCtrl.SetKeyWords(1, pMainFrame->m_syntaxWordList.m_strOMLWordListKeyword);
		rCtrl.SetKeyWords(2, pMainFrame->m_syntaxWordList.m_strOMLWordListOperator);
		rCtrl.SetKeyWords(3, pMainFrame->m_syntaxWordList.m_strOMLWordListMacroTxt);	

		//Setup styles			
		COLORREF colorBack = pSystemOption->m_colorOMLBackGround;

		//得到字体大小
		CDC* pDC = GetDC();  
		int nFontSize;
		nFontSize = -pSystemOption->m_lfOMLTextFont.lfHeight*72 / pDC->GetDeviceCaps(LOGPIXELSY);
		pDC->ReleaseOutputDC();

		rCtrl.StyleClearAll();

		SetAStyle(SCE_OML_DEFAULT, pSystemOption->m_colorOMLText,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);

		SetAStyle(SCE_OML_COMMENTLINE, pSystemOption->m_colorOMLCommentLine,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);
		SetAStyle(SCE_OML_COMMENT, pSystemOption->m_colorOMLCommentBlock,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);

		SetAStyle(SCE_OML_NUMBER, pSystemOption->m_colorOMLDigital,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);

		SetAStyle(SCE_OML_CHARACTER, pSystemOption->m_colorOMLChar,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);
		SetAStyle(SCE_OML_STRING, pSystemOption->m_colorOMLString,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);
		SetAStyle(SCE_OML_KEYWORD, pSystemOption->m_colorOMLKeyWord,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);
		SetAStyle(SCE_OML_MACRO_TXT, pSystemOption->m_colorOMLMacro,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);		
		SetAStyle(SCE_OML_SYMBOL_OPERATOR, pSystemOption->m_colorOMLOperator,colorBack,nFontSize,pSystemOption->m_pchOMLFontName);	

		//行号
		ShowLineNoMargin(pSystemOption->m_bOMLShowLineNumber);	
		//书签
		pSystemOption->m_bOMLShowBookMarker?rCtrl.SetMarginWidthN(1, 16):rCtrl.SetMarginWidthN(1, 0);

		//折叠
		SetFlod(pSystemOption->m_bOMLShowFold,0);
	}	
	
	//Setup auto completion
	//rCtrl.AutoCSetSeparator(_T('|'));

	//Setup call tips
	rCtrl.SetMouseDwellTime(500);
	
	//设置断点
	rCtrl.MarkerDefine(BREAKPOINT_MARKER, BREAKPOINT_STYLE);
	rCtrl.MarkerSetBack(BREAKPOINT_MARKER, RGB(0xFF, 0x00, 0x00));
	rCtrl.MarkerDefine(DEBUGGER_CUR_LINE, DEBUGGER_CUR_LINE_STYLE);
	rCtrl.MarkerSetBack(DEBUGGER_CUR_LINE, RGB(0xFF, 0xFF, 0x00));
}

void COLIDEView::DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back) 
{
	CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.MarkerDefine(marker, markerType);
	rCtrl.MarkerSetFore(marker, fore);
	rCtrl.MarkerSetBack(marker, back);
}

void COLIDEView::SetFlod(bool bShow,int nType)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	if(bShow == false)
	{
		rCtrl.SetMarginWidthN(2, 0);
		return ;
	}

	rCtrl.SetMarginWidthN(2, 16);
	rCtrl.SetMarginSensitiveN(2, TRUE);
	rCtrl.SetMarginTypeN(2, SC_MARGIN_SYMBOL);
	rCtrl.SetMarginMaskN(2, SC_MASK_FOLDERS);
	rCtrl.SetFoldFlags(16);  //收缩时画一直线
	rCtrl.SetProperty(_T("fold"), _T("1"));

	switch(nType)
	{	
	case 0:
		DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));
		DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER, RGB(0xff, 0xff, 0xff), RGB(0x80, 0x80, 0x80));		
		break;
		// Plus for contracted folders, minus for expanded
	case 1:
		DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_PLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		break;
	case 2:
		DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_CIRCLEMINUS, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_CIRCLEPLUS, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNERCURVE, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_CIRCLEPLUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_CIRCLEMINUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNERCURVE, RGB(0xff, 0xff, 0xff), RGB(0x40, 0x40, 0x40));
		break;
		// Arrow pointing right for contracted folders, arrow pointing down for expanded
	case 3:
		DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_ARROWDOWN,RGB(0, 0, 0), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_ARROW,RGB(0, 0, 0), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY,RGB(0, 0, 0), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY,RGB(0, 0, 0), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY,RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY,RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));		
		break;
	}
}

void COLIDEView::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
    CScintillaCtrl& rCtrl = GetCtrl();
    rCtrl.StyleSetFore(style, fore);
    rCtrl.StyleSetBack(style, back);
    if (size >= 1)
        rCtrl.StyleSetSize(style, size);
    if (face)
        rCtrl.StyleSetFont(style, face);
}

void COLIDEView::OnUpdateDocPath(CCmdUI* pCmdUI)
{
    pCmdUI->SetText(GetDocument()->GetPathName());
    pCmdUI->Enable();
}

void COLIDEView::OnUpdateLine(CCmdUI* pCmdUI)
{
    CScintillaCtrl& rCtrl = GetCtrl();
    int nPos = rCtrl.GetCurrentPos();
    int nLine = rCtrl.LineFromPosition(nPos);
    int nColumn = rCtrl.GetColumn(nPos);

    ++nLine;
    ++nColumn;

    CString sLine;
    sLine.Format(_T("行:%d 列:%d"), nLine, nColumn);
    pCmdUI->SetText(sLine);
    pCmdUI->Enable();
}

void COLIDEView::OnUpdateInsert(CCmdUI* pCmdUI)
{
    CString sText;
    sText = GetCtrl().GetOvertype()?_T("覆盖"):_T("插入");
    pCmdUI->SetText(sText);
    pCmdUI->Enable();
}

void COLIDEView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值	

	switch (nChar)
	{
	case VK_TAB:
		{
			if(m_autoCompleteList.GetSafeHwnd())
			{
				CloseAutoWnd();

				CString strText = _T("\t");
				GetCtrl().ReplaceSel(strText);
				return;
			}

			OnFastInputList();

			return;
		}  
		//如果是回车
	case VK_RETURN:
		{			
			CString strData = _T("\n");
			CString strSpace;
			BOOL bIsOpenBrace;
			bIsOpenBrace = GetCurLineBeginSpace(strSpace);
			if(!strSpace.IsEmpty())
			{
				strData += strSpace;
			}
			if(bIsOpenBrace)
			{
				strData += _T("    ");
			}

			GetCtrl().ReplaceSel(strData);

			return;
		}
	case VK_BACK:   //Back键
		{
			CharAdded();

			return;
		}
	}	
   
    CScintillaView::OnChar(nChar, nRepCnt, nFlags);
}

void COLIDEView::AdjustAutoCompleteListSize()
{
	int nItemCount = m_autoCompleteList.GetItemCount();
	int nBoxWidth;
	int nBoxHeight;

	RECT rcItem;
	m_autoCompleteList.GetItemRect(0,&rcItem,LVIR_BOUNDS);
	int nWordHeight = rcItem.bottom - rcItem.top;
	int nWordWidth = nWordHeight/2;

	if(m_autoCompleteList.IsHintList())
	{
		int nMaxLength = 0;
		for(int i=0;i<nItemCount;++i)
		{
			int nItemLength = m_autoCompleteList.GetItemText(i,0).GetLength();
			if(nItemLength > nMaxLength)
			{
				nMaxLength = nItemLength;
			}
		}		
		
		nBoxWidth = (nMaxLength + 6)*nWordWidth;
		nBoxHeight = (nItemCount + 1)*nWordHeight;

		m_autoCompleteList.SetColumnWidth(0,nBoxWidth-nWordWidth);		
	}
	else if(m_autoCompleteList.IsTemplateFileList())
	{
		nBoxWidth = 350;
		nBoxHeight = 160;
	}
	else //if(m_autoCompleteList.IsKeyWordList())
	{
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		if(pMainFrame->m_rcAutoCompleteList.right > 0 || pMainFrame->m_rcAutoCompleteList.bottom > 0)
		{
			nBoxWidth = pMainFrame->m_rcAutoCompleteList.right;
			nBoxHeight = pMainFrame->m_rcAutoCompleteList.bottom;
			m_autoCompleteList.SetColumnWidth(0,pMainFrame->m_nAutoCompleteList_Column0_Width);
			m_autoCompleteList.SetColumnWidth(1,pMainFrame->m_nAutoCompleteList_Column1_Width);			
		}
		else
		{
			int nMaxLength0 = 0,nMaxLength1 = 0;
			for(int i=0;i<nItemCount;++i)
			{
				int nItemLength = 0;
				CString strItemText;

				strItemText = m_autoCompleteList.GetItemText(i,0);
				for(int m=0;m<strItemText.GetLength();++m)
				{
					TCHAR tchWord = strItemText[m];
					nItemLength += (tchWord > 0xFF)?2:1;					
				}				
				if(nItemLength > nMaxLength0)
				{
					nMaxLength0 = nItemLength;
				}

				nItemLength = 0;
				strItemText = m_autoCompleteList.GetItemText(i,1);				
				for(int m=0;m<strItemText.GetLength();++m)
				{
					TCHAR tchWord = strItemText[m];
					nItemLength += (tchWord > 0xFF)?2:1;					
				}	
				if(nItemLength > nMaxLength1)
				{
					nMaxLength1 = nItemLength;
				}
			}

			nMaxLength0 += 1;
			nMaxLength1 += 1;			

			int nColumnWidth0 = nMaxLength0*nWordWidth;
			if(nColumnWidth0 < 80)
			{
				nColumnWidth0 = 80;
			}
			int nColumnWidth1 = nMaxLength1*nWordWidth;

			nBoxWidth = nColumnWidth0 + nColumnWidth1 + nWordHeight;
			nBoxHeight = (nItemCount + 1)*nWordHeight;
			if(nBoxHeight > 160)
			{
				nBoxHeight = 160;
			}

			m_autoCompleteList.SetColumnWidth(0,nColumnWidth0);
			m_autoCompleteList.SetColumnWidth(1,nColumnWidth1);
		}
	}

	CPoint pt = GetCaretPos();
	pt.x += 5;
	pt.y += 5;
	RECT rect;
	GetClientRect(&rect);
	if (pt.y + nBoxHeight > rect.bottom)
	{
		rect.top = rect.bottom-nBoxHeight;
		if (rect.top < 0)
		{
			rect.top = 0;
			rect.bottom = rect.top + nBoxHeight;
		}
	}
	else
	{
		rect.top = pt.y;
		rect.bottom = rect.top + nBoxHeight;
	}

	if (pt.x + nBoxWidth > rect.right)
	{
		rect.left = rect.right-nBoxWidth;
		if (rect.left < 0)
		{
			rect.left = 0;
			rect.right = rect.left + nBoxWidth;
		}
	}
	else
	{
		rect.left = pt.x;
		rect.right = rect.left + nBoxWidth;
	}

	m_autoCompleteList.MoveWindow(&rect,TRUE);
}

void COLIDEView::CloseAutoWnd()
{
	if(m_autoCompleteList.GetSafeHwnd())
	{		
		if(m_autoCompleteList.IsKeyWordList())
		{
			CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
			m_autoCompleteList.GetWindowRect(pMainFrame->m_rcAutoCompleteList);			
			pMainFrame->m_rcAutoCompleteList.right -= pMainFrame->m_rcAutoCompleteList.left;
			pMainFrame->m_rcAutoCompleteList.left = 0;
			pMainFrame->m_rcAutoCompleteList.bottom -= pMainFrame->m_rcAutoCompleteList.top;
			pMainFrame->m_rcAutoCompleteList.top = 0;
			pMainFrame->m_nAutoCompleteList_Column0_Width = m_autoCompleteList.GetColumnWidth(0);
			pMainFrame->m_nAutoCompleteList_Column1_Width = m_autoCompleteList.GetColumnWidth(1);
		}

		m_autoCompleteList.SendMessage(WM_CLOSE);
	}
}

void COLIDEView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

	CloseAutoWnd();

    CScintillaView::OnLButtonDown(nFlags, point);
}

LONG COLIDEView::OnAutoCompleteSelected(WPARAM wParam, LPARAM lParam)
{
    // TODO: 在此添加控件通知处理程序代码

    if(m_autoCompleteList.GetSafeHwnd())
    {
		if(lParam < 0 || lParam >= m_autoCompleteList.GetItemCount())
		{
			return 0;
		}

        CString strText;

		if(m_autoCompleteList.IsTemplateFileList())
		{
			m_autoCompleteList.GetTemplateFileItemText(lParam,strText);
			if(lParam == 0)
			{
				m_autoCompleteList.TemplateFileAddString();				
				m_autoCompleteList.SetFocus();
				return 0;
			}
		}
		else //if(m_autoCompleteList.IsKeyWordList())
		{
			m_autoCompleteList.GetAutoCompleteItemText(lParam,strText);
		}        

		CString strSpace;
		GetCurLineBeginSpace(strSpace);
		if(!strSpace.IsEmpty())
		{
			CString strSpaceTemp = _T("\n");
			strSpaceTemp += strSpace;
			strText.Replace(_T("\n"),strSpaceTemp);
		}
		
        GetCtrl().ReplaceSel(strText);

        CloseAutoWnd();

		SetFocus();
    }

    return  0;
}

BOOL COLIDEView::GetCurLineBeginSpace(CString& strSpace)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	BOOL bIsOpenBrace = FALSE;

	TCHAR chLineText[256];
	if(rCtrl.GetCurLine(256,chLineText) > 0)
	{
		int i;
		for(i=0;i<256;++i)
		{
			if((chLineText[i] != _T(' ')) && (chLineText[i] != _T('\t')))
			{
				break;
			}				

			strSpace += chLineText[i];
		}

		if(chLineText[i] == _T('{'))
		{
			bIsOpenBrace  = TRUE;
		}
	}

	return bIsOpenBrace;
}

LONG COLIDEView::OnAutoCompleteCancel(WPARAM wParam, LPARAM lParam)
{
	if(m_autoCompleteList.IsHintList())
	{
		CScintillaCtrl& rCtrl = GetCtrl();

		long lPos = rCtrl.GetCurrentPos();
		rCtrl.SetSel(lPos,lPos);
	}

	return 0;
}

LONG COLIDEView::OnAutoCompleteAddChar(WPARAM wParam, LPARAM lParam)
{
	char chChar = (char)wParam;

	CScintillaCtrl& rCtrl = GetCtrl();
	switch(chChar)
	{
	case VK_BACK:
		{
			long lPos = rCtrl.GetCurrentPos();
			rCtrl.SetSel(lPos,lPos);
			rCtrl.DeleteBack();
			break;
		}		
	default:
		{
			char chText[2];
			chText[0] = chChar;
			chText[1] = 0;
			
			rCtrl.ReplaceSel(chText);

			break;
		}		
	}

	CharAdded();

	return 0;
}

//判断是否为分隔符
BOOL COLIDEView::IsSeparatorWord(char chWord)
{
	switch(chWord)
	{
	case ' ':
	case '\t':
	case '\n':
	case '!':
	case '%':
	case '^':
	case '&':	
	case '*':
	case '(':
	case ')':
	case '-':
	case '+':
	case '=':
	case '{':
	case '}':
	case '[':
	case ']':
	case ':':
	case ';':
	case '\'':
	case '"':
	case '<':
	case '>':
	case ',':
	case '.':
	case '?':
	case '/':
	case '|':
	case '\\':
		return TRUE;
	}

	return FALSE;
}

void COLIDEView::CharAdded()
{
	int nHintStringType_AutoComplete;
	if(m_nSyntaxType == OVST_OASM)
	{		
		nHintStringType_AutoComplete = HST_OASM_AUTO_COMPLETE;
	}
	else if(m_nSyntaxType == OVST_OML)
	{		
		nHintStringType_AutoComplete = HST_OML_AUTO_COMPLETE;
	}
	else
	{
		return;
	}

	CScintillaCtrl& rCtrl = GetCtrl();

	int nStartSel = rCtrl.GetSelectionStart();
	int nEndSel = rCtrl.GetSelectionEnd();	

	//Display the auto completion list
	for(int i=0;i<m_pHintString->GetItemCount(nHintStringType_AutoComplete);++i)
	{
		int nLen = (int)strlen(m_pHintString->GetItemInput(nHintStringType_AutoComplete,i));
		//Get the previous nLen characters and if it is "abcd " case insensitive
		//then display a list which allows "123", "456" or the "789"

		if ((nLen > 0) && (nStartSel == nEndSel) && (nStartSel >= nLen))
		{
			bool bTestPreWord = false;
			if(nStartSel > nLen)
			{
				nLen += 1;
				bTestPreWord = true;
			}

			TextRange tr;
			tr.chrg.cpMin = nStartSel - nLen;
			tr.chrg.cpMax = nEndSel;
			char* pchText = new char[nLen+1];
			pchText[0] = '\0';
			tr.lpstrText = pchText;
			rCtrl.GetTextRange(&tr);

			bool bMatch = false;
			char* pchTextCmp = pchText;
			if(bTestPreWord)
			{
				if(IsSeparatorWord(pchText[0]))
				{
					pchTextCmp ++;
					nLen --;

					if(_strcmpi(pchTextCmp, m_pHintString->GetItemInput(nHintStringType_AutoComplete,i)) == 0)
					{
						bMatch = true;
					}	
				}
			}
			else
			{
				if(_strcmpi(pchTextCmp, m_pHintString->GetItemInput(nHintStringType_AutoComplete,i)) == 0)
				{
					bMatch = true;				
				}
			}			

			if(bMatch)
			{
				rCtrl.SetSel(nStartSel - nLen,nEndSel);	

				CString strItemString;
				strItemString = m_pHintString->GetItemHint(nHintStringType_AutoComplete,i);
				RECT rect = {0,0,0,0};					
				//Display the auto completion list
				if(m_autoCompleteList.Show(&rCtrl,rect,strItemString,m_nSyntaxType,_T('|')))
				{
					AdjustAutoCompleteListSize();
				}

				//if(strItemString.Find(_T('|')) > 0)
				//{					
				//	RECT rect = {0,0,0,0};					
				//	//Display the auto completion list
				//	if(m_autoCompleteList.Show(&rCtrl,rect,strItemString,m_nSyntaxType,_T('|')))
				//	{
				//		AdjustAutoCompleteListSize();
				//	}
				//}
				//else
				//{
				//	CString strReplaceText = strItemString;

				//	CString strSpace;
				//	GetCurLineBeginSpace(strSpace);
				//	if(!strSpace.IsEmpty())
				//	{
				//		CString strData = _T("\n");
				//		strData += strSpace;
				//		strReplaceText.Replace(_T("\n"),strData);
				//	}									

				//	rCtrl.ReplaceSel(strReplaceText);
				//}
			}

			delete[] pchText;

			if(bMatch)
				return;
		}		
	}
}

void COLIDEView::OnCharAdded(SCNotification* pSCNotification)
{	
	CharAdded();
}

//A simple example of call tips
void COLIDEView::OnDwellStart(SCNotification* pSCNotification)
{
	int nHintStringType;
	if(m_nSyntaxType == OVST_OASM)
	{
		nHintStringType = HST_OASM_TIP;
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		nHintStringType = HST_OML_TIP;
	}
	else
	{
		return;
	}


	CScintillaCtrl& rCtrl = GetCtrl();

	//Only display the call tip if the scintilla window has focus
	CWnd* pFocusWnd = GetFocus();
	if (pFocusWnd && (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd()))
	{
		for(int i=0;i<m_pHintString->GetItemCount(nHintStringType);++i)
		{
			int nLen = (int)strlen(m_pHintString->GetItemInput(nHintStringType,i));

			//Get the previous nLen characters and next nLen characters arround
			//the current dwell position and if it is "xxxx " case insensitive
			//then display "this message is xxxx" as a call tip
			TextRange tr;
			tr.chrg.cpMin = max(0, pSCNotification->position - nLen);
			tr.chrg.cpMax = min(pSCNotification->position + nLen, rCtrl.GetLength());
			char* pchText = new char[nLen*2+1];
			pchText[0] = '\0';
			tr.lpstrText = pchText;
			rCtrl.GetTextRange(&tr);
			bool bMatch = false;

			//Display the call tip
			_strupr_s(pchText,nLen*2+1);
			if (strstr(pchText,m_pHintString->GetItemInput(nHintStringType,i)))
			{
				bMatch = true;
				rCtrl.CallTipShow(pSCNotification->position, m_pHintString->GetItemHint(nHintStringType,i));
			}

			delete[] pchText;

			if(bMatch)
				return;
		}		
	}
}

void COLIDEView::OnDwellEnd(SCNotification* /*pSCNotification*/)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//Cancel any outstanding call tip
	if (rCtrl.CallTipActive())
		rCtrl.CallTipCancel();
}

void COLIDEView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	//Let the base class do its thing
	CScintillaView::OnActivate(nState, pWndOther, bMinimized);

	CScintillaCtrl& rCtrl = GetCtrl();	

	//Cancel any outstanding call tip
	if (nState == WA_INACTIVE)
	{
		if(rCtrl.CallTipActive())
		{
			rCtrl.CallTipCancel();
		}		
	}
}

void COLIDEView::GotoPos(int nLine,int nRow)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//rCtrl.GotoLine(nLine);
	rCtrl.GotoPos(rCtrl.GetLineIndentPosition(nLine)+nRow);
}

void COLIDEView::OnChange()
{
	//动态设置行号边距
	ShowLineNoMargin(GetCtrl().GetMarginWidthN(0) > 0);

	BOOL bAutoSave = FALSE;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(m_nSyntaxType == OVST_OASM)
	{
		bAutoSave = pMainFrame->m_systemOption.m_bOASMAutoSave;
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		bAutoSave = pMainFrame->m_systemOption.m_bOMLAutoSave;
	}

	if(bAutoSave && m_nAutoSaveTimer == 0)
	{
		CDocument *pDocument = GetDocument();
		if(pDocument && !pDocument->GetPathName().IsEmpty())
		{
			m_nAutoSaveTimer = 100;
			SetTimer(m_nAutoSaveTimer,10*1000,0);
		}
	}	
}

void COLIDEView::ShowLineNoMargin(bool bShow)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nLineWidth = 0;
	if(bShow)
	{
		int nLineCount = rCtrl.GetLineCount();
		int nWordCount = 1;
		while(nLineCount >= 10)
		{
			++nWordCount;
			nLineCount /= 10;
		}

		int nSize = rCtrl.StyleGetSize(STYLE_DEFAULT);
		int nZoom = rCtrl.GetZoom();
		nSize += nZoom;
		nLineWidth = nSize * nWordCount;
		if(nLineWidth < 4)
		{
			nLineWidth = 4;
		}	
	}
	
	rCtrl.SetMarginWidthN(0, nLineWidth);
}

void COLIDEView::OnZoom(SCNotification* pSCNotification)
{
	//动态设置行号边距
	ShowLineNoMargin(GetCtrl().GetMarginWidthN(0) > 0);
}

void COLIDEView::OnSyntaxWordOperator()
{
	ASSERT_VALID(this);

	UINT nCmdID = static_cast<UINT>(LOWORD(GetCurrentMessage()->wParam));

	CString strData;
	
	switch (nCmdID)
	{	
	case ID_SYNTAX_WORD_COMMENT_LINE:  strData = _T("∥");break;
	case ID_SYNTAX_WORD_COMMENT_BLOCK: strData = _T("「  」");break;
	case ID_SYNTAX_WORD_INCLUDE_TEXT:  strData = _T("《 》");break;
	case ID_SYNTAX_WORD_INCLUDE_LIB:   strData = _T("〈 〉");break;
	case ID_SYNTAX_WORD_SEGMENT_EXTERN:strData = _T("︽\n\n︾");break;
	case ID_SYNTAX_WORD_SEGMENT_DATA:  strData = _T("︻\n\n︼");break;
	case ID_SYNTAX_WORD_SEGMENT_RDATA: strData = _T("﹃\n\n﹄");break;
	case ID_SYNTAX_WORD_SEGMENT_BSS:   strData = _T("﹁\n\n﹂");break;
	case ID_SYNTAX_WORD_SEGMENT_CODE:  strData = _T("︷\n\n︸");break;
	case ID_SYNTAX_WORD_STRUCT:        strData = _T("∑\n{\n}");break;
	case ID_SYNTAX_WORD_UNION:         strData = _T("σ\n{\n}");break;
	case ID_SYNTAX_WORD_ENUM:          strData = _T("ξ\n{\n}");break;
	case ID_SYNTAX_WORD_TYPE_DEFINE:   strData = _T("∈");break;
	case ID_SYNTAX_WORD_MACRO_DEFINE:  strData = _T("∵");break;
	case ID_SYNTAX_WORD_DEGREE:        strData = _T("°");break;
	case ID_SYNTAX_WORD_HDOB:          strData = _T("′");break;
	case ID_SYNTAX_WORD_START:         strData = _T("∏");break;
	case ID_SYNTAX_WORD_FUNCTION:      strData = _T("∫");break;
	case ID_SYNTAX_WORD_LABLE:         strData = _T("～");break;
	case ID_SYNTAX_WORD_ADDR:          strData = _T("＆");break;
	case ID_SYNTAX_WORD_ARRAY_DEFINE:  strData = _T("‥");break;
	case ID_SYNTAX_WORD_ARRAY_MEMBER:  strData = _T("：");break;
	case ID_SYNTAX_WORD_WCHAR:         strData = _T("‘’");break;
	case ID_SYNTAX_WORD_WSTRING:       strData = _T("“”");break;
	case ID_SYNTAX_WORD_BLOCK_CONNECT: strData = _T("﹉\n\n﹍");break;
	case ID_SYNTAX_WORD_LINE_CONNECT:  strData = _T("…");break;
	case ID_SYNTAX_WORD_INSN_JOIN:     strData = _T("ˇ");break;	
	case ID_OPERATOR_IF:               strData = _T("∮");break;
	case ID_OPERATOR_ELSE:             strData = _T("∝");break;
	case ID_OPERATOR_OR:               strData = _T("‖");break;
	case ID_OPERATOR_ALSO:             strData = _T("∪");break;
	case ID_OPERATOR_NEG:              strData = _T("ˉ");break;
	case ID_OPERATOR_CALL:             strData = _T("↘");break;
	case ID_OPERATOR_RET:              strData = _T("↖");break;
	case ID_OPERATOR_JMP:              strData = _T("→");break;
	case ID_OPERATOR_EXIT:             strData = _T("←");break;
	case ID_OPERATOR_BREAK:            strData = _T("↙");break;
	case ID_OPERATOR_CONTINUE:         strData = _T("↗");break;
	case ID_OPERATOR_INTERRUPT:        strData = _T("↑");break;
	case ID_OPERATOR_HLT:              strData = _T("↓");break;
	case ID_OPERATOR_PUSH:             strData = _T("≮");break;
	case ID_OPERATOR_POP:              strData = _T("≯");break;
	case ID_OPERATOR_FLAGR:            strData = _T("§");break;
	case ID_OPERATOR_SET:              strData = _T("∠");break;
	case ID_OPERATOR_ENTER:            strData = _T("▽");break;
	case ID_OPERATOR_LEAVE:            strData = _T("△");break;
	case ID_OPERATOR_CMP:              strData = _T("∞");break;
	case ID_OPERATOR_XCHG:             strData = _T("∽");break;
	case ID_OPERATOR_STRING:           strData = _T("≌");break;
	case ID_OPERATOR_WAIT:             strData = _T("Ω");break;
	case ID_OPERATOR_NOP:              strData = _T("Φ");break;
	case ID_OPERATOR_ABOVE:            strData = _T("∨");break;
	case ID_OPERATOR_BELOW:            strData = _T("∧");break;
	case ID_OPERATOR_GT_ASSIGN:        strData = _T("≥");break;
	case ID_OPERATOR_LT_ASSIGN:        strData = _T("≤");break;
	case ID_OPERATOR_OVERFLOW:         strData = _T("♂");break;
	case ID_OPERATOR_ODD:              strData = _T("♀");break;
	case ID_OPERATOR_ZERO:             strData = _T("◎");break;
	case ID_OPERATOR_FWAIT:            strData = _T("ω");break;
	case ID_OPERATOR_FNOP:             strData = _T("φ");break;
	case ID_OPERATOR_DIVISOR:          strData = _T("≈");break;
	case ID_OPERATOR_SQUARE_ROOT:      strData = _T("√");break;
	case ID_OPERATOR_PI:               strData = _T("π");break;
	case ID_OPERATOR_LOG:              strData = _T("㏒");break;
	case ID_OPERATOR_LN:               strData = _T("㏑");break;
	case ID_OPERATOR_POWER:            strData = _T("＾");break;	
	case ID_OPERATOR_MUL:              strData = _T("×");break;
	case ID_OPERATOR_DIV:              strData = _T("÷");break;
	case ID_OPERATOR_SIGN:             strData = _T("±");break;
		break;
	default:
		return;
	}

	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.ReplaceSel(strData);
}

void COLIDEView::OnInsertRegister()
{
	ASSERT_VALID(this);

	UINT nCmdID = static_cast<UINT>(LOWORD(GetCurrentMessage()->wParam));

	CString strData;

	switch (nCmdID)
	{
	case ID_INSERT_REG_AL:    strData = _T("累加低 ");break;
	case ID_INSERT_REG_AH:    strData = _T("累加高 ");break;
	case ID_INSERT_REG_BL:    strData = _T("基数低 ");break;
	case ID_INSERT_REG_BH:    strData = _T("基数高 ");break;
	case ID_INSERT_REG_CL:    strData = _T("计数低 ");break;
	case ID_INSERT_REG_CH:    strData = _T("计数高 ");break;
	case ID_INSERT_REG_DL:    strData = _T("数据低 ");break;
	case ID_INSERT_REG_DH:    strData = _T("数据高 ");break;
	case ID_INSERT_REG_AX:    strData = _T("累加16 ");break;
	case ID_INSERT_REG_BX:    strData = _T("基数16 ");break;
	case ID_INSERT_REG_CX:    strData = _T("计数16 ");break;
	case ID_INSERT_REG_DX:    strData = _T("数据16 ");break;
	case ID_INSERT_REG_BP:    strData = _T("基址16 ");break;
	case ID_INSERT_REG_SP:    strData = _T("栈址16 ");break;
	case ID_INSERT_REG_SI:    strData = _T("源址16 ");break;
	case ID_INSERT_REG_DI:    strData = _T("的址16 ");break;
	case ID_INSERT_REG_EAX:   strData = _T("累加32 ");break;
	case ID_INSERT_REG_EBX:   strData = _T("基数32 ");break;
	case ID_INSERT_REG_ECX:   strData = _T("计数32 ");break;
	case ID_INSERT_REG_EDX:   strData = _T("数据32 ");break;
	case ID_INSERT_REG_EBP:   strData = _T("基址32 ");break;
	case ID_INSERT_REG_ESP:   strData = _T("栈址32 ");break;
	case ID_INSERT_REG_ESI:   strData = _T("源址32 ");break;
	case ID_INSERT_REG_EDI:   strData = _T("的址32 ");break;
	case ID_INSERT_REG_CS:    strData = _T("码段 ");break;
	case ID_INSERT_REG_DS:    strData = _T("数段 ");break;
	case ID_INSERT_REG_ES:    strData = _T("附段 ");break;
	case ID_INSERT_REG_SS:    strData = _T("栈段 ");break;
	case ID_INSERT_REG_FS:    strData = _T("志段 ");break;
	case ID_INSERT_REG_GS:    strData = _T("全段 ");break;
	case ID_INSERT_REG_CR0:   strData = _T("控0 ");break;
	case ID_INSERT_REG_CR2:   strData = _T("控2 ");break;
	case ID_INSERT_REG_CR3:   strData = _T("控3 ");break;
	case ID_INSERT_REG_CR4:   strData = _T("控4 ");break;
	case ID_INSERT_REG_DR0:   strData = _T("调0 ");break;
	case ID_INSERT_REG_DR1:   strData = _T("调1 ");break;
	case ID_INSERT_REG_DR2:   strData = _T("调2 ");break;
	case ID_INSERT_REG_DR3:   strData = _T("调3 ");break;
	case ID_INSERT_REG_DR6:   strData = _T("调6 ");break;
	case ID_INSERT_REG_DR7:   strData = _T("调7 ");break;
	case ID_INSERT_REG_TR0:   strData = _T("任0 ");break;
	case ID_INSERT_REG_TR1:   strData = _T("任1 ");break;
	case ID_INSERT_REG_TR2:   strData = _T("任2 ");break;
	case ID_INSERT_REG_TR3:   strData = _T("任3 ");break;
	case ID_INSERT_REG_TR4:   strData = _T("任4 ");break;
	case ID_INSERT_REG_TR5:   strData = _T("任5 ");break;
	case ID_INSERT_REG_TR6:   strData = _T("任6 ");break;
	case ID_INSERT_REG_TR7:   strData = _T("任7 ");break;
	case ID_INSERT_REG_ST0:   strData = _T("浮0 ");break;
	case ID_INSERT_REG_ST1:   strData = _T("浮1 ");break;
	case ID_INSERT_REG_ST2:   strData = _T("浮2 ");break;
	case ID_INSERT_REG_ST3:   strData = _T("浮3 ");break;
	case ID_INSERT_REG_ST4:   strData = _T("浮4 ");break;
	case ID_INSERT_REG_ST5:   strData = _T("浮5 ");break;
	case ID_INSERT_REG_ST6:   strData = _T("浮6 ");break;
	case ID_INSERT_REG_ST7:   strData = _T("浮7 ");break;
	case ID_INSERT_REG_MM0:   strData = _T("媒0 ");break;
	case ID_INSERT_REG_MM1:   strData = _T("媒1 ");break;
	case ID_INSERT_REG_MM2:   strData = _T("媒2 ");break;
	case ID_INSERT_REG_MM3:   strData = _T("媒3 ");break;
	case ID_INSERT_REG_MM4:   strData = _T("媒4 ");break;
	case ID_INSERT_REG_MM5:   strData = _T("媒5 ");break;
	case ID_INSERT_REG_MM6:   strData = _T("媒6 ");break;
	case ID_INSERT_REG_MM7:   strData = _T("媒7 ");break;
	case ID_INSERT_REG_XMM0:  strData = _T("流0 ");break;
	case ID_INSERT_REG_XMM1:  strData = _T("流1 ");break;
	case ID_INSERT_REG_XMM2:  strData = _T("流2 ");break;
	case ID_INSERT_REG_XMM3:  strData = _T("流3 ");break;
	case ID_INSERT_REG_XMM4:  strData = _T("流4 ");break;
	case ID_INSERT_REG_XMM5:  strData = _T("流5 ");break;
	case ID_INSERT_REG_XMM6:  strData = _T("流6 ");break;
	case ID_INSERT_REG_XMM7:  strData = _T("流7 ");break;
	default:
		return;
	}

	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.ReplaceSel(strData);
}

void COLIDEView::OnAddSentence()
{
	ASSERT_VALID(this);

	UINT nCmdID = static_cast<UINT>(LOWORD(GetCurrentMessage()->wParam));

	CString strData;

	if(m_nSyntaxType == OVST_OASM)
	{
		switch (nCmdID)
		{
		case ID_SENTENCE_SEGMENT_DATA:
			strData = _T(".数据段\n{\n}");
			break;
		case ID_SENTENCE_SEGMENT_RDATA:
			strData = _T(".只读段\n{\n}");
			break;
		case ID_SENTENCE_SEGMENT_BSS:
			strData = _T(".预留段\n{\n}");
			break;
		case ID_SENTENCE_SEGMENT_EXTERN:
			strData = _T(".引用段\n{\n}");
			break;
		case ID_SENTENCE_SEGMENT_CODE:
			strData = _T(".代码段\n{\n}");
			break;
		case ID_SENTENCE_FUNCTION:
			strData = _T("函数 函数名()\n{\n}");
			break;
		case ID_SENTENCE_IF:
			strData = _T("如果()\n{\n}");
			break;
		case ID_SENTENCE_IF_ELSE:
			strData = _T("如果()\n{\n}\n否则\n{\n}");
			break;
		case ID_SENTENCE_IF_ELSEIF_ELSE:
			strData = _T("如果()\n{\n}\n否则如果()\n{\n}\n否则\n{\n}");
			break;
		case ID_SENTENCE_WHILE:
			strData = _T("循环()\n{\n}");
			break;
		default:
			return;
		}
	}
	else if(m_nSyntaxType == OVST_OML)
	{
		switch (nCmdID)
		{
		case ID_OML_SENTENCE_FUNCTION:
			strData = _T("函数 函数名()\n{\n}");
			break;
		case ID_OML_SENTENCE_IF:
			strData = _T("如果()\n{\n}");
			break;
		case ID_OML_SENTENCE_IF_ELSE:
			strData = _T("如果()\n{\n}\n否则\n{\n}");
			break;
		case ID_OML_SENTENCE_IF_ELSEIF_ELSE:
			strData = _T("如果()\n{\n}\n否则如果()\n{\n}\n否则\n{\n}");
			break;
		case ID_OML_SENTENCE_WHILE:
			strData = _T("循环()\n{\n}");
			break;
		default:
			return;
		}
	}	

	CScintillaCtrl& rCtrl = GetCtrl();
	TCHAR chLineText[256];
	int nLineLength = rCtrl.GetCurLine(256,chLineText);
	if(nLineLength > 0)
	{
		CString strTemp = _T("\n");
		for(int i=0;i<nLineLength;++i)
		{
			strTemp += (chLineText[nLineLength] == _T('\t'))?_T('\t'):_T(' ');
		}
		strData.Replace(_T("\n"),strTemp);
	}
	
	rCtrl.ReplaceSel(strData);
}

void COLIDEView::OnSyntaxHighLightType()
{
	ASSERT_VALID(this);

	UINT nCmdID = static_cast<UINT>(LOWORD(GetCurrentMessage()->wParam));

	switch (nCmdID)
	{
	case ID_HIGH_LIGHT_OASM:
		m_nSyntaxType = OVST_OASM;
		break;
	case ID_HIGH_LIGHT_OML:
		m_nSyntaxType = OVST_OML;
		break;
	default:
		return;
	}

	UpdateAllStyle();
}

void COLIDEView::OnTabAdd()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strSelText = rCtrl.GetSelText();
	CString strNewText = _T("    ");
	strNewText += strSelText;
	strNewText.Replace(_T("\n"),_T("\n    "));		

	long lSelStart = rCtrl.GetSelectionStart();
	rCtrl.ReplaceSel(strNewText);	
	rCtrl.SetSel(lSelStart,rCtrl.GetCurrentPos());
}

void COLIDEView::OnTabSub()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strSelText = rCtrl.GetSelText();
	strSelText.Replace(_T("\n\t"),_T("\n    "));
	for(int i=0;i<4;++i)
	{
		if(strSelText.GetLength() < 1)
			break;

		if(strSelText[0] == _T(' '))
		{
			strSelText = strSelText.Right(strSelText.GetLength() - 1);
		}
		strSelText.Replace(_T("\n "),_T("\n"));
	}

	long lSelStart = rCtrl.GetSelectionStart();
	rCtrl.ReplaceSel(strSelText);	
	rCtrl.SetSel(lSelStart,rCtrl.GetCurrentPos());
}

void COLIDEView::OnCommentAdd()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strSelText = rCtrl.GetSelText();
	CString strTemp = _T("//");
	strTemp += strSelText;
	strSelText = strTemp;

	int nPos = 0;
	while(true)
	{
		nPos = strSelText.Find(_T('\n'),nPos);
		if((nPos < 0) || (strSelText.GetLength() == nPos+1))			
			break;

		++nPos;
		if(strSelText[nPos] == _T('\t'))
		{
			++nPos;
		}
		else
		{
			CString strMid4 = strSelText.Mid(nPos,4);
			int i = 0;
			for(i=0;i<strMid4.GetLength();++i)
			{
				if(strMid4[i] != _T(' '))
					break;

				++nPos;
			}
		}	

		CString strNew = strSelText.Left(nPos);
		strNew += _T("//");
		strNew += strSelText.Right(strSelText.GetLength() - nPos);
		strSelText = strNew;
	}

	long lSelStart = rCtrl.GetSelectionStart();
	rCtrl.ReplaceSel(strSelText);
	rCtrl.SetSel(lSelStart,rCtrl.GetCurrentPos());	
}

void COLIDEView::OnCommentSub()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strSelText = rCtrl.GetSelText();	
	if(strSelText.GetLength() < 2)
		return;

	if(strSelText.Left(2) == _T("//"))
	{
		strSelText = strSelText.Right(strSelText.GetLength() - 2);
	}
	
	int nPos = 0;
	while(true)
	{
		nPos = strSelText.Find(_T('\n'),nPos);
		if((nPos < 0) || (strSelText.GetLength() == nPos+1))
			break;

		++nPos;
		while((strSelText[nPos] == _T(' ')) || (strSelText[nPos] == _T('\t')))
		{
			++nPos;
		}

		if(strSelText.Mid(nPos,2) == _T("//"))
		{
			CString strNew = strSelText.Left(nPos);
			strNew += strSelText.Right(strSelText.GetLength() - nPos - 2);
			strSelText = strNew;
		}
	}
	
	long lSelStart = rCtrl.GetSelectionStart();
	rCtrl.ReplaceSel(strSelText);	
	rCtrl.SetSel(lSelStart,rCtrl.GetCurrentPos());
}

void COLIDEView::OnFastInputList()
{
	RECT rect= {0,0,0,0};
	if(m_autoCompleteList.Show(&GetCtrl(),rect,&((CMainFrame*)AfxGetMainWnd())->m_autoCompleteString,m_nSyntaxType,FALSE))
	{
		AdjustAutoCompleteListSize();
	}
}

void COLIDEView::OnFileTemplateList()
{
	RECT rect= {0,0,0,0};
	if(m_autoCompleteList.Show(&GetCtrl(),rect,&((CMainFrame*)AfxGetMainWnd())->m_autoCompleteString,m_nSyntaxType,TRUE))
	{
		AdjustAutoCompleteListSize();
	}
}

#include "./Controls/XFolderDialog/XFolderDialog.h"
#include "./Common/Global.h"
#include "./Common/Common.h"

void COLIDEView::OnIncludeFile()
{
	// TODO: 在此添加命令处理程序代码

	CScintillaCtrl& rCtrl = GetCtrl();
	CString strData;

	UINT nCmdID = static_cast<UINT>(LOWORD(GetCurrentMessage()->wParam));

	if(m_nSyntaxType == OVST_OASM)
	{
		if(nCmdID == ID_INCLUDE_OASM_HEAD)
		{		
			strData = _T(".包含文<*oasm32.oah>\n");
			rCtrl.ReplaceSel(strData);

			return;
		}

		if(nCmdID == ID_INCLUDE_GENERAL)
		{
			strData = _T(".包含文<*windows.oah>\n.包含文<*user32.oah>\n.包含文<*kernel32.oah>\n.引用库<*user32.lib>\n.引用库<*kernel32.lib>\n");
			rCtrl.ReplaceSel(strData);

			return;
		}

		CString strCurFile = GetDocument()->GetPathName();

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CString strOASMPath = pMainFrame->m_systemOption.m_strOasmPath;
		CString strIncludePath,strLibPath;	
		if(!strOASMPath.IsEmpty())
		{	
			//如果是相对路径
			if (strOASMPath[0] == _T('.'))
			{
				GetAbsolutePathByRelativePath(strOASMPath,pMainFrame->GetAppDirectory());
			}

			int nDotPos = strOASMPath.ReverseFind(_T('\\'));
			CString strSysPath = strOASMPath.Left(nDotPos);	
			strIncludePath = strSysPath + _T("\\include\\");
			strLibPath = strSysPath + _T("\\lib\\");
		}	

		CString   szFileFilter1 =  
			_T("O汇编头文件(*.oah *.oam)|*.oah;*.oam|")
			_T("所有文件(*.*)|*.*|");
		CString   szFileFilter2 =  
			_T("库文件(*.lib)|*.lib|")
			_T("所有文件(*.*)|*.*|");	

		LPCTSTR lpstrTitle;
		LPCTSTR pszFileFilter;	
		BOOL bIsLibFile = FALSE;

		CString strInitDir;

		switch (nCmdID)
		{
		case ID_INCLUDE_CUR_TEXT:
			bIsLibFile = FALSE;
			if(!strCurFile.IsEmpty())
			{
				strInitDir = strCurFile.Left(strCurFile.ReverseFind(_T('\\')));
			}		
			lpstrTitle = _T("包含本地文件");
			pszFileFilter = szFileFilter1;
			break;
		case ID_INCLUDE_SYS_TEXT:
			bIsLibFile = FALSE;
			strInitDir = strIncludePath;
			lpstrTitle = _T("包含系统文件");
			pszFileFilter = szFileFilter1;
			break;
		case ID_INCLUDE_CUR_LIB:
			bIsLibFile = TRUE;
			if(!strCurFile.IsEmpty())
			{
				strInitDir = strCurFile.Left(strCurFile.ReverseFind(_T('\\')));
			}
			lpstrTitle = _T("引用本地库文件");		
			pszFileFilter = szFileFilter2;
			break;
		case ID_INCLUDE_SYS_LIB:
			bIsLibFile = TRUE;
			strInitDir = strLibPath;
			lpstrTitle = _T("引用系统库文件");		
			pszFileFilter = szFileFilter2;
			break;
		default:
			ASSERT(FALSE);
		}	

		CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,pszFileFilter,this);   
		dlg.m_ofn.lpstrInitialDir = strInitDir;
		dlg.m_ofn.lpstrTitle = lpstrTitle;

		if(dlg.DoModal() == IDOK)
		{
			POSITION   pos;
			for(pos=dlg.GetStartPosition();pos;)
			{  
				CString   str;
				str=dlg.GetNextPathName(pos);

				switch (nCmdID)
				{
				case ID_INCLUDE_CUR_TEXT:
					if(!strCurFile.IsEmpty())
					{
						GetRelativePath(strCurFile,str);
					}
					strData = _T(".包含文<");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_INCLUDE_SYS_TEXT:
					if(!strIncludePath.IsEmpty())
					{
						GetRelativePath(strIncludePath,str);
					}				
					strData = _T(".包含文<*");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_INCLUDE_CUR_LIB:
					if(!strCurFile.IsEmpty())
					{
						GetRelativePath(strCurFile,str);
					}
					strData = _T(".引用库<");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_INCLUDE_SYS_LIB:
					if(!strLibPath.IsEmpty())
					{
						GetRelativePath(strLibPath,str);
					}				
					strData = _T(".引用库<*");
					strData += str;
					strData += _T(">\n");
					break;
				}

				rCtrl.ReplaceSel(strData);
			}
		}
	}	
	else if(m_nSyntaxType == OVST_OML)
	{
		CString strCurFile = GetDocument()->GetPathName();

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CString strOMLPath = pMainFrame->m_systemOption.m_strOMLPath;
		CString strIncludePath,strLibPath;	
		if(!strOMLPath.IsEmpty())
		{	
			//如果是相对路径
			if (strOMLPath[0] == _T('.'))
			{
				GetAbsolutePathByRelativePath(strOMLPath,pMainFrame->GetAppDirectory());
			}

			int nDotPos = strOMLPath.ReverseFind(_T('\\'));
			CString strSysPath = strOMLPath.Left(nDotPos);	
			strIncludePath = strSysPath + _T("\\include\\");
			strLibPath = strSysPath + _T("\\lib\\");
		}	

		CString   szFileFilter1 =  
			_T("O中间语言文件(*.omh *.omp)|*.omh;*.omp|")
			_T("所有文件(*.*)|*.*|");
		CString   szFileFilter2 =  
			_T("库文件(*.lib)|*.lib|")
			_T("所有文件(*.*)|*.*|");	

		LPCTSTR lpstrTitle;
		LPCTSTR pszFileFilter;	
		BOOL bIsLibFile = FALSE;

		CString strInitDir;

		switch (nCmdID)
		{
		case ID_OML_INCLUDE_CUR_TEXT:
			bIsLibFile = FALSE;
			if(!strCurFile.IsEmpty())
			{
				strInitDir = strCurFile.Left(strCurFile.ReverseFind(_T('\\')));
			}		
			lpstrTitle = _T("包含本地文件");
			pszFileFilter = szFileFilter1;
			break;
		case ID_OML_INCLUDE_SYS_TEXT:
			bIsLibFile = FALSE;
			strInitDir = strIncludePath;
			lpstrTitle = _T("包含系统文件");
			pszFileFilter = szFileFilter1;
			break;
		case ID_OML_INCLUDE_CUR_LIB:
			bIsLibFile = TRUE;
			if(!strCurFile.IsEmpty())
			{
				strInitDir = strCurFile.Left(strCurFile.ReverseFind(_T('\\')));
			}
			lpstrTitle = _T("引用本地库文件");		
			pszFileFilter = szFileFilter2;
			break;
		case ID_OML_INCLUDE_SYS_LIB:
			bIsLibFile = TRUE;
			strInitDir = strLibPath;
			lpstrTitle = _T("引用系统库文件");		
			pszFileFilter = szFileFilter2;
			break;
		default:
			ASSERT(FALSE);
		}	

		CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,pszFileFilter,this);   
		dlg.m_ofn.lpstrInitialDir = strInitDir;
		dlg.m_ofn.lpstrTitle = lpstrTitle;

		if(dlg.DoModal() == IDOK)
		{
			POSITION   pos;
			for(pos=dlg.GetStartPosition();pos;)
			{  
				CString   str;
				str=dlg.GetNextPathName(pos);

				switch (nCmdID)
				{
				case ID_OML_INCLUDE_CUR_TEXT:
					if(!strCurFile.IsEmpty())
					{
						GetRelativePath(strCurFile,str);
					}
					strData = _T(".包含文<");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_OML_INCLUDE_SYS_TEXT:
					if(!strIncludePath.IsEmpty())
					{
						GetRelativePath(strIncludePath,str);
					}				
					strData = _T(".包含文<*");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_OML_INCLUDE_CUR_LIB:
					if(!strCurFile.IsEmpty())
					{
						GetRelativePath(strCurFile,str);
					}
					strData = _T(".引用库<");
					strData += str;
					strData += _T(">\n");
					break;
				case ID_OML_INCLUDE_SYS_LIB:
					if(!strLibPath.IsEmpty())
					{
						GetRelativePath(strLibPath,str);
					}				
					strData = _T(".引用库<*");
					strData += str;
					strData += _T(">\n");
					break;
				}

				rCtrl.ReplaceSel(strData);
			}
		}
	}
}

void COLIDEView::OnSetBreakPoint()
{
	// TODO: 在此添加命令处理程序代码

	CSyntaxCtrl& rCtrl = GetCtrl();	
	int nLine = rCtrl.GetCurrentLine();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int nBreakLine = 0;
	DEBUGGER_BREAKPOINT bp;
	bp.m_bInstalled = true;
	wcscpy(bp.m_tchFileName,GetDocument()->GetPathName());
	bp.m_nLine = nLine;

	if(LineHasBreakPoint(nLine))
	{
		//没有在调试状态
		if(pMainFrame->m_dwDebugThreadID == 0)
		{
			DeleteBreakPoint(nLine);
		}
		else
		{			
			bp.m_bInstalled = false;
			SendThreadMessage(pMainFrame->m_dwDebugThreadID,WM_DEBUGGER_INSTALLBREAKPOINTFROMFILE,(WPARAM)&bp,NULL);
			nBreakLine = bp.m_nLine;

			if(nBreakLine == nLine)
			{
				DeleteBreakPoint(nBreakLine);
			}
		}		
	}
	else
	{
		//表示没有在调试状态
		if(pMainFrame->m_dwDebugThreadID == 0)
		{
			SetBreakPoint(nLine);
		}
		else
		{
			bp.m_bInstalled = true;	
			SendThreadMessage(pMainFrame->m_dwDebugThreadID,WM_DEBUGGER_INSTALLBREAKPOINTFROMFILE,(WPARAM)&bp,NULL);
			nBreakLine = bp.m_nLine;

			if(nBreakLine >= 0)
			{
				SetBreakPoint(nBreakLine);
			}
		}				
	}
}

LRESULT COLIDEView::OnDebuggerMoveTo(WPARAM wParam,LPARAM lParam)
{
	CSyntaxCtrl& rCtrl = GetCtrl();	
	
	m_nDebuggerLine = wParam;	
	rCtrl.GotoLine(m_nDebuggerLine);
	rCtrl.MarkerAdd(m_nDebuggerLine, DEBUGGER_CUR_LINE);

	return 1;
}

LRESULT COLIDEView::OnDebuggerContinue(WPARAM wParam,LPARAM lParam)
{
	m_nDebuggerLine = -1;
	GetCtrl().MarkerDeleteAll(DEBUGGER_CUR_LINE);

	return 1;
}

LRESULT COLIDEView::OnDebuggerEnd(WPARAM wParam,LPARAM lParam)
{
	CSyntaxCtrl& rCtrl = GetCtrl();	
	rCtrl.MarkerDeleteAll(DEBUGGER_CUR_LINE);

	return 1;
}

bool COLIDEView::LineHasMarker(int line,int marker)
{
	if(line < 0)
	{
		line = GetCtrl().GetCurrentLine();
	}

	return GetCtrl().MarkerGet(line) & (1 << marker);
}

int COLIDEView::GetLineCount()
{
	return GetCtrl().GetLineCount();
}

bool COLIDEView::LineHasBreakPoint(int nLine)
{
	return  LineHasMarker(nLine,BREAKPOINT_MARKER);
}

void COLIDEView::SetBreakPoint(int nLine)
{
	GetCtrl().MarkerAdd(nLine, BREAKPOINT_MARKER);
}

void COLIDEView::DeleteBreakPoint(int nLine)
{
	GetCtrl().MarkerDelete(nLine, BREAKPOINT_MARKER);
}

void COLIDEView::DeleteAllBreakPoint()
{
	int nLineCount = GetLineCount();
	for(int i=0;i<nLineCount;++i)
	{
		if(LineHasBreakPoint(i))
		{
			DeleteBreakPoint(i);
		}
	}
}

void COLIDEView::OnUpdateHighLightOasm(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(m_nSyntaxType == OVST_OASM);
}

void COLIDEView::OnUpdateHighLightOml(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(m_nSyntaxType == OVST_OML);
}

void COLIDEView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(nIDEvent == m_nAutoSaveTimer)
	{
		GetDocument()->DoFileSave();

		KillTimer(m_nAutoSaveTimer);
		m_nAutoSaveTimer = 0;
	}	

	CScintillaView::OnTimer(nIDEvent);
}

void COLIDEView::OnDestroy()
{
	if(m_nAutoSaveTimer)
	{
		KillTimer(m_nAutoSaveTimer);
		m_nAutoSaveTimer = 0;
	}

	CScintillaView::OnDestroy();	
}
