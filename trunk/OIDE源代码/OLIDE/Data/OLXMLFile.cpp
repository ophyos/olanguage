#include "StdAfx.h"
#include ".\olxmlfile.h"
#include <string>
#include <sstream>
#include "../Common/UnicodeCovert.h"

COLXMLFile::COLXMLFile(void)
{
}

COLXMLFile::~COLXMLFile(void)
{
}

void COLXMLFile::StrToChar(const CString& strData,char* pchData,int nLength)
{
#ifdef _UNICODE
	UnicodeToChar(strData,pchData,nLength);
#else
	strcpy(pchData,strData);
#endif

}

void COLXMLFile::IntToChar(int iData,char* pchData,int nLength)
{
	_itoa_s(iData,pchData,nLength,10);
}

bool COLXMLFile::CreateOLanguageFile(const char* pchFileName,int nType,bool bSave)
{
	m_xmlDoc.Clear();

	m_xmlDoc.SetValue(pchFileName);

	//设置文件头
	m_xmlDoc.Parse(OLXMLKey_OLanguageHead);

	//设置O语言文件标记
	TiXmlElement xmlElementTemp(OLXMLKey_OLanguageFile);
	m_xmlDoc.InsertEndChild(xmlElementTemp)->ToElement()->SetAttribute(OLXMLKey_FileType,nType);

	if(bSave)
	{
		return SaveFile();
	}

	return true;
}

//打开O语言文件
int COLXMLFile::OpenOLanguageFile(const char* pchFileName)
{
	m_xmlDoc.Clear();

	//打开O语言文件
	bool bLoadFile = m_xmlDoc.LoadFile(pchFileName);
	if ( m_xmlDoc.Error() && m_xmlDoc.ErrorId() == TiXmlBase::TIXML_ERROR_OPENING_FILE ) 
	{		
		return -1;
	}

	//加载O语言文件
	if(!bLoadFile)
	{		
		return -1;
	}

	//判断文件合法性
	if(GetOLanguageFileElement() == NULL)
	{		
		return -1;
	}

	return GetType();
}

TiXmlDocument* COLXMLFile::GetXMLDoc()
{
	return &m_xmlDoc;
}

TiXmlElement* COLXMLFile::GetOLanguageFileElement()
{
	return GetXMLDoc()->FirstChildElement(OLXMLKey_OLanguageFile);
}

void COLXMLFile::SetType(int nType)
{
	//类型必须大于等于0
	assert(nType >= 0);

	TiXmlElement* pXmlElementOLanguageFile = GetOLanguageFileElement();
	assert(pXmlElementOLanguageFile);

	pXmlElementOLanguageFile->SetAttribute(OLXMLKey_FileType,nType);
}

int COLXMLFile::GetType()
{
	TiXmlElement* pXmlElementOLanguageFile = GetOLanguageFileElement();
	assert(pXmlElementOLanguageFile);
	
	return GetXmlElementAttributeValue(pXmlElementOLanguageFile,OLXMLKey_FileType);
}

bool COLXMLFile::SaveFile()
{
	return m_xmlDoc.SaveFile();
}

//解析ID
int COLXMLFile::GetXmlElementAttributeValue(TiXmlElement* pXmlElement,const char* pchAttributeName)
{
	assert(pXmlElement);

	//解析ID属性
	TiXmlAttribute* pXmlAttribute = NULL;
	pXmlAttribute = pXmlElement->FirstAttribute();
	while(pXmlAttribute != NULL)
	{
		if(strcmp(pXmlAttribute->Name(),pchAttributeName) == 0)
		{
			return pXmlAttribute->IntValue();
		}

		pXmlAttribute = pXmlAttribute->Next();
	}

	return 0;
}
