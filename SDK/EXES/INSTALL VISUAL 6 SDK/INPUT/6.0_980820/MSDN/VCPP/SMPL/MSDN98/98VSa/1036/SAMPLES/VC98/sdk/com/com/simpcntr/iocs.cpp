//**********************************************************************
// File name: IOCS.CPP
//
//      Implementation file for COleClientSite
//
// Functions:
//
//      See IOCS.H for class definition
//
// Copyright (c) 1992 - 1997 Microsoft Corporation. All rights reserved.
//**********************************************************************

#include "pre.h"
#include "iocs.h"
#include "ias.h"
#include "ioipf.h"
#include "ioips.h"
#include "app.h"
#include "site.h"
#include "doc.h"


//**********************************************************************
//
// COleClientSite::QueryInterface
//
// Purpose:
//
//      Used for interface negotiation at this interface
//
// Parameters:
//
//      REFIID riid         -   A reference to the interface that is
//                              being queried.
//
//      LPVOID FAR* ppvObj  -   An out parameter to return a pointer to
//                              the interface.
//
// Return Value:
//
//      S_OK                -   The interface is supported.
//      E_NOINTERFACE       -   The interface is not supported
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//      CSimpleSite::QueryInterface SITE.CPP
//
// Comments:
//
//********************************************************************

STDMETHODIMP COleClientSite::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
        OutputDebugString("In IOCS::QueryInterface\r\n");

        // delegate to the container Site
        return m_pSite->QueryInterface(riid, ppvObj);
}

//**********************************************************************
//
// CSimpleApp::AddRef
//
// Purpose:
//
//      Adds to the reference count at the interface level.
//
// Parameters:
//
//      None
//
// Return Value:
//
//      ULONG   -   The new reference count of the interface
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//********************************************************************

STDMETHODIMP_(ULONG) COleClientSite::AddRef()
{
        OutputDebugString("In IOCS::AddRef\r\n");

        // increment the interface reference count (for debugging only)
        ++m_nCount;

        // delegate to the container Site
        return m_pSite->AddRef();
}


//**********************************************************************
//
// CSimpleApp::Release
//
// Purpose:
//
//      Decrements the reference count at this level
//
// Parameters:
//
//      None
//
// Return Value:
//
//      ULONG   -   The new reference count of the interface.
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//********************************************************************

STDMETHODIMP_(ULONG) COleClientSite::Release()
{
        OutputDebugString("In IOCS::Release\r\n");

        // decrement the interface reference count (for debugging only)
        --m_nCount;

        // delegate to the container Site
        return m_pSite->Release();
}

//**********************************************************************
//
// COleClientSite::SaveObject
//
// Purpose:
//
//      Called by the object when it wants to be saved to persistant
//      storage
//
// Parameters:
//
//      None
//
// Return Value:
//
//      S_OK
//
// Function Calls:
//      Function                            Location
//
//      OutputDebugString                   Windows API
//      IOleObject::QueryInterface          Object
//      IPersistStorage::SaveCompleted      Object
//      IPersistStorage::Release            Object
//      OleSave                             OLE API
//                           OLE API
//
// Comments:
//
//********************************************************************

STDMETHODIMP COleClientSite::SaveObject()
{
        CStabilize stabilize(m_pSite);
        LPPERSISTSTORAGE lpPS;
        SCODE sc = E_FAIL;

        OutputDebugString("In IOCS::SaveObject\r\n");

        // get a pointer to IPersistStorage
        HRESULT hErr = m_pSite->m_lpOleObject->QueryInterface(IID_IPersistStorage, (LPVOID FAR *)&lpPS);

        // save the object
        if (hErr == NOERROR)
                {
                sc =  OleSave(lpPS, m_pSite->m_lpObjStorage, TRUE) ;
                lpPS->SaveCompleted(NULL);
                lpPS->Release();
                }

        return sc;
}

//**********************************************************************
//
// COleClientSite::GetMoniker
//
// Purpose:
//
//      Not Implemented
//
// Parameters:
//
//      Not Implemented
//
// Return Value:
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//      This function is not implemented because we don't support
//      linking.
//
//********************************************************************

STDMETHODIMP COleClientSite::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER FAR* ppmk)
{
        OutputDebugString("In IOCS::GetMoniker\r\n");

        // need to null the out pointer
        *ppmk = NULL;

        return E_NOTIMPL;
}

//**********************************************************************
//
// COleClientSite::GetContainer
//
// Purpose:
//
//      Not Implemented
//
// Parameters:
//
//      Not Implemented
//
// Return Value:
//
//      Not Implemented
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//      Not Implemented
//
//********************************************************************

STDMETHODIMP COleClientSite::GetContainer(LPOLECONTAINER FAR* ppContainer)
{
        OutputDebugString("In IOCS::GetContainer\r\n");

        // NULL the out pointer
        *ppContainer = NULL;

        return E_NOTIMPL;
}

//**********************************************************************
//
// COleClientSite::ShowObject
//
// Purpose:
//
//      Not Implemented
//
// Parameters:
//
//      Not Implemented
//
// Return Value:
//
//      Not Implemented
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//      This function is not implemented because we don't support
//      linking.
//
//********************************************************************

STDMETHODIMP COleClientSite::ShowObject()
{
        OutputDebugString("In IOCS::ShowObject\r\n");
        return NOERROR;
}

//**********************************************************************
//
// COleClientSite::OnShowWindow
//
// Purpose:
//
//      Object calls this method when it is opening/closing non-InPlace
//      Window
//
// Parameters:
//
//      BOOL fShow  - TRUE if Window is opening, FALSE if closing
//
// Return Value:
//
//      S_OK
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//      InvalidateRect              Windows API
//                   OLE API
//
// Comments:
//
//********************************************************************

STDMETHODIMP COleClientSite::OnShowWindow(BOOL fShow)
{
        CStabilize stabilize(m_pSite);
        OutputDebugString("In IOCS::OnShowWindow\r\n");
        m_pSite->m_fObjectOpen = fShow;
        InvalidateRect(m_pSite->m_lpDoc->m_hDocWnd, NULL, TRUE);

        // if object window is closing, then bring container window to top
        if (! fShow) {
                BringWindowToTop(m_pSite->m_lpDoc->m_hDocWnd);
                SetFocus(m_pSite->m_lpDoc->m_hDocWnd);
        }
        return S_OK;
}

//**********************************************************************
//
// COleClientSite::RequestNewObjectLayout
//
// Purpose:
//
//      Not Implemented
//
// Parameters:
//
//      Not Implemented
//
// Return Value:
//
//      Not Implemented
//
// Function Calls:
//      Function                    Location
//
//      OutputDebugString           Windows API
//
// Comments:
//
//      Not Implemented
//
//********************************************************************

STDMETHODIMP COleClientSite::RequestNewObjectLayout()
{
        OutputDebugString("In IOCS::RequestNewObjectLayout\r\n");
        return E_NOTIMPL;
}
