/*************************************************************************
**
**    OLE 2.0 Property Set Utilities
**
**    suminfo.h
**
**    This file contains file contains data structure defintions,
**    function prototypes, constants, etc. for OLE 2.0 Property Set
**    utilities used to manage the Summary Info property set.
**
**    (c) Copyright Microsoft Corp. 1990 - 1996 All Rights Reserved
**
*************************************************************************/

#ifndef SUMINFO_H
#define SUMINFO_H

#include <ole2.h>
#include <oleauto.h>

/* A SUMINFO variable is an instance of an abstract data type.  Thus,
**    there can be an arbitrary number of SummaryInfo streams open
**    simultaneously (subject to available memory).  Each variable must
**    be initialized prior to use by calling Init and freed after its
**    last use by calling Free.  The param argument to Init is reserved
**    for future expansion and should be zero initially. Once a SUMINFO
**    variable is allocated (by Init), the user can call the Set
**    procedures to initialize fields.  A copy of the arguments is made
**    in every case except SetThumbnail where control of the storage
**    occupied by the METAFILEPICT is merely transferred.  When the
**    Free routine is called, all storage will be deallocated including
**    that of the thumbnail.  The arguments to SetThumbNail and the
**    return values from GetThumbNail correspond to the OLE2.0 spec.
**    Note that on input, the thumbnail is read on demand but all the
**    other properties are pre-loaded.  The thumbnail is manipulated as
**    a windows handle to a METAFILEPICT structure, which in turn
**    contains a handle to the METAFILE.  The transferClip argument on
**    GetThumbNail, when set to true, transfers responsibility for
**    storage management of the thumbnail to the caller; that is, after
**    Free has been called, the handle is still valid. Clear can be
**    used to free storage for all the properties but then you must
**    call Read to load them again.  All the code is based on FAR
**    pointers.
**    CoInitialize MUST be called PRIOR to calling OleStdInitSummaryInfo.
**    Memory is allocated using the currently active IMalloc*
**    allocator (as is returned by call CoGetMalloc(MEMCTX_TASK) ).
**
** Common scenarios:
**    Read SummaryInfo
**    ----------------
**      OleStdInitSummaryInfo()
**      OleStdReadSummaryInfo()
**      . . . . .
**      call different Get routines
**      . . . . .
**      OleStdFreeSummaryInfo()
**
**    Create SummaryInfo
**    ------------------
**      OleStdInitSummaryInfo()
**      call different Set routines
**      OleStdWriteSummaryInfo()
**      OleStdFreeSummaryInfo()
**
**    Update SummaryInfo
**    ------------------
**      OleStdInitSummaryInfo()
**      OleStdReadSummaryInfo()
**      OleStdGetThumbNailProperty(necessary only if no SetThumb)
**      call different Set routines
**      OleStdWriteSummaryInfo()
**      OleStdFreeSummaryInfo()
*/

#define WORDMAX 256     //current string max for APPS; 255 + null terminator

typedef     union {
     short    iVal;             /* VT_I2                */
     long     lVal;             /* VT_I4                */
     float    fltVal;           /* VT_R4                */
     double       dblVal;       /* VT_R8                */
     DWORD bool;                /* VT_BOOL              */
     SCODE    scodeVal;         /* VT_ERROR             */
     DWORD    systimeVal;       /* VT_SYSTIME           */
     unsigned char bstrVal[WORDMAX]; /* VT_BSTR              */
   } VTUNION;

typedef struct _PROPSETLIST
   {
   FMTID formatID;
   DWORD byteOffset;
   } PROPSETLIST;

typedef struct _PROPIDLIST
   {
   DWORD propertyID;
   DWORD byteOffset;
   } PROPIDLIST;

typedef struct _PROPVALUE
   {
   DWORD vtType;
   VTUNION vtValue;
   } PROPVALUE;

typedef struct _SECTION
   {
   DWORD cBytes;
   DWORD cProperties;
   PROPIDLIST rgPropId[1/*cProperties*/];  //variable-length array
   PROPVALUE rgPropValue[1];      //CANNOT BE ACCESSED BY NAME; ONLY BY POINTER
   } SECTION;

typedef struct _SUMMARYINFO
   {
   WORD byteOrder;
   WORD formatVersion;
   WORD getOSVersion;
   WORD osVersion;
   CLSID classId;  //from compobj.h
   DWORD cSections;
   PROPSETLIST rgPropSet[1/*cSections*/]; //variable-length array
   SECTION rgSections[1/*cSections*/];    //CANNOT BE ACCESSED BY NAME; ONLY BY POINTER
   } SUMMARYINFO;

#define osWinOnDos 0
#define osMac 1
#define osWinNT 2

#define cPIDSI_STANDARD (PIDSI_DOC_SECURITY+1-2)

#ifndef WIN32
#define MAXWORD 256         //maximum string size for APPS at present
#endif

typedef struct _STDZ
   {
   DWORD vtType;
   union {
   DWORD vtByteCount;
   OLECHAR fill[4];  //use last byte as byte count for stz requests
   };
   OLECHAR rgchars[MAXWORD];
   } STDZ;
#define VTCB fill[3]    //used to set/get the count byte when in memory

typedef struct _THUMB
   {
   DWORD vtType;
   DWORD cBytes;       //clip size in memory
   DWORD selector;     //on disk -1,win clip no.  -2,mac clip no. -3,ole FMTID  0,bytes  nameLength, format name
   DWORD clipFormat;
   LPOLESTR lpstzName;
   LPOLESTR lpByte;
   } THUMB;

#define VT_CF_BYTES 0
#define VT_CF_WIN (-1)
#define VT_CF_MAC (-2)
#define VT_CF_FMTID (-3)
#define VT_CF_NAME (-4)
#define VT_CF_EMPTY (-5)
#define VT_CF_OOM (-6)      // Out of memory
typedef THUMB FAR *LPTHUMB;

typedef STDZ FAR *LPSTDZ;

typedef struct _TIME
   {
   DWORD vtType;
   FILETIME time;
   } TIME;

typedef struct _INTS
   {
   DWORD vtType;
   DWORD value;
   } INTS;

#define MAXTIME (PIDSI_LASTSAVE_DTM-PIDSI_EDITTIME+1)
#define MAXINTS (PIDSI_CHARCOUNT-PIDSI_PAGECOUNT+1+1)
#define MAXSTDZ (PIDSI_REVNUMBER-PIDSI_TITLE+1+1)

typedef struct _STANDARDSECINMEM
   {
   DWORD cBytes;
   DWORD cProperties;
   PROPIDLIST rgPropId[cPIDSI_STANDARD/*cProperties*/];  //variable-length array
   TIME rgTime[MAXTIME];
   INTS rgInts[MAXINTS];
   LPSTDZ rglpsz[MAXSTDZ];
   THUMB thumb;
   } STANDARDSECINMEM;


#define OFFSET_NIL 0X00000000

#define AllSecurityFlagsEqNone 0
#define fSecurityPassworded 1
#define fSecurityRORecommended 2
#define fSecurityRO 4
#define fSecurityLockedForAnnotations 8

#define PropStreamNamePrefixByte '\005'
#define PropStreamName "\005SummaryInformation"
#define cbNewSummaryInfo(nSection) (sizeof(SUMMARYINFO)-sizeof(SECTION)+sizeof(PROPSETLIST)*((nSection)-1))
#define cbNewSection(nPropIds) (sizeof(SECTION)-sizeof(PROPVALUE)+sizeof(PROPIDLIST)*((nPropIds)-1))

#define FIntelOrder(prop) ((prop)->byteOrder==0xfffe)
#define SetOs(prop, os) {(prop)->osVersion=os; (prop)->getOSVersion=LOWORD(GetVersion());}
#define SetSumInfFMTID(fmtId) {(fmtId)->Data1=0XF29F85E0; *(long FAR *)&(fmtId)->Data2=0X10684FF9;\
            *(long FAR *)&(fmtId)->Data4[0]=0X000891AB; *(long FAR *)&(fmtId)->Data4[4]=0XD9B3272B;}
#define FEqSumInfFMTID(fmtId) ((fmtId)->dword==0XF29F85E0&&*((long FAR *)&(fmtId)->words)==0X10684FF9&&\
            *((long FAR *)&(fmtId)->bytes[0])==0X000891AB&&*((long FAR *)&(fmtId)->bytes[4])==0XD9B3272B)
#define FSzEqPropStreamName(sz) _fstricmp(sz, PropStreamName)
#define ClearSumInf(lpsuminf, cb) {_fmemset(lpsuminf,0,cb); (lpsuminf)->byteOrder=0xfffe;\
            SetOs(lpsuminf, osWinOnDos);}

typedef void FAR *LPSUMINFO;
typedef LPSTR LPSTZR;
typedef void FAR *THUMBNAIL;  //for VT_CF_WIN this is an unlocked global handle
#define API __far __pascal


/*************************************************************************
** Public Summary Info Property Set Management API
*************************************************************************/

extern "C" {
STDAPI_(LPSUMINFO) OleStdInitSummaryInfo(int reserved);
STDAPI_(void) OleStdFreeSummaryInfo(LPSUMINFO FAR *lplp);
STDAPI_(void) OleStdClearSummaryInfo(LPSUMINFO lp);
STDAPI_(int) OleStdReadSummaryInfo(LPSTREAM lpStream, LPSUMINFO lp);
STDAPI_(int) OleStdWriteSummaryInfo(LPSTREAM lpStream, LPSUMINFO lp);
STDAPI_(DWORD) OleStdGetSecurityProperty(LPSUMINFO lp);
STDAPI_(int) OleStdSetSecurityProperty(LPSUMINFO lp, DWORD security);
STDAPI_(LPSTR) OleStdGetStringProperty(LPSUMINFO lp, DWORD pid);
STDAPI_(int) OleStdSetStringProperty(LPSUMINFO lp, DWORD pid, LPOLESTR lpsz);
STDAPI_(LPSTZR) OleStdGetStringZProperty(LPSUMINFO lp, DWORD pid);
STDAPI_(void) OleStdGetDocProperty(
      LPSUMINFO       lp,
      DWORD FAR*      nPage,
      DWORD FAR*      nWords,
      DWORD FAR*      nChars
);
STDAPI_(int) OleStdSetDocProperty(
      LPSUMINFO       lp,
      DWORD           nPage,
      DWORD           nWords,
      DWORD           nChars
);
STDAPI_(int) OleStdGetThumbNailProperty(
      LPSTREAM        lps,
      LPSUMINFO       lp,
      DWORD FAR*      clipFormatNo,
      LPOLESTR FAR*   lpszName,
      THUMBNAIL FAR*  clip,
      DWORD FAR*      byteCount,
      BOOL            transferClip
);
STDAPI_(int) OleStdSetThumbNailProperty(
      LPSTREAM        lps,
      LPSUMINFO       lp,
      int             vtcfNo,
      DWORD           clipFormatNo,
      LPOLESTR        lpszName,
      THUMBNAIL       clip,
      DWORD           byteCount
);
STDAPI_(void) OleStdGetDateProperty(
      LPSUMINFO       lp,
      DWORD           pid,
      int FAR*        yr,
      int FAR*        mo,
      int FAR*        dy,
      DWORD FAR*      sc
);
STDAPI_(int) OleStdSetDateProperty(
      LPSUMINFO       lp,
      DWORD           pid,
      int             yr,
      int             mo,
      int             dy,
      int             hr,
      int             mn,
      int             sc
);

} //END C

/*************************************************************************
** DEBUG ASSERTION ROUTINES
*************************************************************************/

#if DBG
#include "assert.h"
#define FnAssert(lpstrExpr, lpstrMsg, lpstrFileName, iLine)     \
        (_assert(lpstrMsg ? lpstrMsg : lpstrExpr,               \
                 lpstrFileName,                                 \
                 iLine), NOERROR)
#endif //DBG

#endif  // SUMINFO_H
