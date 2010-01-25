
#include "StdAfx.h"
#include "Common.h"

#ifdef _UNICODE
#define get_full_path _wfullpath
#else
#define get_full_path _fullpath
#endif

BOOL GetAbsolutePathByRelativePath(CString& strRelativePath,const CString& strPathRefer)
{
	TCHAR chBuf[_MAX_PATH];
	if(!strPathRefer.IsEmpty())
	{
		TCHAR chCurDir[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH,chCurDir);
		if(!SetCurrentDirectory(strPathRefer))
		{
			strRelativePath.Empty();
			return FALSE;
		}

		get_full_path(chBuf,strRelativePath,_MAX_PATH);
		SetCurrentDirectory(chCurDir);
	}
	else
	{
		get_full_path(chBuf,strRelativePath,_MAX_PATH);
	}

	strRelativePath = chBuf;

	return TRUE;
}

void DelayNop(DWORD dwMillisecond)
{
	//下面代码是延迟500毫秒
	DWORD dwStart,dwEnd;
	dwStart = GetTickCount();
	do
	{
		MSG msg;
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		dwEnd = GetTickCount();
	}while(dwEnd - dwStart < dwMillisecond);
}