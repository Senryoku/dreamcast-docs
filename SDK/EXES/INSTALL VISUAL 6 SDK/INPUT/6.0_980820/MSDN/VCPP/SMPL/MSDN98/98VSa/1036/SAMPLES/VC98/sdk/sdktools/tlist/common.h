
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*		  Copyright (C) 1994-1996 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#define TITLE_SIZE          64
#define PROCESS_SIZE        MAX_PATH


//
// task list structure
//
typedef struct _TASK_LIST {
    DWORD       dwProcessId;
    DWORD       dwInheritedFromProcessId;
    BOOL        flags;
    HANDLE      hwnd;
    CHAR        ProcessName[PROCESS_SIZE];
    CHAR        WindowTitle[TITLE_SIZE];
} TASK_LIST, *PTASK_LIST;

typedef struct _TASK_LIST_ENUM {
    PTASK_LIST  tlist;
    DWORD       numtasks;
} TASK_LIST_ENUM, *PTASK_LIST_ENUM;


//
// Function pointer types for accessing platform-specific functions
//
typedef DWORD (*LPGetTaskList)(PTASK_LIST, DWORD);
typedef BOOL  (*LPEnableDebugPriv)(VOID);


//
// Function prototypes
//
DWORD
GetTaskList95(
    PTASK_LIST  pTask,
    DWORD       dwNumTasks
    );

DWORD
GetTaskListNT(
    PTASK_LIST  pTask,
    DWORD       dwNumTasks
    );


BOOL
EnableDebugPriv95(
    VOID
    );

BOOL
EnableDebugPrivNT(
    VOID
    );

BOOL
KillProcess(
    PTASK_LIST tlist,
    BOOL       fForce
    );

VOID
GetWindowTitles(
    PTASK_LIST_ENUM te
    );

BOOL
MatchPattern(
    PUCHAR String,
    PUCHAR Pattern
    );
