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
 *  circbuf.h
 */


/* Structure to manage the circular input buffer.
 */
typedef struct circularBuffer_tag
{
    HANDLE  hSelf;          /* handle to this structure */
    HANDLE  hBuffer;        /* buffer handle */
    WORD    wError;         /* error flags */
    DWORD   dwSize;         /* buffer size (in EVENTS) */
    DWORD   dwCount;        /* byte count (in EVENTS) */
    LPEVENT lpStart;        /* ptr to start of buffer */
    LPEVENT lpEnd;          /* ptr to end of buffer (last byte + 1) */
    LPEVENT lpHead;         /* ptr to head (next location to fill) */
    LPEVENT lpTail;         /* ptr to tail (next location to empty) */
} CIRCULARBUFFER;
typedef CIRCULARBUFFER FAR *LPCIRCULARBUFFER;


/* Function prototypes
 */
LPCIRCULARBUFFER AllocCircularBuffer(DWORD dwSize);
void FreeCircularBuffer(LPCIRCULARBUFFER lpBuf);
WORD FAR PASCAL GetEvent(LPCIRCULARBUFFER lpBuf, LPEVENT lpEvent);
