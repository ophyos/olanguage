#include "StdAfx.h"
#include ".\olxmlsolutionfile.h"
#include ".\olxmlfile.h"
#include ".\OLXMLKeyFile.h"

COLXMLSolutionFile::COLXMLSolutionFile(void)
{

}

COLXMLSolutionFile::~COLXMLSolutionFile(void)
{
}

bool COLXMLSolutionFile::CreateSolutionFile(const char* pchFileName,bool bSave)
{
	COLXMLFile OLXMLFile;

	OLXMLFile.CreateOLanguageFile(pchFileName,OFT_SOLUTION,false);

	if(bSave)
	{
		return OLXMLFile.SaveFile();
	}

	return true;
}

bool COLXMLSolutionFile::WriteSolution(const char* pchFileName,COLXMLSolution* pOLXMLSolution)
{
	assert(pOLXMLSolution);

	COLXMLFile OLXMLFile;

	//打开工程文档
	if(OLXMLFile.OpenOLanguageFile(pchFileName) != OFT_SOLUTION)
		return false;

	TiXmlElement* pxmlElementOLanguageFile = OLXMLFile.GetOLanguageFileElement();

	TiXmlElement xmlElement("");
	TiXmlText xmlText("");

	//设置方案名称
	TiXmlElement* pxmlElementSolutionName = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_SolutionName);
	xmlText.SetValue(pOLXMLSolution->m_chSolutionName);
	if(pxmlElementSolutionName)
	{
		pxmlElementSolutionName->Clear();
		pxmlElementSolutionName->InsertEndChild(xmlText);
	}
	else
	{
		xmlElement.SetValue(OLXMLKey_SolutionName);
		pxmlElementOLanguageFile->InsertEndChild(xmlElement)->InsertEndChild(xmlText);
	}
    
	//得到工程文件结点
	TiXmlElement* pxmlProjectFileElement = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_ProjectFile);	
	//如果没有工程文件结点，创建一个工程文件结点
	if(pxmlProjectFileElement == NULL)
	{
		TiXmlElement xmlProjectFileElement(OLXMLKey_ProjectFile);
		pxmlProjectFileElement = pxmlElementOLanguageFile->InsertEndChild(xmlProjectFileElement)->ToElement();
	}

	//设置工程结点

	pxmlProjectFileElement->Clear();

	TiXmlElement xmlProjectElement(OLXMLKey_Project);
	TiXmlElement* pxmlElement = NULL;

	COLProjectFileProperty* pProjectFileProperty = NULL;
	std::list<COLProjectFileProperty>::iterator itProjectFileProperty;
	for(itProjectFileProperty = pOLXMLSolution->m_listProjectFile.begin();itProjectFileProperty != pOLXMLSolution->m_listProjectFile.end();++itProjectFileProperty)
	{
		pProjectFileProperty = &(*itProjectFileProperty);

		//在方案文件中保存工程
		xmlProjectElement.Clear();

		////设置工程名称
		//xmlElement.SetValue(OLXMLKey_ProjectName);
		//pxmlElement = xmlProjectElement.InsertEndChild(xmlElement)->ToElement();
		//xmlText.SetValue(pProjectFileProperty->m_strProjectName.c_str());
		//pxmlElement->InsertEndChild(xmlText);

		//设置工程路径
		xmlElement.SetValue(OLXMLKey_ProjectPath);
		pxmlElement = xmlProjectElement.InsertEndChild(xmlElement)->ToElement();
		xmlText.SetValue(pProjectFileProperty->m_chProjectFileName);
		pxmlElement->InsertEndChild(xmlText);
		
		//设置树结点展开状态结点
		xmlElement.SetValue(OLXMLKey_ProjectTreeNodeExpandState);
		pxmlElement = xmlProjectElement.InsertEndChild(xmlElement)->ToElement();
		if(pProjectFileProperty->m_bIsExpand)
		{
			xmlText.SetValue("1");
		}
		else
		{
			xmlText.SetValue("0");
		}
		pxmlElement->InsertEndChild(xmlText);
		
		//添加工程结点
		pxmlProjectFileElement->InsertEndChild(xmlProjectElement);
	}

	return OLXMLFile.SaveFile();
}

bool COLXMLSolutionFile::ReadSolution(const char* pchFileName,COLXMLSolution* pOLXMLSolution)
{
	assert(pOLXMLSolution);

	COLXMLFile OLXMLFile;

	//打开工程文档
	if(OLXMLFile.OpenOLanguageFile(pchFileName) != OFT_SOLUTION)
		return false;

	TiXmlElement* pxmlElementOLanguageFile = OLXMLFile.GetOLanguageFileElement();

	//得到方案名称
	TiXmlElement* pxmlElementSolutionName = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_SolutionName);
	if((pxmlElementSolutionName != NULL) && (!pxmlElementSolutionName->NoChildren()) && (pxmlElementSolutionName->FirstChild()->Type() == TiXmlNode::NodeType::TEXT))
	{
		strcpy(pOLXMLSolution->m_chSolutionName,pxmlElementSolutionName->FirstChild()->Value());
	}

	//得到工程文件结点
	TiXmlElement* pxmlProjectFileElement = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_ProjectFile);
	if(pxmlProjectFileElement == NULL)
		return false;

	TiXmlElement* pxmlProjectElement = pxmlProjectFileElement->FirstChildElement(OLXMLKey_Project);
	while(pxmlProjectElement)
	{
		COLProjectFileProperty projectFileProperty;
		TiXmlElement* pxmlElement = NULL;

		////得到工程名
		//pxmlElement = pxmlProjectElement->FirstChildElement(OLXMLKey_ProjectName);
		//if(pxmlElement)
		//{
		//	projectFileProperty.m_strProjectName = pxmlElement->FirstChild()->Value();
		//}

		//得到工程路径
		pxmlElement = pxmlProjectElement->FirstChildElement(OLXMLKey_ProjectPath);
		if((pxmlElement != NULL) && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::NodeType::TEXT))
		{
			strcpy(projectFileProperty.m_chProjectFileName,pxmlElement->FirstChild()->Value());
		}

		//得到工程树结点状态
		pxmlElement = pxmlProjectElement->FirstChildElement(OLXMLKey_ProjectTreeNodeExpandState);
		if((pxmlElement != NULL) && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::NodeType::TEXT))
		{
			if(strcmp(pxmlElement->FirstChild()->Value(),"0") == 0)
			{
				projectFileProperty.m_bIsExpand = false;
			}
			else
			{
				projectFileProperty.m_bIsExpand = true;
			}
		}

		//将工程文件属性添加到工程文件列表
		pOLXMLSolution->m_listProjectFile.push_back(projectFileProperty);

		//得到下一个工程结点
		pxmlProjectElement = pxmlProjectElement->NextSiblingElement(OLXMLKey_Project);
	}

	return true;
}

char* COLXMLSolutionFile::GetSolutionName(COLXMLSolution* pOLXMLSolution)
{
	assert(pOLXMLSolution);

	return pOLXMLSolution->m_chSolutionName;
}

void COLXMLSolutionFile::SetSolutionName(COLXMLSolution* pOLXMLSolution,const char* pchSolutionName)
{
	assert(pOLXMLSolution);

	strcpy(pOLXMLSolution->m_chSolutionName,pchSolutionName);
}

bool COLXMLSolutionFile::PopFrontProjectFileProperty(COLXMLSolution* pOLXMLSolution,COLProjectFileProperty* pProjectFileProperty)
{
	assert(pOLXMLSolution);
	assert(pProjectFileProperty);

	if(pOLXMLSolution->m_listProjectFile.empty())
		return false;

	*pProjectFileProperty = *pOLXMLSolution->m_listProjectFile.begin();
	pOLXMLSolution->m_listProjectFile.pop_front();

	return true;
}

void COLXMLSolutionFile::PushBackProjectFileProperty(COLXMLSolution* pOLXMLSolution,COLProjectFileProperty* pProjectFileProperty)
{
	assert(pOLXMLSolution);
	assert(pProjectFileProperty);

	pOLXMLSolution->m_listProjectFile.push_back(*pProjectFileProperty);
}

COLXMLSolution* COLXMLSolutionFile::CreateSolutionData()
{
	COLXMLSolution* pOLXMLSolution = new COLXMLSolution();
	return pOLXMLSolution;
}

void COLXMLSolutionFile::DestorySolutionData(COLXMLSolution* pOLXMLSolution)
{
	delete pOLXMLSolution;
}