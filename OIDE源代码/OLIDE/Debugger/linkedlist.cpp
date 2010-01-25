
#include "stdafx.h"
#include "linkedlist.h"
//#include <assert.h>

//CLinkOper类
CLinkOper::CLinkOper()
{	
	InitList();
}

CLinkOper::~CLinkOper()
{
	DestroyList();
}

bool  CLinkOper::InitList()
{
	m_pRootElement = new CLinkElement();
	if(m_pRootElement == 0)
		return false;

	m_pCurElement = m_pRootElement;
	m_pLastElement = 0;

	m_nLength = 0;

	return true;
}

bool CLinkOper::ClearList()
{
	if(m_pRootElement == 0)
		return false;

	m_pCurElement = m_pRootElement->GetNext();
	while(m_pCurElement)
	{
		m_pRootElement->SetNext(m_pCurElement->GetNext());

		DeleteData(m_pCurElement->GetData());
		delete m_pCurElement;

		m_pCurElement = m_pRootElement->GetNext();
	}

	m_pCurElement = 0;
	m_pLastElement = 0;
	m_nLength = 0;

	return true;
}

bool CLinkOper::DestroyList()
{
	if(!ClearList())
	{
		return false;
	}

	if(m_pRootElement)
	{
		delete m_pRootElement;
		m_pRootElement = 0;
	}

	return true;
}

CLinkElement* CLinkOper::PushData(void* data)
{
	if(m_pLastElement==0)
	{
		m_pLastElement = m_pRootElement;
	}

	InsertNode(m_pLastElement,data);

	return m_pLastElement;
}

CLinkElement* CLinkOper::InsertNode(CLinkElement* pAfterWhich,void* pData)
{
	CLinkElement* newNode = new CLinkElement;
	if(newNode)
	{
		newNode->SetData(pData);
		newNode->SetNext(pAfterWhich->GetNext());
		pAfterWhich->SetNext(newNode);

		m_pCurElement = newNode;

		if(pAfterWhich == m_pLastElement)
		{
			m_pLastElement = newNode;
		}

		++m_nLength;

		return newNode;
	}

	return 0;
}

bool CLinkOper::RemoveData(void* pData)
{
	if(m_pRootElement == 0)
		return false;

	CLinkElement* pPreElement = m_pRootElement;
	CLinkElement* pCurElement = pPreElement->GetNext();
	while(pCurElement)
	{
		if(pCurElement->GetData() == pData)
		{
			pPreElement->SetNext(pCurElement->GetNext());
			if(pCurElement == m_pLastElement)
			{
				m_pLastElement = pPreElement;
			}

			pCurElement->SetNext(NULL);
			DeleteData(pCurElement->GetData());
			delete pCurElement;

			m_pCurElement = pPreElement;

			--m_nLength;

			return true;
		}		

		pPreElement = pCurElement;
		pCurElement = pCurElement->GetNext();
	}

	return false;
}

////遍历元素使用下列形式
//void CLinkOper::Travel()
//{
//	void* pData;
//	for(GetFirstElement();!isEnd();GetNextElement())
//	{
//		pData = GetCurElement()->GetData();
//	}
//}


