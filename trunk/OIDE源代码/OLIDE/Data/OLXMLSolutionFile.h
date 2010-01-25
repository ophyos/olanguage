#pragma once

//处理O语言方案XML文件

#include ".\OLXMLProjectData.h"
#include <list>

class COLXMLSolution
{
public:
	COLXMLSolution(void)
	{
		memset(m_chSolutionName,0,MAX_NAME);
		m_listProjectFile.clear();
	}
	~COLXMLSolution(void)
	{
	}

	char  m_chSolutionName[MAX_NAME];
	std::list<COLProjectFileProperty> m_listProjectFile;
};

class COLXMLSolutionFile
{
public:
	COLXMLSolutionFile(void);
	~COLXMLSolutionFile(void);

public:
    
	static bool CreateSolutionFile(const char* pchFileName,bool bSave);
	static bool WriteSolution(const char* pchFileName,COLXMLSolution* pOLXMLSolution);
	static bool ReadSolution(const char* pchFileName,COLXMLSolution* pOLXMLSolution);

	static char* GetSolutionName(COLXMLSolution* pOLXMLSolution);
	static void SetSolutionName(COLXMLSolution* pOLXMLSolution,const char* pchSolutionName);
	static bool PopFrontProjectFileProperty(COLXMLSolution* pOLXMLSolution,COLProjectFileProperty* pProjectFileProperty);
	static void PushBackProjectFileProperty(COLXMLSolution* pOLXMLSolution,COLProjectFileProperty* pProjectFileProperty);

	static COLXMLSolution* CreateSolutionData();
	static void DestorySolutionData(COLXMLSolution* pOLXMLSolution);
};
