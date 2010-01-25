#include "StdAfx.h"
#include ".\olxmlprojectfile.h"
#include ".\OLXMLKeyFile.h"
#include ".\olxmlfile.h"
#include <string>
#include <sstream>
#include "../Common/UnicodeCovert.h"

COLXMLProjectFile::COLXMLProjectFile(void)
{
}

COLXMLProjectFile::~COLXMLProjectFile(void)
{
}

bool COLXMLProjectFile::CreateProjectFile(const char* pchFileName,bool bSave)
{
	COLXMLFile OLXMLFile;

	OLXMLFile.CreateOLanguageFile(pchFileName,OFT_PROJECT,false);

	if(bSave)
	{
		return OLXMLFile.SaveFile();
	}

	return true;
}

bool COLXMLProjectFile::WriteProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty)
{
	assert(pProjectProperty);

    COLXMLFile OLXMLFile;

	//打开工程文档
	if(OLXMLFile.OpenOLanguageFile(pchFileName) != OFT_PROJECT)
		return false;

	//设置工程属性结点
	TiXmlElement xmlElementProperty("");
	xmlElementProperty.SetValue(OLXMLKey_ProjectProperty);

	TiXmlText xmlText("");
	TiXmlElement xmlElement("");
	TiXmlElement* pXmlElement = NULL;

	//设置链接器
	xmlElement.SetValue(OLXMLKey_ProjectPropertyLinker);
	pXmlElement = xmlElementProperty.InsertEndChild(xmlElement)->ToElement();

	//设置代码目录
	xmlText.SetValue(pProjectProperty->m_chCodeDir);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyCodeDir);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

	//设置资源目录
	xmlText.SetValue(pProjectProperty->m_chResourceDir);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyResourceDir);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);	

	std::string strTemp;
		
	//设置程序类型
	std::ostringstream format_string1;
	format_string1 << pProjectProperty->m_nProgramType;
	strTemp = format_string1.str();
	xmlText.SetValue(strTemp.c_str());
	xmlElement.SetValue(OLXMLKey_ProjectPropertyProgramType);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

	//设置子系统
	//将整型转换为字符串	
	std::ostringstream format_string2;
	format_string2 << pProjectProperty->m_nLinkSubSystem;
	strTemp = format_string2.str();
	xmlText.SetValue(strTemp.c_str());
	xmlElement.SetValue(OLXMLKey_ProjectPropertySubSystem);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

	//设置调试版中间文件输出目录
	xmlText.SetValue(pProjectProperty->m_chDebugMiddleOutPutPath);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyDebugMiddleOutPutPath);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

	//设置调试版执行文件路径
	xmlText.SetValue(pProjectProperty->m_chDebugOutPutFileName);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyDebugOutPutFileName);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);	

	//设置纯净版中间文件输出目录
	xmlText.SetValue(pProjectProperty->m_chReleaseMiddleOutPutPath);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyReleaseMiddleOutPutPath);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

	//设置纯净版执行文件路径
	xmlText.SetValue(pProjectProperty->m_chReleaseOutPutFileName);
	xmlElement.SetValue(OLXMLKey_ProjectPropertyReleaseOutPutFileName);
	pXmlElement->InsertEndChild(xmlElement)->InsertEndChild(xmlText);	

	//设置生成记录
	xmlElement.SetValue(OLXMLKey_ProjectPropertyBuildRecord);
	TiXmlElement* pXmlElementBuildRecord = xmlElementProperty.InsertEndChild(xmlElement)->ToElement();

	char chTemp[MAX_PATH];
	int nRecordCount = pProjectProperty->m_pProjectBuildRecord->GetCount();
	for(int i=0;i<nRecordCount;++i)
	{
		xmlElement.SetValue(OLXMLKey_ProjectPropertyBuildRecordItem);
		TiXmlElement* pXmlElementBuildRecordItem = pXmlElementBuildRecord->InsertEndChild(xmlElement)->ToElement();

		CString strFileName,strFileTime,strObjFileTime;
		pProjectProperty->m_pProjectBuildRecord->GetAt(i,strFileName,strFileTime,strObjFileTime);

		//设置生成文件名
		CopyStr(chTemp,MAX_PATH,strFileName);
		xmlText.SetValue(chTemp);
		xmlElement.SetValue(OLXMLKey_ProjectPropertyBuildFileName);
		pXmlElementBuildRecordItem->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

		//设置生成文件时间
		CopyStr(chTemp,MAX_PATH,strFileTime);
		xmlText.SetValue(chTemp);
		xmlElement.SetValue(OLXMLKey_ProjectPropertyBuildFileTime);
		pXmlElementBuildRecordItem->InsertEndChild(xmlElement)->InsertEndChild(xmlText);

		//设置生成目标文件时间
		CopyStr(chTemp,MAX_PATH,strObjFileTime);
		xmlText.SetValue(chTemp);
		xmlElement.SetValue(OLXMLKey_ProjectPropertyBuildObjFileTime);
		pXmlElementBuildRecordItem->InsertEndChild(xmlElement)->InsertEndChild(xmlText);
	}	

	//保存工程文档信息
	TiXmlElement* pxmlElementOLanguageFile = OLXMLFile.GetOLanguageFileElement();

	//设置工程名称
	TiXmlElement* pxmlElementTemp = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_ProjectName);
	xmlText.SetValue(pProjectProperty->m_chProjectName);
	if(pxmlElementTemp)
	{
		pxmlElementTemp->Clear();
		pxmlElementTemp->InsertEndChild(xmlText);
	}
	else
	{
		xmlElement.SetValue(OLXMLKey_ProjectName);
		pxmlElementOLanguageFile->InsertEndChild(xmlElement)->InsertEndChild(xmlText);
	}
	
	pxmlElementTemp = pxmlElementOLanguageFile->FirstChildElement(xmlElementProperty.Value());
	if(pxmlElementTemp != NULL)
	{
		pxmlElementOLanguageFile->RemoveChild(pxmlElementTemp);
	}

	pxmlElementOLanguageFile->InsertEndChild(xmlElementProperty);

	return OLXMLFile.SaveFile();
}

bool COLXMLProjectFile::ReadProjectProperty(const char* pchFileName,COLProjectProperty* pProjectProperty)
{
	assert(pProjectProperty);

	COLXMLFile OLXMLFile;

	if(OLXMLFile.OpenOLanguageFile(pchFileName) != OFT_PROJECT)
		return false;

	TiXmlElement* pxmlElementOLanguageFile = OLXMLFile.GetOLanguageFileElement();

	//得到工程名称
	TiXmlElement* pxmlElementProjectName = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_ProjectName);
	if(pxmlElementProjectName && (!pxmlElementProjectName->NoChildren()) && (pxmlElementProjectName->FirstChild()->Type() == TiXmlNode::TEXT))
	{
		strcpy(pProjectProperty->m_chProjectName,pxmlElementProjectName->FirstChild()->Value());
	}

	//得到工程属性结点
	TiXmlElement* pxmlElementProperty = NULL;
	pxmlElementProperty = pxmlElementOLanguageFile->FirstChildElement(OLXMLKey_ProjectProperty);
	if(pxmlElementProperty == NULL)
		return false;

	//得到链接器结点
	TiXmlElement* pxmlElementLinker = pxmlElementProperty->FirstChildElement(OLXMLKey_ProjectPropertyLinker);
	if(pxmlElementLinker)
	{
		TiXmlElement* pxmlElement = NULL;

		//得到代码目录
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyCodeDir);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chCodeDir, pxmlElement->FirstChild()->Value());
		}

		//得到资源目录
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyResourceDir);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chResourceDir, pxmlElement->FirstChild()->Value());
		}		

		//得到程序类型
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyProgramType);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			pProjectProperty->m_nProgramType = atoi(pxmlElement->FirstChild()->Value());
		}

		//得到子系统
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertySubSystem);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			pProjectProperty->m_nLinkSubSystem = atoi(pxmlElement->FirstChild()->Value());
		}
		
		//得到调试版中间文件输出路径
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyDebugMiddleOutPutPath);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chDebugMiddleOutPutPath, pxmlElement->FirstChild()->Value());
		}
		//得到调试版生成文件路径
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyDebugOutPutFileName);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chDebugOutPutFileName, pxmlElement->FirstChild()->Value());
		}		

		//得到纯净版中间文件输出路径
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyReleaseMiddleOutPutPath);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chReleaseMiddleOutPutPath, pxmlElement->FirstChild()->Value());
		}
		//得到纯净版生成文件路径
		pxmlElement = pxmlElementLinker->FirstChildElement(OLXMLKey_ProjectPropertyReleaseOutPutFileName);
		if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
		{
			strcpy(pProjectProperty->m_chReleaseOutPutFileName, pxmlElement->FirstChild()->Value());
		}	
	}

	//得到生成记录
	TiXmlElement* pxmlElementBuildRecord = pxmlElementProperty->FirstChildElement(OLXMLKey_ProjectPropertyBuildRecord);
	if(pxmlElementBuildRecord)
	{
		TiXmlElement* pxmlElementBuildRecordItem = pxmlElementBuildRecord->FirstChildElement(OLXMLKey_ProjectPropertyBuildRecordItem);
		while(pxmlElementBuildRecordItem)
		{
			TiXmlElement* pxmlElement = 0;
			CString strFileName,strFileTime,strObjFileTime;
			
			//得到文件名
			pxmlElement = pxmlElementBuildRecordItem->FirstChildElement(OLXMLKey_ProjectPropertyBuildFileName);
			if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
			{
				strFileName = pxmlElement->FirstChild()->Value();				
			}

			//得到文件时间
			pxmlElement = pxmlElementBuildRecordItem->FirstChildElement(OLXMLKey_ProjectPropertyBuildFileTime);
			if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
			{
				strFileTime = pxmlElement->FirstChild()->Value();				
			}

			//得到目标文件时间
			pxmlElement = pxmlElementBuildRecordItem->FirstChildElement(OLXMLKey_ProjectPropertyBuildObjFileTime);
			if(pxmlElement && (!pxmlElement->NoChildren()) && (pxmlElement->FirstChild()->Type() == TiXmlNode::TEXT))
			{
				strObjFileTime = pxmlElement->FirstChild()->Value();
			}

			pProjectProperty->m_pProjectBuildRecord->AddRecord(strFileName,strFileTime,strObjFileTime);

			pxmlElementBuildRecordItem = pxmlElementBuildRecordItem->NextSiblingElement(OLXMLKey_ProjectPropertyBuildRecordItem);
		}		
	}

	return true;
}
