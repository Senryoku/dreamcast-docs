/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    privs.c

Abstract:

    This module illustrates how to use the Windows NT LSA security API
    to manage account privileges on the local or a remote machine.

    When targetting a domain controller for privilege update operations,
    be sure to target the primary domain controller for the domain.
    The privilege settings are replicated by the primary domain controller
    to each backup domain controller as appropriate.  The NetGetDCName()
    Lan Manager API call can be used to get the primary domain controller
    computer name from a domain name.

    For a list of privilges, consult winnt.h, and search for
    SE_ASSIGNPRIMARYTOKEN_NAME.

    For a list of logon rights, which can also be assigned using this
    sample code, consult ntsecapi.h, and search for SE_BATCH_LOGON_NAME

    You can use domain\account as argv[1]. For instance, mydomain\scott will
    grant the privilege to the mydomain domain account scott.

    The optional target machine is specified as argv[2], otherwise, the
    account database is updated on the local machine.

    The LSA APIs used by this sample are Unicode only.

    Use LsaRemoveAccountRights() to remove account rights.

Author:

    Scott Field (sfield)    17-Apr-96
        Minor cleanup

    Scott Field (sfield)    12-Jul-95

--*/

#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include <windows.h>
#include <stdio.h>

#include "ntsecapi.h"

NTSTATUS
OpenPolicy(
    LPWSTR ServerName,          // machine to open policy on (Unicode)
    DWORD DesiredAccess,        // desired access to policy
    PLSA_HANDLE PolicyHandle    // resultant policy handle
    );

BOOL
GetAccountSid(
    LPTSTR SystemName,          // where to lookup account
    LPTSTR AccountName,         // account of interest
    PSID *Sid                   // resultant buffer containing SID
    );

NTSTATUS
SetPrivilegeOnAccount(
    LSA_HANDLE PolicyHandle,    // open policy handle
    PSID AccountSid,            // SID to grant privilege to
    LPWSTR PrivilegeName,       // privilege to grant (Unicode)
    BOOL bEnable                // enable or disable
    );

void
InitLsaString(
    PLSA_UNICODE_STRING LsaString, // destination
    LPWSTR String                  // source (Unicode)
    );

void
DisplayNtStatus(
    LPSTR szAPI,                // pointer to function name (ANSI)
    NTSTATUS Status             // NTSTATUS error value
    );

void
DisplayWinError(
    LPSTR szAPI,                // pointer to function name (ANSI)
    DWORD WinError              // DWORD WinError
    );

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

//
// If you have the ddk, include ntstatus.h.
//
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#endif

int
__cdecl
main(
    int argc,
    char *argv[]
    )
{
    LSA_HANDLE PolicyHandle;

    WCHAR wComputerName[256]=L"";   // static machine name buffer
    TCHAR AccountName[256];         // static account name buffer
    PSID pSid;

    NTSTATUS Status;
    int iRetVal=RTN_ERROR;          // assume error from main

    if(argc == 1) {
        fprintf(stderr,"Usage: %s <Account> [TargetMachine]\n", argv[0]);
        return RTN_USAGE;
    }

    //
    // Pick up account name on argv[1].
    // Assumes source is ANSI. Resultant string is ANSI or Unicode
    //
    wsprintf(AccountName, TEXT("%hS"), argv[1]);

    //
    // Pick up machine name on argv[2], if appropriate
    // assumes source is ANSI. Resultant string is Unicode.
    //
    if(argc == 3) wsprintfW(wComputerName, L"%hS", argv[2]);

    //
    // Open the policy on the target machine.
    //
    Status = OpenPolicy(
                wComputerName,      // target machine
                POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES,
                &PolicyHandle       // resultant policy handle
                );

    if(Status != STATUS_SUCCESS) {
        DisplayNtStatus("OpenPolicy", Status);
        return RTN_ERROR;
    }

    //
    // Obtain the SID of the user/group.
    // Note that we could target a specific machine, but we don't.
    // Specifying NULL for target machine searches for the SID in the
    // following order: well-known, Built-in and local, primary domain,
    // trusted domains.
    //
    if(GetAccountSid(
            NULL,       // default lookup logic
            AccountName,// account to obtain SID
            &pSid       // buffer to allocate to contain resultant SID
            )) {
        //
        // We only grant the privilege if we succeeded in obtaining the
        // SID. We can actually add SIDs which cannot be looked up, but
        // looking up the SID is a good sanity check which is suitable for
        // most cases.

        //
        // Grant the SeServiceLogonRight to users represented by pSid.
        //
        Status = SetPrivilegeOnAccount(
                    PolicyHandle,           // policy handle
                    pSid,                   // SID to grant privilege
                    L"SeServiceLogonRight", // Unicode privilege
                    TRUE                    // enable the privilege
                    );

        if(Status == STATUS_SUCCESS)
            iRetVal = RTN_OK;
        else
            DisplayNtStatus("SetPrivilegeOnAccount", Status);
    }
    else {
        //
        // Error obtaining SID.
        //
        DisplayWinError("GetAccountSid", GetLastError());
    }

    //
    // Close the policy handle.
    //
    LsaClose(PolicyHandle);

    //
    // Free memory allocated for SID.
    //
    if(pSid != NULL) HeapFree(GetProcessHeap(), 0, pSid);

    return iRetVal;
}

/*++
This function attempts to obtain a SID representing the supplied
account on the supplied system.

If the function succeeds, the return value is TRUE. A buffer is
allocated which contains the SID representing the supplied account.
This buffer should be freed when it is no longer needed by calling
HeapFree(GetProcessHeap(), 0, buffer)

If the function fails, the return value is FALSE. Call GetLastError()
to obtain extended error information.

Scott Field (sfield)    12-Jul-95
--*/

BOOL
GetAccountSid(
    LPTSTR SystemName,
    LPTSTR AccountName,
    PSID *Sid
    )
{
    LPTSTR ReferencedDomain=NULL;
    DWORD cbSid=128;    // initial allocation attempt
    DWORD cchReferencedDomain=16; // initial allocation size
    SID_NAME_USE peUse;
    BOOL bSuccess=FALSE; // assume this function will fail

    __try {

    //
    // initial memory allocations
    //
    *Sid = (PSID)HeapAlloc(GetProcessHeap(), 0, cbSid);

    if(*Sid == NULL) __leave;

    ReferencedDomain = (LPTSTR)HeapAlloc(
                    GetProcessHeap(),
                    0,
                    cchReferencedDomain * sizeof(TCHAR)
                    );

    if(ReferencedDomain == NULL) __leave;

    //
    // Obtain the SID of the specified account on the specified system.
    //
    while(!LookupAccountName(
                    SystemName,         // machine to lookup account on
                    AccountName,        // account to lookup
                    *Sid,               // SID of interest
                    &cbSid,             // size of SID
                    ReferencedDomain,   // domain account was found on
                    &cchReferencedDomain,
                    &peUse
                    )) {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            //
            // reallocate memory
            //
            *Sid = (PSID)HeapReAlloc(
                        GetProcessHeap(),
                        0,
                        *Sid,
                        cbSid
                        );
            if(*Sid == NULL) __leave;

            ReferencedDomain = (LPTSTR)HeapReAlloc(
                        GetProcessHeap(),
                        0,
                        ReferencedDomain,
                        cchReferencedDomain * sizeof(TCHAR)
                        );
            if(ReferencedDomain == NULL) __leave;
        }
        else __leave;
    }

    //
    // Indicate success.
    //
    bSuccess = TRUE;

    } // try
    __finally {

    //
    // Cleanup and indicate failure, if appropriate.
    //

    HeapFree(GetProcessHeap(), 0, ReferencedDomain);

    if(!bSuccess) {
        if(*Sid != NULL) {
            HeapFree(GetProcessHeap(), 0, *Sid);
            *Sid = NULL;
        }
    }

    } // finally

    return bSuccess;
}

NTSTATUS
SetPrivilegeOnAccount(
    LSA_HANDLE PolicyHandle,    // open policy handle
    PSID AccountSid,            // SID to grant privilege to
    LPWSTR PrivilegeName,       // privilege to grant (Unicode)
    BOOL bEnable                // enable or disable
    )
{
    LSA_UNICODE_STRING PrivilegeString;

    //
    // Create a LSA_UNICODE_STRING for the privilege name.
    //
    InitLsaString(&PrivilegeString, PrivilegeName);

    //
    // grant or revoke the privilege, accordingly
    //
    if(bEnable) {
        return LsaAddAccountRights(
                PolicyHandle,       // open policy handle
                AccountSid,         // target SID
                &PrivilegeString,   // privileges
                1                   // privilege count
                );
    }
    else {
        return LsaRemoveAccountRights(
                PolicyHandle,       // open policy handle
                AccountSid,         // target SID
                FALSE,              // do not disable all rights
                &PrivilegeString,   // privileges
                1                   // privilege count
                );
    }
}

void
InitLsaString(
    PLSA_UNICODE_STRING LsaString,
    LPWSTR String
    )
{
    DWORD StringLength;

    if(String == NULL) {
        LsaString->Buffer = NULL;
        LsaString->Length = 0;
        LsaString->MaximumLength = 0;
        return;
    }

    StringLength = lstrlenW(String);
    LsaString->Buffer = String;
    LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
    LsaString->MaximumLength=(USHORT)(StringLength+1) * sizeof(WCHAR);
}

NTSTATUS
OpenPolicy(
    LPWSTR ServerName,
    DWORD DesiredAccess,
    PLSA_HANDLE PolicyHandle
    )
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    LSA_UNICODE_STRING ServerString;
    PLSA_UNICODE_STRING Server;

    //
    // Always initialize the object attributes to all zeroes.
    //
    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

    if (ServerName != NULL) {
        //
        // Make a LSA_UNICODE_STRING out of the LPWSTR passed in
        //
        InitLsaString(&ServerString, ServerName);
        Server = &ServerString;
    } else {
        Server = NULL;
    }

    //
    // Attempt to open the policy.
    //
    return LsaOpenPolicy(
                Server,
                &ObjectAttributes,
                DesiredAccess,
                PolicyHandle
                );
}

void
DisplayNtStatus(
    LPSTR szAPI,
    NTSTATUS Status
    )
{
    //
    // Convert the NTSTATUS to Winerror. Then call DisplayWinError().
    //
    DisplayWinError(szAPI, LsaNtStatusToWinError(Status));
}

void
DisplayWinError(
    LPSTR szAPI,
    DWORD WinError
    )
{
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    //
    // TODO: Get this fprintf out of here!
    //
    fprintf(stderr,"%s error!\n", szAPI);

    if(dwBufferLength=FormatMessageA(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        WinError,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPSTR) &MessageBuffer,
                        0,
                        NULL
                        ))
    {
        DWORD dwBytesWritten; // unused

        //
        // Output message string on stderr.
        //
        WriteFile(
            GetStdHandle(STD_ERROR_HANDLE),
            MessageBuffer,
            dwBufferLength,
            &dwBytesWritten,
            NULL
            );

        //
        // Free the buffer allocated by the system.
        //
        LocalFree(MessageBuffer);
    }
}
