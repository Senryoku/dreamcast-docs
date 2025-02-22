/* ps2-load-ip

   commands.h

   Copyright (c)2000-2001 Andrew Kieschnick
   Copyright (c)2002 Dan Potter
   License: GPL

   $Id: commands.h,v 1.1 2002/10/30 05:34:12 bardtx Exp $
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

extern unsigned int tool_ip;
extern unsigned char tool_mac[6];
extern unsigned short tool_port;

#include "packet.h"

void cmd_reboot(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_execute(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_loadbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_partbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_donebin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_sendbinq(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_sendbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_version(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_retval(ip_header_t * ip, udp_header_t * udp, command_t * command);
void cmd_init();

#endif
