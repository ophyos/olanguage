
#include "stdafx.h"
#include "ReadDebugData.h"
#include "PeFile.h"

CReadDebugData::CReadDebugData()
{
	m_uiCodeSegmentAddr = 0;
	m_uiCodeSegmentLength = 0;
	m_uiDataSegmentAddr = 0;		
	m_uiDataSegmentLength = 0;
}

CReadDebugData::~CReadDebugData()
{

}

int CReadDebugData::SearchSourceFileNameList(const CString& str)
{
	for(int i=0;i<m_strarrSourceFileNameList.GetCount();++i)
	{
		if(m_strarrSourceFileNameList.GetAt(i) == str)
			return i;
	}

	return -1;
}

bool CReadDebugData::Read(TCHAR* pchPEFileName)
{
	DWORD dwBinType = 0;
	//判断是否为32位可执行文件
	if((!GetBinaryType(pchPEFileName,&dwBinType)) || (dwBinType != SCS_32BIT_BINARY))
	{
		return false;
	}

	CPeFile peFile;
	peFile.SetFileName(pchPEFileName);
	if(!peFile.LoadFile())//加载PE文件
	{
		return false;
	}

	PIMAGE_FILE_HEADER      pFH=NULL;
	PIMAGE_SECTION_HEADER   pSH=NULL;
	PIMAGE_OPTIONAL_HEADER  pOH=NULL;

	pFH = peFile.GetFileHeader();
	pOH = peFile.GetOptionalHeader();
	pSH = peFile.GetFirstSectionHeader();	

	m_strarrSourceFileNameList.RemoveAll();
	m_debugDataItemLine.ClearList();

	bool bResult = false;
	for(int i=0;i<pFH->NumberOfSections;i++)
	{
		//如果段具有可执行属性则说明是代码段
		if((pSH->Characteristics & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE)
		{
			m_uiCodeSegmentAddr = pOH->ImageBase + pSH->VirtualAddress;
			m_uiCodeSegmentLength = pSH->SizeOfRawData;
		}
		//如果是数据段
		else if(strcmp((char*)pSH->Name,".data") == 0)
		{
			m_uiDataSegmentAddr = pOH->ImageBase + pSH->VirtualAddress;
			m_uiDataSegmentLength = pSH->SizeOfRawData;
		}
		//如果是调试段
		else if(strcmp((char*)pSH->Name,".odebug") == 0)
		{
			unsigned char *pSectionData = (unsigned char*)(pSH->PointerToRawData + (unsigned char*)peFile.m_stMapFile.ImageBase);
			unsigned char *pSectionDataStart = pSectionData;

			//如果在调试段数据范围内且最开始的两个字节是"OD"标识则表示是合法的调试数据
			while((pSectionData < pSectionDataStart+pSH->SizeOfRawData) && (pSectionData[0] == 'O') && (pSectionData[1] == 'D'))
			{
				pSectionData += 2;
				unsigned short usSourceFileNameCount = *(unsigned short*)pSectionData;
				pSectionData += sizeof(unsigned short);

				int* pIndexArray = new int[usSourceFileNameCount];
				if(pIndexArray)
				{
					//读取源代码文件名
					CString strSourceFileName;
					for(unsigned short i=0;i<usSourceFileNameCount;++i)
					{
						strSourceFileName = (char*)pSectionData;

						pIndexArray[i] = SearchSourceFileNameList(strSourceFileName);
						if(pIndexArray[i] < 0)//没有搜索到
						{
							m_strarrSourceFileNameList.Add(strSourceFileName);
							pIndexArray[i] = m_strarrSourceFileNameList.GetCount() - 1;
						}

						pSectionData += strlen((char*)pSectionData);
						pSectionData ++;
					}

					//读取调试数据项
					unsigned long usDebugItemCount = *(unsigned long*)pSectionData;
					pSectionData += sizeof(unsigned long);
					for(unsigned long i=0;i<usDebugItemCount;++i)
					{
						unsigned short usDebugItemType = *(unsigned short*)pSectionData;
						pSectionData += sizeof(unsigned short);
						switch(usDebugItemType)
						{
							//行数据
						case DEBUG_NODE_TYPE_LINE:
							{
								DEBUG_DATA_ITEM_LINE debug_data_item_line;
								debug_data_item_line.m_usFileIndex = *(unsigned short*)pSectionData;
								if( (debug_data_item_line.m_usFileIndex >= 0) && (debug_data_item_line.m_usFileIndex < usSourceFileNameCount))
								{
									debug_data_item_line.m_usFileIndex = pIndexArray[debug_data_item_line.m_usFileIndex];
									pSectionData += sizeof(unsigned short);
									debug_data_item_line.m_lLine = *(long*)pSectionData;
									debug_data_item_line.m_lLine --; //实际的行号与得到的行号差1
									pSectionData += sizeof(long);
									debug_data_item_line.m_ulAddr = *(unsigned long*)pSectionData;
									pSectionData += sizeof(unsigned long);

									m_debugDataItemLine.Add(debug_data_item_line);	
								}												

								break;
							}
						}
					}

					delete[] pIndexArray;
				}				
			}	

			bResult = true;
		}

		pSH++;
	}

	//peFile.UnLoadFile();

	return bResult;
}

DEBUG_DATA_ITEM_LINE* CReadDebugData::GetMatchLineItem(TCHAR* pchFileName,int nLine,bool bMatchLine)
{
	int nFileIndex = -1;
	for(int i=0;i<m_strarrSourceFileNameList.GetCount();++i)
	{
		if(m_strarrSourceFileNameList.GetAt(i) == pchFileName)
		{
			nFileIndex = i;
			break;
		}
	}
	if(nFileIndex < 0)
		return 0;

	for(m_debugDataItemLine.GetFirstElement();!m_debugDataItemLine.isEnd();m_debugDataItemLine.GetNextElement())
	{
		DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = m_debugDataItemLine.GetCurDebugDataItemLine();
		//找到相应的行
		if((p_debug_data_item_line->m_usFileIndex == nFileIndex) && (p_debug_data_item_line->m_lLine == nLine))
		{
			return p_debug_data_item_line;
		}
	}

	//精确匹配行
	if(bMatchLine)
	{
		return  0;
	}

	//没有找到对应的行则搜索最靠近的行
	DEBUG_DATA_ITEM_LINE* p_debug_data_item_line_temp = 0;
	for(m_debugDataItemLine.GetFirstElement();!m_debugDataItemLine.isEnd();m_debugDataItemLine.GetNextElement())
	{
		DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = m_debugDataItemLine.GetCurDebugDataItemLine();		
		if(p_debug_data_item_line->m_usFileIndex == nFileIndex)
		{
			if(p_debug_data_item_line->m_lLine > nLine)
			{
				if(p_debug_data_item_line_temp == 0)
				{
					p_debug_data_item_line_temp = p_debug_data_item_line;
				}
				else
				{
					if(p_debug_data_item_line->m_lLine < p_debug_data_item_line_temp->m_lLine)
					{
						p_debug_data_item_line_temp = p_debug_data_item_line;
					}
				}
			}
		}
	}

	return p_debug_data_item_line_temp;
}

DEBUG_DATA_ITEM_LINE* CReadDebugData::GetMatchAddrItem(unsigned long ulAddr)
{
	DEBUG_DATA_ITEM_LINE* p_debug_data_item_line = 0;
	for(m_debugDataItemLine.GetFirstElement();!m_debugDataItemLine.isEnd();m_debugDataItemLine.GetNextElement())
	{
		p_debug_data_item_line = m_debugDataItemLine.GetCurDebugDataItemLine();
		if(p_debug_data_item_line->m_ulAddr == ulAddr)
		{
			return p_debug_data_item_line;
		}
	}

	return 0;
}