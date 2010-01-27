// OFOwner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "OFOwner.h"
#include "OFParse.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

#ifdef _DEBUG
	Parse("F:\\Myprogram\\OL\\OFL\\Release\\界面\\框架窗口.txt");
	//Parse("F:\\Myprogram\\OL\\OFL\\Debug\\界面\\界面语言示例.txt");
#else
	//Parse("界面\\界面语言示例.txt");
	Parse("界面\\框架窗口.txt");
#endif

	return 0;
}

