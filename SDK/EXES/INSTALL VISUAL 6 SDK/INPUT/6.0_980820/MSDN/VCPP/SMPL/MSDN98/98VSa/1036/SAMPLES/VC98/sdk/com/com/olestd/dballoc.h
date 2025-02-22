/***
*dballoc.h
*
*  Copyright (C) 1992-96, Microsoft Corporation.  All Rights Reserved.
*
*Purpose:
*  This file contains the definition of CDbAlloc - A debug implementation
*  of the IMalloc interface.
*
*Implementation Notes:
*
*****************************************************************************/

#ifndef DBALLOC_H_INCLUDED /* { */
#define DBALLOC_H_INCLUDED


interface IDbOutput : public IUnknown
{
   STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
   STDMETHOD_(ULONG, AddRef)(THIS) PURE;
   STDMETHOD_(ULONG, Release)(THIS) PURE;

   virtual void _cdecl Printf (THIS_
     char FAR* szFmt, ...) PURE;

   STDMETHOD_(void, Assertion)(THIS_
     BOOL cond,
     char FAR* szExpr,
     char FAR* szFile,
     UINT uLine,
     char FAR* szMsg) PURE;
};


#endif /* } DBALLOC_H_INCLUDED */
