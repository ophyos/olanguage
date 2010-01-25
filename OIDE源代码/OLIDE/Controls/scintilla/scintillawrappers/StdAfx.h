#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif						

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE support
#include <afxtempl.h>		    // MFC template support

//Pull in support for Scintilla
#include "./Scintilla/platform.h"
#include "./Scintilla/scintilla.h"
#include "./Scintilla/SciLexer.h"
