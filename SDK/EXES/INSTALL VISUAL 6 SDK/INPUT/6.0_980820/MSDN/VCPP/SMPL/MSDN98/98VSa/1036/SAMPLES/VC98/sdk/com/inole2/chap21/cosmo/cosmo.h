/*
 * COSMO.H
 * Cosmo Chapter 21
 *
 * Single include file that pulls in everything needed for other
 * source files in the Cosmo application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _COSMO_H_
#define _COSMO_H_

#define INC_CLASSLIB
#define INC_OLE2UI
//CHAPTER21MOD
#define CHAPTER21
//End CHAPTER21MOD
#include <inole.h>
#include "resource.h"


//Get the editor window information.
#include "polyline.h"



//COSMO.CPP:  Frame object that creates a main window

class CCosmoFrame : public CFrame
    {
    friend class CFigureClassFactory;
    friend class CFigure;   //For UI purposes.

    private:
        HBITMAP         m_hBmpLines[5];     //Menu item bitmaps
        UINT            m_uIDCurLine;       //Current line selection
        BOOL            m_fInitialized;     //Did OleInitalize work?
        LPCLASSFACTORY  m_pIClassDataTran;  //For locking

        BOOL            m_fEmbedding;       //-Embedding found?
        DWORD           m_dwRegCO;          //Registration key
        LPCLASSFACTORY  m_pIClassFactory;

    protected:
        //Overridable for creating a CClient for this frame
        virtual PCClient  CreateCClient(void);

        virtual BOOL      RegisterAllClasses(void);
        virtual BOOL      PreShowInit(void);
        virtual UINT      CreateToolbar(void);

        virtual LRESULT   OnCommand(HWND, WPARAM, LPARAM);
        virtual void      OnDocumentDataChange(PCDocument);
        virtual void      OnDocumentActivate(PCDocument);

        //New for this class
        virtual void      CreateLineMenu(void);

    public:
        CCosmoFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CCosmoFrame(void);

        //Overrides
        virtual BOOL      Init(PFRAMEINIT);
        virtual void      UpdateMenus(HMENU, UINT);
        virtual void      UpdateToolbar(void);

        //New for this class
        virtual void      CheckLineSelection(UINT);
        virtual void      UpdateEmbeddingUI(BOOL, PCDocument
                              , LPCTSTR, LPCTSTR);
    };


typedef CCosmoFrame *PCCosmoFrame;





//CLIENT.CPP

/*
 * The only reason we have a derived class here is to override
 * CreateCDocument so we can create our own type as well as
 * overriding NewDocument to perform one other piece of work once
 * the document's been created.
 */

class CCosmoClient : public CClient
    {
    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument CreateCDocument(void);

    public:
        CCosmoClient(HINSTANCE, PCFrame);
        virtual ~CCosmoClient(void);

        virtual PCDocument NewDocument(BOOL);
    };


typedef CCosmoClient *PCCosmoClient;




//DOCUMENT.CPP

//Constant ID for the window polyline that lives in a document
#define ID_POLYLINE         10


class CCosmoDoc : public CDocument
    {
    friend class CPolylineAdviseSink;

    //These need access to FQueryPasteFromData, PasteFromData
    friend class CDropTarget;
    friend class CDropSource;

    friend class CFigureClassFactory;
    friend class CFigure;

    protected:
        UINT                    m_uPrevSize;    //Last WM_SIZE wParam
        LONG                    m_lVer;         //Loaded Polyline ver

        PCPolyline              m_pPL;          //Polyline window here
        PCPolylineAdviseSink    m_pPLAdv;       //Advises from Polyline

        class CDropTarget      *m_pDropTarget;  //Registered target
        BOOL                    m_fDragSource;  //Source==target?

        UINT                    m_cfEmbedSource;
        UINT                    m_cfObjectDescriptor;

        class CFigure          *m_pFigure;      //The object in us.

        //CHAPTER21MOD
        LPMONIKER               m_pMoniker;     //Our file
        DWORD                   m_dwRegROT;     //From IROT::Register

        UINT                    m_cfLinkSource;
        UINT                    m_cfLinkSrcDescriptor;
        //End CHAPTER21MOD

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        void             DropSelectTargetWindow(void);

    public:
        CCosmoDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CCosmoDoc(void);

        virtual BOOL     Init(PDOCUMENTINIT);

        virtual void     Clear(void);

        virtual BOOL     FDirtySet(BOOL);
        virtual BOOL     FDirtyGet(void);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);
        //CHAPTER21MOD
        virtual void     Rename(LPTSTR);
        //End CHAPTER21MOD

        virtual void     Undo(void);
        virtual BOOL     Clip(HWND, BOOL);
        virtual HGLOBAL  RenderFormat(UINT);
        virtual BOOL     RenderMedium(UINT, LPSTGMEDIUM);
        virtual BOOL     FQueryPaste(void);
        virtual BOOL     Paste(HWND);

        //These were protected.  Now for IOleObject, should be public.
        virtual BOOL     FQueryPasteFromData(LPDATAOBJECT);
        virtual BOOL     PasteFromData(LPDATAOBJECT);
        LPDATAOBJECT     TransferObjectCreate(BOOL);

        virtual COLORREF ColorSet(UINT, COLORREF);
        virtual COLORREF ColorGet(UINT);

        virtual UINT     LineStyleSet(UINT);
        virtual UINT     LineStyleGet(void);
    };

typedef CCosmoDoc *PCCosmoDoc;


//These color indices wrap the polyline definitions
#define DOCCOLOR_BACKGROUND             POLYLINECOLOR_BACKGROUND
#define DOCCOLOR_LINE                   POLYLINECOLOR_LINE


//Drag-drop interfaces we need in the document
class CDropTarget : public IDropTarget
    {
    protected:
        ULONG               m_cRef;
        PCCosmoDoc          m_pDoc;

        LPDATAOBJECT        m_pIDataObject;     //From DragEnter

    public:
        CDropTarget(PCCosmoDoc);
        ~CDropTarget(void);

        //IDropTarget interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP DragEnter(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragOver(DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragLeave(void);
        STDMETHODIMP Drop(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
    };


typedef CDropTarget *PCDropTarget;


class CDropSource : public IDropSource
    {
    protected:
        ULONG               m_cRef;
        PCCosmoDoc          m_pDoc;

    public:
        CDropSource(PCCosmoDoc);
        ~CDropSource(void);

        //IDropSource interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP QueryContinueDrag(BOOL, DWORD);
        STDMETHODIMP GiveFeedback(DWORD);
    };


typedef CDropSource *PCDropSource;

//Include classes necessary to become an OLE Document server.
#include "cosmole.h"


#endif //_COSMO_H_
