/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    pop3evnt.h

Abstract:

    Definitions for POP3 Server Events

Author:

    RichardW,  3 Jan 95

Revision History:

Notes:

    This file is generated by the MC tool from the pop3evnt.mc file.

--*/


#ifndef __POP3EVNT_H__
#define __POP3EVNT_H__

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: POP3EVENT_SERVICE_STARTED
//
// MessageText:
//
//  The POP3 Service started successfully.
//
#define POP3EVENT_SERVICE_STARTED        0x000003E8L

//
// MessageId: POP3EVENT_MAIL_DELIVERED
//
// MessageText:
//
//  A message was successfully delivered for %1.
//
#define POP3EVENT_MAIL_DELIVERED         0x000003E9L

//
// MessageId: POP3EVENT_MAIL_DIRECTORY_CREATED
//
// MessageText:
//
//  A new mail directory was created for %1.
//
#define POP3EVENT_MAIL_DIRECTORY_CREATED 0x400007D0L

//
// MessageId: POP3EVENT_USER_CONNECT
//
// MessageText:
//
//  A client has connected
//
#define POP3EVENT_USER_CONNECT           0x400007D1L

//
// MessageId: POP3EVENT_USER_DISCONNECT
//
// MessageText:
//
//  A client has disconnected
//
#define POP3EVENT_USER_DISCONNECT        0x400007D2L

//
// MessageId: POP3EVENT_MAIL_DIRECTORY_LOCKED
//
// MessageText:
//
//  The mail directory for user %1 was locked, and could not be accessed.
//
#define POP3EVENT_MAIL_DIRECTORY_LOCKED  0x80000BB8L

//
// MessageId: POP3EVENT_VOLUME_FULL
//
// MessageText:
//
//  The volume containing the mail directory, %1, is full.
//
#define POP3EVENT_VOLUME_FULL            0x80000BB9L

//
// MessageId: POP3EVENT_LOGON_FAILURE
//
// MessageText:
//
//  A logon attempt has failed.
//
#define POP3EVENT_LOGON_FAILURE          0x80000BBAL

//
// MessageId: POP3EVENT_PARAMETER_MISSING
//
// MessageText:
//
//  The service is not configured correctly, and data was not found
//  in the registry for path %1
//
#define POP3EVENT_PARAMETER_MISSING      0xC0000FA0L


#endif  //__POP3EVNT_H__

