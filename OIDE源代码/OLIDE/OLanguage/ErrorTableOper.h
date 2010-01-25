#pragma once

#include "../../OLangue/syserrorattr.h"

//错误处理接口
typedef int (* GETERRORCOUNT)();
typedef void (* CLEARERRORTABLE)();
typedef SYS_ERROR_POSITION (* GETFIRSTSYSERROR)();
typedef SYS_ERROR_POSITION (* GETENDSYSERROR)();
typedef void (* GETSYSERRORATTR)(SYS_ERROR_POSITION&,int&,char*,char*,char*,char*,char*);


//CErrorInfo类
class CErrorInfo
{
	//类构造
public:
	CErrorInfo();
	~CErrorInfo();

	//类属性
	int     m_nErrorCode;
	CString m_strErrorCodeInfo;
	CString m_strErrorSymbol;
	CString m_strErrorOwner;
	CString m_strErrorFileName;
	CString m_strConflictOwner;
};

class CErrorTableOper
{
public:
	CErrorTableOper(void);
	~CErrorTableOper(void);

public:

	//错误处理
	static int  GetErrorCount();
	static void ClearErrorTable();
	static SYS_ERROR_POSITION GetFirstSysError();
	static SYS_ERROR_POSITION GetEndSysError();
	static void GetSysErrorAttr(SYS_ERROR_POSITION& posSysError,CErrorInfo& errorInfo);
};


