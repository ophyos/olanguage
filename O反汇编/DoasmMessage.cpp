
#include "DoasmMessage.h"
#include "./DoasmDll.h"

struct DOASM_MESSAGE_INFO
{
	int   m_nMsgCode;
	char* m_pMessage;
};

DOASM_MESSAGE_INFO doasm_msg_info_chinese[] = 
{
	DOASM_MSG_NULL,                             "",	
	DOASM_MSG_PE_FILE_NOT_EXIST,                "\n%s 文件不存在!",
	DOASM_MSG_PE_FILE_INVALID,                  "\n%s 不是32位PE文件!",
	DOASM_MSG_LOAD_PE_FILE_FAILD,               "\n加载 %s 文件失败!",
	DOASM_MSG_LOAD_LANGUAGE_FILE_FAILD,         "\n%s 加载语言文件失败!",
	DOASM_MSG_OPEN_DOASM_FILE_FAILD,            "\n%s 打开反汇编文件(.doa)失败!",
	DOASM_MSG_DOASM_FILE_INFO,                  "反汇编文件:%s \n加载地址:%08X  入口地址:%08X\n",
	DOASM_MSG_SEGMENT_INFO_TITLE,               "\n  段基本信息,段个数:%04X",
	DOASM_MSG_SEGMENT_NAME,                     "\n    段名称:%s  ",
	DOASM_MSG_SEGMENT_INFO,                     "加载地址:%08X  文件位置:%08X  段大小:%08X  特征值:%08X",
	DOASM_MSG_CODE_SEGMENT,                     "\n\n----- 代码段(%s) [文件位置:%08X  段大小:%08X] -------\n",
	DOASM_MSG_NO_EXECUTE_SEGMENT,               "\n\n没有找到可执行段!",
	DOASM_MSG_ENTRY_POINT,                      ">>>程序入口 程序将从这里开始执行>>>\n",
	DOASM_MSG_ALL_ZERO_DATA,                    "全0数据\n",
	DOASM_MSG_NOT_INSTRUCTION_DATA,             "字符 '%s'  //非指令数据",
	DOASM_MSG_UNKNOW_INSTRUCTION_DATA,          "字节 '%02X'  //非指令数据",
	DOASM_MSG_LANGUAGE_INTER_CODE_INVALID,      "\n语言内码 (0x%08X) 无效!",
};

DOASM_MESSAGE_INFO doasm_msg_info_english[] = 
{
	DOASM_MSG_NULL,                             "",	
	DOASM_MSG_PE_FILE_NOT_EXIST,                "\n%s File Not Exist!",
	DOASM_MSG_PE_FILE_INVALID,                  "\n%s Not Bit32 PE File!",
	DOASM_MSG_LOAD_PE_FILE_FAILD,               "\nLoad %s File Faild!",
	DOASM_MSG_LOAD_LANGUAGE_FILE_FAILD,         "\n%s Load Language File Faild!",
	DOASM_MSG_OPEN_DOASM_FILE_FAILD,            "\n%s Open Doasm File(.doa) Faild!",
	DOASM_MSG_DOASM_FILE_INFO,                  "Disassembly of File:%s \nImagebase:%08X  Entry Point:%08X\n",
	DOASM_MSG_SEGMENT_INFO_TITLE,               "\n  Segment Information,Number of Segment:%04X",
	DOASM_MSG_SEGMENT_NAME,                     "\n    Name:%s  ",
	DOASM_MSG_SEGMENT_INFO,                     "RVA:%08X  Offset:%08X  Size:%08X  Flags:%08X",
	DOASM_MSG_CODE_SEGMENT,                     "\n\n----- Code Segment(%s) [Segment Offset:%08X  Segment Size:%08X] -------\n",
	DOASM_MSG_NO_EXECUTE_SEGMENT,               "\n\nNo Execute Segment!",
	DOASM_MSG_ENTRY_POINT,                      ">>>Program Entry Point>>>\n",
	DOASM_MSG_ALL_ZERO_DATA,                    "Byte 0 Dup(0)\n",
	DOASM_MSG_NOT_INSTRUCTION_DATA,             "Char '%s'  //Not Instruction Data",
	DOASM_MSG_UNKNOW_INSTRUCTION_DATA,          "Byte '%02X'  //Not Instruction Data",	
	DOASM_MSG_LANGUAGE_INTER_CODE_INVALID,      "\nLanguage Code (0x%08X) Invalid!",
};

char* GetDoasmMessageInfo(int nMsgCode)
{	
	DOASM_MESSAGE_INFO* p_msg_info = doasm_msg_info_chinese;
	int nMessageCount = sizeof(doasm_msg_info_chinese)/sizeof(doasm_msg_info_chinese[0]);

	switch(doi_GetLanguageType())
	{
	case DLT_ENGLISH:           p_msg_info = doasm_msg_info_english;break;
	case DLT_SIMPLE_CHINESE:    p_msg_info = doasm_msg_info_chinese;break;
	}
	
	for(int i=0;i<nMessageCount;++i)
	{
		if(p_msg_info[i].m_nMsgCode == nMsgCode)
			return p_msg_info[i].m_pMessage;
	}

	return 0;
}