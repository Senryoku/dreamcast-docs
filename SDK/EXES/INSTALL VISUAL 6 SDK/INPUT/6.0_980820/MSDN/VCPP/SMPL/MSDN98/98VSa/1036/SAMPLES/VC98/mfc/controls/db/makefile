# makefile - Handy makefile for command-line use
#
# Usage:
#   nmake [options] [all|clean]
#
# Options:
#   DEBUG=0     Build retail version
#   DEBUG=1     Build debug version (default)

# This is a part of the Microsoft Foundation Classes C++ library.
# Copyright (C) 1992-1997 Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Microsoft Foundation Classes Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Microsoft Foundation Classes product.

!ifndef DEBUG
DEBUG=1
!endif

!if "$(DEBUG)" == "1"
all:
	nmake -f DB.mak CFG="DB - Win32 Debug"
clean:
	@-if exist Debug\*.* echo y | erase Debug\*.*
!else
all:
	nmake -f DB.mak CFG="DB - Win32 Release"
clean:
	@-if exist Release\*.* echo y | erase Release\*.*
!endif
