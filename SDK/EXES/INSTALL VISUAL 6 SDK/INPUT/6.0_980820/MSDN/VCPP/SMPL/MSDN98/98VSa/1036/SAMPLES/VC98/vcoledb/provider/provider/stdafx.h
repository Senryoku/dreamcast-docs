// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
//
// This is a part of the ActiveX Template Library.
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#if !defined(AFX_STDAFX_H__254F556D_8C6D_11D0_90B2_00AA00A70DB8__INCLUDED_)
#define AFX_STDAFX_H__254F556D_8C6D_11D0_90B2_00AA00A70DB8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_MULTI_THREADED

#ifdef _DEBUG
#define _ATL_DEBUG_QI
#endif //_DEBUG


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <atlcom.h>
#include <atldb.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__254F556D_8C6D_11D0_90B2_00AA00A70DB8__INCLUDED)
