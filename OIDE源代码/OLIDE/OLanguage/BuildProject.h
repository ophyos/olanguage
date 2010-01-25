#pragma once

//±‡“Îπ§≥Ã
typedef void (* BUILDCMDINTERFACE)(int,const char*,int);
typedef void (* BUILDPROJECT)(const char*,BUILDCMDINTERFACE);

enum BUILD_INTERFACE_CMD_TYPE
{
	BICT_NULL,
	BICT_OUTPUT,
	BICT_BUILD_CODE,
	BICT_LINK_EXE
};

class CBuildProject
{
	friend class CProjectProperty;

public:
	CBuildProject(void);
	~CBuildProject(void);

public:

	static void BuildProject(CProjectProperty* pProjectProperty);

private:

	static void Build(const char* pchFileName);
	//static void OutPutError();
};
