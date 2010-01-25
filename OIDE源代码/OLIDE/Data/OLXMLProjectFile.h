#pragma once

//处理O语言工程XML文件

#include ".\OLXMLProjectData.h"

class COLXMLProjectFile
{
public:
	COLXMLProjectFile(void);
	~COLXMLProjectFile(void);

	static bool CreateProjectFile(const char* pchFileName,bool bSave);
	static bool WriteProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty);
	static bool ReadProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty);
};
