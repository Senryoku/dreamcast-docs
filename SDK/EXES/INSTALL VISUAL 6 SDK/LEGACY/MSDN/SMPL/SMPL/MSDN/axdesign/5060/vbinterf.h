//---------------------------------------------------------------------------
// IVBGetControl
//---------------------------------------------------------------------------
// This interface lives on the X-Object
//---------------------------------------------------------------------------

// Constants for dwWhich parameter:
#define GC_WCH_SIBLING          0x00000001L
#define GC_WCH_CONTAINER        0x00000002L   // no FONLYAFTER/BEFORE
#define GC_WCH_CONTAINED        0x00000003L   // no FONLYAFTER/BEFORE
#define GC_WCH_ALL              0x00000004L
#define GC_WCH_FREVERSEDIR      0x08000000L   // OR'd with others
#define GC_WCH_FONLYAFTER       0x10000000L   // OR'd with others
#define GC_WCH_FONLYBEFORE      0x20000000L   // OR'd with others
#define GC_WCH_FSELECTED        0x40000000L   // OR'd with others

DECLARE_INTERFACE_(IVBGetControl, IUnknown)
    {
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IVBGetControl methods ****
    STDMETHOD(EnumControls)(THIS_ DWORD dwOleContF, DWORD dwWhich, LPENUMUNKNOWN FAR *ppenumUnk) PURE;
    };

//---------------------------------------------------------------------------
// IGetOleObject
//---------------------------------------------------------------------------
// This interface lives on the Extender Object (X-Object / hctl)
//---------------------------------------------------------------------------
DECLARE_INTERFACE_(IGetOleObject, IUnknown)
    {
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IGetOleObject methods ****
    STDMETHOD(GetOleObject)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    };

#ifndef __VBAPI_H__
//---------------------------------------------------------------------------
// IVBDDE
//---------------------------------------------------------------------------

typedef UINT ERR;

//---------------------------------------------------------------------------
// Data xfer structure for VBM_LINKGETDATA or VBM_LINKSETDATA
//---------------------------------------------------------------------------
typedef struct tagVBLINKDATA
  {
  WORD     wReserved;
  DWORD    cb;            // Size of data
  HANDLE   hData;         // Handle to data
  DWORD    dwReserved;
  } VBLINKDATA;

typedef VBLINKDATA FAR *LPLINKDATA;
#endif

//---------------------------------------------------------------------------
// Link modes
//---------------------------------------------------------------------------
#define LINKMODENONE                    0
#define LINKMODEAUTO                    1
#define LINKMODEMANUAL                  2
#define LINKMODENOTIFY          3

#define LINKMODESERVERPOKE              1
#define LINKMODESERVERNOPOKE    2

#define VBDDEDATA VBLINKDATA
#define LPDDEDATA LPLINKDATA

//---------------------------------------------------------------------------
// Misc DDE defines
//---------------------------------------------------------------------------
#define MAX_EXEC                        256
#define MAXLINKITEMNAME                 256

#define ACCEPTSDATAFORMAT                1
#define SUPPLIESDATAFORMAT               2

#define LINKSRCASK                       0
#define LINKSRCTELL                      1

#define LINK_DATA_OK                     0
#define LINK_DATA_OOM                    1
#define LINK_DATA_FORMATBAD              2
#define LINK_DATA_SETFAILED              3

/* Definition of interface: IVBDDESite */
#undef INTERFACE
#define INTERFACE IVBDDESite
DECLARE_INTERFACE_(IVBDDESite, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //(CLIENT) pass in a string and we will add the index
    STDMETHOD_(VOID, VBLinkMakeItemName)(THIS_ char FAR * lpszBuff) PURE;
    //(SERVER) notifies the server that the data exposed by this control
    // has changed.
    STDMETHOD_(ERR,  VBLinkPostAdvise)(THIS) PURE;
    //(CLIENT) design time only. default implementation of LinkPasteLinkOk
    STDMETHOD_(BOOL, VBPasteLinkOk)(THIS_ HANDLE FAR * phTriplet) PURE;
    //(CLIENT) default implementation of GetItemName
    STDMETHOD_(ERR,  LinkGetItemNameDefault)(THIS_ int ls, char FAR * lpszlinkitem) PURE;
};

/* Definition of interface: IVBDDE */
#undef INTERFACE
#define INTERFACE IVBDDE
DECLARE_INTERFACE_(IVBDDE, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //(BOTH)
    STDMETHOD_(LRESULT, LinkEnumFormats)(THIS_ UINT df, UINT i) PURE;
    //both?
    STDMETHOD_(LRESULT, LinkGetData)    (THIS_ int cf, LPDDEDATA lpddedata) PURE;
    STDMETHOD_(LRESULT, LinkSetData)    (THIS_ int cf, LPDDEDATA lpddedata) PURE;
    STDMETHOD_(LRESULT, LinkGetItemName)(THIS_ int ls, char FAR * lpszlinkitem) PURE;
    //(CLIENT)
    STDMETHOD_(BOOL, QPasteLinkOk)      (THIS) PURE;
};

#undef INTERFACE
#define INTERFACE IVBFormat
DECLARE_INTERFACE_(IVBFormat,IUnknown)
  {
  /* IUnknown methods */
  STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppvObj) PURE;
  STDMETHOD_(unsigned long, AddRef)(THIS) PURE;
  STDMETHOD_(unsigned long, Release)(THIS) PURE;
  STDMETHOD(Format)(VARIANT FAR *vData,  BSTR bstrFormat, LPVOID lpBuffer,
	USHORT cb,  LONG lcid, SHORT sFirstDayOfWeek,
	USHORT sFirstWeekOfYear, USHORT * rcb) PURE;
  };

#undef INTERFACE
#define INTERFACE IVBFiles
DECLARE_INTERFACE_(IVBFiles,IUnknown)
  {
  /* IUnknown methods */
  STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppvObj) PURE;
  STDMETHOD_(unsigned long, AddRef)(THIS) PURE;
  STDMETHOD_(unsigned long, Release)(THIS) PURE;

  STDMETHOD(Read)   (USHORT usFileNo, LPVOID lpBuffer, UINT cb) PURE;

  STDMETHOD(Write)  (USHORT usFileNo, LPVOID lpBuffer, UINT cb) PURE;

  STDMETHOD(Seek)   (USHORT usFileNo, ULONG lOffset, ULONG *plPos) PURE;

  STDMETHOD(SeekRel)(USHORT usFileNo, ULONG lOffset, ULONG *plPos) PURE;
  };


#undef INTERFACE
#define INTERFACE IGetVBAObject
DECLARE_INTERFACE_(IGetVBAObject,IUnknown)
  {
  /* IUnknown methods */
  STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppvObj) PURE;
  STDMETHOD_(unsigned long, AddRef)(THIS) PURE;
  STDMETHOD_(unsigned long, Release)(THIS) PURE;

  STDMETHOD(GetObject)(THIS_ REFIID riid, void FAR* FAR* ppvObj, DWORD dwReserved) PURE;
  };

//#include <initguid.h>

//IVBGetControl & IGetOleObject
DEFINE_GUID(IID_IVBGetControl, 0x40A050A0L, 0x3C31, 0x101B, 0xA8, 0x2E, 0x08, 0x00, 0x2B, 0x2B, 0x23, 0x37);
DEFINE_GUID(IID_IGetOleObject, 0x8A701DA0L, 0x4FEB, 0x101B, 0xA8, 0x2E, 0x08, 0x00, 0x2B, 0x2B, 0x23, 0x37);

//DDE
DEFINE_GUID(IID_IVBDDE,     0xCC867200L, 0x0DC1, 0x101B, 0xA3, 0xF6, 0x00, 0xAA, 0x00, 0x34, 0xE4, 0xE9);
DEFINE_GUID(IID_IVBDDESite, 0xD856BCC0L, 0x0DC1, 0x101B, 0xA3, 0xF6, 0x00, 0xAA, 0x00, 0x34, 0xE4, 0xE9);

//Format & Files
DEFINE_GUID(IID_IGetVBAObject, 0x91733A60L, 0x3F4C, 0x101B, 0xA3, 0xF6, 0x00, 0xAA, 0x00, 0x34, 0xE4, 0xE9);
DEFINE_GUID(IID_IVBFormat, 0x9849FD60L, 0x3768, 0x101B, 0x8D, 0x72, 0xAE, 0x61,0x64, 0xFF, 0xE3, 0xCF);
DEFINE_GUID(IID_IVBFiles, 0xB53BA860L, 0x3768, 0x101B, 0x8D, 0x72, 0x00, 0xDD, 0x01, 0x0E, 0xDF, 0xAA);

