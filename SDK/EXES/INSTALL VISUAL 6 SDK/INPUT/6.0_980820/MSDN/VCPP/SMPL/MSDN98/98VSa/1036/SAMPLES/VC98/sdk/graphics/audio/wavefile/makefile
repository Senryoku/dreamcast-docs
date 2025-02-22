# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

TARGETNAME =    wavef32

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = $(TARGETNAME).sym
!endif

all: $(TARGETNAME).dll $(SYM)

OBJS=		wavefile.obj factory1.obj extra.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

wavefile.res: wavefile.rc wavefile.rcv
    $(rc) -r -DWIN32 $(OTHERRCOPTS) wavefile.rc


# Update the object files if necessary

factory1.obj: factory1.c wavefile.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) factory1.c

extra.obj: extra.c extra.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) extra.c

wavefile.obj: wavefile.c wavefile.h muldiv32.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) wavefile.c


# Update the executable file if necessary, and if so, add the resource back in.

$(TARGETNAME).dll $(TARGETNAME).map:  $(OBJS) wavefile.res
    $(implib) -out:$(@B).lib -def:$(TARGETNAME).def $(OBJS)
    $(link) $(linkdebug) $(dlllflags) -out:$*.dll  \
           $(@B).exp $(OBJS) wavefile.res $(olelibsdll) vfw32.lib winmm.lib \
               -map:$*.map
    
$(TARGETNAME).sym:	$*.map
	mapsym $*.map

clean:
    @if exist $(TARGETNAME).dll del $(TARGETNAME).dll
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
