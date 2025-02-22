/*************************************************************/
/**                                                         **/
/**                 Microsoft RPC Examples                  **/
/**                 OSF DCE Sample Application              **/
/**           Copyright(c) Microsoft Corp. 1992-1996        **/
/**                                                         **/
/*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "msg.h"        /* header file generated by M/IDL compiler */

#if defined(__RPC_WIN32__) || defined(__RPC_DOS__)

/*
 On MS platforms we must include the dceport.h header file
 which maps OSF DCE style APIs to MS style APIs.
*/

#include "dceport.h"

#else
#include <pthread.h>
#endif

#ifndef _CRTAPI1
#define _CRTAPI1
#endif

void Usage()
{
  printf("Usage : client -n <server_name>\n");
  printf("               -t <transport>   - optional, default ncacn_ip_tcp\n");
  printf("               -e <endpoint>    - optional, should match server\n");
  printf("               -s <message>     - optional, send a different message\n");
  printf("               -x               - use to stop the server\n");
  exit(1);
}

int _CRTAPI1
main(int argc, char *argv[])
{
    unsigned32 status;
    unsigned char * pszProtocolSequence = (unsigned char *)"ncacn_ip_tcp";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = NULL;
    unsigned char * pszStringBinding    = NULL;
    unsigned char * pszMessage          = (unsigned char *)"Hello World";
    int fStopServer = 0;
    int i;

    printf ("Microsoft RPC Demo - OSF DCE Interop Message Client\n");

    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'n':  /* network address */
                pszNetworkAddress = (unsigned char *)argv[++i];
                break;
            case 't':  /* protocol sequence */
                pszProtocolSequence = (unsigned char *)argv[++i];
                break;
            case 'e':  /* network endpoint */
                pszEndpoint = (unsigned char *)argv[++i];
                break;
            case 's':  /* update message */
                pszMessage = (unsigned char *)argv[++i];
                break;
            case 'x':  /* stop the server */
                fStopServer = 1;
                break;
            case 'h':
            case '?':
            default:
                Usage();
            }
        }
        else
            Usage();
    }

    rpc_string_binding_compose(0,   /* no object uuid */
                               pszProtocolSequence,
                               pszNetworkAddress,
                               pszEndpoint,
                               0,  /* no options */
                               &pszStringBinding,
                               &status);
    if (status) {
        printf("rpc_string_binding_compose returned 0x%x\n", status);
        return(status);
    }

    rpc_binding_from_string_binding(pszStringBinding,
                                    &interop_binding_handle,
                                    &status);
    if (status) {
        printf("rpc_binding_from_string_binding returned 0x%x\n", status);
        return(status);
    }

    rpc_string_free(&pszStringBinding,&status);
    if (status) {
        printf("rpc_string_free returned 0x%x\n", status);
        return(status);
    }

    TRY {
       ClientMessage(pszMessage);

       printf("Message sent okay\n");
       if (fStopServer)
           {
           ShutdownServer();
           printf("Server shutdown\n");
           }
    }
    CATCH_ALL {
       printf("RPC raised exception 0x%x\n", THIS_CATCH);
    }
    ENDTRY

    rpc_binding_free(&interop_binding_handle, &status);
    if (status) {
        printf("rpc_binding_free returned 0x%x\n", status);
        return(status);
    }

    return(0);
}

