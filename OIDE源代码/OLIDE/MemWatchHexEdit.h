#pragma once
#include "./controls/hexedit/hexeditbase.h"

class CMemWatchHexEdit : public CHexEditBase
{
public:
	CMemWatchHexEdit(void);
	~CMemWatchHexEdit(void);

	UINT GetDataOffsetFromPoint(POINT point);

protected:

	virtual void MoveCaretPos(POINT point);
};
