#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   pickle Application                    **#
#**            Copyright(c) Microsoft Corp. 1992-1996       **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags:G3=Gz)
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

all : pickltc

# Make the picklt client
pickltc : pickltc.exe
pickltc.exe : pickltc.obj picklt_c.obj
    $(link) $(linkdebug) $(conflags) -out:pickltc.exe \
      pickltc.obj picklt_c.obj \
      rpcrt4.lib $(conlibsdll)

# client main program
pickltc.obj : pickltc.c picklt.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# client stub
picklt_c.obj : picklt_c.c picklt.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stub and header file from the IDL file
picklt.h picklt_c.c: picklt.idl picklt.acf
    midl -oldnames -no_cpp -ms_ext picklt.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del picklt_c.c
    -del picklt.h

