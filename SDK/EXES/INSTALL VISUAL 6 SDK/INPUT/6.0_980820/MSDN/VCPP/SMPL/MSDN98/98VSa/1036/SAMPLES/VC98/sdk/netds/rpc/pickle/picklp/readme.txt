PICKLEP


The PICKLEP program demonstrates data procedure serialization. The program 
demonstrates a fixed buffer style pickling and an incremental style pickling 
depending on the switches being used.

The implicit_handle primitive is used as the pickling handle.

With default switches, the program encodes data to a file. To decode data 
from the file, use -d switch.

FILES
=====

The directory samples\rpc\pickle\picklp contains the following files for
building the distributed application PICKLP:

File          Description

README.TXT    Readme file for the PICKLE sample
PICKLP.IDL    Interface definition language file
PICKLP.ACF    Attribute configuration file
PICKLPC.C     Client main program
MAKEFILE      Nmake file to build for Windows NT or Windows 95
MAKEFILE.DOS  Nmake file to build for MS-DOS

-----------------------------------------------------------------------
BUILDING THE (CLIENT) FOR MICROSOFT WINDOWS NT OR WINDOWS 95
-----------------------------------------------------------------------

The following environment variables should already be set for you:

  set CPU=i386
  set INCLUDE=%SDKROOT%\h
  set LIB=%SDKROOT%\lib
  set PATH=%SDKROOT%\system32;%SDKROOT%\bin

where %SDKROOT% is the root directory for the 32-bit Windows SDK.

For mips,  set CPU=mips
For alpha, set CPU=alpha

Build the sample distributed application:

  nmake cleanall
  nmake

This builds the executable programs picklpc.exe.
There is no server side in this sample as the notion of server does not
apply to pickling.

------------------------------------------
BUILDING THE CLIENT APPLICATION FOR MS-DOS
------------------------------------------

After installing the Microsoft Visual C/C++ version 1.50 development
environment and the 16-bit RPC SDK on a Windows NT or Windows 95
computer, you can build the sample client application from Windows NT
or Windows 95:

  nmake -f makefile.dos cleanall
  nmake -f makefile.dos

This builds the client application callc.exe.

You may also execute the Microsoft Visual C/C++ compiler under MS-DOS.
This requires a two-step build process.

  Step One: Compile the .IDL files under Windows NT or Windows 95:

     nmake -a -f makefile.dos picklp.h

  Step Two: Compile the C sources (stub and application) under MS-DOS:

     nmake -f makefile.dos

-----------------------
RUNNING THE APPLICATION
-----------------------

The default setting for this application is to encode data to 
pickle.dat file. Enter:

  picklpc

To decode data that has been encoded, enter:

  picklpc -d

Several other command line switches are available to change settings for 
this program. For a listing of the switches available from the client 
program, enter:

  picklpc -?
