/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994, 1995
                      picklp Example

    FILE:       picklpc.c

    USAGE:      picklpc  -f filename  (file to write to/read from)
                         -d           (serialization direction: decode)
                         -e           (serialization direction: encode)
                         -i           (incremental serialization on)

    PURPOSE:    The only side of RPC application

    FUNCTIONS:  main() - serializes data to or from a file

    COMMENTS:   Data procedure serialization is demonstrated here

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "picklp.h"    // header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates\n\
the use of the [encode,decode] attributes. For more information\n\
about the attributes and RPC API functions, see the RPC programming\n\
guide and reference.\n\n"

/*  Used for incremental style only. */

void __RPC_USER PicAlloc( void * pState, char ** ppBuf, unsigned int * pCount);
void __RPC_USER PicWrite( void * pState, char *  pBuf,  unsigned int Count);
void __RPC_USER PicRead ( void * pState, char ** pBuf,  unsigned int * pCount);

typedef struct PickleControlBlock
{
    unsigned char *         pMemBuffer;
    unsigned char *         pBufferStart;
    unsigned long           LastSize;
} PickleControlBlock;

static PickleControlBlock                 UserState;
static PickleControlBlock * pUserState = &UserState;

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -d\n");
    fprintf(stderr, " -e\n");
    fprintf(stderr, " -ffilename\n");
    fprintf(stderr, " -i \n");
    exit(1);
}

void DumpData(
    char * pszComment,
    char * pszText,
    OBJECT1 * pObject1,
    OBJECT2 * pObject2 )
{
    int i;

    printf( "\n%s\n", pszComment );
    printf( "\tString\n\t\t%s\n", pszText );

    printf( "\tObject1");
    for (i=0; i < ARR_SIZE; i++)
        {
        if ( (i % 5) == 0 )
            printf( "\n\t\t");
        printf( "%08xl  ", pObject1->al[i] );
        }
    printf( "\n\t\t%x\n", pObject1->s );

    printf( "\tObject2");
    printf( "\n\t\t%x", pObject2->sSize );
    for (i=0; i < ARR_SIZE; i++)
        {
        if ( (i % 10) == 0 )
            printf( "\n\t\t");
        printf( "%04x  ", pObject2->as[i] );
        }
    printf( "\n" );
}

void WriteDataToFile(
    char *          pszFileName,
    char *          pbBuffer,
    unsigned long   ulSizeToWrite )
{
    FILE *      pFile;
    size_t      Count;

    if ( pszFileName ) {

        pFile = fopen( pszFileName, "w+b" );
        if ( pFile == NULL ) {
            printf("Cannot open the file for writing\n");
            exit(1);
            }

        Count = sizeof(long);
        if ( fwrite( &ulSizeToWrite, sizeof(byte), Count, pFile) != Count ) {
            printf("Cannot write1 to the file\n");
            exit(1);
            }

        Count = (size_t) ulSizeToWrite;
        if ( fwrite( pbBuffer, sizeof(byte), Count, pFile) != Count ) {
            printf("Cannot write2 to the file\n");
            exit(1);
            }

        if ( fclose( pFile ) != 0) {
            printf("Failed to close the file\n");
            exit(1);
            }
        }
}

void ReadDataFromFile(
    char *          pszFileName,
    char *          pbBuffer,
    unsigned long   ulBufferSize )
{
    FILE *          pFile;
    size_t          Count;
    unsigned long   ulWrittenSize;


    if ( pszFileName ) {

        pFile = fopen( pszFileName, "r+b" );
        if ( pFile == NULL ) {
            printf("Cannot open the file for reading\n");
            exit(1);
            }

        Count = sizeof(long);
        if ( fread( &ulWrittenSize, sizeof(byte), Count, pFile) != Count ) {
            printf("Cannot read1 from the file\n");
            exit(1);
            }

        Count = (size_t)ulWrittenSize;
        if ( fread( pbBuffer, sizeof(byte), Count, pFile) != Count ) {
            printf("Cannot read2 from the file\n");
            exit(1);
            }

        if ( fclose( pFile ) != 0) {
            printf("Failed to close the file\n");
            exit(1);
            }
        }
}

void _CRTAPI1 main(int argc, char **argv)
{
    RPC_STATUS status;

    unsigned char * pbPicklingBuffer = NULL;

    char * pszStyle      = NULL;
    char * pszFileName   = "pickle.dat";
    int i;
    int fEncode = 1;
    int fFixedStyle = 1;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'd':
                fEncode = 0;
                break;
            case 'e':
                fEncode = 1;
                break;
            case 'i':
                fFixedStyle = 0;
                break;
            case 'f':
                pszFileName = argv[i] + 2;
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

    /* Fixed buffer style: the buffer should be big enough.  */
    /* Please note that the buffer has to be aligned at 8.   */

    pbPicklingBuffer = (unsigned char *)
            midl_user_allocate( BUFSIZE * sizeof(unsigned char));

    if ( pbPicklingBuffer == NULL ) {
        printf("Cannot allocate the pickling buffer\n");
        exit(1);
        }
    else
        memset( pbPicklingBuffer, 0xdd, BUFSIZE );

    /*
        Set the pickling handle that will be used for data serialization.
        The global ImplicitPicHandle is used, but it has to be set up.
    */

    if ( fEncode ) {

        unsigned char * pszNameId;
        OBJECT1         Object1;
        OBJECT2   *     pObject2;
        unsigned long   ulEncodedSize = 0;

        printf("\nEncoding run: use -d for decoding\n\n");

        if ( fFixedStyle ) {

            printf("Creating a fixed buffer encoding handle\n");
            status = MesEncodeFixedBufferHandleCreate( pbPicklingBuffer,
                                                       BUFSIZE,
                                                       & ulEncodedSize,
                                                       & ImplicitPicHandle );
            printf("MesEncodeFixedBufferHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }
        else {

            pUserState->LastSize = 0;
            pUserState->pMemBuffer = (char *)pbPicklingBuffer;
            pUserState->pBufferStart = (char *)pbPicklingBuffer;

            printf("Creating an incremental encoding handle\n");
            status = MesEncodeIncrementalHandleCreate( pUserState,
                                                       PicAlloc,
                                                       PicWrite,
                                                       & ImplicitPicHandle );
            printf("MesEncodeIncrementalHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }

        /* Creating objects to manipulate */

        pszNameId = "Procedure pickling sample";

        for (i = 0; i < ARR_SIZE; i++)
            Object1.al[i] = 0x37370000 + i;
        Object1.s = 0x4646;

        pObject2 = midl_user_allocate( sizeof(OBJECT2) + ARR_SIZE*sizeof(short) );
        if (pObject2 == NULL ) {
            printf("Out of memory for Object2\n");
            exit(1);
        }

        pObject2->sSize = ARR_SIZE;
        for (i = 0; i < ARR_SIZE; i++)
            pObject2->as[i] = 0x7700 + i;

        DumpData( "Data to be encoded", pszNameId, &Object1, pObject2 );

        printf("\nEncoding all the arguments to the buffer\n\n");
        ProcPickle( pszNameId, & Object1, pObject2 );

        printf("Writing the data to the file: %s\n", pszFileName);
        WriteDataToFile( pszFileName,
                         pbPicklingBuffer,
                         fFixedStyle  ? ulEncodedSize
                                      : pUserState->LastSize);

        midl_user_free( pObject2 );
    }
    else {
        char            acNameBuffer[50];
        OBJECT1         Object1;
        OBJECT2   *     pObject2;

        printf("\nDecoding run: use -e for encoding\n\n");

        printf("Reading the data from the file: %s\n\n", pszFileName );
        ReadDataFromFile( pszFileName,
                          pbPicklingBuffer,
                          BUFSIZE );

        if ( fFixedStyle ) {

            printf("Creating a decoding handle\n");
            status = MesDecodeBufferHandleCreate( pbPicklingBuffer,
                                                  BUFSIZE,
                                                  & ImplicitPicHandle );
            printf("MesDecodeFixedBufferHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }
        else {

            pUserState->LastSize = 0;
            pUserState->pMemBuffer = (char *)pbPicklingBuffer;
            pUserState->pBufferStart = (char *)pbPicklingBuffer;

            printf("Creating an incremental decoding handle\n");
            status = MesDecodeIncrementalHandleCreate( pUserState,
                                                       PicRead,
                                                       & ImplicitPicHandle );
            printf("MesDecodeIncrementalHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }


        /* Creating objects to manipulate */

        pObject2 = midl_user_allocate( sizeof(OBJECT2) + ARR_SIZE*sizeof(short));
        if (pObject2 == NULL ) {
            printf("Out of memory for Object2\n");
            exit(1);
        }

        printf("\nDecoding all the arguments from the buffer\n");
        ProcPickle( acNameBuffer, & Object1, pObject2 );

        DumpData( "Decoded data", acNameBuffer, &Object1, pObject2 );

        midl_user_free( pObject2 );
    }

    printf("\nData serialization done.\n");

    midl_user_free( pbPicklingBuffer );

    printf("\nFreeing the serialization handle.\n");
    status = MesHandleFree( ImplicitPicHandle );
    printf("MesHandleFree returned 0x%x\n", status);

    exit(0);

}  // end main()

/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

/* A pickling buffer has to be aligned at 8.
   malloc() doesn't guarantee that, so some gimmick has to be done.
*/

#define ALIGN_TO8( p)   (char *)((unsigned long)((char *)p + 7) & ~7)

void __RPC_FAR * __RPC_USER  MIDL_user_allocate(size_t s)
{
    unsigned char * pcAllocated;
    unsigned char * pcUserPtr;

    pcAllocated = (unsigned char *) malloc( s + 15 );
    pcUserPtr =  ALIGN_TO8( pcAllocated );
    if ( pcUserPtr == pcAllocated )
        pcUserPtr = pcAllocated + 8;

    *(pcUserPtr - 1) = pcUserPtr - pcAllocated;

    return( pcUserPtr );
}

void __RPC_USER  MIDL_user_free(void __RPC_FAR *f)
{
    unsigned char * pcAllocated;
    unsigned char * pcUserPtr;

    pcUserPtr = (unsigned char *) f;
    pcAllocated = pcUserPtr - *(pcUserPtr - 1);

    free( pcAllocated );
}

/*********************************************************************/
/*                 Incremental style helper routines                 */
/*********************************************************************/

void  __RPC_USER
PicAlloc(
    void *          pState,
    char **         ppBuf,
    unsigned int  * pCount )
{
    /* This routines "allocates" the next part from the preallocated
       buffer. It could call midl_user_allocate, too.
    */

    PickleControlBlock * pPic = (PickleControlBlock *)pState;

    if ( (pPic->pMemBuffer - pPic->pBufferStart) + *pCount <= BUFSIZE )
        *ppBuf = (char *)pPic->pMemBuffer;
    else {
        printf(" Buffer too small\n");
        exit(1);
    }
}

void __RPC_USER
PicWrite(
    void *          pState,
    char *          pBuf,
    unsigned int    Count )
{
    /* This routine just marks how much of the preallocated buffer is used.
    */

    PickleControlBlock * pPic = (PickleControlBlock *)pState;


    if ( pPic->pMemBuffer != pBuf ) {
        printf(" Buffer poiner corrupted\n");
        exit(1);
    }
    pPic->pMemBuffer += Count;
    pPic->LastSize += Count;
}

void __RPC_USER
PicRead(
    void *          pState,
    char **         ppBuf,
    unsigned int  * pCount )
{
    /* This routine returns another portion of the preread buffer. */

    PickleControlBlock * pPic = (PickleControlBlock *)pState;

    *ppBuf = (char *)pPic->pMemBuffer;
    pPic->pMemBuffer += *pCount;
}

/* end picklpc.c */


