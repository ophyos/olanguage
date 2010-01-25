
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

//CLinkElement类
class CLinkElement
{
	//类构造
public:
	CLinkElement(){ SetNext(0); SetData(0);}
	virtual ~CLinkElement(){}

private:

	CLinkElement* m_pNextElement;

	void* m_pData; 

public:

	CLinkElement* GetNext(){ return m_pNextElement;}
	void SetNext(CLinkElement* pNextElement){ m_pNextElement = pNextElement;};

	void* GetData(){ return m_pData;}
	void SetData(void* pData){ m_pData = pData;};
};

//CLinkOper类
class CLinkOper
{
	//类构造
public:
	CLinkOper();
	virtual ~CLinkOper();

	//类属性
private:
	CLinkElement* m_pRootElement;
	CLinkElement* m_pLastElement;
	CLinkElement* m_pCurElement;

	int m_nLength;

	//成员函数
public:

	bool  InitList();
	bool  ClearList();
	bool  DestroyList();

	CLinkElement* PushData(void* data);
	
	CLinkElement* GetCurElement(){ return m_pCurElement;};
	void SetCurElement(CLinkElement* pCurElement){ m_pCurElement = pCurElement;};
	CLinkElement* GetLastElement(){ return m_pLastElement;};
	CLinkElement* InsertNode(CLinkElement* pAfterWhich,void* pData);		
	bool RemoveData(void* pData);
	int  GetLength(){ return m_nLength;};

	//move
	CLinkElement* GetFirstElement(){ m_pCurElement = m_pRootElement->GetNext();return m_pCurElement;};
	CLinkElement* GetNextElement(){ if(m_pCurElement == 0)return 0;m_pCurElement = m_pCurElement->GetNext();return m_pCurElement;}

	bool  isEnd(){ return (m_pCurElement==0);}
	bool  isEmpty(){ return (m_nLength == 0); }

protected:

	virtual void DeleteData(void* pData){ if(pData){delete pData;} }
};



#endif //_LINKED_LIST_H_