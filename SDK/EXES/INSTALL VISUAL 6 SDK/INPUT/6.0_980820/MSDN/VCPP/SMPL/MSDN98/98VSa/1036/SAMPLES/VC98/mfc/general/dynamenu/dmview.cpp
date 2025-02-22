// dmview.cpp
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
//
// Purpose: implementation of the CDynaMenuView class
//
// Functions:
//   Most of this file was generated by AppWizard.  The functions
//   which contain code specific to this sample are:
//
//      CDynaMenuView::OnDraw()             -- draw the view contents

#include "stdafx.h"
#include "dynamenu.h"

#include "dmdoc.h"
#include "dmview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView

IMPLEMENT_DYNCREATE(CDynaMenuView, CView)

BEGIN_MESSAGE_MAP(CDynaMenuView, CView)
	//{{AFX_MSG_MAP(CDynaMenuView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView construction/destruction

CDynaMenuView::CDynaMenuView()
{
	// TODO: add construction code here
}

CDynaMenuView::~CDynaMenuView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView drawing

//***********************************************************************
// Function: CDynaMenuView::OnDraw()
//
// Purpose:
//    OnDraw is called by the framework to render an image of the
//    document.
//
//    We'll just put a string in the center of the client area for
//    demonstration purposes.  The string is drawn in the current
//    color selected for the associated document.
//
// Parameters:
//    none
//
// Returns:
//    none.
//
// Comments:
//    see the CView::OnDraw() documentation for further information
//
//***********************************************************************
void CDynaMenuView::OnDraw(CDC* pDC)
{
	CDynaMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// set color to use for text
	int iColor   = pDoc->m_iColor;
	COLORREF crf = CDynaMenuDoc::m_aColorDef[iColor].m_crf;

	pDC->SetTextColor(crf);
	pDC->SetBkMode(TRANSPARENT);

	// output a string to the center of the client area
	CRect rc;
	GetClientRect(rc);
	pDC->DrawText(_T("This text is displayed in the current color."), -1,
				  rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView printing

BOOL CDynaMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDynaMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDynaMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView diagnostics

#ifdef _DEBUG
void CDynaMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CDynaMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynaMenuDoc* CDynaMenuView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CDynaMenuDoc, m_pDocument);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynaMenuView message handlers
