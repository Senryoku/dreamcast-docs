/*****************************************************************************
 *
 *  Perfmon.h - This is the main include file. It contains all major data
 *              structures and general defines.
 *
 *  Microsoft Confidential
 *  Copyright (c) 1992-1997 Microsoft Corporation
 *
 *  Author: Mike Moskowicz
 *
 *          [1-May-1992]
 *
 ****************************************************************************/


#include <limits.h>
#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <stdlib.h>
#include <string.h>
#include <winperf.h>
#include <tchar.h>

#include "perfmrc.h"
#include "strids.h"
#include "menuids.h"
#include "dlgids.h"

#include "sizes.h"
#include "typedefs.h"
#include "winhelpr.h"


extern VOID LoadLineGraphSettings(PGRAPHSTRUCT);
extern VOID LoadRefreshSettings(PGRAPHSTRUCT);
extern VOID SetGraphTimer(PGRAPHSTRUCT lgraph) ;
extern BOOL QueryTitleEntry(HKEY,DWORD,DWORD,DWORD,LPTSTR);
extern VOID ResetGraphTimer(PGRAPHSTRUCT lgraph);


//==========================================================================//
//                                  Constants                               //
//==========================================================================//

typedef LONG NTSTATUS;

#define VERSION_NUMBER      1
#define SAVED_LOG           4
#define SAVED_ALERT         2
#define SAVED_GRAPH         1
#define SAVED_WORKSPACE     (SAVED_GRAPH | SAVED_ALERT | SAVED_LOG)
#define FNAMLEN             128


#ifdef JAPAN
#define szScalesFontFace         TEXT("System")
#define iScalesFontHeight        10
#define szScalesPrinterFontFace  TEXT("System")
#else
#define szScalesFontFace         TEXT("Helv")
#define iScalesFontHeight        8
#define szScalesPrinterFontFace  TEXT("Helvetica")
#endif

#define iScalesPrinterFontHeight 12
#define iTitlePrinterFontHeight  18

#define crLightGray              RGB (0xC0, 0xC0, 0xC0)
#define crDarkGray               RGB (0x40, 0x40, 0x40) 
#define crGray                   RGB (0x80, 0x80, 0x80)
#define crRed                    RGB (0xFF, 0x00, 0x00)
#define crGreen                  RGB (0x00, 0xFF, 0x00)
#define crBlue                   RGB (0x00, 0x00, 0xFF)
#define crBlack                  RGB (0x00, 0x00, 0x00)
#define crWhite                  RGB (0xFF, 0xFF, 0xFF)


#define LogTimerID               100
#define AlertTimerID             200
#define ChartTimerID             300
#define ReportTimerID            400


#define ChartTool                IDM_VIEWCHART
#define AlertTool                IDM_VIEWALERT
#define LogTool                  IDM_VIEWLOG
#define ReportTool               IDM_VIEWREPORT
#define AddTool                  IDM_TOOLBARADD
#define EditTool                 IDM_TOOLBARMODIFY
#define DeleteTool               IDM_TOOLBARDELETE
#define RefreshTool              IDM_TOOLBARREFRESH
#define BookmarkTool             IDM_OPTIONSBOOKMARK
#define OptionsTool              IDM_TOOLBAROPTIONS


#define szComputerPrefix         TEXT("\\\\")      // two backslashes


#define WIDESTYLES               FALSE       // Don't allow wide styled lines

//
// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

#define ARGUMENT_PRESENT(ArgumentPointer)    (\
    (CHAR *)(ArgumentPointer) != (CHAR *)(NULL) )

//==========================================================================//
//                                Global Data                               //
//==========================================================================//


#include "globals.h"


//==========================================================================//
//                             Exported Functions                           //
//==========================================================================//


LRESULT APIENTRY MainWndProc (HWND hwnd, 
                              UINT message, 
                              DWORD wParam, 
                              LONG lParam) ;


void SizePerfmonComponents (void) ;

#define TSPRINTF _stprintf

// #ifdef UNICODE
// #define TSPRINTF swprintf
// #else
// #define TSPRINTF sprintf
// #endif

