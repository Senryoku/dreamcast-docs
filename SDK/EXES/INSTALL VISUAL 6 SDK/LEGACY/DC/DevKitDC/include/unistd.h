/* KallistiOS 1.1.6

   unistd.h
   (c)2000-2001 Dan Potter

   $Id: unistd.h,v 1.3 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __UNISTD_H
#define __UNISTD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stddef.h>
#include <arch/types.h>

#define true (1)
#define false (0)

void usleep(unsigned long usec);

__END_DECLS

#endif	/* __UNISTD_H */

