
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//    PROGRAM: ENUMDRV.C
//
//    PURPOSE: Determines all drives in the system, both local and remote,
//             and their file system type
//

#define  STRICT

#include "cfiler.h"

LPTSTR 		lpDriveStrings = NULL;
extern CRITICAL_SECTION gDrvCS;  // Drive list critical section var.
extern LPDINFO          glpDrives;

/********************************************************************************\
*    FUNCTION: CheckRM(LPTSTR)
*
*    PURPOSE: Verifies that a removeable media drive contains a disk
*
*    COMMENTS:
*
*        This function is called each time a drive type is determined to be
*        removeable (DRIVE_REMOVEABLE).  An attempt is made to open a
*        file in the root directory of the drive.  If the attempt succeeds,
*        then media is present in the drive and subsequent calls to the
*        drive can be safely made.  If the call fails, then there is no media
*        present in the drive and no attempts should be made to access this
*        drive.  The Error Mode is temporarily set to 1 to allow failures
*        to immediately return to the calling program.  This eliminates
*        unwanted dialog boxes that prompt for disks to be placed in the
*        drive.
*
*    INPUT: szDriveName - removeable media drive name (ex - "a:")
*
*    OUTPUT: Returns TRUE if media present
*                    FALSE if media is not present
\*********************************************************************************/

BOOL CheckRM( LPTSTR lpszDriveName )
{
    TCHAR    szFileName[DIRECTORY_STRING_SIZE];
    DWORD    dwHold;

    SetErrorMode( SEM_FAILCRITICALERRORS );

    lstrcpy( szFileName, lpszDriveName );
    lstrcat( szFileName, TEXT(".") );

    dwHold = GetFileAttributes( szFileName );

    SetErrorMode( 0 );

    //  If no error, media must be in drive.
    if( dwHold != 0xFFFFFFFF ){
        return(TRUE);
    }
    else{
        dwHold = GetLastError();
        if( dwHold != ERROR_NOT_READY )
            ErrorMsg(TEXT("CheckRM: Get Removable Media Info Failure."));

        return(FALSE);
    }

}

/*********************************************************************************\
*    FUNCTION: DWORD EnumDrives(*LPDINFO)
*
*    PURPOSE: Enumerates available drives, and information on them. If the
*               DINFO structure passed in is NULL, it creates a linked list
*               of DINFO structures, reporting information on each available
*              drive.  If DINFO points to an existing structure, the list
*              is updated.
*
*   COMMENTS:
*       The number of available drives is first determined by a call to
*       GetLogicalDrives.  This provides a bit mask of all logical drives.
*
*       For each logical drive, a call is made to GetDriveType to determine
*       the drive type.  If the logical drive is not in the bit mask that
*       was created with the GetLogicalDrives call, then this drive is
*       bypassed.
*
*   INPUT:  LPDINFO dINfo: A pointer to a DRVINFO Structure.
*
*   OUTPUT: Returns the number of DINFO structures in the linked
*           list pointed to by dInfo.  Value is negative if error.
\**********************************************************************************/

void EnumDrives(LPDINFO *lplpRoot)
{
  DWORD         dwDriveMask;
  DWORD         dwCount;
  LPTSTR        lpszRootPathName=TEXT("?:\\");
  
  LPTSTR        lpParse;

  LPDINFO       lpDInfo = (LPDINFO)0,                // new node ptr
                lpHold = (LPDINFO)0,                 // list walking ptrs
                lpBack = (LPDINFO)0,
                lpRoot = *lplpRoot;     // root ptr


  EnterCriticalSection(&gDrvCS);

  dwCount=GetLogicalDriveStrings( 0, lpDriveStrings);
  if( !dwCount ){
    LeaveCriticalSection(&gDrvCS);
    ErrorMsg(TEXT("EnumDrives: Get Drive Strings error"));
    ExitThread((DWORD)-1);
  }

  // allocate memory, +1 for trailing NULL
  lpDriveStrings = (LPTSTR)malloc((dwCount + 1) * sizeof(TCHAR));
 
  if( lpDriveStrings == NULL){
      LeaveCriticalSection(&gDrvCS);
      ErrorMsg(TEXT("EnumDrives: Allocation error"));
      ExitThread((DWORD)-2);
  }

  if(dwCount < GetLogicalDriveStrings( dwCount, lpDriveStrings) ){
      LeaveCriticalSection(&gDrvCS);
      ErrorMsg(TEXT("EnumDrives: Drive String size Changed!"));
      ExitThread((DWORD)-3);
  }
  lpParse = lpDriveStrings;

  dwDriveMask=GetLogicalDrives();

  //
  // walk list, inserting, deleting, & updating nodes as necessary
  //
  dwCount = 0;
  lpHold = lpBack = lpRoot;

  for (*lpszRootPathName=TEXT('a');*lpszRootPathName<=TEXT('z');(*lpszRootPathName)++){
    if (dwDriveMask & 1){   // drive exists. Insert or update.

      dwCount++;

      //
      // if lpHold (the list walking ptr) is NULL, or the drive that exists
      //  does not already have a node in the list, allocate a node.
      //
      if( !lpHold || lpHold->DriveLetter > *lpszRootPathName ){
        //
        // Allocating memory for DRVINFO node
        //
        lpDInfo = (LPDINFO) malloc((DWORD)sizeof(DRVINFO));
      
        if( lpDInfo == NULL){
          LeaveCriticalSection(&gDrvCS);
          ErrorMsg(TEXT("EnumDrives: DRVINFO Allocation error"));
          ExitThread((DWORD)-4);
        }

        //
        // insert new node into list
        //
        if( lpHold == lpRoot ){
          lpDInfo->next = lpRoot;
          lpRoot = lpDInfo;
        }
        else{
          lpDInfo->next = lpBack->next;
          lpBack->next = lpDInfo;
        }

        lpBack = lpDInfo;
        lpHold = lpDInfo->next;

        lpDInfo->DriveLetter = *lpszRootPathName;
      }
      else{
        if( lpBack != lpHold )
          lpBack = lpBack->next;
        lpHold = lpHold->next;
      }

      lpBack->DriveType = GetDriveType(lpszRootPathName);
     
      lpBack->DriveName = lpParse;
      lpParse += lstrlen(lpParse)+1;
    }
    else{               // drive does not exist.
      if( lpHold )      //   if node exists, delete it.
        if( lpHold->DriveLetter == *lpszRootPathName ){
          if( lpHold == lpRoot )
            lpRoot = lpBack = lpHold->next;
          else
            lpBack->next = lpHold->next;

          free((LPVOID)lpHold);

          lpHold = lpBack->next;
        }
    }
    dwDriveMask >>= 1;
  
  } // end for

  *lplpRoot = lpRoot;
  
  LeaveCriticalSection(&gDrvCS);
   
  ExitThread(dwCount);
}
