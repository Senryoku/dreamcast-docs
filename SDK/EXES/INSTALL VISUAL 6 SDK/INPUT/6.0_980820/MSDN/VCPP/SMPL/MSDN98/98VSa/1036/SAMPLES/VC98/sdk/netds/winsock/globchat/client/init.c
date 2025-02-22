// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   init.c
//
//  PURPOSE:   Performs application and instance specific initialization.
//
//  FUNCTIONS:
//    InitApplication() - Initializes window data and registers window.
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <wsipx.h>              // IPX Sockets defs
#include <wsnetbs.h>
#include <nspapi.h>
#include "globals.h"            // prototypes specific to this application

HINSTANCE hInst;                // current instance

char szAppName[9];              // The name of this application
char szTitle[40];               // The title bar text

char szConnectName[16];
char szConnectServer[16];

BOOL i_should_sleep = TRUE;

//
//  FUNCTION: InitApplication(HINSTANCE, int)
//
//  PURPOSE: Initializes window data and registers window class.
//
//  PARAMETERS:
//    hInstance - The handle to the instance of this application that
//                is currently being executed.
//    nCmdShow  - Specifies how the main window is to be displayed.
//
//  RETURN VALUE:
//    TRUE  - Success
//    FALSE - Initialization failed
//
//  COMMENTS:
//
//    This function is called at application initialization time.  It
//    performs initialization tasks for the current application instance.
//    Unlike Win16, in Win32, each instance of an application must register
//    window classes.
//
//    In this function, we initialize a window class by filling out a data
//    structure of type WNDCLASS and calling the Windows RegisterClass()
//    function.  Then we create the main window and show it.
//
//

BOOL InitApplication(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASS  wc;
    HWND      hwnd; // Main window handle.
    WORD      wVersionRequested;
    WSADATA   wsaData;

    // Load the application name and description strings.

    LoadString(hInstance, IDS_APPNAME, szAppName, sizeof(szAppName));
    LoadString(hInstance, IDS_DESCRIPTION, szTitle, sizeof(szTitle));

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.

    hInst = hInstance; // Store instance handle in our global variable

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
    wc.cbClsExtra    = 0;                       // No per-class extra data.
    wc.cbWndExtra    = 0;                       // No per-window extra data.
    wc.hInstance     = hInstance;               // Owner of this class
    wc.hIcon         = LoadIcon (hInstance, szAppName); // Icon name from .RC
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Default color
    wc.lpszMenuName  = szAppName;               // Menu name from .RC
    wc.lpszClassName = szAppName;               // Name to register as

    // Register the window class and return FALSE if unsuccesful.

    if (!RegisterClass(&wc))
    {
        return FALSE;
    }

    // Create a main window for this application instance.
    hwnd = CreateWindow(szAppName,           // See RegisterClass() call
                        szTitle,             // Text for window title bar
                        WS_OVERLAPPEDWINDOW, // Window style
                        CW_USEDEFAULT, 0,    // Use default positioning
                        CW_USEDEFAULT, 0,    // Use default size
                        NULL,                // Overlapped has no parent
                        NULL,                // Use the window class menu
                        hInstance,           // This instance owns this window
                        NULL                 // Don't need data in WM_CREATE
    );

    // If window could not be created, return "failure"
    if (!hwnd)
        return FALSE;

    // Make the window visible; update its client area; and return "success"
    ShowWindow(hwnd, nCmdShow);  // Show the window
    UpdateWindow(hwnd);          // Sends WM_PAINT message

    // Link in Winsock DLL
    wVersionRequested = MAKEWORD(1,1);
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        return FALSE;
    }

    return TRUE;                 // We succeeded...
}
