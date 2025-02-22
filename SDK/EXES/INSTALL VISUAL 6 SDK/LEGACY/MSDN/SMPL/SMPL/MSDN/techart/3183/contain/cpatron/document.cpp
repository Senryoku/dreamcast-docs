/*
 * DOCUMENT.CPP
 * Patron Control Containter
 *
 * Implementation of the CPatronDoc derivation of CDocument that
 * manages pages for us.
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
#include <memory.h>
#include <dlgs.h>       //Pring Dlg button IDs



/*
 * CPatronDoc::CPatronDoc
 * CPatronDoc::~CPatronDoc
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame of the frame object.
 */

CPatronDoc::CPatronDoc(HINSTANCE hInst, PCFrame pFR)
    : CDocument(hInst, pFR)
    {
    m_pPG=NULL;
    m_lVer=VERSIONCURRENT;
    m_pIStorage=NULL;
    m_fPrintSetup=TRUE;
    m_pDropTarget=NULL;

    m_cfEmbeddedObject=RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
    m_cfObjectDescriptor=RegisterClipboardFormat
        (CF_OBJECTDESCRIPTOR);

    m_cfLinkSource=RegisterClipboardFormat(CF_LINKSOURCE);
    m_cfLinkSrcDescriptor=RegisterClipboardFormat
        (CF_LINKSRCDESCRIPTOR);

    m_fShowTypes         =FALSE;
    m_cRef               =1L;
    m_fRename            =TRUE;
    m_dwRegROT           =0L;
    m_pIPersistFile      =NULL;
    m_pIOleItemContainer =NULL;

    m_pIOleIPUIWindow    =NULL;
    m_pIOleIPActiveObject=NULL;
    m_fNoObjectFrameTools=FALSE;
    //CONTROLMOD
    m_fDesignMode        =FALSE;
    //End CONTROLMOD

    return;
    }


CPatronDoc::~CPatronDoc(void)
    {
    if (0L!=m_dwRegROT)
        OleStdRevokeAsRunning(&m_dwRegROT);

    if (NULL!=m_pIPersistFile)
        delete m_pIPersistFile;

    if (NULL!=m_pIOleItemContainer)
        delete m_pIOleItemContainer;

    if (NULL!=m_pPG)
        delete m_pPG;

    if (NULL!=m_pIOleIPUIWindow)
        delete m_pIOleIPUIWindow;

    if (NULL!=m_pIStorage)
        m_pIStorage->Release();

    CoFreeUnusedLibraries();
    return;
    }





/*
 * CPatronDoc::QueryInterface
 * CPatronDoc::AddRef
 * CPatronDoc::Release
 *
 * Purpose:
 *  IUnknown members for CPatronDoc object.
 */

STDMETHODIMP CPatronDoc::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * WARNING:  Because the *ppv=this implicitly does
     * *ppv=(LPVOID)this, the this pointer is incorrectly cast
     * from a CPatronDoc pointer to LPVOID where we want an
     * IUnknown pointer instead.  CPatronDoc uses multiple
     * inheritance here which means that we have to explicitly
     * provide the typecast to select the base class like
     * IUnknown.  If you don't do this, calls to AddRef, for
     * example, might call your desctructor!
     */

    if (IID_IUnknown==riid)
        *ppv=(LPUNKNOWN)this;

    if (IID_IOleItemContainer==riid || IID_IOleContainer==riid
        || IID_IParseDisplayName==riid)
        *ppv=m_pIOleItemContainer;

    if (IID_IPersistFile==riid || IID_IPersist==riid)
        *ppv=m_pIPersistFile;

    if (IID_IOleWindow==riid || IID_IOleInPlaceUIWindow==riid)
        *ppv=m_pIOleIPUIWindow;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CPatronDoc::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CPatronDoc::Release(void)
    {
    ULONG           cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);

    return cRefT;
    }




/*
 * CPatronDoc::FInit
 *
 * Purpose:
 *  Initializes an already created document window.  The client
 *  actually creates the window for us, then passes that here for
 *  further initialization.
 *
 * Parameters:
 *  pDI             PDOCUMENTINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPatronDoc::FInit(PDOCUMENTINIT pDI)
    {
    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    if (!CDocument::FInit(pDI))
        return FALSE;

    //Pages are created when we get a ULoad later.

    //Instantiate our interfaces
    m_pIPersistFile=new CImpIPersistFile(this, this);

    if (NULL==m_pIPersistFile)
        return FALSE;

    m_pIOleItemContainer=new CImpIOleItemContainer(this, this, TRUE);

    if (NULL==m_pIOleItemContainer)
        return FALSE;

    m_pIOleIPUIWindow=new CImpIOleInPlaceUIWindow(this, this);

    if (NULL==m_pIOleIPUIWindow)
        return FALSE;

    return TRUE;
    }







/*
 * CPatronDoc::FMessageHook
 *
 * Purpose:
 *  Processes WM_SIZE for the document so we can resize the Pages
 *  window.
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return
 *                  value for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing,
 *                  FALSE otherwise.
 */

BOOL CPatronDoc::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    UINT        dx, dy;
    RECT        rc;

    *pLRes=0;

    //CLASSLIB always sends MDIACTIVATE, regardless of MDI or SDI.
    if (WM_MDIACTIVATE==iMsg)
        {
        /*
         * Win32 has hWndActivate in lParam.  Win16 has it in
         * LOWORD(lParam).  (HWND)(UINT) handles both cases.
         */
        BOOL    fActivate=((HWND)(UINT)lParam==hWnd);

        if (NULL!=m_pIOleIPActiveObject)
            {
            //Hide our tools
            if (fActivate)
                g_pFR->ShowUIAndTools(m_fNoObjectFrameTools, FALSE);

            m_pIOleIPActiveObject->OnDocWindowActivate(fActivate);
            }
        else
            {
            //Restore frame-level UI if we're becoming active.
            if (fActivate)
                g_pFR->ReinstateUI();
            }
        }

    //Eat to prevent flickering
    if (WM_ERASEBKGND==iMsg)
        return TRUE;

    if (WM_SIZE==iMsg && NULL!=m_pPG)
        {
        dx=LOWORD(lParam);
        dy=HIWORD(lParam);

        if (SIZE_MINIMIZED!=wParam)
            {
            //Resize Pages window to fit the new document size.
            GetClientRect(hWnd, &rc);
            m_pPG->RectSet(&rc, FALSE);
            }

        if (NULL!=m_pIOleIPActiveObject)
            {
            //Also tell in-place objects that document was resized.
            m_pIOleIPActiveObject->ResizeBorder(&rc
                , m_pIOleIPUIWindow, FALSE);
            }
        }

    if (WM_DESTROY==iMsg)
        {
        /*
         * We have to revoke the drop target here because the window
         * will be destroyed and the property forcefully removed
         * before we could do this in the destructor.
         */
        if (NULL!=m_pDropTarget)
            {
            RevokeDragDrop(m_hWnd);
            CoLockObjectExternal(m_pDropTarget, FALSE, TRUE);
            m_pDropTarget->Release();
            }

        return FALSE;
        }

    /*
     * We return FALSE even on WM_SIZE so we can let the default
     * procedure handle maximized MDI child windows appropriately.
     */
    return FALSE;
    }







/*
 * CPatronDoc::Clear
 *
 * Purpose:
 *  Sets all contents in the document back to defaults with no
 *  filename.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Clear(void)
    {
    //Completely reset the pages
    if (NULL!=m_pPG)
        m_pPG->FIStorageSet(NULL, FALSE, FALSE);

    CDocument::Clear();
    m_lVer=VERSIONCURRENT;
    return;
    }




/*
 * CPatronDoc::FDirtyGet
 *
 * Purpose:
 *  Returns the current dirty status of the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the file is clean, FALSE otherwise.
 */

BOOL CPatronDoc::FDirtyGet()
    {
    BOOL    fPageDirty;

    fPageDirty=m_pPG->FIsDirty();
    return m_fDirty | fPageDirty;
    }





/*
 * CPatronDoc::Delete
 *
 * Purpose:
 *  Removed the current object from the document.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Delete(void)
    {
    if (NULL!=m_pPG)
        m_pPG->TenantDestroy();

    CoFreeUnusedLibraries();
    return;
    }



/*
 * CPatronDoc::FQueryPrinterSetup
 *
 * Purpose:
 *  Returns whether or not the Printer Setup menu item can be
 *  enabled.  Once you create a tenant in any page, Printer Setup
 *  is voided simply to keep this sample simple, that is, we don't
 *  have to worry about reorganizing potentially large amounts
 *  of layout after we start plopping down objects.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE to enable the menu, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPrinterSetup(void)
    {
    return m_fPrintSetup;
    }





/*
 * CPatronDoc::FQueryObjectSelected
 *
 * Purpose:
 *  Returns whether or not there is an object selected in this
 *  document for Cut, Copy, Delete functions.
 *
 * Parameters:
 *  hMenu           HMENU of the Edit menu.
 *
 * Return Value:
 *  BOOL            TRUE if we have an object, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryObjectSelected(HMENU hMenu)
    {
    return m_pPG->FQueryObjectSelected(hMenu);
    }





/*
 * CPatronDoc::ULoad
 *
 * Purpose:
 *  Loads a given document without any user interface overwriting
 *  the previous contents of the editor.
 *
 * Parameters:
 *  fChangeFile     BOOL indicating if we're to update the window
 *                  title and the filename from using this file.
 *  pszFile         LPTSTR to the filename to load.  Could be NULL
 *                  for an untitled document.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_...
 */

UINT CPatronDoc::ULoad(BOOL fChangeFile, LPTSTR pszFile)
    {
    RECT        rc;
    LPSTORAGE   pIStorage;
    HRESULT     hr;
    CLSID       clsID;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;

    if (NULL==pszFile)
        {
        //Create a new temp file.
        hr=StgCreateDocfile(NULL, dwMode | STGM_CREATE
            | STGM_DELETEONRELEASE, 0, &pIStorage);

        //Mark this our class since we check with ReadClassStg.
        if (SUCCEEDED(hr))
            WriteClassStg(pIStorage, CLSID_PatronPages);
        }
    else
        {
        hr=StgOpenStorage(pszFile, NULL, dwMode, NULL, 0, &pIStorage);
        }

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    //Check if this is our type of file and exit if not.
    hr=ReadClassStg(pIStorage, &clsID);

    if (FAILED(hr) || CLSID_PatronPages!=clsID)
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    //Attempt to create our contained Pages window.
    m_pPG=new CPages(m_hInst, m_cf);
    GetClientRect(m_hWnd, &rc);

    //Always use WS_CLIPCHILDREN with in-place support.
    if (!m_pPG->FInit(m_hWnd, &rc, WS_CLIPCHILDREN | WS_CHILD
        | WS_VISIBLE, ID_PAGES, NULL))
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    if (!m_pPG->FIStorageSet(pIStorage, FALSE
        , (BOOL)(NULL==pszFile)))
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    //Open the window up for drag-drop
    m_pDropTarget=new CDropTarget(this);

    if (NULL!=m_pDropTarget)
        {
        m_pDropTarget->AddRef();
        CoLockObjectExternal(m_pDropTarget, TRUE, FALSE);
        RegisterDragDrop(m_hWnd, m_pDropTarget);
        }

    m_pIStorage=pIStorage;
    Rename(pszFile);

    //Do initial setup if new file, otherwise Pages handles things.
    if (NULL==pszFile)
        {
        //Go initialize the Pages for the default printer.
        if (!PrinterSetup(NULL, TRUE))
            return DOCERR_COULDNOTOPEN;

        //Go create an initial page.
        m_pPG->PageInsert(0);
        }
    else
        {
        //Can't change an already saved configuration
        m_fPrintSetup=FALSE;
        }

    FDirtySet(FALSE);
    return DOCERR_NONE;
    }







/*
 * CPatronDoc::USave
 *
 * Purpose:
 *  Writes the file to a known filename, requiring that the user
 *  has previously used FileOpen or FileSaveAs in order to have
 *  a filename.
 *
 * Parameters:
 *  uType           UINT indicating the type of file the user
 *                  requested to save in the File Save As dialog.
 *  pszFile         LPTSTR under which to save.  If NULL, use the
 *                  current name.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_...
 */

UINT CPatronDoc::USave(UINT uType, LPTSTR pszFile)
    {
    HRESULT     hr;
    LPSTORAGE   pIStorage;

    //Save or Save As with the same file is just a commit.
    if (NULL==pszFile
        || (NULL!=pszFile && 0==lstrcmpi(pszFile, m_szFile)))
        {
        WriteFmtUserTypeStg(m_pIStorage, m_cf
            , PSZ(IDS_CLIPBOARDFORMAT));

        //Insure pages are up to date.
        m_pPG->FIStorageUpdate(FALSE);

        //Commit everyting
        m_pIStorage->Commit(STGC_ONLYIFCURRENT);

        FDirtySet(FALSE);
        return DOCERR_NONE;
        }

    /*
     * When we're given a name, open the storage, creating it new
     * if it does not exist or overwriting the old one.  Then CopyTo
     * from the current to the new, Commit the new, Release the old.
     */

    hr=StgCreateDocfile(pszFile, STGM_TRANSACTED | STGM_READWRITE
        | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    WriteClassStg(pIStorage, CLSID_PatronPages);
    WriteFmtUserTypeStg(pIStorage, m_cf, PSZ(IDS_CLIPBOARDFORMAT));

    //Insure all pages are up-to-date.
    m_pPG->FIStorageUpdate(TRUE);

    //This also copies the CLSID we stuff in here on file creation.
    hr=m_pIStorage->CopyTo(NULL, NULL, NULL, pIStorage);

    if (FAILED(hr))
        {
        SCODE       sc;

        pIStorage->Release();
        sc=GetScode(hr);

        /*
         * If we failed because of low memory, use IRootStorage
         * to switch into the new file.
         */
        if (E_OUTOFMEMORY==sc)
            {
            LPROOTSTORAGE        pIRoot;

            //Delete file we already created
            DeleteFile(pszFile);

            if (FAILED(m_pIStorage->QueryInterface
                (IID_IRootStorage, (PPVOID)&pIRoot)))
                return DOCERR_WRITEFAILURE;

            hr=pIRoot->SwitchToFile(pszFile);
            pIRoot->Release();

            if (FAILED(hr))
                return DOCERR_WRITEFAILURE;

            //If successful, the Commit below finishes the save.
            pIStorage=m_pIStorage;
            m_pIStorage->AddRef();    //Matches Release below
            }
        }

    pIStorage->Commit(STGC_ONLYIFCURRENT);

    /*
     * Revert changes on the original storage.  If this was a temp
     * file, it's deleted since we used STGM_DELETEONRELEASE.
     */
    m_pIStorage->Release();

    //Make this new storage current
    m_pIStorage=pIStorage;
    m_pPG->FIStorageSet(pIStorage, TRUE, FALSE);

    FDirtySet(FALSE);

    if (m_fRename)
        Rename(pszFile);    //Update caption bar.

    return DOCERR_NONE;
    }








/*
 * CPatronDoc::FClip
 *
 * Purpose:
 *  Places a private format, a metafile, and a bitmap of the display
 *  on the clipboard, optionally implementing Cut by deleting the
 *  data in the current window after rendering.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *  fCut            BOOL indicating cut (TRUE) or copy (FALSE).
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::FClip(HWND hWndFrame, BOOL fCut)
    {
    if (NULL==m_pPG)
        return FALSE;

    return m_pPG->TenantClip(fCut);
    }





/*
 * CPatronDoc::FPaste
 *
 * Purpose:
 *  Retrieves the private data format from the clipboard and sets it
 *  to the current figure in the editor window.
 *
 *  Note that if this function is called, then the clipboard format
 *  is available because the Paste menu item is only enabled if the
 *  format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::FPaste(HWND hWndFrame)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet=FALSE;
    FORMATETC       fe;
    TENANTTYPE      tType;

    if (NULL==m_pPG)
        return FALSE;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    //Go get type and format we *can* paste, then actually paste it.
    if (FQueryPasteFromData(pIDataObject, &fe, &tType))
        {
        fRet=FPasteFromData(pIDataObject, &fe, tType, NULL
            , 0L, TRUE);
        }

    pIDataObject->Release();
    return fRet;
    }




/*
 * CPatronDoc::FQueryPaste
 *
 * Purpose:
 *  Determines if we can paste data from the clipboard.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPaste(void)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    fRet=FQueryPasteFromData(pIDataObject, NULL, NULL);

    fRet |= FQueryPasteLinkFromData(pIDataObject, NULL, NULL);
    pIDataObject->Release();
    return fRet;
    }






/*
 * CPatronDoc::FPasteSpecial
 *
 * Purpose:
 *  Retrieves a specific data format from the clipboard and sends
 *  it to the editor window appropriately.
 *
 *  Note that if this function is called, then the appropriate
 *  format is available because the Paste menu item is only
 *  enabled if the format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::FPasteSpecial(HWND hWndFrame)
    {
    OLEUIPASTESPECIAL   ps;
    OLEUIPASTEENTRY     rgPaste[6];
    UINT                rgcf[1];        //For ps.m_arrLinkTypes
    DWORD               dwData=0;
    UINT                uTemp;
    BOOL                fRet=FALSE;

    if (NULL==m_pPG)
        return FALSE;

    memset(&ps, 0, sizeof(ps));

    if (FAILED(OleGetClipboard(&ps.lpSrcDataObj)))
        return FALSE;

    ps.cbStruct=sizeof(ps);
    ps.hWndOwner=hWndFrame;

    ps.dwFlags=PSF_SELECTPASTE;
    ps.arrPasteEntries=rgPaste;

    //Set up Paste Special descriptor arrays.
    SETDefFormatEtc(rgPaste[0].fmtetc, m_cf, TYMED_HGLOBAL);
    rgPaste[0].lpstrFormatName=PSZ(IDS_CLIPBOARDFORMAT);
    rgPaste[0].lpstrResultText=PSZ(IDS_PASTEASPATRON);
    rgPaste[0].dwFlags=OLEUIPASTE_PASTEONLY;

    //Embedded objects can be iconic displays if the user wants.
    SETDefFormatEtc(rgPaste[1].fmtetc, m_cfEmbeddedObject
        , TYMED_ISTORAGE);
    rgPaste[1].lpstrFormatName=PSZ(IDS_PASTEOBJECT);
    rgPaste[1].lpstrResultText=PSZ(IDS_PASTEASOBJECT);

    /*
     * CAUTION:  Use OLEUI_PASTE with embedded objects or else
     * this item will not show up in the dialog.  I learned this the
     * hard way (that is, after about 6 hours of pulling hair!).
     */
    rgPaste[1].dwFlags=OLEUIPASTE_PASTE | OLEUIPASTE_ENABLEICON;


    SETDefFormatEtc(rgPaste[2].fmtetc,CF_METAFILEPICT,TYMED_MFPICT);
    rgPaste[2].lpstrFormatName=PSZ(IDS_PASTEMETAFILE);
    rgPaste[2].lpstrResultText=PSZ(IDS_PASTEASMETAFILE);
    rgPaste[2].dwFlags=OLEUIPASTE_PASTEONLY;

    SETDefFormatEtc(rgPaste[3].fmtetc, CF_DIB, TYMED_HGLOBAL);
    rgPaste[3].lpstrFormatName=PSZ(IDS_PASTEDIB);
    rgPaste[3].lpstrResultText=PSZ(IDS_PASTEASDIB);
    rgPaste[3].dwFlags=OLEUIPASTE_PASTEONLY;

    SETDefFormatEtc(rgPaste[4].fmtetc, CF_BITMAP, TYMED_GDI);
    rgPaste[4].lpstrFormatName=PSZ(IDS_PASTEBITMAP);
    rgPaste[4].lpstrResultText=PSZ(IDS_PASTEASBITMAP);
    rgPaste[4].dwFlags=OLEUIPASTE_PASTEONLY;

    SETDefFormatEtc(rgPaste[5].fmtetc,m_cfLinkSource,TYMED_ISTREAM);
    rgPaste[5].lpstrFormatName=PSZ(IDS_PASTELINK);
    rgPaste[5].lpstrResultText=PSZ(IDS_PASTEASLINK);
    rgPaste[5].dwFlags=OLEUIPASTE_LINKTYPE1 | OLEUIPASTE_ENABLEICON;

    //Types we can Paste Link from the clipboard.
    rgcf[0]=m_cfLinkSource;
    ps.arrLinkTypes=rgcf;
    ps.cLinkTypes=1;
    ps.cPasteEntries=6;

    uTemp=OleUIPasteSpecial(&ps);

    if (OLEUI_OK==uTemp)
        {
        UINT        i=ps.nSelectedIndex;
        TENANTTYPE  tType;

        if (ps.fLink)
            tType=TENANTTYPE_LINKEDOBJECTFROMDATA;
        else
            {
            if (1==ps.nSelectedIndex)
                tType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;
            else
                tType=TENANTTYPE_STATIC;
            }

        //Handle iconic aspects...from links as well
        if ((1==i || ps.fLink) && (PSF_CHECKDISPLAYASICON
            & ps.dwFlags) && NULL!=ps.hMetaPict)
            {
            rgPaste[i].fmtetc.dwAspect=DVASPECT_ICON;
            dwData=(DWORD)(UINT)ps.hMetaPict;
            }

        fRet=FPasteFromData(ps.lpSrcDataObj, &rgPaste[i].fmtetc
            , tType, NULL, dwData, FALSE);

        //Always free this regardless of what we do with it.
        if (NULL!=ps.hMetaPict)
            OleUIMetafilePictIconFree(ps.hMetaPict);
        }

    ps.lpSrcDataObj->Release();
    return fRet;
    }




/*
 * CPatronDoc::FQueryPasteFromData
 * (Protected)
 *
 * Purpose:
 *  Determines if we can paste data from a data object.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which we might want to paste.
 *  pFE             LPFORMATETC in which to return the first format
 *                  we can use.  Ignored if NULL.
 *  ptType          PTENANTTYPE in which to store the type of
 *                  object we can paste.  Ignored if NULL.
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPasteFromData(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, PTENANTTYPE ptType)
    {
    FORMATETC       fe;
    HRESULT         hr, hr2;

    if (NULL!=(LPVOID)ptType)
        *ptType=TENANTTYPE_STATIC;

    //Any of our specific data here?
    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);
    hr=pIDataObject->QueryGetData(&fe);

    //If embedded object data is available, set the appropriate type
    hr2=OleQueryCreateFromData(pIDataObject);

    if (NOERROR==hr2)
        {
        if (NULL!=pFE)
            {
            /*
             * Default to content.  FPaste will use
             * CF_OBJECTDESCRIPTOR to figure the actual aspect.
             */
            SETDefFormatEtc(*pFE, m_cfEmbeddedObject
                , TYMED_ISTORAGE);
            }

        if (NULL!=(LPVOID)ptType)
            *ptType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;

        /*
         * Return now if PatronObject wasn't available, otherwise
         * break out so that pFE gets PatronObject format.
         */
        if (NOERROR!=hr)
            return TRUE;
        }


    if (NOERROR!=hr && NOERROR!=hr2)
        {
        //Try metafile, DIB, then bitmap, setting fe each time
        SETDefFormatEtc(fe, CF_METAFILEPICT, TYMED_MFPICT);
        hr=pIDataObject->QueryGetData(&fe);

        if (NOERROR!=hr)
            {
            SETDefFormatEtc(fe, CF_DIB, TYMED_HGLOBAL);
            hr=pIDataObject->QueryGetData(&fe);

            if (NOERROR!=hr)
                {
                SETDefFormatEtc(fe, CF_BITMAP, TYMED_GDI);
                hr=pIDataObject->QueryGetData(&fe);
                }
            }
        }

    if (NOERROR==hr && NULL!=pFE)
        *pFE=fe;

    return (NOERROR==hr);
    }





/*
 * CPatronDoc::FQueryPasteLinkFromData
 * (Protected)
 *
 * Purpose:
 *  Determines if we can paste link from a data object.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which we might want to paste.
 *  pFE             LPFORMATETC in which to return the first format
 *                  we can use.  Ignored if NULL.
 *  ptType          PTENANTTYPE in which to store the type of object
 *                  we can paste.  Ignored if NULL.
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPasteLinkFromData(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, PTENANTTYPE ptType)
    {
    HRESULT         hr;

    if (NULL==pIDataObject)
        return FALSE;

    hr=OleQueryLinkFromData(pIDataObject);

    if (NOERROR!=hr)
        return FALSE;

    if (NULL!=pFE)
        SETDefFormatEtc(*pFE, m_cfLinkSource, TYMED_ISTREAM);

    if (NULL!=(LPVOID)ptType)
        *ptType=TENANTTYPE_LINKEDOBJECTFROMDATA;

    return TRUE;
    }






/*
 * CPatronDoc::FPasteFromData
 * (Protected)
 *
 * Purpose:
 *  Retrieves the private data format from a data object and sets
 *  it to the current figure in the editor window.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which to paste.
 *  pFE             LPFORMATETC to use in the paste. Cannot be NULL.
 *  tType           TENANTTYPE to paste.
 *  ppo             PPATRONOBJECT containing placement data.
 *  dwData          DWORD extra data sensitive to tType
 *  fUseObjDesc     BOOL indicating to use CF_OBJECTDESCRIPTOR
 *                  format for determining the aspect of the object
 *                  if the format is available.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::FPasteFromData(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, TENANTTYPE tType, PPATRONOBJECT ppo
    , DWORD dwData, BOOL fUseObjDesc)
    {
    BOOL                fRet;
    HRESULT             hr;
    PATRONOBJECT        po;
    STGMEDIUM           stm;
    LPOBJECTDESCRIPTOR  pOD;
    FORMATETC           fe;
    BOOL                fRelease=FALSE;

    if (NULL==pFE)
        return FALSE;

    //If not given any placement data, see if we can retrieve it
    if (pFE->cfFormat==m_cf && NULL==ppo)
        {
        hr=pIDataObject->GetData(pFE, &stm);

        if (SUCCEEDED(hr))
            {
            ppo=(PPATRONOBJECT)GlobalLock(stm.hGlobal);

            po=*ppo;
            ppo=&po;

            //If there's an object here, make sure type is right.
            if (ppo->fe.cfFormat==m_cfEmbeddedObject)
                tType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;

            if (ppo->fe.cfFormat==m_cfLinkSource)
                tType=TENANTTYPE_LINKEDOBJECTFROMDATA;

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);
            }
        }

    /*
     * If we're told to look at CF_OBJECTDESCRIPTOR, then try to get
     * the data and copy the aspect out of it.  We're not interested
     * in any other part of it, however.
     */
    if (fUseObjDesc)
        {
        SETDefFormatEtc(fe, m_cfObjectDescriptor, TYMED_HGLOBAL);

        hr=pIDataObject->GetData(&fe, &stm);

        if (FAILED(hr))
            {
            SETDefFormatEtc(fe, m_cfLinkSrcDescriptor
                , TYMED_HGLOBAL);
            hr=pIDataObject->GetData(&fe, &stm);
            }

        if (SUCCEEDED(hr))
            {
            pOD=(LPOBJECTDESCRIPTOR)GlobalLock(stm.hGlobal);
            pFE->dwAspect=pOD->dwDrawAspect;

            if (NULL!=ppo)
                ppo->fe.dwAspect=pFE->dwAspect;

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);

            /*
             * Furthermore, if pFE->dwAspect is DVASPECT_ICON, get
             * the metafile which will always be the icon
             * representation.
             */
            SETFormatEtc(fe, CF_METAFILEPICT, DVASPECT_ICON, NULL
                , TYMED_MFPICT, -1);

            if (SUCCEEDED(pIDataObject->GetData(&fe, &stm)))
                {
                dwData=(DWORD)(UINT)stm.hGlobal;
                fRelease=TRUE;
                }
            }
        }

    fRet=m_pPG->TenantCreate(tType, pIDataObject, pFE, ppo, dwData);

    //Release the stm from the last GetData
    if (fRelease)
        ReleaseStgMedium(&stm);

    if (fRet)
        {
        //Disable Printer Setup once we've created a tenant.
        m_fPrintSetup=FALSE;
        FDirtySet(TRUE);
        }

    return fRet;
    }




/*
 * CPatronDoc::FQueryEnableEditLinks
 *
 * Purpose:
 *  Determines whether or not the Edit Links menu item should be
 *  enabled on the frame window menu.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE to enable the item, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryEnableEditLinks(void)
    {
    return m_pPG->FQueryLinksInPage();
    }





/*
 * CPatronDoc::FEditLinks
 *
 * Purpose:
 *  Invokes the links dialog in which the end-user can manipulate
 *  all the links in the current page.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame window to use as the dialog
 *                  parent.
 *
 * Return Value:
 *  BOOL            TRUE if the function was successful,
 *                  FALSE otherwise.
 */

BOOL CPatronDoc::FEditLinks(HWND hWndFrame)
    {
    UINT                    uRet;
    OLEUIEDITLINKS          el;
    PCIOleUILinkContainer   pIUILinks;

    memset(&el, 0, sizeof(el));
    el.cbStruct=sizeof(el);
    el.hWndOwner=hWndFrame;

    if (!m_pPG->FGetUILinkContainer(&pIUILinks))
        return FALSE;

    el.lpOleUILinkContainer=pIUILinks;
    uRet=OleUIEditLinks(&el);

    //Only the IOleUILinkContainer interface will know dirtying.
    m_fDirty=pIUILinks->m_fDirty;

    el.lpOleUILinkContainer->Release();
    return TRUE;
    }



/*
 * CPatronDoc::FShowOrQueryObjectTypes
 *
 * Purpose:
 *  If querying, we return whether or not ShowObjects is active
 *  in this document.  Otherwise pass-through to
 *  CPages::ShowObjectTypes.
 *
 * Parameters:
 *  fQuery          BOOL indicating query or set.
 *  fShow           BOOL indicating to show the type or not.
 *
 * Return Value:
 *  None
 */

BOOL CPatronDoc::FShowOrQueryObjectTypes(BOOL fQuery, BOOL fShow)
    {
    if (fQuery)
        return m_fShowTypes;

    m_fShowTypes=fShow;
    m_pPG->ShowObjectTypes(fShow);
    return TRUE;
    }





/*
 * CPatronDoc::FConvertObject
 *
 * Purpose:
 *  Invokes the Change Type dialog on the current object.  Here it's just
 *  a pass-through to the pages.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame window.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful, FALSE otherwise.
 */

BOOL CPatronDoc::FConvertObject(HWND hWndFrame)
    {
    return m_pPG->FConvertObject(hWndFrame);
    }





/*
 * CPatronDoc::Print
 *
 * Purpose:
 *  Prints the current document.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame to use for dialog parents.
 *
 * Return Value:
 *  BOOL            TRUE if printing happened, FALSE if it didn't
 *                  start or didn't complete.
 */

BOOL CPatronDoc::Print(HWND hWndFrame)
    {
    PRINTDLG        pd;
    BOOL            fSuccess;

    memset(&pd, 0, sizeof(PRINTDLG));
    pd.lStructSize=sizeof(PRINTDLG);
    pd.hwndOwner  =hWndFrame;
    pd.nCopies    =1;
    pd.nFromPage  =(USHORT)-1;
    pd.nToPage    =(USHORT)-1;
    pd.nMinPage   =1;
    pd.nMaxPage   =m_pPG->NumPagesGet();

    pd.lpfnPrintHook=PrintDlgHook;

    //Get the current document printer settings
    pd.hDevMode=m_pPG->DevModeGet();

    pd.Flags=PD_RETURNDC | PD_ALLPAGES | PD_COLLATE
        | PD_HIDEPRINTTOFILE | PD_NOSELECTION | PD_ENABLEPRINTHOOK;

    if (!PrintDlg(&pd))
        return FALSE;

    if (NULL!=pd.hDevMode)
        GlobalFree(pd.hDevMode);

    if (NULL!=pd.hDevNames)
        GlobalFree(pd.hDevNames);

    //Go do the actual printing.
    fSuccess=m_pPG->Print(pd.hDC, PSZ(IDS_DOCUMENTNAME), pd.Flags
        , pd.nFromPage, pd.nToPage, pd.nCopies);

    if (!fSuccess)
        {
        MessageBox(m_hWnd, PSZ(IDS_PRINTERROR)
            , PSZ(IDS_DOCUMENTCAPTION), MB_OK);
        }

    return fSuccess;
    }






/*
 * CPatronDoc::PrinterSetup
 *
 * Purpose:
 *  Selects a new printer and options for this document.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame to use for dialog parents.
 *  fDefault        BOOL to avoid any dialog and just use the
 *                  default.
 *
 * Return Value:
 *  UINT            Undefined
 *
 */

UINT CPatronDoc::PrinterSetup(HWND hWndFrame, BOOL fDefault)
    {
    PRINTDLG        pd;

    //Attempt to get printer metrics for the default printer.
    memset(&pd, 0, sizeof(PRINTDLG));
    pd.lStructSize=sizeof(PRINTDLG);

    if (fDefault)
        pd.Flags=PD_RETURNDEFAULT;
    else
        {
        pd.hwndOwner=hWndFrame;
        pd.Flags=PD_PRINTSETUP;

        //Get the current document printer settings
        pd.hDevMode=m_pPG->DevModeGet();
        }

    if (!PrintDlg(&pd))
        return FALSE;

    if (!m_pPG->DevModeSet(pd.hDevMode, pd.hDevNames))
        {
        GlobalFree(pd.hDevNames);
        GlobalFree(pd.hDevMode);
        return FALSE;
        }

    FDirtySet(TRUE);
    return 1;
    }







/*
 * CPatronDoc::NewPage
 *
 * Purpose:
 *  Creates a new page in the document's pages control after the
 *  current page.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::NewPage(void)
    {
    FDirtySet(TRUE);
    return m_pPG->PageInsert(0);
    }







/*
 * CPatronDoc::DeletePage
 *
 * Purpose:
 *  Deletes the current page from the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the now current page.
 */

UINT CPatronDoc::DeletePage(void)
    {
    FDirtySet(TRUE);
    return m_pPG->PageDelete(0);
    }







/*
 * CPatronDoc::NextPage
 *
 * Purpose:
 *  Shows the next page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::NextPage(void)
    {
    UINT        iPage;

    iPage=m_pPG->CurPageGet();
    return m_pPG->CurPageSet(++iPage);
    }







/*
 * CPatronDoc::PreviousPage
 *
 * Purpose:
 *  Shows the previous page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::PreviousPage(void)
    {
    UINT        iPage;

    //If iPage is zero, then we wrap around to the end.
    iPage=m_pPG->CurPageGet();
    return m_pPG->CurPageSet(--iPage);
    }






/*
 * CPatronDoc::FirstPage
 *
 * Purpose:
 *  Shows the first page page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::FirstPage(void)
    {
    return m_pPG->CurPageSet(0);
    }






/*
 * CPatronDoc::LastPage
 *
 * Purpose:
 *  Shows the last page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the last page.
 */

UINT CPatronDoc::LastPage(void)
    {
    return m_pPG->CurPageSet(NOVALUE);
    }



/*
 * PrintDlgHook
 *
 * Purpose:
 *  Callback hook for the Print Dialog so we can hide the Setup
 *  button.  Patron only allows Setup before anything exists on
 *  the page, and is not written to handle setup at Print time.
 */

UINT CALLBACK PrintDlgHook(HWND hDlg, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    if (WM_INITDIALOG==iMsg)
        {
        HWND        hWnd;

        hWnd=GetDlgItem(hDlg, psh1);
        ShowWindow(hWnd, SW_HIDE);
        return TRUE;
        }

    return FALSE;
    }




/*
 * CPatronDoc::Rename
 *
 * Purpose:
 *  Overrides the normal rename to include notification of tenants
 *  in this document of the new name.  This is so embedded objects
 *  are told the correct name through IOleObject::SetHostNames.
 *
 * Parameters:
 *  pszFile         LPTSTR to the new filename.
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Rename(LPTSTR pszFile)
    {
    LPMONIKER   pmk;

    /*
     * If we're UI Activated an in-place object already, then we
     * can't let CDocument::Rename screw with the caption.  To
     * prevent that we temporarily NULL the member m_pAdv which
     * prevents CDocument::Rename from changing the caption.
     * It's a hack...
     *
     * We're UI Active when we have an IOleInPlaceActiveObject
     * pointer.
     */

    if (NULL!=m_pIOleIPActiveObject)
        {
        CDocumentAdviseSink *pAdv=m_pAdv;

        m_pAdv=NULL;
        CDocument::Rename(pszFile);
        m_pAdv=pAdv;
        }
    else
        CDocument::Rename(pszFile);

    /*
     * Get rid of the old moniker.  The OldStd function sets the
     * key to zero.
     */
    if (0L!=m_dwRegROT)
        OleStdRevokeAsRunning(&m_dwRegROT);

    if (NULL==pszFile)
        return;

    CreateFileMoniker(pszFile, &pmk);

    if (NULL!=pmk)
        {
        OleStdRegisterAsRunning(this, pmk, &m_dwRegROT);

        //Give a moniker to linked objects in tenants.
        m_pPG->NotifyTenantsOfRename(pszFile, pmk);

        //No need for us to hold on to this.
        pmk->Release();
        }

    return;
    }





/*
 * CPatronDoc::FInsertObject
 *
 * Purpose:
 *  Retrieves a CLSID or a filename from the Insert Object dialog
 *  box and creates an object using those identifiers.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::FInsertObject(HWND hWndFrame)
    {
    OLEUIINSERTOBJECT   io;
    DWORD               dwData=0;
    TCHAR               szFile[CCHPATHMAX];
    UINT                uTemp;
    BOOL                fRet=FALSE;

    if (NULL==m_pPG)
        return FALSE;

    memset(&io, 0, sizeof(io));

    io.cbStruct=sizeof(io);
    io.hWndOwner=hWndFrame;

    szFile[0]=0;
    io.lpszFile=szFile;
    io.cchFile=CCHPATHMAX;

    //We now support linking, so remove the IOF_DISABLELINK flag.
    io.dwFlags=IOF_SELECTCREATENEW;

    uTemp=OleUIInsertObject(&io);

    if (OLEUI_OK==uTemp)
        {
        TENANTTYPE      tType;
        LPVOID          pv;
        FORMATETC       fe;

        SETDefFormatEtc(fe, 0, TYMED_NULL);

        if (io.dwFlags & IOF_SELECTCREATENEW)
            {
            tType=TENANTTYPE_EMBEDDEDOBJECT;
            pv=&io.clsid;
            }
        else
            {
            if (io.dwFlags & IOF_CHECKLINK)
                tType=TENANTTYPE_LINKEDFILE;
            else
                tType=TENANTTYPE_EMBEDDEDFILE;

            pv=szFile;
            }

        if ((io.dwFlags & IOF_CHECKDISPLAYASICON)
            && NULL!=io.hMetaPict)
            {
            fe.dwAspect=DVASPECT_ICON;
            dwData=(DWORD)(UINT)io.hMetaPict;
            }

        fRet=m_pPG->TenantCreate(tType, pv, &fe, NULL, dwData);

        //Free this regardless of what we do with it.
        if (NULL!=io.hMetaPict)
            OleUIMetafilePictIconFree(io.hMetaPict);

        if (fRet)
            {
            //Disable Printer Setup once we've created a tenant.
            m_fPrintSetup=FALSE;
            FDirtySet(TRUE);
            }
        }

    return fRet;
    }




/*
 * CPatronDoc::ActivateObject
 *
 * Purpose:
 *  Executes a verb on the currently selected object.
 *
 * Parameters:
 *  iVerb           LONG of the selected verb.
 *  pMSG            LPMSG that caused the activation.
 *
 * Return Value:
 *  None
 */

void CPatronDoc::ActivateObject(LONG iVerb, LPMSG pMSG)
    {
    m_pPG->ActivateObject(iVerb, pMSG);
    return;
    }



/*
 * CPatronDoc::NoObjectFrameTools
 *
 * Purpose:
 *  Saves/retrieves a flag with the document that says whether or
 *  not the object active in this document has *frame* tools.  We
 *  need this to tell the frame what to do when document activation
 *  switches.
 *
 * Parameters:
 *  fNoTools        BOOL TRUE to indicate the object has no tools.
 *                  FALSE says the object has tools.
 *  fSet            BOOL indicating if this is a set (TRUE) or get
 *                  (FALSE) operation.
 *
 * Return Value:
 *  BOOL            Value of flag for Get operations, previous value
 *                  for Set operations.
 */

BOOL CPatronDoc::NoObjectFrameTools(BOOL fNoTools, BOOL fSet)
    {
    BOOL        fLast=m_fNoObjectFrameTools;

    if (fSet)
        m_fNoObjectFrameTools=fNoTools;

    return fLast;
    }



//CONTROLMOD
/*
 * CPatronDoc::FToggleOrQueryDesignMode
 *
 * Purpose:
 *  If querying, we return whether or not Design Mode is active
 *  in this document.  Otherwise pass-through to
 *  CPages::ToggleDesignMode.
 *
 * Parameters:
 *  fQuery          BOOL indicating query or set.
 *  fDesign         BOOL indicating we're in Design Mode or not.
 *
 * Return Value:
 *  None
 */

BOOL CPatronDoc::FToggleOrQueryDesignMode(BOOL fQuery, BOOL fDesign)
    {
    if (fQuery)
        return m_fDesignMode;

    m_fDesignMode=fDesign;
    m_pPG->ToggleDesignMode(fDesign);
    return TRUE;
    }



/*
 * CPatronDoc::FQueryEnableEvents
 *
 * Purpose:
 *  Determines whether or not the Edit Events menu item should be
 *  enabled on the frame window menu.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE to enable the item, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryEnableEvents(void)
    {
    return m_pPG->FQueryEnableEvents();
    }


/*
 * CPatronDoc::AssignEvents
 *
 * Purpose:
 *  Pass-through to CPages::AssignEvents
 *
 * Parameters:
 *  hWndFrame       HWND to use as the dialog parent.
 *
 * Return Value:
 *  None
 */

void CPatronDoc::AssignEvents(HWND hWndFrame)
    {
    m_pPG->AssignEvents(hWndFrame);
    return;
    }


//End CONTROLMOD
