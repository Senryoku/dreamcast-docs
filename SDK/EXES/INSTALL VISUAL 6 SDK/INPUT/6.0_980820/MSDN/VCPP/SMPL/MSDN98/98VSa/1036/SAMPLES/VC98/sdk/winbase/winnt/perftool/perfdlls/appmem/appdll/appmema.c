/*++

Copyright (C) 1995-1997 Microsoft Corporation

Module Name:

    appmema.c

Abstract:

    application memory performance counter interface functions

    This file contains the memory allocation function "wrappers"
    to allow monitoring of the memory usage by a performance monitoring
    application (e.g. PERFMON).

Revision History

    30 Aug 1995     Bob Watson (a-robw)     Created

--*/
#include <windows.h>
#include "appmema.h"
#include "..\pub\appmem.h"

HGLOBAL
GlobalAllocP (
    UINT    fuFlags,
    DWORD   cbBytes
)
{
    HGLOBAL hReturn;
    DWORD   dwSize;

    hReturn = GlobalAlloc (fuFlags, cbBytes);

    if (hReturn != NULL) {
        // only collect statistics on successful calls
        if (pAppData != NULL) {
            // only update data if data block is valid
            // update call count
            pAppData->dwAllocCalls++;
            dwSize = GlobalSize(hReturn);
            pAppData->dwApplicationBytes += dwSize;
        }
    }
    return hReturn;
}

HGLOBAL
GlobalFreeP (
    HGLOBAL hglbMem
)
{
    HGLOBAL hReturn;
    DWORD   dwSize;

    // get size of block before freeing it
    dwSize = GlobalSize (hglbMem);
    if (dwSize > 0) {
        // size was obtained OK so free the block
        hReturn = GlobalFree (hglbMem);
        if (hReturn == NULL) {
            // memory was freed
            if (pAppData != NULL) {
                // update call count
                pAppData->dwFreeCalls++;
                pAppData->dwApplicationBytes -= dwSize;
            }
        } else {
            // memory was not freed so don't change data
        }
    } else {
        // unable to read memory size
    }
    return hReturn;
}

HGLOBAL
GlobalReAllocP (
    HGLOBAL hglbMem,
    DWORD   cbBytes,
    UINT    fuFlags
)
{
    HGLOBAL hReturn;
    DWORD   dwBeforeSize = 0;
    DWORD   dwAfterSize = 0;

    // get size of block before re-alloc-ing it
    dwBeforeSize = GlobalSize (hglbMem);
    if (dwBeforeSize > 0) {
        // size was obtained OK so realloc the block
        hReturn = GlobalReAlloc (hglbMem, cbBytes, fuFlags);
        if (hReturn != NULL) {
            // memory was re alloc'd so get the new size
            dwAfterSize = GlobalSize (hReturn);
        } else {
            // memory was not re-alloced so set after size to 0
        }
        if (pAppData != NULL) {
            // update call count
            pAppData->dwReAllocCalls++;
            pAppData->dwApplicationBytes -= dwBeforeSize;
            pAppData->dwApplicationBytes += dwAfterSize;
        }
    } else {
        // unable to read memory size nothing has changed
        // return original pointer
        hReturn = hglbMem;
    }
    return hReturn;
}
