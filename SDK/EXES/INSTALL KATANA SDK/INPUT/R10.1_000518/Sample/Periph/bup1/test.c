/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Backup Sample #1

	1999.5.31
*/

#include <shinobi.h>
#include "backup.h"
#include <setjmp.h>

Sint32 gFrameCount;

void DispBackupRAMInfo(Sint32 x, Sint32 y, Sint32 drive);

void njUserInit(void)
{
	gFrameCount = 0;

    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 10000, 0, -1, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x0000C060);

	BupInit();
}

Sint32 njUserMain(void)
{
	Sint32 drive;
	Sint32 x, y;

	njPrintC(NJM_LOCATION(2, 2), "BACKUP SAMPLE #1");
	njPrintH(NJM_LOCATION(30, 2), gFrameCount++, 8);

	x = 2;
	y = 2;
	for (drive = 0; drive < 8; drive++) {
		y = drive * 2 + 6;
		DispBackupRAMInfo(x, y, drive);
	}

	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	BupExit();
	sbExitSystem();
	syBtExit();
}


/*===============================================================*/
/* メモリーカードの状態を表示する                                */
/* 接続されていなければ「---」を、フォーマットされていなければ   */
/* 「UNFORMAT」を、フォーマットされている場合は空き容量と最大    */
/* 容量を表示します。                                            */
/* Display information of memory card.                           */
/* If memory card is not connected, "---" is displayed.          */
/* If memory card is not formatted, "UNFORMAT", is displayed.    */
/* if memory card is formatted, free volume and maximum volume   */
/* is displayed.                                                 */
/*===============================================================*/

void DispBackupRAMInfo(Sint32 x, Sint32 y, Sint32 drive)
{
	const BACKUPINFO* binfo;
	BUS_DISKINFO* diskinfo;

	binfo = BupGetInfo(drive);
	diskinfo = &binfo->DiskInfo;

	njPrint(NJM_LOCATION(x, y), "MEMORY CARD #%d",drive);

	if (binfo->Ready) {
		if (binfo->IsFormat) {
			njPrint(NJM_LOCATION(x + 15, y), "%04d/%04d BLOCKS",
				diskinfo->free_user_blocks,
				diskinfo->total_user_blocks);
		} else {
			njPrint(NJM_LOCATION(x + 15, y), "UNFORMAT        ");
		}
	} else {
		if (binfo->Operation == BUD_OP_MOUNT) {
			njPrint(NJM_LOCATION(x + 15, y), "CHECKING...     ");
		} else {
			njPrint(NJM_LOCATION(x + 15, y), "----------------");
		}
	}
}

