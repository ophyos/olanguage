
#ifndef  _COMMON_H_
#define  _COMMON_H_

//由相对路径得到绝对路径
//如果strPathRefer为空,则得到相对于当前工作目录的绝对路径
BOOL GetAbsolutePathByRelativePath(CString& strRelativePath,const CString& strPathRefer);
void DelayNop(DWORD dwMillisecond); //延迟空操作

#endif //_COMMON_H_