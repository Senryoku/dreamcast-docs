!include <ntwin32.mak>

proj=netmsg

all: $(proj).exe

$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvars) $(cdebug) $(proj).c

$(proj).exe: $(proj).obj
    $(link) $(ldebug) -out:$(proj).exe $(proj).obj
