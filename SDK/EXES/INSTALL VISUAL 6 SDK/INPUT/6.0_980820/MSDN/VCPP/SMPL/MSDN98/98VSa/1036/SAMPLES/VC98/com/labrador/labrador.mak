# Microsoft Developer Studio Generated NMAKE File, Based on labrador.dsp
!IF "$(CFG)" == ""
CFG=Labrador - Win32 EXE Release
!MESSAGE No configuration specified. Defaulting to Labrador - Win32 EXE Release.
!ENDIF 

!IF "$(CFG)" != "Labrador - Win32 EXE Release" && "$(CFG)" != "Labrador - Win32 EXE Debug" && "$(CFG)" != "Labrador - Win32 EXE Unicode Release" && "$(CFG)" != "Labrador - Win32 EXE Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "labrador.mak" CFG="Labrador - Win32 EXE Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Labrador - Win32 EXE Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Labrador - Win32 EXE Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Labrador - Win32 EXE Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Labrador - Win32 EXE Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Labrador - Win32 EXE Release"

OUTDIR=.\RelEXE
INTDIR=.\RelEXE
# Begin Custom Macros
OutDir=.\RelEXE
# End Custom Macros

ALL : ".\Labrador.tlb" ".\Labrador.h" ".\Lab_p.c" ".\Lab_i.c" ".\dlldata.c" "$(OUTDIR)\labrador.exe" ".\RelEXE\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LabObj.obj"
	-@erase "$(INTDIR)\Labrador.obj"
	-@erase "$(INTDIR)\labrador.pch"
	-@erase "$(INTDIR)\Labrador.res"
	-@erase "$(INTDIR)\prelab.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\labrador.exe"
	-@erase ".\RelEXE\regsvr32.trg"
	-@erase "dlldata.c"
	-@erase "Lab_i.c"
	-@erase "Lab_p.c"
	-@erase "Labrador.h"
	-@erase "Labrador.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yu"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Labrador.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labrador.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\labrador.pdb" /machine:I386 /out:"$(OUTDIR)\labrador.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LabObj.obj" \
	"$(INTDIR)\Labrador.obj" \
	"$(INTDIR)\prelab.obj" \
	"$(INTDIR)\Labrador.res"

"$(OUTDIR)\labrador.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\RelEXE
TargetPath=.\RelEXE\labrador.exe
InputPath=.\RelEXE\labrador.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Debug"

OUTDIR=.\DebEXE
INTDIR=.\DebEXE
# Begin Custom Macros
OutDir=.\DebEXE
# End Custom Macros

ALL : ".\Labrador.tlb" ".\Labrador.h" ".\Lab_p.c" ".\Lab_i.c" ".\dlldata.c" "$(OUTDIR)\labrador.exe" ".\DebEXE\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LabObj.obj"
	-@erase "$(INTDIR)\Labrador.obj"
	-@erase "$(INTDIR)\labrador.pch"
	-@erase "$(INTDIR)\Labrador.res"
	-@erase "$(INTDIR)\prelab.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\labrador.exe"
	-@erase "$(OUTDIR)\labrador.ilk"
	-@erase "$(OUTDIR)\labrador.pdb"
	-@erase ".\DebEXE\regsvr32.trg"
	-@erase "dlldata.c"
	-@erase "Lab_i.c"
	-@erase "Lab_p.c"
	-@erase "Labrador.h"
	-@erase "Labrador.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yu"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Labrador.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labrador.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\labrador.pdb" /debug /machine:I386 /out:"$(OUTDIR)\labrador.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LabObj.obj" \
	"$(INTDIR)\Labrador.obj" \
	"$(INTDIR)\prelab.obj" \
	"$(INTDIR)\Labrador.res"

"$(OUTDIR)\labrador.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebEXE
TargetPath=.\DebEXE\labrador.exe
InputPath=.\DebEXE\labrador.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Release"

OUTDIR=.\RelEXEU
INTDIR=.\RelEXEU
# Begin Custom Macros
OutDir=.\RelEXEU
# End Custom Macros

ALL : ".\Labrador.tlb" ".\Labrador.h" ".\Lab_p.c" ".\Lab_i.c" ".\dlldata.c" "$(OUTDIR)\labrador.exe" ".\RelEXEU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LabObj.obj"
	-@erase "$(INTDIR)\Labrador.obj"
	-@erase "$(INTDIR)\labrador.pch"
	-@erase "$(INTDIR)\Labrador.res"
	-@erase "$(INTDIR)\prelab.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\labrador.exe"
	-@erase ".\RelEXEU\regsvr32.trg"
	-@erase "dlldata.c"
	-@erase "Lab_i.c"
	-@erase "Lab_p.c"
	-@erase "Labrador.h"
	-@erase "Labrador.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yu"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Labrador.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labrador.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\labrador.pdb" /machine:I386 /out:"$(OUTDIR)\labrador.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LabObj.obj" \
	"$(INTDIR)\Labrador.obj" \
	"$(INTDIR)\prelab.obj" \
	"$(INTDIR)\Labrador.res"

"$(OUTDIR)\labrador.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\RelEXEU
TargetPath=.\RelEXEU\labrador.exe
InputPath=.\RelEXEU\labrador.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Debug"

OUTDIR=.\DebEXEU
INTDIR=.\DebEXEU
# Begin Custom Macros
OutDir=.\DebEXEU
# End Custom Macros

ALL : ".\Labrador.tlb" ".\Labrador.h" ".\Lab_p.c" ".\Lab_i.c" ".\dlldata.c" "$(OUTDIR)\labrador.exe" ".\DebEXEU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LabObj.obj"
	-@erase "$(INTDIR)\Labrador.obj"
	-@erase "$(INTDIR)\labrador.pch"
	-@erase "$(INTDIR)\Labrador.res"
	-@erase "$(INTDIR)\prelab.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\labrador.exe"
	-@erase "$(OUTDIR)\labrador.ilk"
	-@erase "$(OUTDIR)\labrador.pdb"
	-@erase ".\DebEXEU\regsvr32.trg"
	-@erase "dlldata.c"
	-@erase "Lab_i.c"
	-@erase "Lab_p.c"
	-@erase "Labrador.h"
	-@erase "Labrador.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yu"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Labrador.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labrador.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\labrador.pdb" /debug /machine:I386 /out:"$(OUTDIR)\labrador.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LabObj.obj" \
	"$(INTDIR)\Labrador.obj" \
	"$(INTDIR)\prelab.obj" \
	"$(INTDIR)\Labrador.res"

"$(OUTDIR)\labrador.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebEXEU
TargetPath=.\DebEXEU\labrador.exe
InputPath=.\DebEXEU\labrador.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("labrador.dep")
!INCLUDE "labrador.dep"
!ELSE 
!MESSAGE Warning: cannot find "labrador.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Labrador - Win32 EXE Release" || "$(CFG)" == "Labrador - Win32 EXE Debug" || "$(CFG)" == "Labrador - Win32 EXE Unicode Release" || "$(CFG)" == "Labrador - Win32 EXE Unicode Debug"
SOURCE=.\LabObj.cpp

"$(INTDIR)\LabObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\labrador.pch" ".\Labrador.h"


SOURCE=.\Labrador.cpp

"$(INTDIR)\Labrador.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\labrador.pch" ".\Lab_i.c" ".\Labrador.h"


SOURCE=.\Labrador.idl

!IF  "$(CFG)" == "Labrador - Win32 EXE Release"

InputPath=.\Labrador.idl

".\Labrador.h"	".\Labrador.tlb"	".\Lab_i.c"	".\Lab_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Labrador.h /iid Lab_i.c /proxy Lab_p.c Labrador.idl
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Debug"

InputPath=.\Labrador.idl

".\Labrador.h"	".\Labrador.tlb"	".\Lab_i.c"	".\Lab_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Labrador.h /iid Lab_i.c /proxy Lab_p.c Labrador.idl
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Release"

InputPath=.\Labrador.idl

".\Labrador.h"	".\Labrador.tlb"	".\Lab_i.c"	".\Lab_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Labrador.h /iid Lab_i.c /proxy Lab_p.c Labrador.idl
<< 
	

!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Debug"

InputPath=.\Labrador.idl

".\Labrador.h"	".\Labrador.tlb"	".\Lab_i.c"	".\Lab_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h Labrador.h /iid Lab_i.c /proxy Lab_p.c Labrador.idl
<< 
	

!ENDIF 

SOURCE=.\Labrador.rc

"$(INTDIR)\Labrador.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\prelab.cpp

!IF  "$(CFG)" == "Labrador - Win32 EXE Release"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yc"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prelab.obj"	"$(INTDIR)\labrador.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yc"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prelab.obj"	"$(INTDIR)\labrador.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yc"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prelab.obj"	"$(INTDIR)\labrador.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Labrador - Win32 EXE Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\labrador.pch" /Yc"prelab.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prelab.obj"	"$(INTDIR)\labrador.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

