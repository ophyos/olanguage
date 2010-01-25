
// OLIDEDoc.cpp : COLIDEDoc 类的实现
//

#include "stdafx.h"
#include "OLIDE.h"

#include "OLIDEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COLIDEDoc

IMPLEMENT_DYNCREATE(COLIDEDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(COLIDEDoc, CScintillaDoc)
END_MESSAGE_MAP()


// COLIDEDoc 构造/析构

COLIDEDoc::COLIDEDoc()
{
	// TODO: 在此添加一次性构造代码

}

COLIDEDoc::~COLIDEDoc()
{
}


// COLIDEDoc 诊断

#ifdef _DEBUG
void COLIDEDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void COLIDEDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG


// COLIDEDoc 命令
