// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C1AC210D_8ABF_11D1_B145_000000000000__INCLUDED_)
#define AFX_STDAFX_H__C1AC210D_8ABF_11D1_B145_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>
#include <afxcmn.h> 

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <ObjModel\addauto.h>
#include <ObjModel\appdefs.h>
#include <ObjModel\appauto.h>
#include <ObjModel\blddefs.h>
#include <ObjModel\bldauto.h>
#include <ObjModel\textdefs.h>
#include <ObjModel\textauto.h>
#include <ObjModel\dbgdefs.h>
#include <ObjModel\dbgauto.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C1AC210D_8ABF_11D1_B145_000000000000__INCLUDED)
