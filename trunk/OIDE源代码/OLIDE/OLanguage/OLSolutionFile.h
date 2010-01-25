#pragma once

#include "../Data/OLXMLProjectData.h"

class COLSolutionFile
{
	friend class COLXMLSolution;

public:

	COLSolutionFile(void);
	~COLSolutionFile(void);

private:

	COLXMLSolution* m_OLXMLSolution;

public:

	bool CreateSolutionFile(const char* pchFileName,bool bSave);
	bool WriteSolution(const char* pchFileName);
	bool ReadSolution(const char* pchFileName);

	CString GetSolutionName();
	void SetSolutionName(const char* pchSolutionName);
	bool PopFrontProjectFileProperty(COLProjectFileProperty* pProjectFileProperty);
	void PushBackProjectFileProperty(COLProjectFileProperty* pProjectFileProperty);

private:

	void CreateSolutionData();
	void DestorySolutionData();
};
