// pressdlg.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CPressMeDlg dialog


class CPressMeDlg : public CDialog
{
protected:
	CBitmapButton m_buttonOk;
	CBitmapButton m_buttonCancel;
public:
	//{{AFX_DATA(CPressMeDlg)
		enum { IDD = IDD_PRESS_ME };
	//}}AFX_DATA
	CPressMeDlg();

	BOOL OnInitDialog();
	//{{AFX_MSG(CPressMeDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
