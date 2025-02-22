// Random.h : Declaration of the CRandom
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

#include "connres.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRandom

const int nMaxSessions = 10;

class CRandom :
	public IDispatchImpl<IRandom, &IID_IRandom, &LIBID_CONNECTLib>,
	public IConnectionPointContainerImpl<CRandom>,
	public IConnectionPointImpl<CRandom, &IID_IRandomEvent, CComDynamicUnkArray>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CRandom,&CLSID_CoRandom>
{
public:
	CRandom()
	{
		memset(m_rsArray, 0, nMaxSessions*sizeof(RandomSessionData));
	}
	~CRandom();

BEGIN_COM_MAP(CRandom)
	COM_INTERFACE_ENTRY2(IDispatch, IRandom)
	COM_INTERFACE_ENTRY(IRandom)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
//  DECLARE_NOT_AGGREGATABLE(CRandom)
// Remove the comment from the line above if you don't want your object to
// support aggregation.  The default is to support it

	DECLARE_REGISTRY_RESOURCEID(IDR_Random)

// Connection Point
	BEGIN_CONNECTION_POINT_MAP(CRandom)
		CONNECTION_POINT_ENTRY(IID_IRandomEvent)
	END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRandom
	STDMETHOD(Start)(long* pnID);
	STDMETHOD(Stop)(long nID);
	STDMETHOD(StopAll)();

	// method to broadcast a call on the current connections
	HRESULT Fire(long  nID);
	// info associated to each session
	struct RandomSessionData
	{
		CRandom* pRandom;
		HANDLE m_hEvent;
		HANDLE m_hThread;
		int m_nID;
	};
protected:

	RandomSessionData m_rsArray[nMaxSessions];
	void CreateRandomSession(RandomSessionData& rs);

	_ThreadModel::AutoCriticalSection m_cs;
};
