# Microsoft Developer Studio Project File - Name="mc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=mc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mc.mak" CFG="mc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mc - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "mc - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "mc - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "mc.exe"
# PROP Bsc_Name "mc.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "mc - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "mc.exe"
# PROP Bsc_Name "mc.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "mc - Win32 Release"
# Name "mc - Win32 Debug"

!IF  "$(CFG)" == "mc - Win32 Release"

!ELSEIF  "$(CFG)" == "mc - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Group "Source Files" 
# Begin Source File

SOURCE=.\MC.C
# End Source File
# Begin Source File

SOURCE=.\MCLEX.C
# End Source File
# Begin Source File

SOURCE=.\MCOUT.C
# End Source File
# Begin Source File

SOURCE=.\MCPARSE.C
# End Source File
# Begin Source File

SOURCE=.\MCUTIL.C
# End Source File
# End Group 
# Begin Group "Header Files" 
# Begin Source File

SOURCE=.\MC.H
# End Source File
# End Group 
# Begin Group "Resource Files" 
# End Group 
# End Target
# End Project
