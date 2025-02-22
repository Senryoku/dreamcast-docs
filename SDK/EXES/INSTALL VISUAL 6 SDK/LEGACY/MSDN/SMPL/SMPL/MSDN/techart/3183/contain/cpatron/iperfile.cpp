/*
 * IPERFILE.CPP
 * Patron Control Containter
 *
 * Implementation of the IPersistFile interface for Patron's
 * documents.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CImpIPersistFile:CImpIPersistFile
 * CImpIPersistFile::~CImpIPersistFile
 *
 * Constructor Parameters:
 *  pDoc            PCPatronDoc associated with this interface
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistFile::CImpIPersistFile(PCPatronDoc pDoc
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pDoc=pDoc;
    m_pUnkOuter=pUnkOuter;
    return;
    }


CImpIPersistFile::~CImpIPersistFile(void)
    {
    return;
    }




/*
 * CImpIPersistFile::QueryInterface
 * CImpIPersistFile::AddRef
 * CImpIPersistFile::Release
 *
 * Purpose:
 *  Standard set of IUnknown members for this interface
 */

STDMETHODIMP CImpIPersistFile::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIPersistFile::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the file represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistFile::GetClassID(LPCLSID pClsID)
    {
    *pClsID=CLSID_PatronPages;
    return NOERROR;
    }





/*
 * CImpIPersistFile::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this file since
 *  it was loaded or initialized new.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Contains S_OK if we ARE dirty, S_FALSE if
 *                  NOT dirty.
 */

STDMETHODIMP CImpIPersistFile::IsDirty(void)
    {
    return ResultFromScode(m_pDoc->FDirtyGet() ? S_OK : S_FALSE);
    }





/*
 * IPersistFile::Load
 *
 * Purpose:
 *  Asks the server to load the document for the given filename.
 *
 * Parameters:
 *  pszFile         LPCTSTR to the filename to load.
 *  grfMode         DWORD containing open flags requested from the
 *                  caller.  Currently these are safely ignored.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistFile::Load(LPCTSTR pszFile, DWORD grfMode)
    {
    UINT        uRet;

    uRet=m_pDoc->ULoad(TRUE, (LPTSTR)pszFile);
    return (DOCERR_NONE==uRet) ? NOERROR
        : ResultFromScode(STG_E_READFAULT);
    }





/*
 * IPersistFile::Save
 *
 * Purpose:
 *  Instructs the server to write the current file into a new
 *  filename, possibly then using that filename as the current one.
 *
 * Parameters:
 *  pszFile         LPCTSTR of the file into which we save.  If NULL,
 *                  this means save the current file.
 *  fRemember       BOOL indicating if we're to use this filename as
 *                  the current file now (Save As instead of Save
 *                  Copy As).
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistFile::Save(LPCTSTR pszFile, BOOL fRemember)
    {
    UINT        uRet;

    /*
     * Since we don't want to mess with changing USave (which would
     * require changes to CLASSLIB (urk) we instead save fRemember
     * in the document before calling USave which supresses the call
     * to CPatronDoc::Rename if FALSE.
     */

    m_pDoc->m_fRename=fRemember;
    uRet=m_pDoc->USave(0, (LPTSTR)pszFile);
    m_pDoc->m_fRename=TRUE;

    return (DOCERR_NONE==uRet) ? NOERROR
        : ResultFromScode(STG_E_WRITEFAULT);
    }





/*
 * IPersistFile::SaveCompleted
 *
 * Purpose:
 *  Informs us that the operation that called Save is now finished
 *  and we can access the file again.
 *
 * Parameters:
 *  pszFile         LPCTSTR of the file in which we can start
 *                  writing again.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistFile::SaveCompleted(LPCTSTR pszFile)
    {
    return NOERROR;
    }




/*
 * IPersistFile::GetCurFile
 *
 * Purpose:
 *  Retrieves the name of the current file.
 *
 * Parameters:
 *  ppszFile        LPTSTR * into which we store a pointer to
 *                  the filename that should be allocated with the
 *                  shared IMalloc.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistFile::GetCurFile(LPTSTR * ppszFile)
    {
    LPMALLOC    pIMalloc;
    LPTSTR       psz;
    UINT        uRet;

    *ppszFile=NULL;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_FAIL);

    psz=(LPTSTR)pIMalloc->Alloc(OLEUI_CCHPATHMAX*sizeof(TCHAR));
    pIMalloc->Release();

    uRet=m_pDoc->FilenameGet(psz, OLEUI_CCHPATHMAX);

    //If we have no filename, return the prompt for File Open/Save.
    if (0==uRet)
        lstrcpy(psz, (*m_pDoc->m_pST)[IDS_EXTENSION]);

    *ppszFile=psz;
    return (0==uRet) ? ResultFromScode(S_FALSE) : NOERROR;
    }
