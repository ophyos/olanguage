
#ifndef _OWI_SPLITTER_H_
#define _OWI_SPLITTER_H_

#include "../../ExportDefine.h"

OFL_API void _stdcall Splitter_SetControl1(void* pSplitter,void* c);
OFL_API void _stdcall Splitter_SetControl2(void* pSplitter,void* c);
OFL_API void* _stdcall Splitter_GetControl1(void* pSplitter);
OFL_API void* _stdcall Splitter_GetControl2(void* pSplitter);

OFL_API void _stdcall Splitter_DestroyControl(void* pSplitter);	 
OFL_API char* _stdcall Splitter_GetClass(void* pSplitter);
OFL_API char* _stdcall Splitter_GetCaption(void* pSplitter);
OFL_API void _stdcall Splitter_SetCaption(void* pSplitter,char* string);

#endif //_OWI_SPLITTER_H_