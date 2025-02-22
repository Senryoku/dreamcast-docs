//**********************************************************************
// File name: IOIPS.H
//
//      Definition of COleInPlaceSite
//
// Copyright (c) 1992 - 1997 Microsoft Corporation. All rights reserved.
//**********************************************************************
#if !defined( _IOIPS_H_ )
#define _IOIPS_H_


class CSimpleSite;

interface COleInPlaceSite : public IOleInPlaceSite
{
	int m_nCount;
	CSimpleSite FAR * m_pSite;

	COleInPlaceSite(CSimpleSite FAR *pSite) {
		OutputDebugString("In IOIPS's constructor\r\n");
		m_pSite = pSite;
		m_nCount = 0;
		};

	~COleInPlaceSite() {
		OutputDebugString("In IOIPS;s destructor\r\n");
		assert(m_nCount == 0);
		};

	STDMETHODIMP QueryInterface (REFIID riid, LPVOID FAR* ppv);
	STDMETHODIMP_(ULONG) AddRef ();
	STDMETHODIMP_(ULONG) Release ();

	STDMETHODIMP GetWindow (HWND FAR* lphwnd);
	STDMETHODIMP ContextSensitiveHelp (BOOL fEnterMode);

	// *** IOleInPlaceSite methods ***
	STDMETHODIMP CanInPlaceActivate ();
	STDMETHODIMP OnInPlaceActivate ();
	STDMETHODIMP OnUIActivate ();
	STDMETHODIMP GetWindowContext (LPOLEINPLACEFRAME FAR* lplpFrame,
								   LPOLEINPLACEUIWINDOW FAR* lplpDoc,
								   LPRECT lprcPosRect,
								   LPRECT lprcClipRect,
								   LPOLEINPLACEFRAMEINFO lpFrameInfo);
	STDMETHODIMP Scroll (SIZE scrollExtent);
	STDMETHODIMP OnUIDeactivate (BOOL fUndoable);
	STDMETHODIMP OnInPlaceDeactivate ();
	STDMETHODIMP DiscardUndoState ();
	STDMETHODIMP DeactivateAndUndo ();
	STDMETHODIMP OnPosRectChange (LPCRECT lprcPosRect);
};

#endif
