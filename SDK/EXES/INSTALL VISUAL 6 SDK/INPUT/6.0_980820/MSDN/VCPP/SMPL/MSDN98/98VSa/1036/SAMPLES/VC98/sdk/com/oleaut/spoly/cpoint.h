/*** 
*cpoint.h
*
*  This is a part of the Microsoft Source Code Samples.
*
*  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
*
*  This source code is only intended as a supplement to Microsoft Development
*  Tools and/or WinHelp documentation.  See these sources for detailed
*  information regarding the Microsoft samples programs.
*
*Purpose:
*  Definition of the CPoint class.
*
*  The CPoint object exposes two properties for programatic access
*  via the IDispatch interface.
*
*  properties:
*    X 			- the 'x' coordinate of the point
*    Y 			- the 'y' coordinate of the point
*
*Implementation Notes:
*
*****************************************************************************/

#ifndef	CLASS
#ifdef	__TURBOC__
#define CLASS class huge
#else
#define CLASS class FAR
#endif
#endif

class CPoly;

CLASS CPoint : public IDispatch {
    friend class CPoly;

public:
    static CPoint FAR* Create();

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppvObj);
    STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(unsigned int FAR* pcTypeInfo);

    STDMETHOD(GetTypeInfo)(
      unsigned int iTypeInfo,
      LCID lcid,
      ITypeInfo FAR* FAR* ppTypeInfo);

    STDMETHOD(GetIDsOfNames)(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      unsigned int cNames,
      LCID lcid,
      DISPID FAR* rgdispid);

    STDMETHOD(Invoke)(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      unsigned short wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      unsigned int FAR* pwArgErr);

    /* Introduced methods */

    virtual short PASCAL GetX(void);
    virtual void  PASCAL SetX(short x);
    virtual short PASCAL GetY(void);
    virtual void  PASCAL SetY(short y);

private:
    CPoint();

    unsigned long m_refs;

    short m_x;
    short m_y;
};


// member DISPIDs
//
enum IDMEMBER_CPOINT {
    IDMEMBER_CPOINT_GETX = 1,
    IDMEMBER_CPOINT_SETX,
    IDMEMBER_CPOINT_GETY,
    IDMEMBER_CPOINT_SETY,
    IDMEMBER_CPOINT_MAX
};

// structure used to link together lists of points
//
struct POINTLINK {
    POINTLINK FAR* next;
    CPoint FAR* ppoint;
};


// The CPoint Class Factory
//
CLASS CPointCF : public IClassFactory
{
public:
    static IClassFactory FAR* Create();

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID iid, void FAR* FAR* ppv);
    STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

    /* IClassFactory methods */
    STDMETHOD(CreateInstance)(
      IUnknown FAR* pUnkOuter, REFIID iid, void FAR* FAR* ppv);
#ifdef _MAC
    STDMETHOD(LockServer)(unsigned long fLock);
#else
    STDMETHOD(LockServer)(BOOL fLock);
#endif

private:
    CPointCF();

    unsigned long m_refs;
};
