// tableset.h : interface of the CTables class
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

/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

class CTables : public CRecordset
{
DECLARE_DYNAMIC(CTables)

public:
	CTables(CDatabase* pDatabase = NULL);
	BOOL Open(UINT nOpenType = forwardOnly, LPCSTR lpszSQL = NULL,
		DWORD dwOptions = readOnly);

// Field/Param Data
	//{{AFX_FIELD(CTables, CRecordset)
	CString m_strQualifier;
	CString m_strOwner;
	CString m_strName;
	CString m_strType;
	CString m_strRemarks;
	//}}AFX_FIELD

	CString m_strQualifierParam;
	CString m_strOwnerParam;
	CString m_strNameParam;
	CString m_strTypeParam;

// Implementation
protected:
	virtual CString GetDefaultConnect();    // default connection string
	virtual CString GetDefaultSQL();    // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
};
