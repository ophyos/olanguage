#include "StdAfx.h"
#include "./olsolutionfile.h"
#include "../Data/olxmlsolutionfile.h"

COLSolutionFile::COLSolutionFile(void)
{
	m_OLXMLSolution = NULL;
	CreateSolutionData();
}

COLSolutionFile::~COLSolutionFile(void)
{
	DestorySolutionData();
}

bool COLSolutionFile::CreateSolutionFile(const char* pchFileName,bool bSave)
{
	return COLXMLSolutionFile::CreateSolutionFile(pchFileName,bSave);
}

bool COLSolutionFile::WriteSolution(const char* pchFileName)
{
	return COLXMLSolutionFile::WriteSolution(pchFileName,m_OLXMLSolution);
}

bool COLSolutionFile::ReadSolution(const char* pchFileName)
{
	return COLXMLSolutionFile::ReadSolution(pchFileName,m_OLXMLSolution);
}

CString COLSolutionFile::GetSolutionName()
{
	CString strName;
	strName = COLXMLSolutionFile::GetSolutionName(m_OLXMLSolution);

	return strName;
}

void COLSolutionFile::SetSolutionName(const char* pchSolutionName)
{
	COLXMLSolutionFile::SetSolutionName(m_OLXMLSolution,pchSolutionName);
}

bool COLSolutionFile::PopFrontProjectFileProperty(COLProjectFileProperty* pProjectFileProperty)
{
	return COLXMLSolutionFile::PopFrontProjectFileProperty(m_OLXMLSolution,pProjectFileProperty);
}

void COLSolutionFile::PushBackProjectFileProperty(COLProjectFileProperty* pProjectFileProperty)
{	
	COLXMLSolutionFile::PushBackProjectFileProperty(m_OLXMLSolution,pProjectFileProperty);
}

void COLSolutionFile::CreateSolutionData()
{
	if(m_OLXMLSolution)
	{
		DestorySolutionData();
	}
	
	m_OLXMLSolution = COLXMLSolutionFile::CreateSolutionData();
}

void COLSolutionFile::DestorySolutionData()
{
	COLXMLSolutionFile::DestorySolutionData(m_OLXMLSolution);

	m_OLXMLSolution = NULL;
}
