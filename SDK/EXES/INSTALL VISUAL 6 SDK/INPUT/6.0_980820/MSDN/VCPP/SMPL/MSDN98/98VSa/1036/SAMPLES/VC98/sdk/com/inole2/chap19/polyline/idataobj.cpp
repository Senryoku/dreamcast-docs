/*
 * IDATAOBJ.CPP
 * Polyline Component Chapter 19
 *
 * Implementation of the IDataObject interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIDataObject::~CImpIDataObject(void)
    {
    return;
    }




/*
 * CImpIDataObject::QueryInterface
 * CImpIDataObject::AddRef
 * CImpIDataObject::Release
 */

STDMETHODIMP CImpIDataObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIDataObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDataObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIDataObject::GetData
 *
 * Purpose:
 *  Retrieves data described by a specific FormatEtc into a StgMedium
 *  allocated by this function.  Used like GetClipboardData.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM in which to return the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    UINT            cf=pFE->cfFormat;

    //Check the aspects we support.
    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    pSTM->pUnkForRelease=NULL;

    //Run creates the window to use as a basis for extents
    m_pObj->m_pImpIRunnableObject->Run(NULL);

    //Go render the appropriate data for the format.
    switch (cf)
        {
        case CF_METAFILEPICT:
            pSTM->tymed=TYMED_MFPICT;
            return m_pObj->RenderMetafilePict(&pSTM->hGlobal);

        case CF_BITMAP:
            pSTM->tymed=TYMED_GDI;
            return m_pObj->RenderBitmap((HBITMAP *)&pSTM->hGlobal);

        default:
            if (cf==m_pObj->m_cf)
                {
                pSTM->tymed=TYMED_HGLOBAL;
                return m_pObj->RenderNative(&pSTM->hGlobal);
                }

            break;
        }

    return ResultFromScode(DATA_E_FORMATETC);
    }




/*
 * CImpIDataObject::GetDataHere
 *
 * Purpose:
 *  Renders the specific FormatEtc into caller-allocated medium
 *  provided in pSTM.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM providing the medium into which
 *                  wer render the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    //CHAPTER19MOD
    //We can provide CFSTR_EMBEDSOURCE now.

    UINT        cf;
    HRESULT     hr;

    /*
     * The only reasonable time this is called is for
     * CFSTR_EMBEDSOURCE and TYMED_ISTORAGE (and later for
     * CFSTR_LINKSOURCE).  This means the same as
     * IPersistStorage::Save.
     */

    cf=RegisterClipboardFormat(CFSTR_EMBEDSOURCE);

    //Aspect is unimportant to us here, as is lindex and ptd.
    if (cf==pFE->cfFormat && (TYMED_ISTORAGE & pFE->tymed))
        {
        //We have an IStorage we can write into.
        pSTM->tymed=TYMED_ISTORAGE;
        pSTM->pUnkForRelease=NULL;

        hr=m_pObj->m_pImpIPersistStorage->Save(pSTM->pstg, FALSE);
        m_pObj->m_pImpIPersistStorage->SaveCompleted(NULL);
        return hr;
        }
    //End CHAPTER19MOD

    return ResultFromScode(DATA_E_FORMATETC);
    }






/*
 * CImpIDataObject::QueryGetData
 *
 * Purpose:
 *  Tests if a call to GetData with this FormatEtc will provide
 *  any rendering; used like IsClipboardFormatAvailable.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::QueryGetData(LPFORMATETC pFE)
    {
    UINT            cf=pFE->cfFormat;
    BOOL            fRet=FALSE;

    //Check the aspects we support.
    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    switch (cf)
        {
        case CF_METAFILEPICT:
            fRet=(BOOL)(pFE->tymed & TYMED_MFPICT);
            break;

        case CF_BITMAP:
            fRet=(BOOL)(pFE->tymed & TYMED_GDI);
            break;

        default:
            //Check our own format.
            fRet=((cf==m_pObj->m_cf)
                && (BOOL)(pFE->tymed & TYMED_HGLOBAL));
            break;
        }

    return fRet ? NOERROR : ResultFromScode(S_FALSE);
    }






/*
 * CImpIDataObject::GetCanonicalFormatEtc
 *
 * Purpose:
 *  Provides the caller with an equivalent FormatEtc to the one
 *  provided when different FormatEtcs will produce exactly the
 *  same renderings.
 *
 * Parameters:
 *  pFEIn            LPFORMATETC of the first description.
 *  pFEOut           LPFORMATETC of the equal description.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc
    (LPFORMATETC pFEIn, LPFORMATETC pFEOut)
    {
    if (NULL==pFEOut)
        return ResultFromScode(E_INVALIDARG);

    pFEOut->ptd=NULL;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
    }






/*
 * CImpIDataObject::SetData
 *
 * Purpose:
 *  Places data described by a FormatEtc and living in a StgMedium
 *  into the object.  The object may be responsible to clean up the
 *  StgMedium before exiting.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the data to set.
 *  pSTM            LPSTGMEDIUM containing the data.
 *  fRelease        BOOL indicating if this function is responsible
 *                  for freeing the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::SetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM, BOOL fRelease)
    {
    UINT            cf=pFE->cfFormat;
    BOOL            fRet=FALSE;
    PPOLYLINEDATA   ppl;

    //Check for our own clipboard format and DVASPECT_CONTENT
    if ((cf!=m_pObj->m_cf) || !(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    /*
     * Data can only come from global memory containing a
     * POLYLINEDATA structure that we send to the Polyline's
     * DataSet, a now internal function used from here and
     * from IPersistStorage::Load.
     */

    if (TYMED_HGLOBAL!=pSTM->tymed)
        return ResultFromScode(DATA_E_FORMATETC);

    ppl=(PPOLYLINEDATA)GlobalLock(pSTM->hGlobal);

    if (NULL!=ppl)
        {
        m_pObj->DataSet(ppl, TRUE, TRUE);
        GlobalUnlock(pSTM->hGlobal);
        fRet=TRUE;
        }

    if (fRelease)
        ReleaseStgMedium(pSTM);

    return fRet ? NOERROR : ResultFromScode(DATA_E_FORMATETC);
    }






/*
 * CImpIDataObject::EnumFormatEtc
 *
 * Purpose:
 *  Returns an IEnumFORMATETC object through which the caller can
 *  iterate to learn about all the data formats this object can
 *  provide through either GetData[Here] or SetData.
 *
 * Parameters:
 *  dwDir           DWORD describing a data direction, either
 *                  DATADIR_SET or DATADIR_GET.
 *  ppEnum          LPENUMFORMATETC * in which to return the
 *                  pointer to the enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::EnumFormatEtc(DWORD dwDir
    , LPENUMFORMATETC *ppEnum)
    {
    //CHAPTER19MOD
    //Can now just tell the default handler to do this busy work.
    return m_pObj->m_pDefIDataObject->EnumFormatEtc(dwDir, ppEnum);
    //CHAPTER19MOD
    }




//CHAPTER19MOD
//Removed some comments from this stuff.

/*
 * CImpIDataObject::DAdvise
 * CImpIDataObject::DUnadvise
 * CImpIDataObject::EnumDAdvise
 */

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE, DWORD dwFlags
    , LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        {
        hr=CreateDataAdviseHolder(&m_pObj->m_pIDataAdviseHolder);

        if (FAILED(hr))
            return ResultFromScode(E_OUTOFMEMORY);
        }

    hr=m_pObj->m_pIDataAdviseHolder->Advise(this, pFE
        , dwFlags, pIAdviseSink, pdwConn);

    return hr;
    }


STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConn)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr=m_pObj->m_pIDataAdviseHolder->Unadvise(dwConn);

    return hr;
    }



STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA *ppEnum)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr=m_pObj->m_pIDataAdviseHolder->EnumAdvise(ppEnum);
    return hr;
    }

//End CHAPTER19MOD
