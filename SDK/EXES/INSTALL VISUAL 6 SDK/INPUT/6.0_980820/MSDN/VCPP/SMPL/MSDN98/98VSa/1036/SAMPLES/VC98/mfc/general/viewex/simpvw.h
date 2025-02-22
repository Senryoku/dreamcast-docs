// simpvw.h : interface of the simple view classes
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

// CTextView - text output
// CColorView - color output

/////////////////////////////////////////////////////////////////////////////

class CTextView : public CView
{
protected: // create from serialization only
	CTextView();
	DECLARE_DYNCREATE(CTextView)

// Attributes
public:
	CMainDoc* GetDocument()
			{
				ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
				return (CMainDoc*) m_pDocument;
			}

// Operations
public:

// Implementation
public:
	virtual ~CTextView();
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CColorView : public CView
{
protected: // create from serialization only
	CColorView();
	DECLARE_DYNCREATE(CColorView)

// Attributes
public:
	CMainDoc* GetDocument()
			{
				ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
				return (CMainDoc*) m_pDocument;
			}

// Operations
public:

// Implementation
public:
	virtual ~CColorView();
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView,
					CView* pDeactiveView);

// Generated message map functions
protected:
	//{{AFX_MSG(CColorView)
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
