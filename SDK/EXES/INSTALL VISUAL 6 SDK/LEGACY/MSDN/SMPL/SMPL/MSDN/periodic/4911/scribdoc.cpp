// scribdoc.cpp : implementation of the CScribDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//

#include "stdafx.h"
#include "scribble.h"

#include "scribdoc.h"
#include "pendlg.h"
#include "scribvw.h"
#include "scribitm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribDoc

IMPLEMENT_DYNCREATE(CScribDoc, CDocObjectServerDoc)

BEGIN_MESSAGE_MAP(CScribDoc, CDocObjectServerDoc)
	//{{AFX_MSG_MAP(CScribDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, OnPenWidths)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribDoc construction/destruction

CScribDoc::CScribDoc()
{
	m_sizeDoc = CSize(200, 200);
}

CScribDoc::~CScribDoc()
{
}

BOOL CScribDoc::OnNewDocument()
{
	if (!CDocObjectServerDoc::OnNewDocument())
		return FALSE;
	InitDocument();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CScribDoc serialization

void CScribDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sizeDoc;
	}
	else
	{
		ar >> m_sizeDoc;
	}
	m_strokeList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScribDoc diagnostics

#ifdef _DEBUG
void CScribDoc::AssertValid() const
{
	CDocObjectServerDoc::AssertValid();
}

void CScribDoc::Dump(CDumpContext& dc) const
{
	CDocObjectServerDoc::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribDoc commands

BOOL CScribDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocObjectServerDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}

void CScribDoc::DeleteContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}
	CDocObjectServerDoc::DeleteContents();
}

void CScribDoc::InitDocument()
{
	m_bThickPen = FALSE;
	m_nThinWidth = 2;   // default thin pen is 2 pixels wide
	m_nThickWidth = 5;  // default thick pen is 5 pixels wide
	ReplacePen();       // initialze pen according to current width

	// default document size is 2 x 2 inches
	m_sizeDoc = CSize(200,200);

}

CStroke* CScribDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();  // Mark the document as having been modified, for
						// purposes of confirming File Close.
	return pStrokeItem;
}




/////////////////////////////////////////////////////////////////////////////
// CStroke

IMPLEMENT_SERIAL(CStroke, CObject, 2)

CStroke::CStroke()
{
	// This empty constructor should be used by serialization only
}

CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		ar >> m_rectBounding;
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(m_pointArray[i]);
	}

	pDC->SelectObject(pOldPen);
	return TRUE;
}

void CScribDoc::OnEditClearAll()
{
	DeleteContents();
	SetModifiedFlag();  // Mark the document as having been modified, for
						// purposes of confirming File Close.
	UpdateAllViews(NULL);
}

void CScribDoc::OnPenThickOrThin()
{
	// Toggle the state of the pen between thin or thick.
	m_bThickPen = !m_bThickPen;

	// Change the current pen to reflect the new user-specified width.
	ReplacePen();
}


void CScribDoc::ReplacePen()
{
	m_nPenWidth = m_bThickPen? m_nThickWidth : m_nThinWidth;

	// Change the current pen to reflect the new user-specified width.
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)); // solid black
}

void CScribDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	// Enable the command user interface object (menu item or tool bar
	// button) if the document is non-empty, i.e., has at least one stroke.
	pCmdUI->Enable(!m_strokeList.IsEmpty());
}


void CScribDoc::OnUpdatePenThickOrThin(CCmdUI* pCmdUI)
{
	// Add check mark to Draw Thick Line menu item, if the current
	// pen width is "thick".
	pCmdUI->SetCheck(m_bThickPen);
}


void CScribDoc::OnPenWidths()
{
	CPenWidthsDlg dlg;
	// Initialize dialog data
	dlg.m_nThinWidth = m_nThinWidth;
	dlg.m_nThickWidth = m_nThickWidth;

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.m_nThinWidth;
		m_nThickWidth = dlg.m_nThickWidth;

		// Update the pen that is used by views when drawing new strokes,
		// to reflect the new pen width definitions for "thick" and "thin".
		ReplacePen();
	}
}

void CStroke::FinishStroke()
{
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize()==0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = m_pointArray[0];
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = m_pointArray[i];
		m_rectBounding.left     = min(m_rectBounding.left, pt.x);
		m_rectBounding.right    = max(m_rectBounding.right, pt.x);
		m_rectBounding.top      = max(m_rectBounding.top, pt.y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	return;
}

COleServerItem* CScribDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CScribItem* pItem = new CScribItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

void CScribDoc::OnSetItemRects(LPCRECT lpPosRect, LPCRECT lpClipRect)
{
	// call base class to change the size of the window
	CDocObjectServerDoc::OnSetItemRects(lpPosRect, lpClipRect);

	// notify first view that scroll info should change
	POSITION pos = GetFirstViewPosition();
	CScribView* pView = (CScribView*)GetNextView(pos);
	pView->SetScrollInfo();
}

void CScribDoc::OnEditCopy()
{
	CScribItem* pItem = GetEmbeddedItem();
	pItem->CopyToClipboard(TRUE);
}


