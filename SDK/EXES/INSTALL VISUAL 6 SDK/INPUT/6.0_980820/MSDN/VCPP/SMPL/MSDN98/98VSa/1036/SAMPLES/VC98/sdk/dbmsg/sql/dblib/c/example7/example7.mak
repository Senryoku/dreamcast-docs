# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (MIPS) Console Application" 0x0503
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603
# TARGTYPE "Win32 (PPC) Console Application" 0x0703

!IF "$(CFG)" == ""
CFG=Example7 - Win32 (PPC) Debug
!MESSAGE No configuration specified.  Defaulting to Example7 - Win32 (PPC)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Example7 - Win32 Release" && "$(CFG)" !=\
 "Example7 - Win32 Debug" && "$(CFG)" != "Example7 - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "Example7 - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "Example7 - Win32 MIPS Debug" && "$(CFG)" != "Example7 - Win32 MIPS Release" &&\
 "$(CFG)" != "Example7 - Win32 (PPC) Release" && "$(CFG)" !=\
 "Example7 - Win32 (PPC) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Example7.mak" CFG="Example7 - Win32 (PPC) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Example7 - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "Example7 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Example7 - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Example7 - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "Example7 - Win32 MIPS Debug" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Example7 - Win32 MIPS Release" (based on\
 "Win32 (MIPS) Console Application")
!MESSAGE "Example7 - Win32 (PPC) Release" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE "Example7 - Win32 (PPC) Debug" (based on\
 "Win32 (PPC) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Example7 - Win32 Release"

!IF  "$(CFG)" == "Example7 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Release\Example7.exe"
	-@erase ".\Release\Example7.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Example7.pdb" /machine:I386 /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example7 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Example7.exe"
	-@erase ".\Debug\Example7.obj"
	-@erase ".\Debug\Example7.ilk"
	-@erase ".\Debug\Example7.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Example7.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Example7"
# PROP BASE Intermediate_Dir "Example7"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Example7"
# PROP Intermediate_Dir "Example7"
# PROP Target_Dir ""
OUTDIR=.\Example7
INTDIR=.\Example7

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example7\vc40.pdb"
	-@erase ".\Example7\Example7.exe"
	-@erase ".\Example7\Example7.obj"
	-@erase ".\Example7\Example7.ilk"
	-@erase ".\Example7\Example7.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Example7/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Example7.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Example0"
# PROP BASE Intermediate_Dir "Example0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Example0"
# PROP Intermediate_Dir "Example0"
# PROP Target_Dir ""
OUTDIR=.\Example0
INTDIR=.\Example0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example0\Example7.exe"
	-@erase ".\Example0\Example7.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Example0/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Example7.pdb" /machine:ALPHA /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Example1"
# PROP BASE Intermediate_Dir "Example1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Example1"
# PROP Intermediate_Dir "Example1"
# PROP Target_Dir ""
OUTDIR=.\Example1
INTDIR=.\Example1

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example1\vc40.pdb"
	-@erase ".\Example1\Example7.exe"
	-@erase ".\Example1\Example7.obj"
	-@erase ".\Example1\Example7.ilk"
	-@erase ".\Example1\Example7.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /QMOb2000 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Example1/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:MIPS
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Example7.pdb" /debug /machine:MIPS\
 /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Example2"
# PROP BASE Intermediate_Dir "Example2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Example2"
# PROP Intermediate_Dir "Example2"
# PROP Target_Dir ""
OUTDIR=.\Example2
INTDIR=.\Example2

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example2\Example7.exe"
	-@erase ".\Example2\Example7.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /QMOb2000 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /QMOb2000 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Example2/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:MIPS
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:MIPS
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Example7.pdb" /machine:MIPS /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=

!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Example3"
# PROP BASE Intermediate_Dir "Example3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Example3"
# PROP Intermediate_Dir "Example3"
# PROP Target_Dir ""
OUTDIR=.\Example3
INTDIR=.\Example3

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example3\Example7.exe"
	-@erase ".\Example3\Example7.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Example3/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Example7.pdb" /machine:PPC /out:"$(OUTDIR)/Example7.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Example4"
# PROP BASE Intermediate_Dir "Example4"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Example4"
# PROP Intermediate_Dir "Example4"
# PROP Target_Dir ""
OUTDIR=.\Example4
INTDIR=.\Example4

ALL : "$(OUTDIR)\Example7.exe"

CLEAN : 
	-@erase ".\Example4\vc40.pdb"
	-@erase ".\Example4\Example7.exe"
	-@erase ".\Example4\Example7.obj"
	-@erase ".\Example4\Example7.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/Example7.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Example4/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Example7.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:PPC
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:PPC
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console\
 /pdb:"$(OUTDIR)/Example7.pdb" /debug /machine:PPC /out:"$(OUTDIR)/Example7.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/Example7.obj"

"$(OUTDIR)\Example7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "Example7 - Win32 Release"
# Name "Example7 - Win32 Debug"
# Name "Example7 - Win32 (ALPHA) Debug"
# Name "Example7 - Win32 (ALPHA) Release"
# Name "Example7 - Win32 MIPS Debug"
# Name "Example7 - Win32 MIPS Release"
# Name "Example7 - Win32 (PPC) Release"
# Name "Example7 - Win32 (PPC) Debug"

!IF  "$(CFG)" == "Example7 - Win32 Release"

!ELSEIF  "$(CFG)" == "Example7 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Debug"

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Release"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Release"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Example7.c

!IF  "$(CFG)" == "Example7 - Win32 Release"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 Debug"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Debug"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (ALPHA) Release"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Debug"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 MIPS Release"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Release"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Example7 - Win32 (PPC) Debug"

"$(INTDIR)\Example7.obj" : $(SOURCE) $(DEP_CPP_EXAMP) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
