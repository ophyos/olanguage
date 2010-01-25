#pragma once

//O语言所有要用到的XML数据定义
//包括工程属性和工程文件属性

#ifndef MAX_NAME
#define MAX_NAME 100
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#include "OLProjectBuildRecord.h"

class COLProjectProperty
{
public:
	COLProjectProperty(void)
	{		
		memset(m_chProjectName,0,MAX_NAME*sizeof(char));
		memset(m_chCodeDir,0,MAX_NAME*sizeof(char));
		memset(m_chResourceDir,0,MAX_NAME*sizeof(char));		
		m_nProgramType = 0;		
		m_nLinkSubSystem = 0;		
		memset(m_chDebugMiddleOutPutPath,0,MAX_NAME*sizeof(char));
		memset(m_chDebugOutPutFileName,0,MAX_NAME*sizeof(char));			
		memset(m_chReleaseMiddleOutPutPath,0,MAX_NAME*sizeof(char));
		memset(m_chReleaseOutPutFileName,0,MAX_NAME*sizeof(char));			
	}
	~COLProjectProperty(void)
	{
	}

	char m_chProjectName[MAX_NAME];	
	char m_chCodeDir[MAX_PATH];
	char m_chResourceDir[MAX_PATH];
	int  m_nProgramType;	
	int  m_nLinkSubSystem;	
	char m_chDebugMiddleOutPutPath[MAX_PATH];
	char m_chDebugOutPutFileName[MAX_PATH];
	char m_chReleaseMiddleOutPutPath[MAX_PATH];
	char m_chReleaseOutPutFileName[MAX_PATH];

	COLProjectBuildRecord* m_pProjectBuildRecord;
};

class COLProjectFileProperty
{

public:

	COLProjectFileProperty(void)
	{
		memset(m_chProjectFileName,0,MAX_NAME*sizeof(char));
	}
	~COLProjectFileProperty(void)
	{

	}
	
	char  m_chProjectFileName[MAX_PATH];
	bool  m_bIsExpand; //树结点展开状态
};
