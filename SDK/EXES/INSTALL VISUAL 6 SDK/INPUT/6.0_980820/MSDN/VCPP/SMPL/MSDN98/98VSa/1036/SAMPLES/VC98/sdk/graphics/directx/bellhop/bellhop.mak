# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=bellhop - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to bellhop - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bellhop - Win32 Release" && "$(CFG)" !=\
 "bellhop - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "bellhop.mak" CFG="bellhop - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bellhop - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "bellhop - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "bellhop - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "bellhop - Win32 Release"

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

ALL : "$(OUTDIR)\bellhop.exe"

CLEAN : 
	-@erase "$(INTDIR)\bellhop.obj"
	-@erase "$(INTDIR)\bellhop.res"
	-@erase "$(INTDIR)\cgrptree.obj"
	-@erase "$(INTDIR)\ConnSet.obj"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(OUTDIR)\bellhop.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /YX /c
CPP_PROJ=/nologo /ML /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /Fp"$(INTDIR)/bellhop.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/bellhop.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bellhop.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib advapi32.lib uuid.lib ole32.lib dplayx.lib GDI32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=comctl32.lib kernel32.lib user32.lib advapi32.lib uuid.lib\
 ole32.lib dplayx.lib GDI32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/bellhop.pdb" /machine:I386 /out:"$(OUTDIR)/bellhop.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bellhop.obj" \
	"$(INTDIR)\bellhop.res" \
	"$(INTDIR)\cgrptree.obj" \
	"$(INTDIR)\ConnSet.obj" \
	"$(INTDIR)\dialog.obj"

"$(OUTDIR)\bellhop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"

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

ALL : "$(OUTDIR)\bellhop.exe" "$(OUTDIR)\bellhop.bsc"

CLEAN : 
	-@erase "$(INTDIR)\bellhop.obj"
	-@erase "$(INTDIR)\bellhop.res"
	-@erase "$(INTDIR)\bellhop.sbr"
	-@erase "$(INTDIR)\cgrptree.obj"
	-@erase "$(INTDIR)\cgrptree.sbr"
	-@erase "$(INTDIR)\ConnSet.obj"
	-@erase "$(INTDIR)\ConnSet.sbr"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dialog.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\bellhop.bsc"
	-@erase "$(OUTDIR)\bellhop.exe"
	-@erase "$(OUTDIR)\bellhop.ilk"
	-@erase "$(OUTDIR)\bellhop.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /FR"$(INTDIR)/" /Fp"$(INTDIR)/bellhop.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/bellhop.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bellhop.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bellhop.sbr" \
	"$(INTDIR)\cgrptree.sbr" \
	"$(INTDIR)\ConnSet.sbr" \
	"$(INTDIR)\dialog.sbr"

"$(OUTDIR)\bellhop.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib advapi32.lib uuid.lib ole32.lib dplayx.lib GDI32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=comctl32.lib kernel32.lib user32.lib advapi32.lib uuid.lib\
 ole32.lib dplayx.lib GDI32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/bellhop.pdb" /debug /machine:I386 /out:"$(OUTDIR)/bellhop.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bellhop.obj" \
	"$(INTDIR)\bellhop.res" \
	"$(INTDIR)\cgrptree.obj" \
	"$(INTDIR)\ConnSet.obj" \
	"$(INTDIR)\dialog.obj"

"$(OUTDIR)\bellhop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

################################################################################
# Begin Target

# Name "bellhop - Win32 Release"
# Name "bellhop - Win32 Debug"

!IF  "$(CFG)" == "bellhop - Win32 Release"

!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\bellhop.rc
DEP_RSC_BELLH=\
	".\Bellhop.ico"\
	".\ClosDoor.ico"\
	".\friends.ico"\
	".\group1.ico"\
	".\icon1.ico"\
	".\OpenDoor.ico"\
	

"$(INTDIR)\bellhop.res" : $(SOURCE) $(DEP_RSC_BELLH) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bellhop.cpp
DEP_CPP_BELLHO=\
	".\bellhop.h"\
	".\cgrptree.h"\
	{$(INCLUDE)}"\dplobby.h"\
	

!IF  "$(CFG)" == "bellhop - Win32 Release"


"$(INTDIR)\bellhop.obj" : $(SOURCE) $(DEP_CPP_BELLHO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"


"$(INTDIR)\bellhop.obj" : $(SOURCE) $(DEP_CPP_BELLHO) "$(INTDIR)"

"$(INTDIR)\bellhop.sbr" : $(SOURCE) $(DEP_CPP_BELLHO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialog.cpp
DEP_CPP_DIALO=\
	".\bellhop.h"\
	".\cgrptree.h"\
	{$(INCLUDE)}"\dplobby.h"\
	

!IF  "$(CFG)" == "bellhop - Win32 Release"


"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"


"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"

"$(INTDIR)\dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cgrptree.cpp
DEP_CPP_CGRPT=\
	".\cgrptree.h"\
	{$(INCLUDE)}"\dplobby.h"\
	

!IF  "$(CFG)" == "bellhop - Win32 Release"


"$(INTDIR)\cgrptree.obj" : $(SOURCE) $(DEP_CPP_CGRPT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"


"$(INTDIR)\cgrptree.obj" : $(SOURCE) $(DEP_CPP_CGRPT) "$(INTDIR)"

"$(INTDIR)\cgrptree.sbr" : $(SOURCE) $(DEP_CPP_CGRPT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConnSet.cpp
DEP_CPP_CONNS=\
	".\bellhop.h"\
	".\cgrptree.h"\
	{$(INCLUDE)}"\dplobby.h"\
	

!IF  "$(CFG)" == "bellhop - Win32 Release"


"$(INTDIR)\ConnSet.obj" : $(SOURCE) $(DEP_CPP_CONNS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "bellhop - Win32 Debug"


"$(INTDIR)\ConnSet.obj" : $(SOURCE) $(DEP_CPP_CONNS) "$(INTDIR)"

"$(INTDIR)\ConnSet.sbr" : $(SOURCE) $(DEP_CPP_CONNS) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
