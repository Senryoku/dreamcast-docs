// containerMFC.h : main header file for the CONTAINERMFC application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_CONTAINERMFC_H__925782C7_9815_11D0_944C_00A0C903487E__INCLUDED_)
#define AFX_CONTAINERMFC_H__925782C7_9815_11D0_944C_00A0C903487E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCApp:
// See containerMFC.cpp for the implementation of this class
//

class CContainerMFCApp : public CWinApp
{
public:
	CContainerMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContainerMFCApp)
	public:
	virtual BOOL InitInstance();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CContainerMFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTAINERMFC_H__925782C7_9815_11D0_944C_00A0C903487E__INCLUDED_)
