
// OLIDEDoc.h : COLIDEDoc 类的接口
//


#pragma once

#include "./Controls/scintilla/ScintillaDocView.h"

class COLIDEDoc : public CScintillaDoc
{
protected: // 仅从序列化创建
	COLIDEDoc();
	DECLARE_DYNCREATE(COLIDEDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	
// 实现
public:
	virtual ~COLIDEDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


