/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: Hello */

#ifndef _Hello_H_
#define _Hello_H_

DEFINE_GUID(LIBID_Hello,0xF37C8060L,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

DEFINE_GUID(IID_IHello,0xF37C8062L,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

/* Definition of interface: IHello */
#undef INTERFACE
#define INTERFACE IHello

DECLARE_INTERFACE_(IHello, IDispatch)
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

    /* IHello methods */
    STDMETHOD(get_Application)(THIS_ IHello FAR* FAR* retval) PURE;
    STDMETHOD(get_FullName)(THIS_ BSTR FAR* retval) PURE;
    STDMETHOD(get_Name)(THIS_ BSTR FAR* retval) PURE;
    STDMETHOD(get_Parent)(THIS_ IHello FAR* FAR* retval) PURE;
    STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL VisibleFlag) PURE;
    STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL FAR* retval) PURE;
    STDMETHOD(Quit)(THIS) PURE;
    STDMETHOD(put_HelloMessage)(THIS_ BSTR Message) PURE;
    STDMETHOD(get_HelloMessage)(THIS_ BSTR FAR* retval) PURE;
    STDMETHOD(SayHello)(THIS) PURE;
};

DEFINE_GUID(CLSID_Hello,0xF37C8061L,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifdef __cplusplus
class Hello;
#endif

#endif
