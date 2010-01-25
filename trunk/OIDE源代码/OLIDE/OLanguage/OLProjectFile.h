#pragma once

#include "../Data/OLXMLProjectData.h"

class COLProjectFile
{
public:
	COLProjectFile(void);
	~COLProjectFile(void);

	bool CreateProjectFile(const char* pchFileName,bool bSave);
	bool WriteProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty);
	bool ReadProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty);
};
