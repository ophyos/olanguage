
#include "stdafx.h"
#include "OFParse.h"

#include "../ofl/OFL.h"
#include "InterFaceFun.h"

#ifdef _DEBUG
#pragma comment(lib,"../debug/OFL.lib") 
#else
#pragma comment(lib,"../release/OFL.lib") 
#endif

//添加事件处理函数
void AddInterFaceFun()
{	
	AddInterfaceFunction(框架窗口关闭);	
	AddInterfaceFunction(框架窗口创建);	
	AddInterfaceFunction(框架窗口菜单处理);

	AddInterfaceFunction(关于对话框_关闭);	
}

bool Parse(char* pchFileName)
{
	//系统初始化
	if(!OFDefaultInit(-1))
		return false;

	//添加接口函数
	AddInterFaceFun();

	//解析界面代码，如果界面代码有错误则用窗口显示错误
	if(OFParse(pchFileName,1))
	{
		//显示主窗口
		//OFShowMainWnd("主窗口");
		OFShowMainWnd("框架窗口");
	}

	//程序即将退出，这里要进行必要的清理工作
	OFClear();

	return true;
}

