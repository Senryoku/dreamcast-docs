


/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/***************************************************************************
 *                                                                         *
 *  PROGRAM     : client.c                                                 *
 *                                                                         *
 *  PURPOSE     : To demonstrate how to use the DDEML library from the     *
 *                client side and for basic testing of the DDEML API.      *
 *                                                                         *
 ***************************************************************************/

#include "client.h"
#include <string.h>
#include <memory.h>
#include "infoctrl.h"

/* global variables used in this module or among more than one module */
CONVCONTEXT CCFilter = { sizeof(CONVCONTEXT), 0, 0, 0, 0L, 0L,
    {
        sizeof(SECURITY_QUALITY_OF_SERVICE),
        SecurityImpersonation,
        SECURITY_STATIC_TRACKING,
        TRUE
    }
};
DWORD idInst = 0;
HANDLE hInst;                       /* Program instance handle               */
HANDLE hAccel;                      /* Main accelerator resource             */
HWND hwndFrame           = NULL;    /* Handle to main window                 */
HWND hwndMDIClient       = NULL;    /* Handle to MDI client                  */
HWND hwndActive          = NULL;    /* Handle to currently activated child   */
LONG DefTimeout      = DEFTIMEOUT;  /* default synchronous transaction timeout */
DWORD wDelay = 0;
BOOL fBlockNextCB = FALSE;     /* set if next callback causes a CBR_BLOCK    */
BOOL fTermNextCB = FALSE;      /* set to call DdeDisconnect() on next callback */
BOOL fAutoReconnect = FALSE;   /* set if DdeReconnect() is to be called on XTYP_DISCONNECT callbacks */
HDDEDATA hDataOwned = 0;       /* Current owned huge data handle             */
DWORD fmtLink = 0;                  /* link clipboard format number          */
DWORD DefOptions = 0;               /* default transaction optons            */
OWNED aOwned[MAX_OWNED];            /* list of all owned handles.            */
DWORD cOwned = 0;                   /* number of existing owned handles.     */
FARPROC lpMsgFilterProc;            /* instance proc from MSGF_DDEMGR filter */
HSZ hszHuge;                        /* used for checking huge item data */
HHOOK ghhk = 0;

/*
 * This is the array of formats we support
 */
FORMATINFO aFormats[] = {
#ifdef UNICODE
    { CF_UNICODETEXT, TEXT("CF_UNICODETEXT") },       // exception!  predefined format
#else
    { CF_TEXT, TEXT("CF_TEXT") },       // exception!  predefined format
#endif
    { 0, TEXT("Dummy1")  },
    { 0, TEXT("Dummy2")  },
};

/* Forward declarations of helper functions in this module */
VOID NEAR PASCAL CloseAllChildren(VOID);
VOID NEAR PASCAL InitializeMenu (HANDLE);
VOID NEAR PASCAL CommandHandler (HWND,DWORD);
VOID NEAR PASCAL SetWrap (HWND,BOOL);

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : WinMain(HANDLE, HANDLE, LPTSTR, int)                        *
 *                                                                          *
 *  PURPOSE    : Creates the "frame" window, does some initialization and   *
 *               enters the message loop.                                   *
 *                                                                          *
 ****************************************************************************/
int WINAPI WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR  lpszCmdLine,
INT    nCmdShow)
{
    MSG msg;

    hInst = hInstance;

    /* If this is the first instance of the app. register window classes */
    if (!hPrevInstance){
        if (!InitializeApplication ())
            return 0;
    }

    /* Create the frame and do other initialization */
    if (!InitializeInstance(nCmdShow))
        return 0;

    /* Enter main message loop */
    while (GetMessage (&msg, NULL, 0, 0)){
        ((HOOKPROC)*lpMsgFilterProc)(MSGF_DDEMGR, 0, (LONG)(LPMSG)&msg);
    }

    // free up any appowned handles
    while (cOwned) {
        DdeFreeDataHandle(aOwned[--cOwned].hData);
    }
    DdeFreeStringHandle(idInst, hszHuge);
    DdeUninitialize(idInst);

    UnhookWindowsHook(WH_MSGFILTER, (HOOKPROC)lpMsgFilterProc);
    FreeProcInstance(lpMsgFilterProc);

    return 0;
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : FrameWndProc (hwnd, msg, wParam, lParam )                  *
 *                                                                          *
 *  PURPOSE    : The window function for the "frame" window, which controls *
 *               the menu and encompasses all the MDI child windows. Does   *
 *               the major part of the message processing. Specifically, in *
 *               response to:                                               *
 *                                                                          *
 ****************************************************************************/
LONG  APIENTRY FrameWndProc ( hwnd, msg, wParam, lParam )
HWND   hwnd;
UINT   msg;
WPARAM wParam;
LPARAM lParam;

{
    switch (msg){
        case WM_CREATE:{
            CLIENTCREATESTRUCT ccs;

            /* Find window menu where children will be listed */
            ccs.hWindowMenu = GetSubMenu (GetMenu(hwnd),WINDOWMENU);
            ccs.idFirstChild = IDM_WINDOWCHILD;

            /* Create the MDI client filling the client area */
            hwndMDIClient = CreateWindow (TEXT("mdiclient"),
                                          NULL,
                                          WS_CHILD | WS_CLIPCHILDREN |
                                          WS_VSCROLL | WS_HSCROLL,
                                          0,
                                          0,
                                          0,
                                          0,
                                          hwnd,
                                          (HMENU)0xCAC,
                                          hInst,
                                          (LPTSTR)&ccs);


            ShowWindow (hwndMDIClient,SW_SHOW);
            break;
        }

        case WM_INITMENU:
            InitializeMenu ((HMENU)wParam);
            break;

        case WM_COMMAND:
            CommandHandler (hwnd, LOWORD(wParam));
            break;

        case WM_CLOSE:
            CloseAllChildren();
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            /*  use DefFrameProc() instead of DefWindowProc() since there
             *  are things that have to be handled differently because of MDI
             */
            return DefFrameProc (hwnd,hwndMDIClient,msg,wParam,lParam);
    }
    return 0;
}





/****************************************************************************
 *                                                                          *
 *  FUNCTION   : MDIChildWndProc                                            *
 *                                                                          *
 *  PURPOSE    : The window function for the "child" conversation and list  *
 *               windows.                                                   *
 *                                                                          *
 ****************************************************************************/
LONG  APIENTRY MDIChildWndProc( hwnd, msg, wParam, lParam )
HWND   hwnd;
UINT   msg;
WPARAM wParam;
LPARAM lParam;
{
    MYCONVINFO *pmci;
    RECT rc;

    switch (msg){
    case WM_CREATE:
        /*
         * Create a coresponding conversation info structure to link this
         * window to the conversation or conversation list it represents.
         *
         * lParam: points to the conversation info to initialize our copy to.
         */
        pmci = (MYCONVINFO *)MyAlloc(sizeof(MYCONVINFO));
        if (pmci != NULL) {
            memcpy(pmci,
                    (LPTSTR)((LPMDICREATESTRUCT)((LPCREATESTRUCT)lParam)->lpCreateParams)->lParam,
                    sizeof(MYCONVINFO));
            pmci->hwndXaction = 0;              /* no current transaction yet */
            pmci->x = pmci->y = 0;              /* new transaction windows start here */
            DdeKeepStringHandle(idInst, pmci->hszTopic);/* keep copies of the hszs for us */
            DdeKeepStringHandle(idInst, pmci->hszApp);

             // link hConv and hwnd together
            SetWindowLong(hwnd, 0, (DWORD)pmci);

            /*
             * non-list windows link the conversations to the windows via the
             * conversation user handle.
             */
            if (!pmci->fList)
                DdeSetUserHandle(pmci->hConv, QID_SYNC, (DWORD)hwnd);
        }
        goto CallDCP;
        break;

    case UM_GETNEXTCHILDX:
    case UM_GETNEXTCHILDY:
        /*
         * Calculate the next place to put the next transaction window.
         */
        {
            pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
            GetClientRect(hwnd, &rc);
            if (msg == UM_GETNEXTCHILDX) {
                pmci->x += 14;
                if (pmci->x > (rc.right - 200 - rc.left))
                    pmci->x = 0;
                return(pmci->x);
            } else {
                pmci->y += 12;
                if (pmci->y > (rc.bottom - 100 - rc.top))
                    pmci->y = 0;
                return(pmci->y);
            }
        }
        break;

    case UM_DISCONNECTED:
        /*
         * Disconnected conversations can't have any transactions so we
         * remove all the transaction windows here to show whats up.
         */
        {
            HWND hwndT;
            while (hwndT = GetWindow(hwnd, GW_CHILD))
                DestroyWindow(hwndT);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY:
        /*
         * Cleanup our conversation info structure, and disconnect all
         * conversations associated with this window.
         */
        pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
        pmci->hwndXaction = 0;      /* clear this to avoid focus problems */
        if (pmci->hConv) {
            if (pmci->fList) {
                DdeDisconnectList((HCONVLIST)pmci->hConv);
            } else {
                MyDisconnect(pmci->hConv);
            }
        }
        DdeFreeStringHandle(idInst, pmci->hszTopic);
        DdeFreeStringHandle(idInst, pmci->hszApp);
        MyFree(pmci);
        goto CallDCP;
        break;

    case WM_SETFOCUS:
        /*
         * This catches focus changes caused by dialogs.
         */
        lParam = (LPARAM)hwnd;
        // fall through

    case WM_MDIACTIVATE:
        hwndActive = (HWND)(lParam);
        pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
        /*
         * pass the focus onto the current transaction window.
         */
        if ((lParam == (LONG)hwnd) &&
                IsWindow(pmci->hwndXaction))
            SetFocus(pmci->hwndXaction);
        break;

    case ICN_HASFOCUS:
        /*
         * update which transaction window is the main one.
         */
        pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
        pmci->hwndXaction = wParam ? (HWND)lParam : NULL;
        break;

    case ICN_BYEBYE:
        /*
         * Transaction window is closing...
         *
         * wParam = hwndXact
         * lParam = lpxact
         */
        pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
        if (pmci != NULL) {
            XACT *pxact;

            pxact = (XACT *)lParam;
            if (pxact != NULL) {
                /*
                 * If this transaction is active, abandon it first.
                 */
                if (pxact->fsOptions & XOPT_ASYNC &&
                        !(pxact->fsOptions & XOPT_COMPLETED)) {
                    DdeAbandonTransaction(idInst, pmci->hConv, pxact->Result);
                }
                /*
                 * release resources associated with transaction.
                 */
                DdeFreeStringHandle(idInst, pxact->hszItem);
                MyFree((PTSTR)pxact);
                /*
                 * Locate next apropriate transaction window to get focus.
                 */
                if (!pmci->hwndXaction || pmci->hwndXaction == (HWND)wParam)
                    pmci->hwndXaction = GetWindow(hwnd, GW_CHILD);
                if (pmci->hwndXaction == (HWND)wParam)
                    pmci->hwndXaction = GetWindow((HWND)wParam, GW_HWNDNEXT);
                if (pmci->hwndXaction == (HWND)wParam ||
                        !IsWindow(pmci->hwndXaction) ||
                        !IsChild(hwnd, pmci->hwndXaction))
                    pmci->hwndXaction = NULL;
                else
                    SetFocus(pmci->hwndXaction);
            }
        }
        break;

    case WM_PAINT:
        /*
         * Paint this conversation's related information.
         */
        pmci = (MYCONVINFO *)GetWindowLong(hwnd, 0);
        {
            PAINTSTRUCT ps;
            PTSTR psz;

            BeginPaint(hwnd, &ps);
            SetBkMode(ps.hdc, TRANSPARENT);
            psz = pmci->fList ? GetConvListText((HCONVLIST)pmci->hConv) :
                    GetConvInfoText(pmci->hConv, &pmci->ci);
            if (psz) {
                GetClientRect(hwnd, &rc);
                DrawText(ps.hdc, psz, -1, &rc,
                        DT_WORDBREAK | DT_LEFT | DT_NOPREFIX | DT_TABSTOP);
                MyFree(psz);
            }
            EndPaint(hwnd, &ps);
        }
        break;

    case WM_QUERYENDSESSION:
        return TRUE;

    default:
CallDCP:
        /* Again, since the MDI default behaviour is a little different,
         * call DefMDIChildProc instead of DefWindowProc()
         */
        return DefMDIChildProc (hwnd, msg, wParam, lParam);
    }
    return FALSE;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : Initializemenu ( hMenu )                                   *
 *                                                                          *
 *  PURPOSE    : Sets up greying, enabling and checking of main menu items  *
 *               based on the app's state.                                  *
 *                                                                          *
 ****************************************************************************/
VOID NEAR PASCAL InitializeMenu ( hmenu )
HANDLE hmenu;
{
    BOOL fLink      = FALSE; // set if Link format is on the clipboard;
    BOOL fAny       = FALSE; // set if hwndActive exists
    BOOL fList      = FALSE; // set if hwndActive is a list window
    BOOL fConnected = FALSE; // set if hwndActive is a connection conversation.
    BOOL fXaction   = FALSE; // set if hwndActive has a selected transaction window
    BOOL fXactions  = FALSE; // set if hwndActive contains transaction windows
    BOOL fBlocked   = FALSE; // set if hwndActive conversation is blocked.
    BOOL fBlockNext = FALSE; // set if handActive conversation is blockNext.
    MYCONVINFO *pmci = NULL;

    if (OpenClipboard(hwndFrame)) {
        fLink = (IsClipboardFormatAvailable(fmtLink));
        CloseClipboard();
    }

    if (fAny = (IsWindow(hwndActive) &&
            (pmci = (MYCONVINFO *)GetWindowLong(hwndActive, 0)))) {
        fXactions = (BOOL)GetWindow(hwndActive, GW_CHILD);
        if (!(fList = pmci->fList)) {
            CONVINFO ci;

            ci.cb = sizeof(CONVINFO);
            DdeQueryConvInfo(pmci->hConv, QID_SYNC, &ci);
            fConnected = ci.wStatus & ST_CONNECTED;
            fXaction = IsWindow(pmci->hwndXaction);
            fBlocked = ci.wStatus & ST_BLOCKED;
            fBlockNext = ci.wStatus & ST_BLOCKNEXT;
        }
    }

    EnableMenuItem(hmenu,   IDM_EDITPASTE,
            fLink           ? MF_ENABLED    : MF_GRAYED);

    // IDM_CONNECTED - always enabled.

    EnableMenuItem(hmenu,   IDM_RECONNECT,
            fList           ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_DISCONNECT,
            fConnected && !(fXaction || fXactions) ? MF_ENABLED : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_TRANSACT,
            fConnected      ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem(hmenu,   IDM_ABANDON,
            fXaction        ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem(hmenu,   IDM_ABANDONALL,
            fXactions ? MF_ENABLED : MF_GRAYED);


    EnableMenuItem (hmenu,  IDM_BLOCKCURRENT,
            fConnected && !fBlocked ? MF_ENABLED    : MF_GRAYED);
    CheckMenuItem(hmenu, IDM_BLOCKCURRENT,
            fBlocked        ? MF_CHECKED    : MF_UNCHECKED);

    EnableMenuItem (hmenu,  IDM_ENABLECURRENT,
            fConnected && (fBlocked || fBlockNext) ? MF_ENABLED : MF_GRAYED);
    CheckMenuItem(hmenu,    IDM_ENABLECURRENT,
            !fBlocked       ? MF_CHECKED    : MF_UNCHECKED);

    EnableMenuItem (hmenu,  IDM_ENABLEONECURRENT,
            fConnected && (fBlocked) ? MF_ENABLED : MF_GRAYED);
    CheckMenuItem(hmenu,    IDM_ENABLEONECURRENT,
            fBlockNext      ? MF_CHECKED    : MF_UNCHECKED);

    EnableMenuItem (hmenu,  IDM_BLOCKALLCBS,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_ENABLEALLCBS,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_ENABLEONECB,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem(hmenu,   IDM_BLOCKNEXTCB,
            fAny || fBlockNextCB ? MF_ENABLED    : MF_GRAYED);
    CheckMenuItem(hmenu,    IDM_BLOCKNEXTCB,
            fBlockNextCB    ? MF_CHECKED    : MF_UNCHECKED);

    EnableMenuItem(hmenu,   IDM_TERMNEXTCB,
            fAny || fTermNextCB ? MF_ENABLED    : MF_GRAYED);
    CheckMenuItem(hmenu,    IDM_TERMNEXTCB,
            fTermNextCB     ? MF_CHECKED    : MF_UNCHECKED);

    // IDM_DELAY - always enabled.

    // IDM_TIMEOUT - alwasy enabled.

    EnableMenuItem (hmenu,  IDM_WINDOWTILE,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_WINDOWCASCADE,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_WINDOWICONS,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_WINDOWCLOSEALL,
            fAny            ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_XACTTILE,
            fXactions       ? MF_ENABLED    : MF_GRAYED);

    EnableMenuItem (hmenu,  IDM_XACTCASCADE,
            fXactions       ? MF_ENABLED    : MF_GRAYED);

    CheckMenuItem(hmenu,   IDM_AUTORECONNECT,
            fAutoReconnect  ? MF_CHECKED    : MF_UNCHECKED);

    // IDM_HELPABOUT - always enabled.
}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CloseAllChildren ()                                        *
 *                                                                          *
 *  PURPOSE    : Destroys all MDI child windows.                            *
 *                                                                          *
 ****************************************************************************/
VOID NEAR PASCAL CloseAllChildren ()
{
    HWND hwndT;

    /* hide the MDI client window to avoid multiple repaints */
    ShowWindow(hwndMDIClient,SW_HIDE);

    /* As long as the MDI client has a child, destroy it */
    while ( hwndT = GetWindow (hwndMDIClient, GW_CHILD)){

        /* Skip the icon title windows */
        while (hwndT && GetWindow (hwndT, GW_OWNER))
            hwndT = GetWindow (hwndT, GW_HWNDNEXT);

        if (!hwndT)
            break;

        SendMessage(hwndMDIClient, WM_MDIDESTROY, (DWORD)hwndT, 0L);
    }

    ShowWindow( hwndMDIClient, SW_SHOW);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CommandHandler ()                                          *
 *                                                                          *
 *  PURPOSE    : Processes all "frame" WM_COMMAND messages.                 *
 *                                                                          *
 ****************************************************************************/
VOID NEAR PASCAL CommandHandler (
HWND hwnd,
DWORD id)

{
    MYCONVINFO *pmci = NULL;

    if (hwndActive)
        pmci = (MYCONVINFO *)GetWindowLong(hwndActive, 0);

    switch (id){
        case IDM_EDITPASTE:
            {
                HANDLE hClipData;
                LPTSTR psz;
                XACT xact;

                if (OpenClipboard(hwnd)) {
                    if (hClipData = GetClipboardData(fmtLink)) {
                        if (psz = GlobalLock(hClipData)) {
                            /*
                             * Create a conversation with the link app and
                             * begin a request and advise start transaction.
                             */
                            xact.hConv = CreateConv(DdeCreateStringHandle(idInst, psz, 0),
                                    DdeCreateStringHandle(idInst, &psz[_tcslen(psz) + 1], 0),
                                    FALSE);
                            if (xact.hConv) {
                                psz += _tcslen(psz) + 1;
                                psz += _tcslen(psz) + 1;
                                xact.ulTimeout = DefTimeout;
                                xact.wType = XTYP_ADVSTART;
                                xact.hDdeData = 0;
#ifdef UNICODE
                                xact.wFmt = CF_UNICODETEXT;
#else
                                xact.wFmt = CF_TEXT;
#endif
                                xact.hszItem = DdeCreateStringHandle(idInst, psz, 0);
                                xact.fsOptions = 0;
                                ProcessTransaction(&xact);
                                xact.wType = XTYP_REQUEST;
                                ProcessTransaction(&xact);
                            }
                            GlobalUnlock(hClipData);
                        }
                    }
                    CloseClipboard();
                }
            }
            break;

        case IDM_CONNECT:
        case IDM_RECONNECT:
            DoDialog(MAKEINTRESOURCE(IDD_CONNECT), (DLGPROC)ConnectDlgProc,
                    id == IDM_RECONNECT, FALSE);
            break;

        case IDM_DISCONNECT:
            if (hwndActive) {
                SendMessage(hwndMDIClient, WM_MDIDESTROY, (DWORD)hwndActive, 0L);
            }
            break;

        case IDM_TRANSACT:
            if (DoDialog(MAKEINTRESOURCE(IDD_TRANSACT), (DLGPROC)TransactDlgProc,
                    (DWORD)(LPTSTR)pmci->hConv, FALSE))
                SetFocus(GetWindow(hwndActive, GW_CHILD));
            break;

        case IDM_ABANDON:
            if (pmci != NULL && IsWindow(pmci->hwndXaction)) {
                DestroyWindow(pmci->hwndXaction);
            }
            break;

        case IDM_ABANDONALL:
            DdeAbandonTransaction(idInst, pmci->hConv, 0L);
            {
                HWND hwndXaction;

                hwndXaction = GetWindow(hwndActive, GW_CHILD);
                while (hwndXaction) {
                    DestroyWindow(hwndXaction);
                    hwndXaction = GetWindow(hwndActive, GW_CHILD);
                }
            }
            break;

        case IDM_BLOCKCURRENT:
            DdeEnableCallback(idInst, pmci->hConv, EC_DISABLE);
            InvalidateRect(hwndActive, NULL, TRUE);
            break;

        case IDM_ENABLECURRENT:
            DdeEnableCallback(idInst, pmci->hConv, EC_ENABLEALL);
            InvalidateRect(hwndActive, NULL, TRUE);
            break;

        case IDM_ENABLEONECURRENT:
            DdeEnableCallback(idInst, pmci->hConv, EC_ENABLEONE);
            InvalidateRect(hwndActive, NULL, TRUE);
            break;

        case IDM_BLOCKALLCBS:
            DdeEnableCallback(idInst, 0, EC_DISABLE);
            InvalidateRect(hwndMDIClient, NULL, TRUE);
            break;

        case IDM_ENABLEALLCBS:
            DdeEnableCallback(idInst, 0, EC_ENABLEALL);
            InvalidateRect(hwndMDIClient, NULL, TRUE);
            break;

        case IDM_ENABLEONECB:
            DdeEnableCallback(idInst, 0, EC_ENABLEONE);
            InvalidateRect(hwndMDIClient, NULL, TRUE);
            break;

        case IDM_BLOCKNEXTCB:
            fBlockNextCB = !fBlockNextCB;
            break;

        case IDM_TERMNEXTCB:
            fTermNextCB = !fTermNextCB;
            break;

        case IDM_DELAY:
            DoDialog(MAKEINTRESOURCE(IDD_VALUEENTRY), (DLGPROC)DelayDlgProc, 0,
                    TRUE);
            break;

        case IDM_TIMEOUT:
            DoDialog(MAKEINTRESOURCE(IDD_VALUEENTRY), (DLGPROC)TimeoutDlgProc, 0,
                    TRUE);
            break;

        case IDM_CONTEXT:
            DoDialog(MAKEINTRESOURCE(IDD_CONTEXT), (DLGPROC)ContextDlgProc, 0, TRUE);
            break;

        case IDM_AUTORECONNECT:
            fAutoReconnect = !fAutoReconnect;
            break;

        /* The following are window commands - these are handled by the
         * MDI Client.
         */
        case IDM_WINDOWTILE:
            /* Tile MDI windows */
            SendMessage (hwndMDIClient, WM_MDITILE, 0, 0L);
            break;

        case IDM_WINDOWCASCADE:
            /* Cascade MDI windows */
            SendMessage (hwndMDIClient, WM_MDICASCADE, 0, 0L);
            break;

        case IDM_WINDOWICONS:
            /* Auto - arrange MDI icons */
            SendMessage (hwndMDIClient, WM_MDIICONARRANGE, 0, 0L);
            break;

        case IDM_WINDOWCLOSEALL:
            CloseAllChildren();
            break;

        case IDM_XACTTILE:
            TileChildWindows(hwndActive);
            break;

        case IDM_XACTCASCADE:
            MyCascadeChildWindows(hwndActive);
            break;

        case IDM_HELPABOUT:{
            DoDialog(MAKEINTRESOURCE(IDD_ABOUT), (DLGPROC)AboutDlgProc, 0, TRUE);
            break;
        }

        default:
           /*
            * This is essential, since there are frame WM_COMMANDS generated
            * by the MDI system for activating child windows via the
            * window menu.
            */
            DefFrameProc(hwnd, hwndMDIClient, WM_COMMAND,
                    (WPARAM)MAKELONG(id, 0), (LONG)(0));
    }
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : MPError (flags, id, ...)                            *
 *                                                                          *
 *  PURPOSE    : Flashes a Message Box to the user. The format string is    *
 *               taken from the STRINGTABLE.                                *
 *                                                                          *
 *  RETURNS    : Returns value returned by MessageBox() to the caller.      *
 *                                                                          *
 ****************************************************************************/
INT FAR cdecl MPError(
DWORD bFlags,
DWORD id,
...)
{
    TCHAR sz[160];
    TCHAR szFmt[128];
    va_list args;
    va_start(args, id);

    LoadString (hInst, id, szFmt, sizeof(szFmt));
    wvsprintf (sz, szFmt, args);
    LoadString (hInst, IDS_APPNAME, szFmt, sizeof(szFmt));
    return MessageBox (hwndFrame, sz, szFmt, bFlags);
}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CreateConv()                                               *
 *                                                                          *
 *  PURPOSE    :                                                            *
 *                                                                          *
 *  RETURNS    :                                                            *
 *                                                                          *
 ****************************************************************************/
HCONV CreateConv(
HSZ hszApp,
HSZ hszTopic,
BOOL fList)
{
    HCONV hConv;
    HWND hwndConv = 0;
    CONVINFO ci;

    if (fList) {
        hConv = (HCONV)DdeConnectList(idInst, hszApp, hszTopic, 0, &CCFilter);
    } else {
        hConv = DdeConnect(idInst, hszApp, hszTopic, &CCFilter);
    }
    if (hConv) {
        if (fList) {
            ci.hszSvcPartner = hszApp;
            ci.hszTopic = hszTopic;
        } else {
            ci.cb = sizeof(CONVINFO);
            DdeQueryConvInfo(hConv, QID_SYNC, &ci);
        }
        hwndConv = AddConv(ci.hszSvcPartner, ci.hszTopic, hConv, fList);
        // HSZs get freed when window dies.
    }
    if (!hwndConv) {
        DdeFreeStringHandle(idInst, hszApp);
        DdeFreeStringHandle(idInst, hszTopic);
    }
    return(hConv);
}






/****************************************************************************
 *                                                                          *
 *  FUNCTION   : AddConv()                                                  *
 *                                                                          *
 *  PURPOSE    : Creates an MDI window representing a conversation          *
 *               (fList = FALSE) or a set of MID windows for the list of    *
 *               conversations (fList = TRUE).                              *
 *                                                                          *
 *  EFFECTS    : Sets the hUser for the conversation to the created MDI     *
 *               child hwnd.  Keeps the hszs if successful.                 *
 *                                                                          *
 *  RETURNS    : created MDI window handle.                                 *
 *                                                                          *
 ****************************************************************************/
HWND  APIENTRY AddConv(
HSZ hszApp,
HSZ hszTopic,
HCONV hConv,
BOOL fList)
{
    HWND hwnd;
    MDICREATESTRUCT mcs;
    MYCONVINFO mci;

    if (fList) {
        /*
         * Create all child windows FIRST so we have info for list window.
         */
        CONVINFO ci;
        HCONV hConvChild = 0;

        ci.cb = sizeof(CONVINFO);
        while (hConvChild = DdeQueryNextServer((HCONVLIST)hConv, hConvChild)) {
            if (DdeQueryConvInfo(hConvChild, QID_SYNC, &ci)) {
                AddConv(ci.hszSvcPartner, ci.hszTopic, hConvChild, FALSE);
            }
        }
    }

    mcs.szTitle = GetConvTitleText(hConv, hszApp, hszTopic, fList);

    mcs.szClass = fList ? szList : szChild;
    mcs.hOwner  = hInst;
    mcs.x = mcs.cx = CW_USEDEFAULT;
    mcs.y = mcs.cy = CW_USEDEFAULT;
    mcs.style = GetWindow(hwndMDIClient, GW_CHILD) ?
            WS_CLIPCHILDREN : (WS_MAXIMIZE | WS_CLIPCHILDREN);

    // mci.hwndXaction =
    mci.fList = fList;
    mci.hConv = hConv;
    mci.hszTopic = hszTopic;
    mci.hszApp = hszApp;
    // mci.x =
    // mci.y =
    // mci.ci =
    mcs.lParam = (DWORD)(LPTSTR)&mci;

    hwnd = (HWND)SendMessage (hwndMDIClient, WM_MDICREATE, 0,
             (LONG)(LPMDICREATESTRUCT)&mcs);

    MyFree((PTSTR)(DWORD)mcs.szTitle);

    return hwnd;
}





/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetConvListText()                                          *
 *                                                                          *
 *  RETURN     : Returns a ponter to a string containing a list of          *
 *               conversations contained in the given hConvList freeable    *
 *               by MyFree();                                               *
 *                                                                          *
 ****************************************************************************/
PTSTR GetConvListText(
HCONVLIST hConvList)
{
    HCONV hConv = 0;
    DWORD cConv = 0;
    CONVINFO ci;
    DWORD cb = 0;
    DWORD d;
    TCHAR *psz, *pszStart;

    ci.cb = sizeof(CONVINFO);

    // find out size needed.

    while (hConv = DdeQueryNextServer(hConvList, hConv)) {
        if (DdeQueryConvInfo(hConv, QID_SYNC, &ci)) {
            if (!IsWindow((HWND)ci.hUser)) {
                if (ci.wStatus & ST_CONNECTED) {
                    /*
                     * This conversation doesn't have a corresponding
                     * MDI window.  This is probably due to a reconnection.
                     */
                    ci.hUser = (DWORD)AddConv(ci.hszSvcPartner, ci.hszTopic, hConv, FALSE);
                } else {
                    continue;   // skip this guy - he was closed locally.
                }
            }
            cb += GetWindowTextLength((HWND)ci.hUser);
            if (cConv++)
                cb += 2;        // room for CRLF
        }
    }
    cb++;                       // for terminator.

    // allocate and fill

    if (pszStart = psz = MyAlloc(cb * sizeof(TCHAR))) {
        *psz = TEXT('\0');
        while (hConv = DdeQueryNextServer(hConvList, hConv)) {
            if (DdeQueryConvInfo(hConv, QID_SYNC, &ci) &&
                    IsWindow((HWND)ci.hUser)) {
                d = GetWindowText((HWND)ci.hUser, psz, cb);
                psz += d;
                cb -= d;
                if (--cConv) {
                    *psz++ = TEXT('\r');
                    *psz++ = TEXT('\n');
                    cb -= 2;
                }
            }
        }
    }
    return(pszStart);
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetConvInfoText()                                          *
 *                                                                          *
 *  PURPOSE    : Returns a pointer to a string that reflects a              *
 *               conversation's information.  Freeable by MyFree();         *
 *                                                                          *
 ****************************************************************************/
PTSTR GetConvInfoText(
HCONV hConv,
CONVINFO *pci)
{
    PTSTR psz;
    PTSTR szApp;

    psz = MyAlloc(300 * sizeof(TCHAR));
    pci->cb = sizeof(CONVINFO);
    if (hConv) {
        if (!DdeQueryConvInfo(hConv, QID_SYNC, (PCONVINFO)pci)) {
            _tcscpy(psz, TEXT("State=Disconnected"));
            return(psz);
        }
        szApp = GetHSZName(pci->hszServiceReq);
        wsprintf(psz,
                TEXT("hUser=0x%lx\r\nhConvPartner=0x%lx\r\nhszServiceReq=%s\r\nStatus=%s\r\nState=%s\r\nLastError=%s"),
                pci->hUser, pci->hConvPartner, (LPTSTR)szApp,
                (LPTSTR)Status2String(pci->wStatus),
                (LPTSTR)State2String(pci->wConvst),
                (LPTSTR)Error2String(pci->wLastError));
        MyFree(szApp);
    } else {
        _tcscpy(psz, Error2String(DdeGetLastError(idInst)));
    }
    return(psz);
}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetConvTitleText()                                         *
 *                                                                          *
 *  PURPOSE    : Creates standard window title text based on parameters.    *
 *                                                                          *
 *  RETURNS    : psz freeable by MyFree()                                   *
 *                                                                          *
 ****************************************************************************/
PTSTR GetConvTitleText(
HCONV hConv,
HSZ hszApp,
HSZ hszTopic,
BOOL fList)
{
    DWORD cb;
    PTSTR psz;

    cb = (DWORD)DdeQueryString(idInst, hszApp, NULL, 0, 0) +
            (DWORD)DdeQueryString(idInst, hszTopic, (LPTSTR)NULL, 0, 0) +
            (fList ? 30 : 20);

    if (psz = MyAlloc(cb * sizeof(TCHAR))) {
        DdeQueryString(idInst, hszApp, psz, cb, 0);
        _tcscat(psz, TEXT("|"));
        DdeQueryString(idInst, hszTopic, &psz[_tcslen(psz)], cb, 0);
        if (fList)
            _tcscat(psz, TEXT(" - LIST"));
        wsprintf(&psz[_tcslen(psz)], TEXT(" - (%lx)"), hConv);
    }
    return(psz);
}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : Status2String()                                            *
 *                                                                          *
 *  PURPOSE    : Converts a conversation status word to a string and        *
 *               returns a pointer to that string.  The string is valid     *
 *               till the next call to this function.                       *
 *                                                                          *
 ****************************************************************************/
PTSTR Status2String(
DWORD status)
{
    DWORD c, i;
    static TCHAR szStatus[6 * 18];
    static struct {
        TCHAR *szStatus;
        DWORD status;
    } s2s[] = {
        { TEXT("Connected")    ,   ST_CONNECTED },
        { TEXT("Advise")       ,   ST_ADVISE },
        { TEXT("IsLocal")      ,   ST_ISLOCAL },
        { TEXT("Blocked")      ,   ST_BLOCKED },
        { TEXT("Client")       ,   ST_CLIENT },
        { TEXT("Disconnected") ,   ST_TERMINATED },
        { TEXT("BlockNext")    ,   ST_BLOCKNEXT },
    };
#define CFLAGS 7
    szStatus[0] = TEXT('\0');
    c = 0;
    for (i = 0; i < CFLAGS; i++) {
        if (status & s2s[i].status) {
            if (c++)
                _tcscat(szStatus, TEXT(" | "));
            _tcscat(szStatus, s2s[i].szStatus);
        }
    }
    return szStatus;
#undef CFLAGS
}




/****************************************************************************
 *                                                                          *
 *  FUNCTION   : State2String()                                             *
 *                                                                          *
 *  PURPOSE    : converts a conversation state word to a string and         *
 *               returns a pointer to that string.  The string is valid     *
 *               till the next call to this routine.                        *
 *                                                                          *
 ****************************************************************************/
PTSTR State2String(
DWORD state)
{
    static TCHAR *s2s[] = {
        TEXT("NULL")             ,
        TEXT("Incomplete")       ,
        TEXT("Standby")          ,
        TEXT("Initiating")       ,
        TEXT("ReqSent")          ,
        TEXT("DataRcvd")         ,
        TEXT("PokeSent")         ,
        TEXT("PokeAckRcvd")      ,
        TEXT("ExecSent")         ,
        TEXT("ExecAckRcvd")      ,
        TEXT("AdvSent")          ,
        TEXT("UnadvSent")        ,
        TEXT("AdvAckRcvd")       ,
        TEXT("UnadvAckRcvd")     ,
        TEXT("AdvDataSent")      ,
        TEXT("AdvDataAckRcvd")   ,
        TEXT("?")                ,    // 16
    };

    if (state >= 17)
        return s2s[17];
    else
        return s2s[state];
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : Error2String()                                             *
 *                                                                          *
 *  PURPOSE    : Converts an error code to a string and returns a pointer   *
 *               to that string.  The string is valid until the next call   *
 *               to this function.                                          *
 *                                                                          *
 ****************************************************************************/
PTSTR Error2String(
DWORD error)
{
    static TCHAR szErr[23];
    static TCHAR *e2s[] = {
        TEXT("Advacktimeout")              ,
        TEXT("Busy")                       ,
        TEXT("Dataacktimeout")             ,
        TEXT("Dll_not_initialized")        ,
        TEXT("Dll_usage")                  ,
        TEXT("Execacktimeout")             ,
        TEXT("Invalidparameter")           ,
        TEXT("Low Memory warning")         ,
        TEXT("Memory_error")               ,
        TEXT("Notprocessed")               ,
        TEXT("No_conv_established")        ,
        TEXT("Pokeacktimeout")             ,
        TEXT("Postmsg_failed")             ,
        TEXT("Reentrancy")                 ,
        TEXT("Server_died")                ,
        TEXT("Sys_error")                  ,
        TEXT("Unadvacktimeout")            ,
        TEXT("Unfound_queue_id")           ,
    };
    if (!error) {
        _tcscpy(szErr, TEXT("0"));
    } else if (error > DMLERR_LAST || error < DMLERR_FIRST) {
        _tcscpy(szErr, TEXT("???"));
    } else {
        _tcscpy(szErr, e2s[error - DMLERR_FIRST]);
    }
    return(szErr);
}





/****************************************************************************
 *                                                                          *
 *  FUNCTION   : Type2String()                                              *
 *                                                                          *
 *  PURPOSE    : Converts a wType word and fsOption flags to a string and   *
 *               returns a pointer to that string.  the string is valid     *
 *               until the next call to this function.                      *
 *                                                                          *
 ****************************************************************************/
PTSTR Type2String(
DWORD wType,
DWORD fsOptions)
{
    static TCHAR sz[30];
    static TCHAR o2s[] = TEXT("^!#$X*<?");
    static TCHAR *t2s[] = {
        TEXT("")                 ,
        TEXT("AdvData")          ,
        TEXT("AdvReq")           ,
        TEXT("AdvStart")         ,
        TEXT("AdvStop")          ,
        TEXT("Execute")          ,
        TEXT("Connect")          ,
        TEXT("ConnectConfirm")   ,
        TEXT("XactComplete")    ,
        TEXT("Poke")             ,
        TEXT("Register")         ,
        TEXT("Request")          ,
        TEXT("Term")             ,
        TEXT("Unregister")       ,
        TEXT("WildConnect")      ,
        TEXT("")                 ,
    };
    DWORD bit, c, i;

    _tcscpy(sz, t2s[((wType & XTYP_MASK) >> XTYP_SHIFT)]);
    c = _tcslen(sz);
    sz[c++] = TEXT(' ');
    for (i = 0, bit = 1; i < 7; bit = bit << 1, i++) {
        if (fsOptions & bit)
            sz[c++] = o2s[i];
    }
    sz[c] = TEXT('\0');
    return(sz);
}




/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetHSZName()                                               *
 *                                                                          *
 *  PURPOSE    : Allocates local memory for and retrieves the string form   *
 *               of an HSZ.  Returns a pointer to the local memory or NULL  *
 *               if failure.  The string must be freed via MyFree().        *
 *                                                                          *
 ****************************************************************************/
PTSTR GetHSZName(
HSZ hsz)
{
    PTSTR psz;
    DWORD cb;

    cb = (DWORD)DdeQueryString(idInst, hsz, NULL, 0, 0) + 1;
    psz = MyAlloc(cb * sizeof(TCHAR));
    DdeQueryString(idInst, hsz, psz, cb, 0);
    return(psz);
}


/****************************************************************************
 *
 *  FUNCTION   : MyMsgFilterProc
 *
 *  PURPOSE    : This filter proc gets called for each message we handle.
 *               This allows our application to properly dispatch messages
 *               that we might not otherwise see because of DDEMLs modal
 *               loop that is used while processing synchronous transactions.
 *
 *               Generally, applications that only do synchronous transactions
 *               in response to user input (as this app does) does not need
 *               to install such a filter proc because it would be very rare
 *               that a user could command the app fast enough to cause
 *               problems.  However, this is included as an example.
 *
 ****************************************************************************/
LRESULT CALLBACK MyMsgFilterProc(
int nCode,
WPARAM wParam,
LPARAM lParam)
{
    UNREFERENCED_PARAMETER(wParam);

#define lpmsg ((LPMSG)lParam)
    if (nCode == MSGF_DDEMGR) {

        /* If a keyboard message is for the MDI , let the MDI client
         * take care of it.  Otherwise, check to see if it's a normal
         * accelerator key.  Otherwise, just handle the message as usual.
         */

        if ( !TranslateMDISysAccel (hwndMDIClient, lpmsg) &&
             !TranslateAccelerator (hwndFrame, hAccel, lpmsg)){
            TranslateMessage (lpmsg);
            DispatchMessage (lpmsg);
        }
        return(1);
    }
    if (nCode < 0) {
        CallNextHookEx(ghhk, nCode, wParam, lParam);
    }
    return(0);
#undef lpmsg
}
