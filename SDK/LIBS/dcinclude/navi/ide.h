/* KallistiOS 1.2.0

   navi/ide.h
   (c)2002 Dan Potter
   
   $Id: ide.h,v 1.1 2002/05/05 22:17:51 bardtx Exp $
*/

#ifndef __NAVI_IDE_H
#define __NAVI_IDE_H

#include <arch/types.h>

/* Read n sectors from the hard disk using PIO mode */
int ide_read(uint32 linear,uint32 numsects, void *bufptr);

/* Write n sectors to the hard disk using PIO mode */
int ide_write(uint32 linear,uint32 numsects, void *bufptr);

/* Get the available space */
uint32 ide_num_sectors();

/* Init/Shutdown the device */
int ide_init();
void ide_shutdown();


#endif	/* __NAVI_IDE_H */

