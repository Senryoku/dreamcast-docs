/* KallistiOS 1.1.6

   stdlib.h
   (c)2001-2002 Dan Potter

   $Id: stdlib.h,v 1.3 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __STDLIB_H
#define __STDLIB_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <unistd.h>

/* To be compatible with newer ANSI C */
#include <malloc.h>

/* To make future porting efforts simpler */
#define __P(x) x

/* random number functions */
#define RAND_MAX 0x7fffffff

typedef struct
{
	int quot;	/* quotient */
	int rem;	/* remainder */
} div_t;

typedef struct
{
	long quot;	/* quotient */
	long rem;	/* remainder */
} ldiv_t;

void     abort(void);
int      abs(int);
int      atexit(void (*)(void));
double   atof(const char *);
int      atoi(const char *);
long     atol(const char *);
void    *bsearch(const void *, const void *, size_t, size_t,
		int (*)(const void *, const void *));
void    *calloc(size_t, size_t);
div_t    div(int, int);
void     exit(int);
char    *getenv(const char *);
long     labs(long);
ldiv_t   ldiv(long, long);
int      mblen(const char *, size_t);
size_t   mbstowcs(wchar_t *, const char *, size_t);
int      mbtowc(wchar_t *, const char *, size_t);
char    *mktemp(char *);
int      mkstemp(char *);
int      putenv(char *);
void     qsort(void *, size_t, size_t, int (*)(const void *,
		const void *));
int      rand(void);
int      rand_r(unsigned int *);
long     random(void);
void    *realloc(void *, size_t);
char    *realpath(const char *, char *);
void     srand(unsigned int);
double   strtod(const char *, char **);
long     strtol(const char *, char **, int);
unsigned long  strtoul(const char *, char **, int);
int      system(const char *);
size_t   wcstombs(char *, const wchar_t *, size_t);
int      wctomb(char *, wchar_t);

__END_DECLS

#endif	/* __STDLIB_H */

