
#include "stdafx.h"
#include "Global.h"

//bool FileExist(const TCHAR* pchFileName,bool bDirectory)
//
//  目的: 判断文件是否存在
//
//  注释: 使用ATL字符串作为参数传入要判断的文件名
//        通过传入文件名来判断文件是否存在
//        此函数同时可以判断目录是否存在
//        第二个参数bool bDirectory为true时判断为目录
//        bool bDirectory参数默认为false
//
bool FileExist(const TCHAR* pchFileName,bool bDirectory)
{
	bool bExist = false;
	WIN32_FIND_DATA fd; 
	HANDLE hFind = FindFirstFile(pchFileName, &fd);

	do 
	{
		if (hFind == INVALID_HANDLE_VALUE) 
			break;

		//判断目录
		if(bDirectory)
		{
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				bExist = true;
			}

			break;
		}

		bExist = true;

	}while(false);
	

	FindClose(hFind);

	return bExist;
}

//得到第二个文件相对与第一个路径的相对路径，得到的结果保存在第二个路径中
bool GetRelativePath(const CString& strFirstFileName,CString& strSecondFileName)
{
	if(FileExist(strSecondFileName,true))
	{
		if(strSecondFileName.Right(1) != _T('\\'))
			strSecondFileName += _T('\\');
	}

	CString strLowFirstFileName = strFirstFileName;
	CString strLowSecondFileName =  strSecondFileName;
	strLowFirstFileName.MakeLower();
	strLowSecondFileName.MakeLower();

	int nPos = 0;
	CString strTemp=_T("");
	CString strSamePath=_T("");
	while(true)
	{	
		nPos = strLowSecondFileName.Find(_T('\\'));
		if(nPos < 0)
			break;

		strSamePath += strLowSecondFileName.Left(nPos+1);
		strLowSecondFileName = strLowSecondFileName.Right(strLowSecondFileName.GetLength()-nPos-1);
		if(strLowFirstFileName.Find(strSamePath) != 0)
			break;

		strTemp = strSamePath;
	}

	if(strTemp.IsEmpty())
		return false;

	CString strFirstFilePath = strLowFirstFileName.Left(strLowFirstFileName.ReverseFind(_T('\\'))+1);
	if(strTemp == strFirstFilePath)
	{
		nPos = strFirstFilePath.GetLength();
		strTemp = ".\\";
		strTemp += strSecondFileName.Right(strSecondFileName.GetLength()-nPos);
		strSecondFileName = strTemp;
		return true;
	}

	strSecondFileName = strSecondFileName.Right(strSecondFileName.GetLength()-strTemp.GetLength());
	strFirstFilePath = strFirstFilePath.Right(strFirstFilePath.GetLength()-strTemp.GetLength());
	strTemp.Empty();
	while(true)
	{
		nPos = strFirstFilePath.ReverseFind(_T('\\'));
		if(nPos < 0)
			break;

		strTemp += "..\\";
		strFirstFilePath = strFirstFilePath.Left(nPos);
	}

	strTemp += strSecondFileName;
	strSecondFileName = strTemp;

	return true;
}

//得到第二个文件相对与第一个路径的绝对路径，得到的结果保存在第二个路径中
bool GetAbsolutePath(const CString& strFirstFileName,CString& strSecondFileName)
{
	int nPos = strFirstFileName.ReverseFind(_T('\\'));
	if(nPos < 0)return false;

	CString strFirstFileNameTemp = strFirstFileName.Left(nPos);
	if(strSecondFileName.Left(2) == ".\\")
	{
		strSecondFileName = strSecondFileName.Right(strSecondFileName.GetLength()-1);
		strFirstFileNameTemp += strSecondFileName;
		strSecondFileName = strFirstFileNameTemp;
		return true;
	}

	if(strSecondFileName.Left(3) != "..\\")
		return false;

	while(strSecondFileName.Left(3) == "..\\")
	{
		nPos = strFirstFileNameTemp.ReverseFind(_T('\\'));
		if(nPos < 0)return false;
		strFirstFileNameTemp = strFirstFileNameTemp.Left(nPos);
		strSecondFileName = strSecondFileName.Right(strSecondFileName.GetLength()-3);		
	}

	strFirstFileNameTemp += _T('\\');
	strFirstFileNameTemp += strSecondFileName;
	strSecondFileName = strFirstFileNameTemp;

	return true;
}

bool IsRelativePath(const CString& strPath)
{
	if((strPath.Left(2) == _T(".\\")) || (strPath.Left(3) == _T("..\\")))
		return true;

	return false;
}

//CString GetTitleFromPathName(const CString& strPathName)
//{
//	CString strTemp = strPathName;
//
//	int index1 = strTemp.ReverseFind( _T('\\') );
//	int index2 = strTemp.ReverseFind( _T('.') );
//
//	if( index2 > -1 && index2 > index1 )
//		strTemp = strTemp.Left(index2);
//
//	return strTemp;
//}

CString GetPathFromPathName(const CString& strPathName)
{
	CString strTemp = strPathName;

	int index1 = strTemp.ReverseFind( _T('\\') );

	if( index1 > -1)
		strTemp = strTemp.Left(index1+1);

	return strTemp;
}

//得到文件扩展名
CString GetFileExternName(const CString& strFileName)
{
	CString strFileExternName;
	int nPos = strFileName.ReverseFind(_T('.'));
	if(nPos >= 0)
	{
		strFileExternName = strFileName.Right(strFileName.GetLength()-nPos-1);
	}

	return strFileExternName;
}

CString GetFileNameFromPathName(const CString& strPathName,BOOL bContainExtendName)
{
	CString strTemp = strPathName;

	int index1 = strTemp.ReverseFind( _T('\\') );

	if( index1 > -1)
	{
		strTemp = strTemp.Right(strTemp.GetLength() - index1-1);

		//如果不包含扩展名
		if(!bContainExtendName)
		{
			strTemp = strTemp.Left(strTemp.ReverseFind(_T('.')));
		}
	}

	return strTemp;
}

//创建深度目录
void CreateDepthDirectory(const CString& strDirectory)
{
	//如果目录已经存在则退出
	if(FileExist(strDirectory,true))
		return;

	int nPos = strDirectory.Find(_T('\\'));
	
	CString strTemp;
	while(true)
	{
		nPos++;
		nPos = strDirectory.Find(_T('\\'),nPos);
		if(nPos < 0)break;

		strTemp = strDirectory.Left(nPos);

		if(!FileExist(strTemp,true))
		{
			if(!CreateDirectory(strTemp,NULL))
			{
				break;
			}
		}
	}
}

bool FileRename(const TCHAR* pchOldName, const TCHAR* pchNewName)
{
	try
	{
		CFile::Rename(pchOldName, pchNewName);
	}
	catch(CFileException* pEx )
	{
		CString strMsg;
		strMsg.Format(_T("更改文件名 %s 失败"),pchOldName);
		AfxMessageBox(strMsg);
		//#ifdef _DEBUG
		//	afxDump << "更改文件 " << pOldName << " 失败, cause = "
		//			<< e->m_cause << "\n";
		//#endif
		pEx->Delete();

		return false;
	}

	return true;
}

/***************删除文件到回收站中*******************
pszPath  : 待删除的全路径文件名
bDelete  : TRUE 删除，不移到回收站，FALSE:移到回收站
返回    : TRUE 删除成功     FALSE 删除失败
/******************************************************/

BOOL DeleteFolderOrFile(LPCTSTR pszPath, BOOL bDelete/*=FALSE*/)
{
	SHFILEOPSTRUCT  shDelFile;
	memset(&shDelFile,0,sizeof(SHFILEOPSTRUCT));
	shDelFile.fFlags |= FOF_SILENT;      // 不显示进度
	shDelFile.fFlags |= FOF_NOERRORUI;     //不报告错误信息
	shDelFile.fFlags |= FOF_NOCONFIRMATION;    //直接删除，不进行确认
	// 复制路径到一个以双NULL结束的string变量里
	TCHAR buf[_MAX_PATH + 1];
	_tcscpy(buf, pszPath);   // 复制路径
	buf[_tcslen(buf)+1]=0;   // 在末尾加两个NULL

	// 设置SHFILEOPSTRUCT的参数为删除做准备
	shDelFile.wFunc = FO_DELETE;       // 执行的操作
	shDelFile.pFrom = buf;         // 操作的对象，也就是目录
	shDelFile.pTo = NULL;          // 必须设置为NULL
	if (bDelete) //根据传递的bDelete参数确定是否删除到回收站
	{   
		shDelFile.fFlags &= ~FOF_ALLOWUNDO;    //直接删除，不进入回收站
	}
	else
	{          
		shDelFile.fFlags |= FOF_ALLOWUNDO;    //删除到回收站
	}
	return SHFileOperation(&shDelFile);    //删除
}

int CopyFloderOrFile(LPCTSTR lpszPathFrom,LPCTSTR lpszPathTo,BOOL bMove)
{
	SHFILEOPSTRUCT FileOp;
	FileOp.fFlags = FOF_SILENT /*| FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR*/;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = lpszPathFrom;
	FileOp.pTo = lpszPathTo;	
	FileOp.wFunc = bMove?FO_MOVE:FO_COPY;	
	return SHFileOperation(&FileOp);
}

//   检查操作系统的版本号  
//   版本号无法确定   0  
//   Windows   98   =   1  
//   Windows   98   SE   =   2  
//   Windows   Me   =   3  
//   Windows   NT   =   4  
//   Windows   2000   =   5  
//   Windows   XP/.Net   Server   =   6  
int  GetOSVersion(void)  
{  
	OSVERSIONINFO   osver;  
	osver.dwOSVersionInfoSize   =   sizeof(OSVERSIONINFO);  
	GetVersionEx(&osver);  
	int nOSVersion   =   0;  
	if   (osver.dwPlatformId   ==   VER_PLATFORM_WIN32_WINDOWS)  
	{  
		//   操作系统的版本是   Windows   95,   Windows   98,Windows   98   SE   or   Windows   Me.  
		if   (osver.dwMinorVersion   ==   10)  
		{  
			if   ((osver.dwBuildNumber   &   0xFFFF)   ==   1998)  
			{  
				//   操作系统的版本是   Windows   98  
				nOSVersion   =   1;  
			}  
			else  
			{  
				if   ((osver.dwBuildNumber   &   0xFFFF)   ==   2222)  
				{  
					//   操作系统的版本是   Windows   98   SE  
					nOSVersion   =   2;  
				}  
			}  
		}  
		else  
		{  
			if   ((osver.dwMinorVersion   ==   90)   &&   ((osver.dwBuildNumber   &   0xFFFF)   ==   3000))  
			{  
				//   操作系统的版本是   Windows   Me  
				nOSVersion   =   3;  
			}  
		}  
	}  
	else  
	{  
		if   (osver.dwPlatformId   ==   VER_PLATFORM_WIN32_NT)  
		{  
			//   操作系统的版本是   Windows   NT   3.51,   Windows   NT   4.0,   Windows   2000,   Windows   XP,   or   Windows   .NET   Server.  
			if   (osver.dwMajorVersion   <=   4)  
			{  
				//   操作系统的版本是   Windows   NT  
				nOSVersion   =   4;  
			}  
			else  
			{  
				if   (osver.dwMinorVersion   ==   0)  
				{  
					//   操作系统的版本是   Windows   2000  
					nOSVersion   =   5;  
				}  
				else  
				{  
					//   操作系统的版本是   Windows   XP  
					nOSVersion   =   6;  
				}  
			}  
		}  
	}  

	return nOSVersion;
}   

