/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dpf.h
 *  Content:    header file for debug printf
 *
 ***************************************************************************/
#ifdef NEW_DPF
//#include "newdpf.h"
#else

    #ifndef __DPF_INCLUDED__
    #define __DPF_INCLUDED__

    #ifdef __cplusplus
    extern "C" {
    #endif

    #ifdef WINNT
        #undef DEBUG
        #ifdef DBG
	    #define DEBUG
        #endif
    #endif

    extern void cdecl dprintf( UINT lvl, LPTSTR szFormat, ...);
    extern void DPFInit( void );
    #ifdef DEBUG
        #define DPFINIT()   DPFInit()
        #define DPF         dprintf
        #define DPF_ERR(a)  dprintf( 0, DPF_MODNAME  a );
        extern HWND hWndListBox;
       // #if defined( _WIN32 ) && !defined(WINNT)
	    // #define DEBUG_BREAK()       _try { _asm { int 3 } } _except (EXCEPTION_EXECUTE_HANDLER) {;}
       // #else
	     #define DEBUG_BREAK()       DebugBreak()
       // #endif
        #define USE_DDASSERT
    #else
        #pragma warning(disable:4002)
        #define DPFINIT()
        #define DPF()
        #define DPF_ERR(a)
        #define DEBUG_BREAK()
    #endif

    #if defined(DEBUG) && defined(USE_DDASSERT)

    extern void _DDAssert(LPCTSTR szFile, int nLine, LPCTSTR szCondition);

    #define DDASSERT(condition) if (!(condition)) _DDAssert(TEXT(__FILE__), __LINE__, TEXT(#condition) )

    #else  /* DEBUG && USE_DDASSERT */

    #define DDASSERT(condition)

    #endif /* DEBUG && USE_DDASSERT */

    #ifdef _WIN32

#ifndef UNDER_CE
    #ifdef DEBUG
        __inline DWORD clockrate() {LARGE_INTEGER li; QueryPerformanceFrequency(&li); return li.LowPart;}
        __inline DWORD clock()     {LARGE_INTEGER li; QueryPerformanceCounter(&li);   return li.LowPart;}

        #define TIMEVAR(t)    DWORD t ## T; DWORD t ## N
        #define TIMEZERO(t)   t ## T = 0, t ## N = 0
        #define TIMESTART(t)  t ## T -= clock(), t ## N ++
        #define TIMESTOP(t)   t ## T += clock()
        #define TIMEFMT(t)    ((DWORD)(t) / clockrate()), (((DWORD)(t) * 1000 / clockrate())%1000)
        #define TIMEOUT(t)    if (t ## N) DPF(1, #t ": %ld calls, %ld.%03ld sec (%ld.%03ld)", t ## N, TIMEFMT(t ## T), TIMEFMT(t ## T / t ## N))
    #else
        #define TIMEVAR(t)
        #define TIMEZERO(t)
        #define TIMESTART(t)
        #define TIMESTOP(t)
        #define TIMEFMT(t)
        #define TIMEOUT(t)
    #endif
#endif //UNDER_CE

    #endif
    #ifdef __cplusplus
    }
    #endif

    #endif
#endif //use new dpf
