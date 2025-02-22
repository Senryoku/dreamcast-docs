/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                    Discriminated Union Example

    FILE:       dunionc.c

    USAGE:      dunionc  -n network_address
                         -p protocol_sequence
                         -e endpoint
                         -o options
                         -d discriminant
                         -v union_value

    PURPOSE:    Client side of RPC distributed application

    FUNCTIONS:  main() - binds to server and calls remote procedure

    COMMENTS:   This distributed application illustrates discriminated
                union.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dunion.h"    // header file generated by MIDL compiler


void Usage(char * pszProgramName)
{
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -n network_address\n");
    fprintf(stderr, " -e endpoint\n");
    fprintf(stderr, " -o options\n");
    fprintf(stderr, " -d discriminant\n");
    fprintf(stderr, " -v union_value\n");
    exit(1);
}

void DisplayUnionValue(DISCRIM_UNION_PARAM_TYPE *up,
                       short                    sDiscrim)
{
    printf("sDiscrim = %d, data = ", sDiscrim);
    switch(sDiscrim) {
    case 0:
        printf("short: %d\n", up->sVal);
        break;
    case 1:
        printf("float: %f\n", up->fVal);
        break;
    case 2:
        printf("char: %c\n", up->chVal);
        break;
    default:
        printf("invalid\n");
        break;
    }
}

void _CRTAPI1 main(int argc, char **argv)
{
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = "\\pipe\\dunion";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    int i;

    short sDiscrim = 0;
    DISCRIM_UNION_PARAM_TYPE  up = {1};
    DISCRIM_UNION_STRUCT_TYPE us = {0, 1};

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'n':  // network address
                pszNetworkAddress = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'o':
                pszOptions = argv[++i];
                break;
            case 'd':
                sDiscrim = (short) atoi(argv[++i]);
                if ((sDiscrim > 3) || (sDiscrim < 0))
                    sDiscrim = 0;
                us.sDiscrim = sDiscrim;
                break;
            case 'v':
                switch(sDiscrim) {
                case 0:
                    up.sVal =  (short) atoi(argv[++i]);
                    us.u.sVal = up.sVal;
                    break;
                case 1:
                    up.fVal =  (float) atof(argv[++i]);
                    us.u.fVal = up.fVal;
                    break;
                case 2:
                    up.chVal = *(argv[++i]);
                    us.u.chVal = up.chVal;
                    break;
                default:
                    break;
                }
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

    /* Use a convenience function to concatenate the elements of  */
    /* the string binding into the proper sequence.               */
    status = RpcStringBindingCompose(pszUuid,
                                     pszProtocolSequence,
                                     pszNetworkAddress,
                                     pszEndpoint,
                                     pszOptions,
                                     &pszStringBinding);
    printf("RpcStringBindingCompose returned 0x%x\n", status);
    printf("pszStringBinding = %s\n", pszStringBinding);
    if (status) {
        exit(status);
    }

    /* Set the binding handle that will be used to bind to the server. */
    status = RpcBindingFromStringBinding(pszStringBinding,
                                         &hDiscrim);
    printf("RpcBindingFromStringBinding returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf("Calling the remote procedure 'UnionParamProc'\n");

    RpcTryExcept {
        DisplayUnionValue(&up, sDiscrim);  // display value before call
        UnionParamProc(&up, sDiscrim);     // call the remote procedure

        UnionStructProc(&us);              // call the remote procedure
        DisplayUnionValue(&up, sDiscrim);  // display value after call

        Shutdown();                    // Shut down the server
    }
    RpcExcept(1) {
        printf("Runtime reported exception %ld\n", RpcExceptionCode() );
    }
    RpcEndExcept

    /*  The remote procedure call is complete.  Free the binding handle */
    status = RpcBindingFree(&hDiscrim);
    printf("RpcBindingFree returned 0x%x\n", status);
    if (status) {
        exit(status);
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

/* end file dunionc.c */
