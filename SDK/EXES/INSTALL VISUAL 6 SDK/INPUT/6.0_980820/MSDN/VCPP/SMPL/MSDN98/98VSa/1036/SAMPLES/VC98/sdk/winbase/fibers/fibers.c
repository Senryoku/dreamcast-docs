/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    fibers.c

Abstract:

    This module illustrates the Win32 fiber APIs.

    This example implements a fiber based file copy operation.  Note that
    a number of different techiques exists for copying files programmatically;
    this sample simply illustrates the fiber APIs.

    This example makes use of a fiber data structure which is used to
    determine the behavior and state of the fiber.  One data structure
    exists for each fiber; the pointer to the data structure is passed
    to the fiber at fiber creation time via the lpParameter fiber parameter.

    The executing thread in the process makes a call to ConvertThreadToFiber,
    which allows fibers to be scheduled by the caller.  This also allows
    the resultant fiber to be scheduled by another fiber.

    Next, two additional fibers are created, one fiber which performs read
    operations against a specified file, and another fiber which performs
    the write operations against a specified file.

    The primary fiber then schedules the read fiber.  After a succesful
    read, the read fiber schedules the write fiber.  After a succesful write
    in the write fiber, the write fiber schedules the read fiber.  When
    the read/write cycle has completed, the primary fiber is scheduled,
    which results in the display of the read/write status. If an error occurs
    during the read or write fibers, the primary fiber is scheduled and status
    of the read/write is displayed.

    The fibers, fiber data structures, and file handles are then freed
    prior to process termination.

Author:

    Scott Field (sfield) 30-Nov-95

Revision History:

--*/

#include <windows.h>
#include <stdio.h>

VOID
__stdcall
ReadFiberFunc(
    LPVOID lpParameter
    );

VOID
__stdcall
WriteFiberFunc(
    LPVOID lpParameter
    );

void
DisplayFiberInfo(
    void
    );

typedef struct {
    DWORD dwParameter;          // DWORD parameter to fiber (unused)
    DWORD dwFiberResultCode;    // GetLastError() result code
    HANDLE hFile;               // handle to operate on
    DWORD dwBytesProcessed;     // number of bytes processed
} FIBERDATASTRUCT, *PFIBERDATASTRUCT, *LPFIBERDATASTRUCT;

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

#define BUFFER_SIZE 32768   // read/write buffer size
#define FIBER_COUNT 3       // total number of fibers (including primary)

#define PRIMARY_FIBER 0 // array index to primary fiber
#define READ_FIBER 1    // array index to read fiber
#define WRITE_FIBER 2   // array index to write fiber

LPVOID g_lpFiber[FIBER_COUNT];
LPBYTE g_lpBuffer;
DWORD g_dwBytesRead;

int
__cdecl
main(
    int argc,
    char *argv[]
    )
{
    LPFIBERDATASTRUCT fs;

    if(argc != 3) {
        printf("Usage: %s <SourceFile> <DestinationFile>\n", argv[0]);
        return RTN_USAGE;
    }

    //
    // allocate storage for our fiber data structures
    //
    fs = (LPFIBERDATASTRUCT)HeapAlloc(
        GetProcessHeap(), 0, sizeof(FIBERDATASTRUCT) * FIBER_COUNT);

    if(fs == NULL) {
        printf("HeapAlloc error! (rc%=lu)\n", GetLastError());
        return RTN_ERROR;
    }

    //
    // allocate storage for the read/write buffer
    //
    g_lpBuffer = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, BUFFER_SIZE);
    if(g_lpBuffer == NULL) {
        printf("HeapAlloc error! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    //
    // open the source file
    //
    fs[READ_FIBER].hFile = CreateFile(
        argv[1],
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL
        );

    if(fs[READ_FIBER].hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile error! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    //
    // open the destination file
    //
    fs[WRITE_FIBER].hFile = CreateFile(
        argv[2],
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL
        );

    if(fs[WRITE_FIBER].hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile error! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    //
    // convert this thread to a fiber, to allow scheduling of other fibers
    //
    g_lpFiber[PRIMARY_FIBER] = ConvertThreadToFiber(&fs[PRIMARY_FIBER]);

    if(g_lpFiber[PRIMARY_FIBER] == NULL) {
        printf("ConvertThreadToFiber failed! rc=%lu\n", GetLastError());
        return RTN_ERROR;
    }

    //
    // Just initialize the primary fiber data structure.  We don't use
    // the primary fiber data structure for anything in this sample.
    //
    fs[PRIMARY_FIBER].dwParameter = 0;
    fs[PRIMARY_FIBER].dwFiberResultCode = 0;
    fs[PRIMARY_FIBER].hFile = INVALID_HANDLE_VALUE;

    //
    // create the Read fiber
    //
    g_lpFiber[READ_FIBER] = CreateFiber(0, ReadFiberFunc, &fs[READ_FIBER]);

    if(g_lpFiber[READ_FIBER] == NULL) {
        printf("CreateFiber error! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    fs[READ_FIBER].dwParameter = 0x12345678;

    //
    // create the Write fiber
    //
    g_lpFiber[WRITE_FIBER]=CreateFiber(0, WriteFiberFunc, &fs[WRITE_FIBER]);

    if(g_lpFiber[WRITE_FIBER] == NULL) {
        printf("CreateFiber error! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    fs[WRITE_FIBER].dwParameter = 0x54545454;

    //
    // switch to the read fiber
    //
    SwitchToFiber(g_lpFiber[READ_FIBER]);

    //
    // We have now been scheduled again.  Display results from the read/write
    // fibers
    //
    printf("ReadFiber result == %lu Bytes Processed == %lu\n",
        fs[READ_FIBER].dwFiberResultCode, fs[READ_FIBER].dwBytesProcessed);

    printf("WriteFiber result == %lu Bytes Processed == %lu\n",
        fs[WRITE_FIBER].dwFiberResultCode, fs[WRITE_FIBER].dwBytesProcessed);

    //
    // Delete the fibers
    //
    DeleteFiber(g_lpFiber[READ_FIBER]);
    DeleteFiber(g_lpFiber[WRITE_FIBER]);

    //
    // close handles
    //
    CloseHandle(fs[READ_FIBER].hFile);
    CloseHandle(fs[WRITE_FIBER].hFile);

    //
    // free allocated memory
    //
    HeapFree(GetProcessHeap(), 0, g_lpBuffer);
    HeapFree(GetProcessHeap(), 0, fs);

    return RTN_OK;
}

VOID
__stdcall
ReadFiberFunc(
    LPVOID lpParameter
    )
{
    LPFIBERDATASTRUCT fds = (LPFIBERDATASTRUCT)lpParameter;

    //
    // if this fiber was passed NULL for fiber data, just return,
    // causing the current thread to exit
    //
    if(fds == NULL) {
        printf("Passed NULL fiber data.  Exiting current thread.\n");
        return;
    }

    //
    // display some information pertaining to the current fiber
    //
    DisplayFiberInfo();

    fds->dwBytesProcessed = 0;

    while(1) {
        //
        // read data from file specified in the READ_FIBER data structure
        //
        if(!ReadFile(fds->hFile, g_lpBuffer, BUFFER_SIZE, &g_dwBytesRead, NULL)) {
            break;
        }

        //
        // if we reached EOF, break
        //
        if(g_dwBytesRead == 0) break;

        //
        // update number of bytes processed in the fiber data structure
        //
        fds->dwBytesProcessed += g_dwBytesRead;

        //
        // switch to the write fiber
        //
        SwitchToFiber(g_lpFiber[WRITE_FIBER]);
    } // while

    //
    // update the fiber result code
    //
    fds->dwFiberResultCode = GetLastError();

    //
    // switch back to the primary fiber
    //
    SwitchToFiber(g_lpFiber[PRIMARY_FIBER]);
}

VOID
__stdcall
WriteFiberFunc(
    LPVOID lpParameter
    )
{
    LPFIBERDATASTRUCT fds = (LPFIBERDATASTRUCT)lpParameter;
    DWORD dwBytesWritten;

    //
    // if this fiber was passed NULL for fiber data, just return,
    // causing the current thread to exit
    //
    if(fds == NULL) {
        printf("Passed NULL fiber data.  Exiting current thread.\n");
        return;
    }

    //
    // display some information pertaining to the current fiber
    //
    DisplayFiberInfo();

    //
    // assume all of the writes succeed.  If a write fails, the fiber
    // result code will be updated to reflect the reason for failure
    //
    fds->dwBytesProcessed = 0;
    fds->dwFiberResultCode = ERROR_SUCCESS;

    while (1) {
        //
        // write data to the file specified in the WRITE_FIBER data structure
        //
        if(!WriteFile(fds->hFile, g_lpBuffer, g_dwBytesRead, &dwBytesWritten, NULL)) {
            //
            // if an error occurred writing, break
            //
            break;
        }

        //
        // update number of bytes processed in the fiber data structure
        //
        fds->dwBytesProcessed += dwBytesWritten;

        //
        // switch back to the read fiber
        //
        SwitchToFiber(g_lpFiber[READ_FIBER]);
    }  // while

    //
    // if an error occurred, update the fiber result code...
    //
    fds->dwFiberResultCode = GetLastError();

    //
    // ...and switch to the primary fiber
    //
    SwitchToFiber(g_lpFiber[PRIMARY_FIBER]);
}

void
DisplayFiberInfo(
    void
    )
{
    LPFIBERDATASTRUCT fds = (LPFIBERDATASTRUCT)GetFiberData();
    LPVOID lpCurrentFiber = GetCurrentFiber();

    //
    // determine which fiber we are executing, based on the fiber address
    //
    if(lpCurrentFiber == g_lpFiber[READ_FIBER])
        printf("Read Fiber entered");
    else {
        if(lpCurrentFiber == g_lpFiber[WRITE_FIBER])
            printf("Write Fiber entered");
        else {
            if(lpCurrentFiber == g_lpFiber[PRIMARY_FIBER])
                printf("Primary Fiber entered");
            else
                printf("Unknown Fiber entered");
            }
    }

    //
    // display dwParameter from the current fiber data structure
    //
    printf(" (dwParameter == 0x%lx)\n", fds->dwParameter);
}
