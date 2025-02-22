/* KallistiOS 1.2.0

   mm.c
   (c)2000-2001 Dan Potter
*/

/* Defines a simple UNIX-style memory pool system. Since the Dreamcast has
   multiple distinct areas of memory used for different things, we'll
   want to keep seperate pools. Mainly this will be used with the PowerVR
   and the system RAM, since the SPU has its own program (that can do its
   own memory management). */


/* Note: right now we only support system RAM */


#include <arch/types.h>
#include <arch/arch.h>

CVSID("$Id: mm.c,v 1.3 2003/05/23 02:19:54 bardtx Exp $");

/* The end of the program is always marked by the '_end' symbol. So we'll
   longword-align that and add a little for safety. sbrk() calls will
   move up from there. */
extern unsigned long end;
static void *sbrk_base;

/* MM-wide initialization */
int mm_init() {
	int base = (int)(&end);
	base = (base/4)*4 + 4;		/* longword align */
	sbrk_base = (void*)base;
	
	return 0;
}

/* Simple sbrk function */
void* sbrk(unsigned long increment) {
	void *base = sbrk_base;

	if (increment & 3)
		increment = (increment + 4) & ~3;
	sbrk_base += increment;

	if ( ((uint32)sbrk_base) >= (0x8d000000 - 65536) ) {
		dbglog(DBG_DEAD, "Requested sbrk_base 0x%lx, was 0x%lx, diff %lu\n",
			sbrk_base, (uint32)base, increment);
		panic("out of memory; about to run over kernel stack");
	}
	
	return base;
}


