all: dbg rtl

clean:
    nmake /f "D3DSiberian.mak" CFG="D3DSiberian - Win32 (WCE SH4) Release" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" CLEAN
    nmake /f "D3DSiberian.mak" CFG="D3DSiberian - Win32 (WCE SH4) Debug" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" CLEAN

dbg:
    nmake /f "D3DSiberian.mak" CFG="D3DSiberian - Win32 (WCE SH4) Debug" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" 

rtl:
    nmake /f "D3DSiberian.mak" CFG="D3DSiberian - Win32 (WCE SH4) Release" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" 
