/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: InvisibleDesignerObjects */

#ifndef _InvisibleDesignerObjects_H_
#define _InvisibleDesignerObjects_H_

DEFINE_GUID(LIBID_InvisibleDesignerObjects,0xA2815B20L,0x97D0,0x11CF,0xA0,0xD2,0x00,0xAA,0x00,0x62,0xBE,0x57);
#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#endif

DEFINE_GUID(IID_IInvisibleDesigner,0xA39C0CD0L,0x97D0,0x11CF,0xA0,0xD2,0x00,0xAA,0x00,0x62,0xBE,0x57);

/* Definition of interface: IInvisibleDesigner */
#undef INTERFACE
#define INTERFACE IInvisibleDesigner

DECLARE_INTERFACE_(IInvisibleDesigner, IDispatch)
{
BEGIN_INTERFACE
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

    /* IInvisibleDesigner methods */
    STDMETHOD(get_MyString)(THIS_ BSTR FAR* pbstrMyString) PURE;
    STDMETHOD(put_MyString)(THIS_ BSTR bstrMyString) PURE;
    STDMETHOD_(void, AboutBox)(THIS) PURE;
};

DEFINE_GUID(DIID_DInvisibleDesignerEvents,0xA4D0B8B0L,0x97D0,0x11CF,0xA0,0xD2,0x00,0xAA,0x00,0x62,0xBE,0x57);

/* Definition of dispatch interface: DInvisibleDesignerEvents */
#undef INTERFACE
#define INTERFACE DInvisibleDesignerEvents

DECLARE_INTERFACE_(DInvisibleDesignerEvents, IDispatch)
{
BEGIN_INTERFACE
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
};

DEFINE_GUID(CLSID_InvisibleDesigner,0xA61AC930L,0x97D0,0x11CF,0xA0,0xD2,0x00,0xAA,0x00,0x62,0xBE,0x57);

#ifdef __cplusplus
class InvisibleDesigner;
#endif

#endif
