/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:07:30 1998
 */
/* Compiler settings for usrdef.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include "usrdef.h"

#define TYPE_FORMAT_STRING_SIZE   73                                
#define PROC_FORMAT_STRING_SIZE   17                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: usrdef, ver. 1.0,
   GUID={0x85D7D1C0,0xCA47,0x1067,{0xB3,0x1E,0x00,0xDD,0x01,0x06,0x62,0xDA}} */

handle_t hUnused;


static const RPC_CLIENT_INTERFACE usrdef___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x85D7D1C0,0xCA47,0x1067,{0xB3,0x1E,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE usrdef_ClientIfHandle = (RPC_IF_HANDLE)& usrdef___RpcClientInterface;

extern const MIDL_STUB_DESC usrdef_StubDesc;

static RPC_BINDING_HANDLE usrdef__MIDL_AutoBindHandle;


void UsrdefProc( 
    /* [in] */ DATA_HANDLE_TYPE hBinding,
    /* [string][in] */ unsigned char __RPC_FAR *pszString)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&usrdef_StubDesc,
                          0);
        
        
        _Handle = DATA_HANDLE_TYPE_bind(hBinding);;
        
        if(_Handle == 0)
            {
            RpcRaiseException(RPC_S_INVALID_BINDING);
            }
        
        _StubMsg.BufferLength = 0U + 13U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)hBinding,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pszString,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[70] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)hBinding,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pszString,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[70] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        
        if(_Handle)
            {
            DATA_HANDLE_TYPE_unbind(hBinding,_Handle);
            }
        }
    RpcEndFinally
    
}


void Shutdown( 
    /* [in] */ DATA_HANDLE_TYPE hBinding)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&usrdef_StubDesc,
                          1);
        
        
        _Handle = DATA_HANDLE_TYPE_bind(hBinding);;
        
        if(_Handle == 0)
            {
            RpcRaiseException(RPC_S_INVALID_BINDING);
            }
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)hBinding,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)hBinding,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        
        if(_Handle)
            {
            DATA_HANDLE_TYPE_unbind(hBinding,_Handle);
            }
        }
    RpcEndFinally
    
}


static const MIDL_STUB_DESC usrdef_StubDesc = 
    {
    (void __RPC_FAR *)& usrdef___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &hUnused,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x303006e, /* MIDL Version 3.3.110 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  4 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0x44 ),	/* Type Offset=68 */
/*  8 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 12 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/* 14 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/*  6 */	NdrFcShort( 0x14 ),	/* 20 */
/*  8 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 12 */	NdrFcShort( 0x0 ),	/* 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 18 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 20 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 22 */	NdrFcShort( 0x4 ),	/* 4 */
/* 24 */	NdrFcShort( 0x4 ),	/* 4 */
/* 26 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 28 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 30 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 32 */	NdrFcShort( 0x8 ),	/* 8 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
/* 36 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 38 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 42 */	NdrFcShort( 0xc ),	/* 12 */
/* 44 */	NdrFcShort( 0xc ),	/* 12 */
/* 46 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 48 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 50 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 52 */	NdrFcShort( 0x10 ),	/* 16 */
/* 54 */	NdrFcShort( 0x10 ),	/* 16 */
/* 56 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 58 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 60 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 62 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 64 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 66 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 68 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 70 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */

			0x0
        }
    };
