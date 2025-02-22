/**************************************************************************
 *
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *
 *  Copyright (C) 1992 - 1997 Microsoft Corporation.  All Rights Reserved.
 *
 **************************************************************************/
/****************************************************************************
 *
 *   profile.h: Registry access 
 *
 *   Vidcap32 Source code
 *
 ***************************************************************************/

/*
 * utility functions to read and write values to the profile,
 * using mmtools.ini for Win16 or current user\software\microsoft\mm tools
 * in the registry for Win32
 */

/*
 * read a BOOL flag from the profile, or return default if
 * not found.
 */
BOOL mmGetProfileFlag(LPSTR appname, LPSTR valuename, BOOL bDefault);

/*
 * write a boolean value to the registry, if it is not the
 * same as the default or the value already there
 */
VOID mmWriteProfileFlag(LPSTR appname, LPSTR valuename, BOOL bValue, BOOL bDefault);

/*
 * read a UINT from the profile, or return default if
 * not found.
 */
UINT mmGetProfileInt(LPSTR appname, LPSTR valuename, UINT uDefault);

/*
 * write a UINT to the profile, if it is not the
 * same as the default or the value already there
 */
VOID mmWriteProfileInt(LPSTR appname, LPSTR valuename, UINT uValue, UINT uDefault);

/*
 * read a string from the profile into pResult.
 * result is number of bytes written into pResult
 */
DWORD
mmGetProfileString(
    LPSTR appname,
    LPSTR valuename,
    LPSTR pDefault,
    LPSTR pResult,
    int cbResult
);


/*
 * write a string to the profile
 */
VOID mmWriteProfileString(LPSTR appname, LPSTR valuename, LPSTR pData);


/*
 * read binary values from the profile into pResult.
 * result is number of bytes written into pResult
 */
DWORD
mmGetProfileBinary(
    LPSTR appname,
    LPSTR valuename,
    LPVOID pDefault,  
    LPVOID pResult,   // if NULL, return the required buffer size
    int cbSize);

/*
 * write binary data to the profile
 */
VOID
mmWriteProfileBinary(LPSTR appname, LPSTR valuename, LPVOID pData, int cbData);
		   




