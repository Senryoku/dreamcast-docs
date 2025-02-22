/* KallistiOS 1.1.6

   os/abi/svcmpx.h - adding/removing services
   (C) 2000-2001 Jordan DeLong

   $Id: svcmpx.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

 */

#ifndef __OS_ABI_SVCMPX_H
#define __OS_ABI_SVCMPX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>

typedef struct {
	service_abi_t	hdr;	/* header info */

	void *	(*get_handler)(const char *svcname);	/* here for completeness: progs use lib_open */
	int	(*add_handler)(const char *name, void *svc_struct);
	int	(*remove_handler)(const char *name);
} abi_svcmpx_t;

__END_DECLS

#endif	/* __OS_ABI_SVCMPX_H */

