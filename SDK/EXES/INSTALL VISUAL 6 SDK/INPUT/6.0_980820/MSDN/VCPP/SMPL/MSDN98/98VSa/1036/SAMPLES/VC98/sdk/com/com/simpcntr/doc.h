//**********************************************************************
// File name: doc.h
//
//      Definition of CSimpleDoc
//
// Copyright (c) 1992 - 1997 Microsoft Corporation. All rights reserved.
//**********************************************************************

#if !defined( _DOC_H_ )
#define _DOC_H_

#include <stablize.h>

class CSimpleSite;
class CSimpleApp;

class CSimpleDoc : public IUnknown, public CSafeRefCount
{
public:
        LPSTORAGE       m_lpStorage;
        LPOLEINPLACEACTIVEOBJECT m_lpActiveObject;
        BOOL            m_fInPlaceActive;
        BOOL            m_fAddMyUI;
        BOOL            m_fModifiedMenu;

        CSimpleSite FAR * m_lpSite;
        CSimpleApp FAR * m_lpApp;

        HWND m_hDocWnd;

        static CSimpleDoc FAR * Create(CSimpleApp FAR *lpApp, LPRECT lpRect,HWND hWnd);

        void Close(void);

        CSimpleDoc();
        CSimpleDoc(CSimpleApp FAR *lpApp, HWND hWnd);
        ~CSimpleDoc();

        // IUnknown Interface
        STDMETHODIMP QueryInterface(REFIID riid, LPVOID FAR* ppvObj);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

        void InsertObject(void);
        void DisableInsertObject(void);
        long lResizeDoc(LPRECT lpRect);
        long lAddVerbs(void);
        void PaintDoc(HDC hDC);
};

#endif
