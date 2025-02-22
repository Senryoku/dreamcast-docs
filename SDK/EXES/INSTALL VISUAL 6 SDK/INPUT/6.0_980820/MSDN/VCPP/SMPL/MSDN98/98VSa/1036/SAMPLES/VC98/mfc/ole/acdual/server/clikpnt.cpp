// ClikPnt.cpp : implementation file
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
#include "AutoClik.h"
#include "ClikPnt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoClickPoint

IMPLEMENT_DYNCREATE(CAutoClickPoint, CCmdTarget)

CAutoClickPoint::CAutoClickPoint()
{
	EnableAutomation();

	// To keep the application running as long as an OLE automation
	//  object is active, the constructor calls AfxOleLockApp.

	AfxOleLockApp();
}

CAutoClickPoint::~CAutoClickPoint()
{
	// To terminate the application when all objects created with
	//  with OLE automation, the destructor calls AfxOleUnlockApp.

	AfxOleUnlockApp();
}

void CAutoClickPoint::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//  OnFinalRelease is called.  This implementation deletes the
	//  object.  Add additional cleanup required for your object before
	//  deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CAutoClickPoint, CCmdTarget)
	//{{AFX_MSG_MAP(CAutoClickPoint)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoClickPoint, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAutoClickPoint)
	DISP_PROPERTY(CAutoClickPoint, "x", m_x, VT_I2)
	DISP_PROPERTY(CAutoClickPoint, "y", m_y, VT_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// DUAL_SUPPORT_START
// Original Code:
//     // Note: we add support for IID_IAutoClickPoint to support typesafe binding
//     //  from VBA.  This IID must match the GUID that is attached to the
//     //  dispinterface in the .ODL file.
//
//     // {0368D830-A050-11CE-B0F3-00AA006C28B3}
//     static const IID IID_IAutoClickPoint =
//     { 0x368d830, 0xa050, 0x11ce, { 0xb0, 0xf3, 0x0, 0xaa, 0x0, 0x6c, 0x28, 0xb3 } };
//
//     BEGIN_INTERFACE_MAP(CAutoClickPoint, CCmdTarget)
//          INTERFACE_PART(CAutoClickPoint, IID_IAutoClickPoint, Dispatch)
//     END_INTERFACE_MAP()

// Note: we add support for DIID_IAutoClickPoint to support typesafe binding
// from VBA.  We add support for IID_IDualAutoClickPoint to support our
// dual interface. See ACDual.H for the definition of DIID_IAutoClickPoint
// and IID_IDualAutoClickPoint.
//
// DUAL_ERRORINFO_PART indicates we support OLE Automation
// error handling.
//

BEGIN_INTERFACE_MAP(CAutoClickPoint, CCmdTarget)
	INTERFACE_PART(CAutoClickPoint, DIID_IAutoClickPoint, Dispatch)
	INTERFACE_PART(CAutoClickPoint, IID_IDualAutoClickPoint, DualAutoClickPoint)
	DUAL_ERRORINFO_PART(CAutoClickPoint)
END_INTERFACE_MAP()
// DUAL_SUPPORT_END

/////////////////////////////////////////////////////////////////////////////
// CAutoClickPoint message handlers

// DUAL_SUPPORT_START

// delegate standard IDispatch methods to MFC IDispatch implementation
DELEGATE_DUAL_INTERFACE(CAutoClickPoint, DualAutoClickPoint)

// Our method and property functions can generally just
// delegate back to the methods we generated using
// ClassWizard. However, if we set up properties to
// access variables directly, we will need to write the
// code to get/put the value into the variable.

STDMETHODIMP CAutoClickPoint::XDualAutoClickPoint::put_x(short newX)
{
	METHOD_PROLOGUE(CAutoClickPoint, DualAutoClickPoint)

	TRY_DUAL(IID_IDualAutoClickPoint)
	{
		pThis->m_x = newX;
		return NOERROR;
	}
	CATCH_ALL_DUAL
}

STDMETHODIMP CAutoClickPoint::XDualAutoClickPoint::get_x(short FAR* retval)
{
	METHOD_PROLOGUE(CAutoClickPoint, DualAutoClickPoint)

	TRY_DUAL(IID_IDualAutoClickPoint)
	{
		*retval = pThis->m_x;
		return NOERROR;
	}
	CATCH_ALL_DUAL
}

STDMETHODIMP CAutoClickPoint::XDualAutoClickPoint::put_y(short newY)
{
	METHOD_PROLOGUE(CAutoClickPoint, DualAutoClickPoint)

	TRY_DUAL(IID_IDualAutoClickPoint)
	{
		pThis->m_y = newY;
		return NOERROR;
	}
	CATCH_ALL_DUAL
}

STDMETHODIMP CAutoClickPoint::XDualAutoClickPoint::get_y(short FAR* retval)
{
	METHOD_PROLOGUE(CAutoClickPoint, DualAutoClickPoint)

	TRY_DUAL(IID_IDualAutoClickPoint)
	{
		*retval = pThis->m_y;
		return NOERROR;
	}
	CATCH_ALL_DUAL
}

// Implement ISupportErrorInfo to indicate we support the
// OLE Automation error handler.
IMPLEMENT_DUAL_ERRORINFO(CAutoClickPoint, IID_IDualAutoClickPoint)

// DUAL_SUPPORT_END
