#pragma once

class COLFile
{
public:
	COLFile(void);
	~COLFile(void);

	bool CreateFile(const char* pchFileName,bool bSave = true);
	bool WriteFile(const char* pchFileName);
	bool ReadFile(const char* pchName,const char* pchObjectSpacePath,bool bIsObjectFullName = true);
	void CloseFile();	
};
