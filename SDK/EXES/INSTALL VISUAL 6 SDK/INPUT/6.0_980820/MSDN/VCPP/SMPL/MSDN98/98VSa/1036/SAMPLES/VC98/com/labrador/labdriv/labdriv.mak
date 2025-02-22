# Microsoft Developer Studio Generated NMAKE File, Based on labdriv.dsp
!IF "$(CFG)" == ""
CFG=labdriv - Win32 Release
!MESSAGE No configuration specified. Defaulting to labdriv - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "labdriv - Win32 Release" && "$(CFG)" !=\
 "labdriv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "labdriv.mak" CFG="labdriv - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "labdriv - Win32 Release" (based on\
 "Win32 (x86) Win32 Console Application")
!MESSAGE "labdriv - Win32 Debug" (based on\
 "Win32 (x86) Win32 Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "labdriv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\labdriv.exe" "$(OUTDIR)\labdriv.pch"

!ELSE 

ALL : "$(OUTDIR)\labdriv.exe" "$(OUTDIR)\labdriv.pch"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\labdriv.obj"
	-@erase "$(INTDIR)\labdriv.pch"
	-@erase "$(INTDIR)\prelabdr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\labdriv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)\labdriv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labdriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\labdriv.pdb" /machine:I386 /out:"$(OUTDIR)\labdriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\labdriv.obj" \
	"$(INTDIR)\prelabdr.obj"

"$(OUTDIR)\labdriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "labdriv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\labdriv.exe" "$(OUTDIR)\labdriv.pch"

!ELSE 

ALL : "$(OUTDIR)\labdriv.exe" "$(OUTDIR)\labdriv.pch"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\labdriv.obj"
	-@erase "$(INTDIR)\labdriv.pch"
	-@erase "$(INTDIR)\prelabdr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\labdriv.exe"
	-@erase "$(OUTDIR)\labdriv.ilk"
	-@erase "$(OUTDIR)\labdriv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)\labdriv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labdriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\labdriv.pdb" /debug /machine:I386 /out:"$(OUTDIR)\labdriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\labdriv.obj" \
	"$(INTDIR)\prelabdr.obj"

"$(OUTDIR)\labdriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "labdriv - Win32 Release" || "$(CFG)" ==\
 "labdriv - Win32 Debug"
SOURCE=.\labdriv.cpp

!IF  "$(CFG)" == "labdriv - Win32 Release"

DEP_CPP_LABDR=\
	"..\labrador.tlb"\
	".\prelabdr.h"\
	
CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)\labdriv.pch" /YX"prelabdr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\labdriv.obj" : $(SOURCE) $(DEP_CPP_LABDR) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "labdriv - Win32 Debug"

DEP_CPP_LABDR=\
	".\prelabdr.h"\
	
CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)\labdriv.pch" /YX"prelabdr.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\labdriv.obj" : $(SOURCE) $(DEP_CPP_LABDR) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\prelabdr.cpp

!IF  "$(CFG)" == "labdriv - Win32 Release"

DEP_CPP_PRELA=\
	"..\labrador.tlb"\
	".\prelabdr.h"\
	
CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)\labdriv.pch" /Yc"prelabdr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\prelabdr.obj"	"$(INTDIR)\labdriv.pch" : $(SOURCE) $(DEP_CPP_PRELA)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "labdriv - Win32 Debug"

DEP_CPP_PRELA=\
	".\prelabdr.h"\
	
CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)\labdriv.pch" /Yc"prelabdr.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prelabdr.obj"	"$(INTDIR)\labdriv.pch" : $(SOURCE) $(DEP_CPP_PRELA)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\prelabdr.h

!ENDIF 

