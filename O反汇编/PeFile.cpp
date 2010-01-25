// PeFile.cpp: implementation of the CPeFile class.
//
//////////////////////////////////////////////////////////////////////

#include "PeFile.h"
#include <CommDlg.h>

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPeFile::CPeFile()
{

}

CPeFile::~CPeFile()
{

}

void CPeFile::SetFileName(char* pchFileName)
{
	m_strFileName = pchFileName;
}

BOOL CPeFile::OpenFile()
{
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(ofn));
	
	ofn.lStructSize      =sizeof(ofn);
	ofn.hwndOwner        =GetActiveWindow();
	ofn.hInstance        =GetModuleHandle(NULL);
	ofn.nMaxFile         =MAX_PATH;
	ofn.lpstrInitialDir  =_T(".");
	ofn.lpstrFile        =(LPSTR)(LPCTSTR)m_strFileName;
	ofn.lpstrTitle       =_T("Open");
	ofn.Flags            =OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter      =_T("*.*\0*.*\0");
	if(!GetOpenFileName(&ofn))
		return FALSE;
	return TRUE;
}

BOOL CPeFile::LoadFile()
{
	HANDLE hFile;
	HANDLE hMapping;
	LPVOID ImageBase;

	memset(&m_stMapFile,0,sizeof(MAP_FILE_STRUCT));
	
	hFile=CreateFile((LPCTSTR)m_strFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,0);
	if (!hFile)				   
		return FALSE;
	
	hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	
	if(!hMapping)
	{									
		CloseHandle(hFile);
		return FALSE;
	}
	
	ImageBase=MapViewOfFile(hMapping,FILE_MAP_READ,0,0,0);
    if(!ImageBase)
	{									
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return FALSE;
	}
	m_stMapFile.hFile=hFile;
	m_stMapFile.hMapping=hMapping;
	m_stMapFile.ImageBase=ImageBase;
	
	return TRUE;
}

void CPeFile::UnLoadFile()
{
	if(m_stMapFile.ImageBase)
		UnmapViewOfFile(m_stMapFile.ImageBase);
	
	if(m_stMapFile.hMapping)
		CloseHandle(m_stMapFile.hMapping);
	
	if(m_stMapFile.hFile)
		CloseHandle(m_stMapFile.hFile);
}

BOOL CPeFile::IsPeFile()
{
	PIMAGE_DOS_HEADER  pDH=NULL;
    PIMAGE_NT_HEADERS  pNtH=NULL;
	
    if(!m_stMapFile.ImageBase)
		return FALSE;
	
    pDH=(PIMAGE_DOS_HEADER)m_stMapFile.ImageBase;
    if(pDH->e_magic!=IMAGE_DOS_SIGNATURE)
		return FALSE;
	
    pNtH=(PIMAGE_NT_HEADERS32)((DWORD)pDH+pDH->e_lfanew);
    if (pNtH->Signature != IMAGE_NT_SIGNATURE )
        return FALSE;
	
    return TRUE;
}

PIMAGE_FILE_HEADER CPeFile::GetFileHeader()
{
	PIMAGE_DOS_HEADER  pDH=NULL;
    PIMAGE_NT_HEADERS  pNtH=NULL;
    PIMAGE_FILE_HEADER pFH=NULL;
    
    if(!IsPeFile())
		return NULL;
    pDH=(PIMAGE_DOS_HEADER)m_stMapFile.ImageBase;
    pNtH=(PIMAGE_NT_HEADERS)((DWORD)pDH+pDH->e_lfanew);
    pFH=&pNtH->FileHeader;
    return pFH;
}


PIMAGE_OPTIONAL_HEADER CPeFile::GetOptionalHeader()
{
	PIMAGE_DOS_HEADER  pDH=NULL;
    PIMAGE_NT_HEADERS  pNtH=NULL;
    PIMAGE_OPTIONAL_HEADER pOH=NULL;
	
	if(!IsPeFile())
		return NULL;
    pDH=(PIMAGE_DOS_HEADER)m_stMapFile.ImageBase;
    pNtH=(PIMAGE_NT_HEADERS)((DWORD)pDH+pDH->e_lfanew);
    pOH=&pNtH->OptionalHeader;
    return pOH;
}

PIMAGE_NT_HEADERS CPeFile::GetNtHeaders()
{
	if(!IsPeFile())
		return NULL;
	PIMAGE_NT_HEADERS  pNtH;
	PIMAGE_DOS_HEADER  pDH;
	pDH=(PIMAGE_DOS_HEADER)m_stMapFile.ImageBase;
	pNtH=(PIMAGE_NT_HEADERS)((DWORD)pDH+pDH->e_lfanew);
	
	return pNtH;
}

PIMAGE_SECTION_HEADER CPeFile::GetFirstSectionHeader()
{
	PIMAGE_NT_HEADERS     pNtH=NULL;
    PIMAGE_SECTION_HEADER pSH=NULL;
    
    pNtH=GetNtHeaders();
   	pSH=IMAGE_FIRST_SECTION(pNtH);
	return  pSH;
}

//由虚拟地址转换得到文件加载到内存中的地址
DWORD CPeFile::GetFileRawAddr(DWORD dwRVA)
{
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	PIMAGE_SECTION_HEADER pSectionHeader = GetFirstSectionHeader();
	
	if(pSectionHeader)
	{
		for( int i=0;  i<pFileHeader->NumberOfSections;  i++ )
		{
			if( dwRVA >= pSectionHeader[i].VirtualAddress  && 
				dwRVA < pSectionHeader[i].VirtualAddress + pSectionHeader[i].Misc.VirtualSize)
			{			
				//虚拟地址在节内的偏移量
				DWORD dwAddr = dwRVA - pSectionHeader[i].VirtualAddress;
				//在节内的实际偏移地址
				dwAddr += pSectionHeader[i].PointerToRawData;
				//内存中的地址
				dwAddr += (DWORD)m_stMapFile.ImageBase;

				return dwAddr;
			}
		}
	}

	return  0;
}