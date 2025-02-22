// inputvw.cpp : implementation file
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
#include "viewex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputView

IMPLEMENT_DYNCREATE(CInputView, CFormView)

CInputView::CInputView()
	: CFormView(CInputView::IDD)
{
	//{{AFX_DATA_INIT(CInputView)
	m_strData = "";
	m_iColor = -1;
	//}}AFX_DATA_INIT
}

CInputView::~CInputView()
{
}

void CInputView::OnUpdate(CView*, LPARAM, CObject*)
{
	CMainDoc* pDoc = GetDocument();
	m_strData = pDoc->m_strData;

	if (pDoc->m_colorData == RGB(255, 0, 0))
		m_iColor = 0;
	else if (pDoc->m_colorData == RGB(0, 255, 0))
		m_iColor = 1;
	else if (pDoc->m_colorData == RGB(0, 0, 255))
		m_iColor = 2;
	else
		m_iColor = -1;

TRACE2("OnUpdate: m_iColor = %d ($%lx)\n", m_iColor, pDoc->m_colorData);

	UpdateData(FALSE);  // set the data into the controls
}

void CInputView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputView)
	DDX_Text(pDX, IDC_EDIT1, m_strData);
	DDX_Radio(pDX, IDC_RADIO1, m_iColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputView, CFormView)
	//{{AFX_MSG_MAP(CInputView)
	ON_EN_CHANGE(IDC_EDIT1, OnDataChange)
	ON_BN_CLICKED(IDC_RADIO1, OnDataChange)
	ON_BN_CLICKED(IDC_RADIO2, OnDataChange)
	ON_BN_CLICKED(IDC_RADIO3, OnDataChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputView message handlers

void CInputView::OnDataChange()
{
	if (!UpdateData())
		return;

	CMainDoc* pDoc = GetDocument();
	COLORREF color = RGB(255 * (m_iColor == 0),
						255 * (m_iColor == 1),
						255 * (m_iColor == 2));

	BOOL bUpdate = FALSE;
	if (m_strData != pDoc->m_strData)
	{
		pDoc->m_strData = m_strData;
		bUpdate = TRUE;
	}
	if (color != pDoc->m_colorData)
	{
		pDoc->m_colorData = color;
		bUpdate = TRUE;
	}
	if (bUpdate)
	{
		// if the document stored data then we would call SetModifiedFlag here
		pDoc->UpdateAllViews(this);
	}
}

/////////////////////////////////////////////////////////////////////////////
