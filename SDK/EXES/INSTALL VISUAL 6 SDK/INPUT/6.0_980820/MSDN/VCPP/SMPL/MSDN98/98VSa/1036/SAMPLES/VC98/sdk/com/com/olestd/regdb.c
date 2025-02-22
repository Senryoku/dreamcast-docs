/*
 *  REGDB.C
 *
 *  Functions to query the registration database
 *
 *  OleStdGetMiscStatusOfClass
 *  OleStdGetDefaultFileFormatOfClass
 *  OleStdGetAuxUserType
 *  OleStdGetUserTypeOfClass
 *
 *    (c) Copyright Microsoft Corp. 1992-1996 All Rights Reserved
 *
 */

#define STRICT  1
#include "olestd.h"
#include "common.h"
#include <ctype.h>

OLEDBGDATA


// Replacement for stdlib atol,
// which didn't work and doesn't take far pointers.
// Must be tolerant of leading spaces.
//
//
static LONG Atol(LPSTR lpsz)
{
   signed int sign = +1;
   UINT base = 10;
   LONG l = 0;

   if (NULL==lpsz)
   {
      OleDbgAssert (0);
      return 0;
   }
   while (isspace(*lpsz))
      lpsz++;

   if (*lpsz=='-')
   {
      lpsz++;
      sign = -1;
   }
   if (lpsz[0]=='0' && lpsz[1]=='x')
   {
      base = 16;
      lpsz+=2;
   }

   if (base==10)
   {
      while (isdigit(*lpsz))
      {
         l = l * base + *lpsz - '0';
         lpsz++;
      }
   }
   else
   {
      OleDbgAssert (base==16);
      while (isxdigit(*lpsz))
      {
         l = l * base + isdigit(*lpsz) ? *lpsz - '0' : toupper(*lpsz) - 'A' + 10;
         lpsz++;
      }
   }
   return l * sign;
}



/*
 * OleStdGetUserTypeOfClass(REFCLSID, LPSTR, UINT, HKEY)
 *
 * Purpose:
 *  Returns the user type (human readable class name) of the specified class.
 *
 * Parameters:
 *  rclsid          pointer to the clsid to retrieve user type of.
 *  lpszUserType    pointer to buffer to return user type in.
 *  cch             length of buffer pointed to by lpszUserType
 *  hKey            hKey for reg db - if this is NULL, then we
 *                   open and close the reg db within this function.  If it
 *                   is non-NULL, then we assume it's a valid key to the
 *                   \ root and use it without closing it. (useful
 *                   if you're doing lots of reg db stuff).
 *
 * Return Value:
 *  UINT            Number of characters in returned string.  0 on error.
 *
 */
STDAPI_(UINT) OleStdGetUserTypeOfClass(REFCLSID rclsid, LPOLESTR lpszUserType, UINT cch, HKEY hKey)
{

   LONG     dw;
   LONG     lRet;
   LPOLESTR lpszCLSID, lpszProgID;
   char     lpszAnsiCLSID[256], lpszAnsiProgID[256];
   BOOL     fFreeProgID = FALSE;
   BOOL     bCloseRegDB = FALSE;
   char     szKey[128];
   LPMALLOC lpIMalloc;
   char     lpszAnsiUserType[256];

   if (!lpszUserType)
      return 0;

   *lpszUserType = '\0';
   if (hKey == NULL)
   {

    //Open up the root key.
    lRet=RegOpenKey(HKEY_CLASSES_ROOT, NULL, &hKey);

    if ((LONG)ERROR_SUCCESS!=lRet)
      return (UINT)FALSE;

    bCloseRegDB = TRUE;
   }

   // Get a string containing the class name
   StringFromCLSID(rclsid, &lpszCLSID);

   W2A (lpszCLSID, lpszAnsiCLSID, 256);
   wsprintf(szKey, "CLSID\\%s", lpszAnsiCLSID);


   dw=cch;
   lRet = RegQueryValue(hKey, szKey, lpszAnsiUserType, &dw);
   A2W (lpszAnsiUserType, lpszUserType, cch);

   if ((LONG)ERROR_SUCCESS!=lRet) {
      // Load 'Unknown Source' and 'Unknown Type' strings
      dw = (LONG)LoadString(ghInst, (UINT)IDS_PSUNKNOWNTYPE, lpszAnsiUserType, cch);
      A2W (lpszAnsiUserType, lpszUserType, cch);
   }

   if ( ((LONG)ERROR_SUCCESS!=lRet) && (CoIsOle1Class(rclsid)) )
   {
     // We've got an OLE 1.0 class, so let's try to get the user type
     // name from the ProgID entry.

     ProgIDFromCLSID(rclsid, &lpszProgID);
     fFreeProgID = TRUE;

     dw = cch;
     W2A (lpszProgID, lpszAnsiProgID, 256);
     lRet = RegQueryValue(hKey, lpszAnsiProgID, lpszAnsiUserType, &dw);
     A2W (lpszAnsiUserType, lpszUserType, cch);

     if ((LONG)ERROR_SUCCESS != lRet)
      dw = 0;
   }


   if (NOERROR == CoGetMalloc(MEMCTX_TASK, &lpIMalloc))
   {
      if (fFreeProgID)
       lpIMalloc->lpVtbl->Free(lpIMalloc, (LPVOID)lpszProgID);

      lpIMalloc->lpVtbl->Free(lpIMalloc, (LPVOID)lpszCLSID);
      lpIMalloc->lpVtbl->Release(lpIMalloc);
   }

   if (bCloseRegDB)
     RegCloseKey(hKey);

   return (UINT)dw;

}



/*
 * OleStdGetAuxUserType(RCLSID, WORD, LPSTR, int, HKEY)
 *
 * Purpose:
 *  Returns the specified AuxUserType from the reg db.
 *
 * Parameters:
 *  rclsid          pointer to the clsid to retrieve aux user type of.
 *  hKey            hKey for reg db - if this is NULL, then we
 *                   open and close the reg db within this function.  If it
 *                   is non-NULL, then we assume it's a valid key to the
 *                   \ root and use it without closing it. (useful
 *                   if you're doing lots of reg db stuff).
 *  wAuxUserType    which aux user type field to look for.  In 4/93 release
 *                  2 is short name and 3 is exe name.
 *  lpszUserType    pointer to buffer to return user type in.
 *  cch             length of buffer pointed to by lpszUserType
 *
 * Return Value:
 *  UINT            Number of characters in returned string.  0 on error.
 *
 */
STDAPI_(UINT) OleStdGetAuxUserType(REFCLSID rclsid,
                           WORD     wAuxUserType,
                           LPOLESTR lpszAuxUserType,
                           int      cch,
                           HKEY     hKey)
{
   HKEY     hThisKey;
   BOOL     fCloseRegDB = FALSE;
   LONG     dw;
   LRESULT  lRet;
   LPOLESTR lpszCLSID;
   char     lpszAnsiCLSID[256];
   char     lpszAnsiAuxUserType[256];
   LPMALLOC lpIMalloc;
   char     szKey[OLEUI_CCHKEYMAX];
   char     szTemp[32];

   lpszAnsiAuxUserType[0] = '\0';

   if (NULL == hKey)
   {
     lRet = RegOpenKey(HKEY_CLASSES_ROOT, NULL, &hThisKey);

     if (ERROR_SUCCESS != lRet)
        return 0;
   }
   else
     hThisKey = hKey;

   StringFromCLSID(rclsid, &lpszCLSID);
   W2A (lpszCLSID, lpszAnsiCLSID, 256);

   lstrcpy(szKey, "CLSID\\");
   lstrcat(szKey, lpszAnsiCLSID);
   wsprintf(szTemp, "\\AuxUserType\\%d", wAuxUserType);
   lstrcat(szKey, szTemp);

   dw = cch;

   lRet = RegQueryValue(hThisKey, szKey, lpszAnsiAuxUserType, &dw);

   if (ERROR_SUCCESS != lRet) {
    dw = 0;
    lpszAuxUserType[0] = '\0';
   }


   if (fCloseRegDB)
     RegCloseKey(hThisKey);

   if (NOERROR == CoGetMalloc(MEMCTX_TASK, &lpIMalloc))
   {
      lpIMalloc->lpVtbl->Free(lpIMalloc, (LPVOID)lpszCLSID);
      lpIMalloc->lpVtbl->Release(lpIMalloc);
   }

   A2W (lpszAnsiAuxUserType, lpszAuxUserType, cch);
   return (UINT)dw;
}



/*
 * OleStdGetMiscStatusOfClass(REFCLSID, HKEY)
 *
 * Purpose:
 *  Returns the value of the misc status for the given clsid.
 *
 * Parameters:
 *  rclsid          pointer to the clsid to retrieve user type of.
 *  hKey            hKey for reg db - if this is NULL, then we
 *                   open and close the reg db within this function.  If it
 *                   is non-NULL, then we assume it's a valid key to the
 *                   \\CLSID root and use it without closing it. (useful
 *                   if you're doing lots of reg db stuff).
 *
 * Return Value:
 *  BOOL            TRUE on success, FALSE on failure.
 *
 */
STDAPI_(BOOL) OleStdGetMiscStatusOfClass(REFCLSID rclsid, HKEY hKey, DWORD FAR * lpdwValue)
{
   DWORD dw;
   LONG  lRet;
   LPOLESTR lpszCLSID;
   char     lpszAnsiCLSID[256];
   char  szKey[64];
   char  szMiscStatus[OLEUI_CCHKEYMAX];
   BOOL  bCloseRegDB = FALSE;

   if (hKey == NULL)
   {

    //Open up the root key.
    lRet=RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hKey);

    if ((LONG)ERROR_SUCCESS!=lRet)
      return FALSE;

    bCloseRegDB = TRUE;
   }

   // Get a string containing the class name
   StringFromCLSID(rclsid, &lpszCLSID);
   W2A (lpszCLSID, lpszAnsiCLSID, 256);

   // Construct key
   lstrcpy(szKey, lpszAnsiCLSID);
   lstrcat(szKey, "\\MiscStatus");


   dw=OLEUI_CCHKEYMAX;
   lRet = RegQueryValue(hKey, szKey, /*(LPSTR)*/szMiscStatus, &dw);

   if ((LONG)ERROR_SUCCESS!=lRet)
   {
      OleStdFreeString(lpszCLSID, NULL);

      if (bCloseRegDB)
        RegCloseKey(hKey);

      return FALSE;

   }

   *lpdwValue = Atol(/*(LPSTR)*/szMiscStatus);

   OleStdFreeString(lpszCLSID, NULL);

   if (bCloseRegDB)
     RegCloseKey(hKey);

   return TRUE;


}


/*
 * CLIPFORMAT OleStdGetDefaultFileFormatOfClass(REFCLSID, HKEY)
 *
 * Purpose:
 *  Returns the default file format of the specified class.
 *  this is entered in REGDB as follows:
 *      CLSID\{...}\DataFormats\DefaultFile = <cfFmt>
 *
 * Parameters:
 *  rclsid          pointer to the clsid to retrieve user type of.
 *  hKey            hKey for reg db- if this is NULL, then we
 *                   open and close the reg db within this function.  If it
 *                   is non-NULL, then we assume it's a valid key to the
 *                   \ root and use it without closing it. (useful
 *                   if you're doing lots of reg db stuff).
 *
 * Return Value:
 *  cfFmt   -- DefaultFile format
 *  NULL    -- failed to get default file format
 *
 */
STDAPI_(CLIPFORMAT) OleStdGetDefaultFileFormatOfClass(
      REFCLSID        rclsid,
      HKEY            hKey
)
{
   CLIPFORMAT cfFmt = 0;
   DWORD dw;
   LONG  lRet;
   LPOLESTR lpszCLSID;
   char     lpszAnsiCLSID[256];
   BOOL  bCloseRegDB = FALSE;
   char  szKey[128];
   char  szDefaultFile[OLEUI_CCHKEYMAX];
   BOOL  bStatus = TRUE;


   if (hKey == NULL)
   {

    //Open up the root key.
    lRet=RegOpenKey(HKEY_CLASSES_ROOT, NULL, &hKey);

    if ((LONG)ERROR_SUCCESS!=lRet)
      return 0;

    bCloseRegDB = TRUE;
   }


   // Get a string containing the class name
   StringFromCLSID(rclsid, &lpszCLSID);
   W2A (lpszCLSID, lpszAnsiCLSID, 256);

   // Construct key
   wsprintf(szKey, "CLSID\\%s\\DataFormats\\DefaultFile", lpszCLSID);
   OleStdFreeString(lpszCLSID, NULL);

   dw=OLEUI_CCHKEYMAX;
   lRet = RegQueryValue(hKey, szKey, /*(LPSTR)*/szDefaultFile, (LONG FAR *)&dw);

   if ((LONG)ERROR_SUCCESS!=lRet)
      bStatus = FALSE;
   else {
      /* if the format is a number, then it should refer to one of the
      **    standard Windows formats.
      */
      if (isdigit(szDefaultFile[0]))
         cfFmt = (CLIPFORMAT)Atol(szDefaultFile);
      else
         cfFmt = RegisterClipboardFormat(szDefaultFile);
   }

   if (bCloseRegDB)
     RegCloseKey(hKey);

   return cfFmt;
}
