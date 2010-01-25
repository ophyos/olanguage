// PeFile.h: interface for the CPeFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEFILE_H__97C156DC_93E7_4449_BEF1_65EC98F79846__INCLUDED_)
#define AFX_PEFILE_H__97C156DC_93E7_4449_BEF1_65EC98F79846__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <winnt.h>

#define MAX_STRINGLEN 64
typedef struct _MAP_FILE_STRUCT
{
	HANDLE hFile;
	HANDLE hMapping;
	LPVOID ImageBase;
}  MAP_FILE_STRUCT,* PMAP_FILE_STRUCT;


typedef struct _DASM_CODE
{
	CString strAddr;
	CString strOpcode;
	CString strDisassemble;
	CString strComment;
}DASM_CODE, *PDASM_CODE;

class CPeFile  
{

public:
	PIMAGE_SECTION_HEADER GetFirstSectionHeader();
	PIMAGE_NT_HEADERS GetNtHeaders();
	PIMAGE_OPTIONAL_HEADER GetOptionalHeader();
	PIMAGE_FILE_HEADER GetFileHeader();
	DWORD GetFileOffset(DWORD dwRVA);
	DWORD GetFileRawAddr(DWORD dwRVA);

	BOOL IsPeFile();
	void UnLoadFile();
	MAP_FILE_STRUCT m_stMapFile;
	CString m_strFileName;

	void SetFileName(char* pchFileName);
	BOOL LoadFile();
	BOOL OpenFile();
		
	CPeFile();
	virtual ~CPeFile();

};

#endif // !defined(AFX_PEFILE_H__97C156DC_93E7_4449_BEF1_65EC98F79846__INCLUDED_)
