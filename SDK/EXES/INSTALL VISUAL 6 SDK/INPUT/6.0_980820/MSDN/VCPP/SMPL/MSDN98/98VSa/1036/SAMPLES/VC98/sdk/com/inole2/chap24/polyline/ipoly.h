/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: PolylineTypeLibrary */

#ifndef _PolylineTypeLibrary_H_
#define _PolylineTypeLibrary_H_

DEFINE_GUID(LIBID_PolylineTypeLibrary,0x00021173,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

DEFINE_GUID(IID_IPolylineControl,0x00021171,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of interface: IPolylineControl */
DECLARE_INTERFACE_(IPolylineControl, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* IPolylineControl methods */
    STDMETHOD_(void, put_BackColor)(THIS_ OLE_COLOR cr) PURE;
    STDMETHOD_(OLE_COLOR, get_BackColor)(THIS) PURE;
    STDMETHOD_(void, put_LineColor)(THIS_ OLE_COLOR cr) PURE;
    STDMETHOD_(OLE_COLOR, get_LineColor)(THIS) PURE;
    STDMETHOD_(void, put_LineStyle)(THIS_ short iStyle) PURE;
    STDMETHOD_(short, get_LineStyle)(THIS) PURE;
    STDMETHOD(Clear)(THIS) PURE;
    STDMETHOD(RemoveLastPoint)(THIS) PURE;
};

DEFINE_GUID(DIID_DIPolylineControl,0x00021172,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of dispatch interface: DIPolylineControl */
DECLARE_INTERFACE_(DIPolylineControl, IDispatch)
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

/* Capable of dispatching all the methods of interface IPolylineControl */
};

DEFINE_GUID(IID_IPolylineAdviseSink10,0x00021159,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of interface: IPolylineAdviseSink10 */
DECLARE_INTERFACE_(IPolylineAdviseSink10, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* IPolylineAdviseSink10 methods */
    STDMETHOD_(void, OnPointChange)(THIS) PURE;
    STDMETHOD_(void, OnSizeChange)(THIS) PURE;
    STDMETHOD_(void, OnColorChange)(THIS) PURE;
    STDMETHOD_(void, OnLineStyleChange)(THIS) PURE;
};

DEFINE_GUID(DIID_DIPolylineAdviseSink10,0x00021170,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Definition of dispatch interface: DIPolylineAdviseSink10 */
DECLARE_INTERFACE_(DIPolylineAdviseSink10, IDispatch)
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

    /* DIPolylineAdviseSink10 methods:
    void OnPointChange(void);
    void OnSizeChange(void);
    void OnColorChange(void);
    void OnLineStyleChange(void);
    */
};

DEFINE_GUID(CLSID_Polyline19,0x0002116D,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

class Polyline19;

#endif
