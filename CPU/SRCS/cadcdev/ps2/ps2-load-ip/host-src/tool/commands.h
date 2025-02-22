/* ps2-load-ip

   commands.h

   Copyright (c)2000-2001 Andrew Kieschnick
   License: GPL

   $Id: commands.h,v 1.1 2002/10/30 06:22:50 bardtx Exp $
*/

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int address __attribute__ ((packed));
  unsigned int size __attribute__ ((packed));
  unsigned char data[1] __attribute__ ((packed));
} command_t;

#define CMD_EXECUTE  "EXEC" /* execute */
#define CMD_LOADBIN  "LBIN" /* begin receiving binary */
#define CMD_PARTBIN  "PBIN" /* part of a binary */
#define CMD_DONEBIN  "DBIN" /* end receiving binary */
#define CMD_SENDBIN  "SBIN" /* send a binary */
#define CMD_SENDBINQ "SBIQ" /* send a binary, quiet */
#define CMD_VERSION  "VERS" /* send version info */

#define CMD_RETVAL   "RETV" /* return value */

#define CMD_REBOOT   "RBOT"  /* reboot */

#define COMMAND_LEN  12

#endif
