// AutoAggB.h : Declaration of the CAutoAggB
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "aggres.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Aggreg

class CAutoAggB :
	public IDispatchImpl<IAutoAggB, &IID_IAutoAggB, &LIBID_AGGREGLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CAutoAggB,&CLSID_CAutoAggB>
{
public:
	CAutoAggB(){}
BEGIN_COM_MAP(CAutoAggB)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAutoAggB)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CAutoAggB)
// Remove the comment from the line above if you don't want your object to
// support aggregation.  The default is to support it

DECLARE_REGISTRY_RESOURCEID(IDR_AutoAggB)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAutoAggB
public:
	STDMETHOD(get_Name)(BSTR* pbstrName);
};
