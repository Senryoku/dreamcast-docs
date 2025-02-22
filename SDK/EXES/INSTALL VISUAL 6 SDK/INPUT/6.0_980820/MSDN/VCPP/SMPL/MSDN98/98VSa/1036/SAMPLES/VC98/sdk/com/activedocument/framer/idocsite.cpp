/*
 * IDOCSITE.CPP
 * IOleDocumentSite for Document Objects CSite class
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#include "framer.h"


/*
 * CImpIOleDocumentSite::CImpIOleDocumentSite
 * CImpIOleDocumentSite::~CImpIOleDocumentSite
 *
 * Parameters (Constructor):
 *  pSite           PCSite of the site we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleDocumentSite::CImpIOleDocumentSite(PCSite pSite
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pSite=pSite;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleDocumentSite::~CImpIOleDocumentSite(void)
    {
    return;
    }



/*
 * CImpIOleDocumentSite::QueryInterface
 * CImpIOleDocumentSite::AddRef
 * CImpIOleDocumentSite::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleDocumentSite object.
 */

STDMETHODIMP CImpIOleDocumentSite::QueryInterface(REFIID riid
    , void **ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleDocumentSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleDocumentSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleDocumentsite::ActivateMe
 *
 * Purpose:
 *  Instructs the container to activate the object in this site as
 *  a document object.
 *
 * Parameters:
 *  pView           IOleDocumentView * of the object to activate.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise.
 */

STDMETHODIMP CImpIOleDocumentSite::ActivateMe(IOleDocumentView *pView)
    {
    RECT                rc;
    IOleDocument*       pDoc;
    
    /*
     * If we're passed a NULL view pointer, then try to get one from
     * the document object (the object within us).
     */
    if (NULL==pView)
        {

        if (FAILED(m_pSite->m_pObj->QueryInterface(IID_IOleDocument
            , (void **)&pDoc)))
            return E_FAIL;

        if (FAILED(pDoc->CreateView(m_pSite->m_pImpIOleIPSite
            , m_pSite->m_pIStream, 0, &pView)))            
            return E_OUTOFMEMORY;

        // Release doc pointer since CreateView is a good com method that addrefs
        pDoc->Release();
        }        
    else
        {
        //Make sure that the view has our client site
        pView->SetInPlaceSite(m_pSite->m_pImpIOleIPSite);

        //We're holding onto the pointer, so AddRef it.
        pView->AddRef();
        }


    /*
     * Activation steps, now that we have a view:
     *
     *  1.  Call IOleDocumentView::SetInPlaceSite (assume done since
     *      either the view already knows, or IOleDocument::CreateView
     *      has done it already.
     *
     *  2.  Call IOleDocumentView::SetRect to give a bunch of space to
     *      the view.  In our case this is the whole client area of
     *      the CPages window.  (Patron doesn't use SetRectComplex)
     *
     *  3.  Call IOleDocumentView::Show to make the thing visible.
     *
     *  4.  Call IOleDocumentView::UIActivate to finish the job.
     *
     */

    m_pSite->m_fDocObj=TRUE;
    m_pSite->m_pIOleDocView=pView;
    
    //This sets up toolbars and menus first    
    pView->UIActivate(TRUE);

    //Set the window size sensitive to new toolbars
    GetClientRect(m_pSite->m_hWnd, &rc);
    pView->SetRect(&rc);

	//Makes it all active
    pView->Show(TRUE);    
    return NOERROR;
    }
