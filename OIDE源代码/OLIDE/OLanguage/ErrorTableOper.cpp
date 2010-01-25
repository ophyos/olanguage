#include "StdAfx.h"
#include ".\errortableoper.h"
#include ".\olinterface.h"


CErrorInfo::CErrorInfo(void)
{
	m_nErrorCode = 0;
	m_strErrorCodeInfo.Empty();
	m_strErrorSymbol.Empty();
	m_strErrorOwner.Empty();
	m_strErrorFileName.Empty();
	m_strConflictOwner.Empty();
}

CErrorInfo::~CErrorInfo(void)
{
}


CErrorTableOper::CErrorTableOper(void)
{
}

CErrorTableOper::~CErrorTableOper(void)
{
}

//错误处理
int CErrorTableOper::GetErrorCount()
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	GETERRORCOUNT lpfnGetErrorCount = (GETERRORCOUNT)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceGetErrorCount");
	if(lpfnGetErrorCount == NULL)
		return NULL;

	return lpfnGetErrorCount();
}

void CErrorTableOper::ClearErrorTable()
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	CLEARERRORTABLE lpfnClearErrorTable = (CLEARERRORTABLE)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceClearErrorTable");
	if(lpfnClearErrorTable == NULL)
		return ;

	lpfnClearErrorTable();
}

SYS_ERROR_POSITION CErrorTableOper::GetFirstSysError()
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	GETFIRSTSYSERROR lpfnGetFirstSysError = (GETFIRSTSYSERROR)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceGetFirstSysError");
	if(lpfnGetFirstSysError == NULL)
		return NULL;

	return lpfnGetFirstSysError();
}

SYS_ERROR_POSITION CErrorTableOper::GetEndSysError()
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	GETENDSYSERROR lpfnGetEndSysError = (GETENDSYSERROR)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceGetEndSysError");
	if(lpfnGetEndSysError == NULL)
		return NULL;

	return lpfnGetEndSysError();
}

void CErrorTableOper::GetSysErrorAttr(SYS_ERROR_POSITION& posSysError,CErrorInfo& errorInfo)
{
	ASSERT(g_OLInterface.GetInterface());

	//引用成员函数
	GETSYSERRORATTR lpfnGetSysErrorAttr = (GETSYSERRORATTR)GetProcAddress(g_OLInterface.GetInterface(),"InterfaceGetSysErrorAttr");
	if(lpfnGetSysErrorAttr == NULL)
		return;

	char chErrorInfo[MAX_PATH];
	memset(chErrorInfo,0,MAX_PATH);
	char chErrorSymbol[MAX_PATH];
	memset(chErrorSymbol,0,MAX_PATH);
	char chErrorOwner[MAX_PATH];
	memset(chErrorOwner,0,MAX_PATH);
	char chErrorFileName[MAX_PATH];
	memset(chErrorFileName,0,MAX_PATH);
	char chConflictOwner[MAX_PATH];
	memset(chConflictOwner,0,MAX_PATH);

	lpfnGetSysErrorAttr(posSysError,errorInfo.m_nErrorCode,chErrorInfo,chErrorSymbol,chErrorOwner,chErrorFileName,chConflictOwner);

	errorInfo.m_strErrorCodeInfo = chErrorInfo;
	errorInfo.m_strErrorSymbol   = chErrorSymbol;
 	errorInfo.m_strErrorOwner    = chErrorOwner;
	errorInfo.m_strErrorFileName = chErrorFileName;
	errorInfo.m_strConflictOwner = chConflictOwner;
}


