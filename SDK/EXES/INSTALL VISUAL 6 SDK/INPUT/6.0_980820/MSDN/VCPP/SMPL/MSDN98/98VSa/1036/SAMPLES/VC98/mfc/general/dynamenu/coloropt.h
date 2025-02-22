// coloropt.h
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
// Purpose: interface of the CColorOptDlg class
//
// Functions:
//   Most of this file was generated by AppWizard.  The functions
//   which contain code specific to this sample are:
//
//      CColorOptDlg::CColorOptDlg()         -- dialog constructor
//      CColorOptDlg::DoDataExchange()       -- connect data to controls
//      CColorOptDlg::OnInitDialog()         -- initialize dialog
//
//   These functions are implemented in coloropt.cpp.

/////////////////////////////////////////////////////////////////////////////
// CColorOptDlg dialog

class CDynaMenuDoc;  // defined in dmdoc.h

class CColorOptDlg : public CDialog
{
// Construction
public:
	CColorOptDlg(CDynaMenuDoc* pDoc, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CColorOptDlg)
	enum { IDD = IDD_CHANGECOLOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CDynaMenuDoc* m_pDoc;  // document we want to update

	// Generated message map functions
	//{{AFX_MSG(CColorOptDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
