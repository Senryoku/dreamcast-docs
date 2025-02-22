// ipdridoc.cpp : implementation of the CDriverDoc class
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

#include "stdafx.h"
#include "ipdrive.h"

#include "ipdridoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverDoc

IMPLEMENT_DYNCREATE(CDriverDoc, CDocument)

BEGIN_MESSAGE_MAP(CDriverDoc, CDocument)
	//{{AFX_MSG_MAP(CDriverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverDoc construction/destruction

CDriverDoc::CDriverDoc()
{
	if (!m_map.CreateDispatch(_T("mfc.inproc.varmap")))
	{
		AfxMessageBox(IDP_UNABLE_TO_CREATE_INPROC);
		AfxThrowUserException();
	}
}

CDriverDoc::~CDriverDoc()
{
}

BOOL CDriverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDriverDoc serialization

void CDriverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDriverDoc diagnostics

#ifdef _DEBUG
void CDriverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDriverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDriverDoc commands
