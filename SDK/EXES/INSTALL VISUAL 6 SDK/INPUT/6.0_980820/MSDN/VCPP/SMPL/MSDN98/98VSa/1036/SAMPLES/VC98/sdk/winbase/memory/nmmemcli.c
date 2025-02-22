/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/


#include <windows.h>
#include "memory.h"


/************************************************************************
 * void ErrorOut(LPSTR errstring)
 *
 * Purpose: Print out an meainful error code by means of
 *        GetLastError and printf
 *
 * Inputs:  errstring - the action that failed, passed by the
 *                    calling proc.
 *
 * Returns: none
 *
 * Calls:   GetLastError
 *
\************************************************************************/


void ErrorOut(LPSTR errstring)
{
   DWORD Error;
   char  str[80];

   Error= GetLastError();

   wsprintf(str, GetStringRes(IDS_ERROR), errstring, Error);
   MessageBox(ghwndMain, str, NULL, MB_OK);
}

/*************************************************************************
 * HANDLE OpenMap(LPSTR MapName)
 *
 * Purpose: Open the mapping object pointed to by MapName
 *
 * Inputs: none
 *
 * Returns: handle to mapped object or NULL if failure
 *
 * Calls: OpenFileMapping, ErrorOut
 *
\*************************************************************************/

HANDLE OpenMap( LPSTR MapName)
{
   HANDLE hAMap;

   hAMap= OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                          TRUE,
                          MapName);

   if (hAMap == NULL)
   {
      ErrorOut("OpenFileMapping");
      return(NULL);
   }
   else
      return(hAMap);
}
