
#ifndef _READ_DEBUG_DATA_H_
#define _READ_DEBUG_DATA_H_

#include "DebugData.h"

enum DEBUG_NODE_TYPE
{
	DEBUG_NODE_TYPE_NULL = 0,
	DEBUG_NODE_TYPE_LINE = 1,
	DEBUG_NODE_TYPE_VAR  = 2,
	DEBUG_NODE_TYPE_END,
};

class CReadDebugData
{
public:
	CReadDebugData();
	~CReadDebugData();

	CStringArray m_strarrSourceFileNameList;
	CDebugDataItemLine m_debugDataItemLine;

	unsigned int m_uiCodeSegmentAddr;
	unsigned int m_uiCodeSegmentLength;
	unsigned int m_uiDataSegmentAddr;
	unsigned int m_uiDataSegmentLength;

	bool Read(TCHAR* pchPEFileName);
	DEBUG_DATA_ITEM_LINE* GetMatchLineItem(TCHAR* pchFileName,int nLine,bool bMatchLine);
	DEBUG_DATA_ITEM_LINE* GetMatchAddrItem(unsigned long ulAddr);

private:

	int SearchSourceFileNameList(const CString& str);
};

#endif //_READ_DEBUG_DATA_H_