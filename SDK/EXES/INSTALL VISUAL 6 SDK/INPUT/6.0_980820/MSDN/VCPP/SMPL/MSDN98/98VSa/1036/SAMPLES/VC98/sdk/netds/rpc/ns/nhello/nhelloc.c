/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                       nhello Example

    FILE:       nhelloc.c

    USAGE:      nhelloc  -s string
                         -n name_service_entry_name
                         -t name_syntax_type

    PURPOSE:    Client side of RPC distributed application

    FUNCTIONS:  main() - binds to server and calls remote procedure

    COMMENTS:

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "nhello.h"    // header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates\n\
the use of the name service. For more information about these\n\
RPC API functions, see the RPC programming guide and reference.\n\n"

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -s string\n");
    fprintf(stderr, " -n name_service_entry_name\n");
    fprintf(stderr, " -t name_syntax_type\n");
    exit(1);
}

void _CRTAPI1 main(int argc, char **argv)
{
    unsigned char * pszString     = "hello, world";
    unsigned char * pszEntryName  = "/.:/nhello_sample";
    unsigned char * pszStrBinding = NULL;
    RPC_NS_HANDLE hnsHello;
    RPC_BINDING_HANDLE hHello;
    unsigned long fNameSyntaxType = RPC_C_NS_SYNTAX_DEFAULT;
    RPC_STATUS status;
    unsigned long ulCode;
    short fSuccess = 0;
    short fContinue = 1;
    short i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'n':
                pszEntryName = argv[++i];
                break;
            case 't':
                fNameSyntaxType = (unsigned int) atoi(argv[++i]);
                break;
            case 's':
                pszString = argv[++i];
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    RpcTryExcept {
        status = RpcNsBindingImportBegin(fNameSyntaxType,
                                         pszEntryName,
                                         nhello_v1_0_c_ifspec,
                                         NULL,
                                         &hnsHello);
        printf("RpcNsBindingImportBegin returned 0x%x\n", status);
    }
    RpcExcept(1) {
        ulCode = RpcExceptionCode();
        printf("RPC Runtime raised exception 0x%x\n", ulCode);
        fContinue = 0;
    }
    RpcEndExcept

    if ( status != RPC_S_OK )
        fContinue = 0;

    /* The loop is present because the name service may contain "stale" */
    /* and unusable binding handlers.  This is part of the DCE design.  */
    while( fContinue )
    {
        status = RpcNsBindingImportNext(hnsHello,
                                        &hHello);
        printf("RpcNsBindingImportNext returned 0x%x\n", status);

        if ( (status == RPC_S_NO_MORE_BINDINGS) ||
             (status == RPC_S_NAME_SERVICE_UNAVAILABLE ) )
            break;

        if (status != RPC_S_OK)
            continue;

        RpcBindingToStringBinding( hHello, &pszStrBinding );
        printf("StringBinding: %s\n", pszStrBinding );
        RpcStringFree(&pszStrBinding);

        RpcTryExcept {
            printf("Calling remote procedure HelloProc with string %s\n",
                   pszString);
            HelloProc(hHello, pszString);
            fContinue = 0;
            fSuccess = 1;
        }
        RpcExcept(1) {
            ulCode = RpcExceptionCode();
            printf("RPC Runtime raised exception 0x%x\n", ulCode);
            status = RpcBindingFree(&hHello);
            printf("RpcBindingFree returned 0x%x\n", status);
            fContinue = 1;
        }
        RpcEndExcept

    }

    RpcTryExcept {
        status = RpcNsBindingImportDone(&hnsHello);
        printf("RpcNsBindingImportDone returned 0x%x\n", status);
    }
    RpcExcept(1) {
        ulCode = RpcExceptionCode();
        printf("RPC Runtime raised exception 0x%x\n", ulCode);
        fContinue = 0;
    }
    RpcEndExcept

    if ( fSuccess )
    {
        RpcTryExcept {
            Shutdown(hHello);  // Shutdown is a remote procedure
        }
        RpcExcept(1) {
            ulCode = RpcExceptionCode();
            printf("RPC runtime raised exception 0x%x\n", ulCode);
        }
        RpcEndExcept

        status = RpcBindingFree(&hHello);
        printf("RpcBindingFree returned 0x%x\n", status);
    }

    exit(0);

}  // end main()


/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

/* end file nhelloc.c */
