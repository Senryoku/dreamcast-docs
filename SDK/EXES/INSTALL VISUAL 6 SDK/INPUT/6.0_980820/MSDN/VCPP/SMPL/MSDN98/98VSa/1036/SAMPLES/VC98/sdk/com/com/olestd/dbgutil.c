/*************************************************************************
**
**    OLE 2.0 Common Utilities
**
**    dbgutil.h
**
**    This file contains file contains functions to support debug output.
**
**    (c) Copyright Microsoft Corp. 1990 - 1996 All Rights Reserved
**
*************************************************************************/

#define STRICT  1
#include "olestd.h"

static int s_nDbgIndent = 0;        // indent level for debug message
#if defined( _DEBUG )
static int s_nDbgLevel = 0;   // default dbg level printed
#else
static int s_nDbgLevel = 0;   // default dbg level printed
#endif

STDAPI_(void) OleDbgPrint(
                int     nDbgLvl,
                LPSTR   lpszPrefix,
                LPSTR   lpszMsg,
                int     nIndent
)
{
        if (nDbgLvl <= s_nDbgLevel)
                OleDbgPrintAlways(lpszPrefix, lpszMsg, nIndent);
}


STDAPI_(void) OleDbgPrintAlways(LPSTR lpszPrefix, LPSTR lpszMsg, int nIndent)
{
        int i;

        if (nIndent < 0)
                OleDbgIndent(nIndent);

        if (lpszPrefix && *lpszPrefix != '\0') {
                OutputDebugString("| ");
                for (i = 0; i < s_nDbgIndent; i++)
                        OutputDebugString("----");

                OutputDebugString(lpszPrefix);
                OutputDebugString(": ");
        }

        OutputDebugString(lpszMsg);
        if (nIndent > 0)
                OleDbgIndent(nIndent);
}

STDAPI_(void) OleDbgSetDbgLevel(int nDbgLvl)
{
        s_nDbgLevel = nDbgLvl;
}

STDAPI_(int) OleDbgGetDbgLevel( void )
{
        return s_nDbgLevel;
}

STDAPI_(void) OleDbgIndent(int n)
{
        switch (n) {
                case -1:
                        s_nDbgIndent--;
                        break;
                case 1:
                        s_nDbgIndent++;
                        break;
                case -2:
                        s_nDbgIndent = 0;
                        break;
        }
}


STDAPI_(void) OleDbgPrintRefCnt(
                int         nDbgLvl,
                LPSTR       lpszPrefix,
                LPSTR       lpszMsg,
                LPVOID      lpObj,
                ULONG       refcnt
)
{
        if (nDbgLvl <= s_nDbgLevel)
                OleDbgPrintRefCntAlways(lpszPrefix, lpszMsg, lpObj, refcnt);
}


STDAPI_(void) OleDbgPrintRefCntAlways(
                LPSTR       lpszPrefix,
                LPSTR       lpszMsg,
                LPVOID      lpObj,
                ULONG       refcnt
)
{
#if defined( _DEBUG )
        char szBuf[256];

        wsprintf(szBuf, "[obj=(0x%lx) cnt=%ld] %s", lpObj, refcnt, lpszMsg);
        OleDbgPrintAlways(lpszPrefix, szBuf, 0);
#endif
}


STDAPI_(void) OleDbgPrintRect(
                int         nDbgLvl,
                LPSTR       lpszPrefix,
                LPSTR       lpszMsg,
                LPRECT      lpRect
)
{
        if (nDbgLvl <= s_nDbgLevel)
                OleDbgPrintRectAlways(lpszPrefix, lpszMsg, lpRect);
}


STDAPI_(void) OleDbgPrintRectAlways(
                LPSTR       lpszPrefix,
                LPSTR       lpszMsg,
                LPRECT      lpRect
)
{
#if defined( _DEBUG )
        char szBuf[256];

        wsprintf(
                        szBuf,
                        "%s: (%d,%d)-(%d,%d) %dx%d\r\n",
                        lpszMsg,
                        lpRect->left,
                        lpRect->top,
                        lpRect->right,
                        lpRect->bottom,
                        (lpRect->right-lpRect->left),
                        (lpRect->bottom-lpRect->top)
        );
        OleDbgPrintAlways(lpszPrefix, szBuf, 0);
#endif
}


#define CASE_SCODE(sc)  \
                case sc: \
                        lstrcpy(/*(LPSTR)*/szErrName, /*(LPSTR)*/#sc); \
                        break;

STDAPI_(void) OleDbgPrintScodeAlways(LPSTR lpszPrefix, LPSTR lpszMsg, SCODE sc)
{
#if defined( _DEBUG )
        char szBuf[256];
        char szErrName[40];

        switch (sc) {

                /* SCODE's defined in SCODE.H */

                CASE_SCODE(S_OK)
                CASE_SCODE(S_FALSE)
                CASE_SCODE(E_UNEXPECTED)
                CASE_SCODE(E_OUTOFMEMORY)
                CASE_SCODE(E_INVALIDARG)
                CASE_SCODE(E_NOINTERFACE)
                CASE_SCODE(E_POINTER)
                CASE_SCODE(E_HANDLE)
                CASE_SCODE(E_ABORT)
                CASE_SCODE(E_FAIL)
                CASE_SCODE(E_ACCESSDENIED)

                /* SCODE's defined in OLE2.H */

                CASE_SCODE(OLE_E_OLEVERB)
                CASE_SCODE(OLE_E_ADVF)
                CASE_SCODE(OLE_E_ENUM_NOMORE)
                CASE_SCODE(OLE_E_ADVISENOTSUPPORTED)
                CASE_SCODE(OLE_E_NOCONNECTION)
                CASE_SCODE(OLE_E_NOTRUNNING)
                CASE_SCODE(OLE_E_NOCACHE)
                CASE_SCODE(OLE_E_BLANK)
                CASE_SCODE(OLE_E_CLASSDIFF)
                CASE_SCODE(OLE_E_CANT_GETMONIKER)
                CASE_SCODE(OLE_E_CANT_BINDTOSOURCE)
                CASE_SCODE(OLE_E_STATIC)
                CASE_SCODE(OLE_E_PROMPTSAVECANCELLED)
                CASE_SCODE(OLE_E_INVALIDRECT)
                CASE_SCODE(OLE_E_WRONGCOMPOBJ)
                CASE_SCODE(OLE_E_INVALIDHWND)
                CASE_SCODE(OLE_E_NOT_INPLACEACTIVE)
                CASE_SCODE(OLE_E_CANTCONVERT)
                CASE_SCODE(OLE_E_NOSTORAGE)

                CASE_SCODE(DV_E_FORMATETC)
                CASE_SCODE(DV_E_DVTARGETDEVICE)
                CASE_SCODE(DV_E_STGMEDIUM)
                CASE_SCODE(DV_E_STATDATA)
                CASE_SCODE(DV_E_LINDEX)
                CASE_SCODE(DV_E_TYMED)
                CASE_SCODE(DV_E_CLIPFORMAT)
                CASE_SCODE(DV_E_DVASPECT)
                CASE_SCODE(DV_E_DVTARGETDEVICE_SIZE)
                CASE_SCODE(DV_E_NOIVIEWOBJECT)

                CASE_SCODE(OLE_S_USEREG)
                CASE_SCODE(OLE_S_STATIC)
                CASE_SCODE(OLE_S_MAC_CLIPFORMAT)

                CASE_SCODE(CONVERT10_E_OLESTREAM_GET)
                CASE_SCODE(CONVERT10_E_OLESTREAM_PUT)
                CASE_SCODE(CONVERT10_E_OLESTREAM_FMT)
                CASE_SCODE(CONVERT10_E_OLESTREAM_BITMAP_TO_DIB)
                CASE_SCODE(CONVERT10_E_STG_FMT)
                CASE_SCODE(CONVERT10_E_STG_NO_STD_STREAM)
                CASE_SCODE(CONVERT10_E_STG_DIB_TO_BITMAP)
                CASE_SCODE(CONVERT10_S_NO_PRESENTATION)

                CASE_SCODE(CLIPBRD_E_CANT_OPEN)
                CASE_SCODE(CLIPBRD_E_CANT_EMPTY)
                CASE_SCODE(CLIPBRD_E_CANT_SET)
                CASE_SCODE(CLIPBRD_E_BAD_DATA)
                CASE_SCODE(CLIPBRD_E_CANT_CLOSE)

                CASE_SCODE(DRAGDROP_E_NOTREGISTERED)
                CASE_SCODE(DRAGDROP_E_ALREADYREGISTERED)
                CASE_SCODE(DRAGDROP_E_INVALIDHWND)
                CASE_SCODE(DRAGDROP_S_DROP)
                CASE_SCODE(DRAGDROP_S_CANCEL)
                CASE_SCODE(DRAGDROP_S_USEDEFAULTCURSORS)

                CASE_SCODE(OLEOBJ_E_NOVERBS)
                CASE_SCODE(OLEOBJ_E_INVALIDVERB)
                CASE_SCODE(OLEOBJ_S_INVALIDVERB)
                CASE_SCODE(OLEOBJ_S_CANNOT_DOVERB_NOW)
                CASE_SCODE(OLEOBJ_S_INVALIDHWND)
                CASE_SCODE(INPLACE_E_NOTUNDOABLE)
                CASE_SCODE(INPLACE_E_NOTOOLSPACE)
                CASE_SCODE(INPLACE_S_TRUNCATED)

                /* SCODE's defined in COMPOBJ.H */

                CASE_SCODE(CO_E_NOTINITIALIZED)
                CASE_SCODE(CO_E_ALREADYINITIALIZED)
                CASE_SCODE(CO_E_CANTDETERMINECLASS)
                CASE_SCODE(CO_E_CLASSSTRING)
                CASE_SCODE(CO_E_IIDSTRING)
                CASE_SCODE(CO_E_APPNOTFOUND)
                CASE_SCODE(CO_E_APPSINGLEUSE)
                CASE_SCODE(CO_E_ERRORINAPP)
                CASE_SCODE(CO_E_DLLNOTFOUND)
                CASE_SCODE(CO_E_ERRORINDLL)
                CASE_SCODE(CO_E_WRONGOSFORAPP)
                CASE_SCODE(CO_E_OBJNOTREG)
                CASE_SCODE(CO_E_OBJISREG)
                CASE_SCODE(CO_E_OBJNOTCONNECTED)
                CASE_SCODE(CO_E_APPDIDNTREG)
                CASE_SCODE(CLASS_E_NOAGGREGATION)
                CASE_SCODE(CLASS_E_CLASSNOTAVAILABLE)
                CASE_SCODE(REGDB_E_READREGDB)
                CASE_SCODE(REGDB_E_WRITEREGDB)
                CASE_SCODE(REGDB_E_KEYMISSING)
                CASE_SCODE(REGDB_E_INVALIDVALUE)
                CASE_SCODE(REGDB_E_CLASSNOTREG)
                CASE_SCODE(REGDB_E_IIDNOTREG)
                CASE_SCODE(RPC_E_CALL_REJECTED)
                CASE_SCODE(RPC_E_CALL_CANCELED)
                CASE_SCODE(RPC_E_CANTPOST_INSENDCALL)
                CASE_SCODE(RPC_E_CANTCALLOUT_INASYNCCALL)
                CASE_SCODE(RPC_E_CANTCALLOUT_INEXTERNALCALL)
                CASE_SCODE(RPC_E_CONNECTION_TERMINATED)
                CASE_SCODE(RPC_E_SERVER_DIED)
                CASE_SCODE(RPC_E_CLIENT_DIED)
                CASE_SCODE(RPC_E_INVALID_DATAPACKET)
                CASE_SCODE(RPC_E_CANTTRANSMIT_CALL)
                CASE_SCODE(RPC_E_CLIENT_CANTMARSHAL_DATA)
                CASE_SCODE(RPC_E_CLIENT_CANTUNMARSHAL_DATA)
                CASE_SCODE(RPC_E_SERVER_CANTMARSHAL_DATA)
                CASE_SCODE(RPC_E_SERVER_CANTUNMARSHAL_DATA)
                CASE_SCODE(RPC_E_INVALID_DATA)
                CASE_SCODE(RPC_E_INVALID_PARAMETER)
                CASE_SCODE(RPC_E_UNEXPECTED)

                /* SCODE's defined in DVOBJ.H */

                CASE_SCODE(DATA_S_SAMEFORMATETC)
                CASE_SCODE(VIEW_E_DRAW)
                CASE_SCODE(VIEW_S_ALREADY_FROZEN)
                CASE_SCODE(CACHE_E_NOCACHE_UPDATED)
                CASE_SCODE(CACHE_S_FORMATETC_NOTSUPPORTED)
                CASE_SCODE(CACHE_S_SAMECACHE)
                CASE_SCODE(CACHE_S_SOMECACHES_NOTUPDATED)

                /* SCODE's defined in STORAGE.H */

                CASE_SCODE(STG_E_INVALIDFUNCTION)
                CASE_SCODE(STG_E_FILENOTFOUND)
                CASE_SCODE(STG_E_PATHNOTFOUND)
                CASE_SCODE(STG_E_TOOMANYOPENFILES)
                CASE_SCODE(STG_E_ACCESSDENIED)
                CASE_SCODE(STG_E_INVALIDHANDLE)
                CASE_SCODE(STG_E_INSUFFICIENTMEMORY)
                CASE_SCODE(STG_E_INVALIDPOINTER)
                CASE_SCODE(STG_E_NOMOREFILES)
                CASE_SCODE(STG_E_DISKISWRITEPROTECTED)
                CASE_SCODE(STG_E_SEEKERROR)
                CASE_SCODE(STG_E_WRITEFAULT)
                CASE_SCODE(STG_E_READFAULT)
                CASE_SCODE(STG_E_SHAREVIOLATION)
                CASE_SCODE(STG_E_LOCKVIOLATION)
                CASE_SCODE(STG_E_FILEALREADYEXISTS)
                CASE_SCODE(STG_E_INVALIDPARAMETER)
                CASE_SCODE(STG_E_MEDIUMFULL)
                CASE_SCODE(STG_E_ABNORMALAPIEXIT)
                CASE_SCODE(STG_E_INVALIDHEADER)
                CASE_SCODE(STG_E_INVALIDNAME)
                CASE_SCODE(STG_E_UNKNOWN)
                CASE_SCODE(STG_E_UNIMPLEMENTEDFUNCTION)
                CASE_SCODE(STG_E_INVALIDFLAG)
                CASE_SCODE(STG_E_INUSE)
                CASE_SCODE(STG_E_NOTCURRENT)
                CASE_SCODE(STG_E_REVERTED)
                CASE_SCODE(STG_E_CANTSAVE)
                CASE_SCODE(STG_E_OLDFORMAT)
                CASE_SCODE(STG_E_OLDDLL)
                CASE_SCODE(STG_E_SHAREREQUIRED)
                CASE_SCODE(STG_E_NOTFILEBASEDSTORAGE)
                CASE_SCODE(STG_E_EXTANTMARSHALLINGS)
                CASE_SCODE(STG_S_CONVERTED)

                /* SCODE's defined in MONIKER.H */

                CASE_SCODE(MK_E_CONNECTMANUALLY)
                CASE_SCODE(MK_E_EXCEEDEDDEADLINE)
                CASE_SCODE(MK_E_NEEDGENERIC)
                CASE_SCODE(MK_E_UNAVAILABLE)
                CASE_SCODE(MK_E_SYNTAX)
                CASE_SCODE(MK_E_NOOBJECT)
                CASE_SCODE(MK_E_INVALIDEXTENSION)
                CASE_SCODE(MK_E_INTERMEDIATEINTERFACENOTSUPPORTED)
                CASE_SCODE(MK_E_NOTBINDABLE)
                CASE_SCODE(MK_E_NOTBOUND)
                CASE_SCODE(MK_E_CANTOPENFILE)
                CASE_SCODE(MK_E_MUSTBOTHERUSER)
                CASE_SCODE(MK_E_NOINVERSE)
                CASE_SCODE(MK_E_NOSTORAGE)
                CASE_SCODE(MK_E_NOPREFIX)
                CASE_SCODE(MK_S_REDUCED_TO_SELF)
                CASE_SCODE(MK_S_ME)
                CASE_SCODE(MK_S_HIM)
                CASE_SCODE(MK_S_US)
                CASE_SCODE(MK_S_MONIKERALREADYREGISTERED)

                default:
                        lstrcpy(szErrName, "UNKNOWN SCODE");
        }

        wsprintf(szBuf, "%s %s (0x%lx)\n", lpszMsg, /*(LPSTR)*/szErrName, sc);
        OleDbgPrintAlways(lpszPrefix, szBuf, 0);
#endif  // _DEBUG
}
