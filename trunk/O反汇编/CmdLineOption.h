
#ifndef  _CMD_LINE_OPTION_H_
#define  _CMD_LINE_OPTION_H_

class CCmdLineOption
{
public:	

	CCmdLineOption();
	~CCmdLineOption();

	char  m_chCurExeDir[256];
	char* m_pchPeFile;
	char* m_pchLanguageFile;
	char* m_pchDoasmFile;

	void get_default_doasm_file();

private:

	char* m_pchDoasmFileTemp;
};

#endif //_CMD_LINE_OPTION_H_