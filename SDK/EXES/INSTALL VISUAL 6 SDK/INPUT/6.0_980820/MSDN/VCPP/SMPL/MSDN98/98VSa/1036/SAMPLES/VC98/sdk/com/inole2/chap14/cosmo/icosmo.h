/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: CosmoTypeLibrary */

#ifndef _CosmoTypeLibrary_H_
#define _CosmoTypeLibrary_H_

DEFINE_GUID(LIBID_CosmoTypeLibrary,0x00021165,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

DEFINE_GUID(IID_ICosmoFigure,0x00021161,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of interface: ICosmoFigure */
DECLARE_INTERFACE_(ICosmoFigure, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* ICosmoFigure methods */
    STDMETHOD_(IDispatch *, get_Application)(THIS) PURE;
    STDMETHOD_(IDispatch *, get_Parent)(THIS) PURE;
    STDMETHOD_(BSTR, get_FullName)(THIS) PURE;
    STDMETHOD_(BSTR, get_Name)(THIS) PURE;
    STDMETHOD_(BSTR, get_Path)(THIS) PURE;
    STDMETHOD_(VARIANT_BOOL, get_Saved)(THIS) PURE;
    STDMETHOD_(short, get_NumberOfPoints)(THIS) PURE;
    STDMETHOD_(long, get_BackColor)(THIS) PURE;
    STDMETHOD_(void, put_BackColor)(THIS_ long BackColor) PURE;
    STDMETHOD_(long, get_LineColor)(THIS) PURE;
    STDMETHOD_(void, put_LineColor)(THIS_ long LineColor) PURE;
    STDMETHOD_(short, get_LineStyle)(THIS) PURE;
    STDMETHOD_(void, put_LineStyle)(THIS_ short Style) PURE;
    STDMETHOD_(long, get_Left)(THIS) PURE;
    STDMETHOD_(void, put_Left)(THIS_ long Left) PURE;
    STDMETHOD_(long, get_Top)(THIS) PURE;
    STDMETHOD_(void, put_Top)(THIS_ long Top) PURE;
    STDMETHOD_(long, get_Width)(THIS) PURE;
    STDMETHOD_(void, put_Width)(THIS_ long Width) PURE;
    STDMETHOD_(long, get_Height)(THIS) PURE;
    STDMETHOD_(void, put_Height)(THIS_ long Height) PURE;
    STDMETHOD_(VARIANT_BOOL, get_Visible)(THIS) PURE;
    STDMETHOD_(void, put_Visible)(THIS_ VARIANT_BOOL Visible) PURE;
    STDMETHOD_(void, Activate)(THIS) PURE;
    STDMETHOD_(void, Close)(THIS_ VARIANT SaveChanges, VARIANT Path) PURE;
    STDMETHOD_(void, RevertToSaved)(THIS) PURE;
    STDMETHOD_(void, Save)(THIS) PURE;
    STDMETHOD_(void, SaveAs)(THIS_ BSTR Path) PURE;
    STDMETHOD_(void, Import)(THIS_ BSTR ImportPath) PURE;
    STDMETHOD_(void, Copy)(THIS) PURE;
    STDMETHOD_(void, Cut)(THIS) PURE;
    STDMETHOD_(void, Paste)(THIS) PURE;
    STDMETHOD_(VARIANT_BOOL, AddPoint)(THIS_ short x, short y) PURE;
    STDMETHOD_(void, RemovePoint)(THIS) PURE;
};

DEFINE_GUID(IID_ICosmoFigures,0x00021160,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of interface: ICosmoFigures */
DECLARE_INTERFACE_(ICosmoFigures, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* ICosmoFigures methods */
    STDMETHOD_(IDispatch *, get_Application)(THIS) PURE;
    STDMETHOD_(IDispatch *, get_Parent)(THIS) PURE;
    STDMETHOD_(long, get_Count)(THIS) PURE;
    STDMETHOD_(IDispatch *, Item)(THIS_ VARIANT index) PURE;
    STDMETHOD_(IDispatch *, Add)(THIS) PURE;
    STDMETHOD_(IDispatch *, Open)(THIS_ BSTR Path) PURE;
    STDMETHOD_(void, Close)(THIS) PURE;
    STDMETHOD_(IUnknown *, _NewEnum)(THIS) PURE;
};

DEFINE_GUID(IID_ICosmoApplication,0x0002115F,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of interface: ICosmoApplication */
DECLARE_INTERFACE_(ICosmoApplication, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* ICosmoApplication methods */
    STDMETHOD_(IDispatch *, get_Application)(THIS) PURE;
    STDMETHOD_(IDispatch *, get_ActiveFigure)(THIS) PURE;
    STDMETHOD_(BSTR, get_Caption)(THIS) PURE;
    STDMETHOD_(IDispatch *, get_Figures)(THIS) PURE;
    STDMETHOD_(BSTR, get_FullName)(THIS) PURE;
    STDMETHOD_(BSTR, get_Name)(THIS) PURE;
    STDMETHOD_(BSTR, get_Path)(THIS) PURE;
    STDMETHOD_(long, get_Left)(THIS) PURE;
    STDMETHOD_(void, put_Left)(THIS_ long Left) PURE;
    STDMETHOD_(long, get_Top)(THIS) PURE;
    STDMETHOD_(void, put_Top)(THIS_ long Top) PURE;
    STDMETHOD_(long, get_Width)(THIS) PURE;
    STDMETHOD_(void, put_Width)(THIS_ long Width) PURE;
    STDMETHOD_(long, get_Height)(THIS) PURE;
    STDMETHOD_(void, put_Height)(THIS_ long Height) PURE;
    STDMETHOD_(VARIANT_BOOL, get_Visible)(THIS) PURE;
    STDMETHOD_(void, put_Visible)(THIS_ VARIANT_BOOL Visible) PURE;
    STDMETHOD_(BSTR, get_StatusBar)(THIS) PURE;
    STDMETHOD_(void, put_StatusBar)(THIS_ BSTR Text) PURE;
    STDMETHOD_(void, Quit)(THIS) PURE;
};

DEFINE_GUID(DIID_DICosmoFigure,0x00021164,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of dispatch interface: DICosmoFigure */
DECLARE_INTERFACE_(DICosmoFigure, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

/* Capable of dispatching all the methods of interface ICosmoFigure */
};

DEFINE_GUID(DIID_DICosmoFigures,0x00021163,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of dispatch interface: DICosmoFigures */
DECLARE_INTERFACE_(DICosmoFigures, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

/* Capable of dispatching all the methods of interface ICosmoFigures */
};

DEFINE_GUID(DIID_DICosmoApplication,0x00021162,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of dispatch interface: DICosmoApplication */
DECLARE_INTERFACE_(DICosmoApplication, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

/* Capable of dispatching all the methods of interface ICosmoApplication */
};

DEFINE_GUID(CLSID_Cosmo2Figure,0x00021107,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

class Cosmo2Figure;

DEFINE_GUID(CLSID_Cosmo2Application,0x00021166,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

class Cosmo2Application;

#endif
