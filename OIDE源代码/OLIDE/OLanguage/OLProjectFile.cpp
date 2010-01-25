#include "StdAfx.h"
#include "./olprojectfile.h"
#include "../Data/OLXMLProjectFile.h"


COLProjectFile::COLProjectFile(void)
{
	
}

COLProjectFile::~COLProjectFile(void)
{
}

bool COLProjectFile::CreateProjectFile(const char* pchFileName,bool bSave)
{
	return COLXMLProjectFile::CreateProjectFile(pchFileName,bSave);	
}

bool COLProjectFile::WriteProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty)
{
	return COLXMLProjectFile::WriteProjectProperty(pchFileName,pProjectProperty);
}

bool COLProjectFile::ReadProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty)
{
	return COLXMLProjectFile::ReadProjectProperty(pchFileName,pProjectProperty);
}
