/**************************************************************************
 *
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *
 *  Copyright (C) 1993 - 1997  Microsoft Corporation.  All Rights Reserved.
 * 
 **************************************************************************/

/*
 * prefer.c - Routines to get and set user preferences.
 */

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include "midimon.h"
#include "prefer.h"

/* getPreferences - Reads .INI file and gets the setup preferences.
 *      Currently, the only user preferences are window location and size.
 *      If the .INI file does not exist, returns default values.
 *
 * Params:  lpPreferences - Points to a PREFERENCES data structure that
 *              is filled with the retrieved user preferences.
 *
 * Return:  void
*/
void getPreferences(LPPREFERENCES lpPreferences)
{
    lpPreferences->iInitialX = 
        GetPrivateProfileInt(INI_DISPLAYWINDOW, INI_X, DEF_X, INI_FILENAME);

    lpPreferences->iInitialY = 
        GetPrivateProfileInt(INI_DISPLAYWINDOW, INI_Y, DEF_Y, INI_FILENAME);

    lpPreferences->iInitialW = 
        GetPrivateProfileInt(INI_DISPLAYWINDOW, INI_W, DEF_W, INI_FILENAME);

    lpPreferences->iInitialH = 
        GetPrivateProfileInt(INI_DISPLAYWINDOW, INI_H, DEF_H, INI_FILENAME);
}

/* setPreferences - Writes the .INI file with the given setup preferences.
 *
 * Params:  lpPreferences - Points to a PREFERENCES data structure containing
 *              the user preferences.
 *
 * Return:  void
 */
void setPreferences(LPPREFERENCES lpPreferences)
{
    char szTempString[20];

    while (1) { // This now aborts after one error.
		sprintf(szTempString, "%d", lpPreferences->iInitialX);
		if(WritePrivateProfileString(INI_DISPLAYWINDOW, INI_X,
								  (LPSTR) szTempString, INI_FILENAME) == 0)
			break;
        
		sprintf(szTempString, "%d", lpPreferences->iInitialY);
		if(WritePrivateProfileString(INI_DISPLAYWINDOW, INI_Y,
								  (LPSTR) szTempString, INI_FILENAME) == 0)
			break;
        
		sprintf(szTempString, "%d", lpPreferences->iInitialW);
		if(WritePrivateProfileString(INI_DISPLAYWINDOW, INI_W,
								  (LPSTR) szTempString, INI_FILENAME) == 0)
			break;
        
		sprintf(szTempString, "%d", lpPreferences->iInitialH);
		if(WritePrivateProfileString(INI_DISPLAYWINDOW, INI_H,
								  (LPSTR) szTempString, INI_FILENAME) == 0)
			break;
		return;
	}
	Error(GetStringRes(IDS_WRITEERR));
}
