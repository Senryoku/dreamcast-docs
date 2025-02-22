// Predefined symbols and macros -*- C++ -*-

// Copyright (C) 1997, 1998, 1999, 2000, 2001 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#ifndef _CPP_CPPCONFIG
#define _CPP_CPPCONFIG 1

// Pick up any OS-specific definitions.
#include <bits/os_defines.h>
// And any CPU-specific definitions.
#include <bits/limits.h>

// The current version of the C++ library in compressed ISO date format.
#define __GLIBCPP__ 20011220

// This is necessary until GCC supports separate template
// compilation.  
#define _GLIBCPP_NO_TEMPLATE_EXPORT 1

// This is a hack around not having either pre-compiled headers or
// export compilation. If defined, the io, string, and valarray
// headers will include all the necessary bits. If not defined, the
// implementation optimizes the headers for the most commonly-used
// types. For the io library, this means that larger, out-of-line
// member functions are only declared, and definitions are not parsed
// by the compiler, but instead instantiated into the library binary.
#define _GLIBCPP_FULLY_COMPLIANT_HEADERS 1

// Define this to permit user-level control of the expansion of string
// buffers (via a fn pointer), see basic_string.* for more.
//#define _GLIBCPP_ALLOC_CONTROL

// To enable older, ARM-style iostreams and other anachronisms use this.
//#define _GLIBCPP_DEPRECATED 1

// Use corrected code from the committee library group's issues list.
#define _GLIBCPP_RESOLVE_LIB_DEFECTS 1

// Enable concept checking code from the boost libraries.
//#define _GLIBCPP_CONCEPT_CHECKS 1

// Map gthr.h abstraction to that required for STL.  Do not key off of
// __GTHREADS at this point since we haven't seen the correct symbol
// yet, instead setup so that include/bits/stl_threads.h will know to
// include gthr.h instead of any other type of thread support.  Note:
// that gthr.h may well map to gthr-single.h which is a correct way to
// express no threads support in gcc.  As a user, do not define
// _NOTHREADS without consideration of the consequences (e.g. it is an
// internal ABI change).
#define __STL_GTHREADS
#define __STL_THREADS
#define __STL_VOLATILE volatile

// This is also a user hook, but via -f[no-]exceptions, not direct #defines.
#ifdef __EXCEPTIONS
# define __STL_USE_EXCEPTIONS
# define __STL_TRY try
# define __STL_CATCH_ALL catch(...)
# define __STL_THROW(x) throw x
# define __STL_RETHROW throw
# define __STL_NOTHROW throw()
# define __STL_UNWIND(action) catch(...) { action; throw; }
#else
# define __STL_TRY 
# define __STL_CATCH_ALL if (false)
# define __STL_THROW(x) 
# define __STL_RETHROW 
# define __STL_NOTHROW 
# define __STL_UNWIND(action) 
#endif

// Default to the typically high-speed, pool-based allocator (as
// libstdc++-v2) instead of the malloc-based allocator (libstdc++-v3
// snapshots).  See libstdc++-v3/docs/html/17_intro/howto.html for
// details on why you don't want to override this setting.  Ensure
// that threads are properly configured on your platform before
// assigning blame to the STL container-memory allocator.  After doing
// so, please report any possible issues to libstdc++@gcc.gnu.org .
// Do not blindly #define __USE_MALLOC here or on the command line.

// The remainder of the prewritten config is mostly automatic; all the
// user hooks are listed above.

// XXX 
// Only used in the SGI rope extensions; this is from stl_config.h and
// should be cleaned up.
# define __stl_assert(expr)

/** @namespace std
 *  @brief Everything defined by the ISO C++ Standard is within namespace std.
 */

// End of prewritten config; the discovered settings follow.
/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if you have a working `mmap' system call.  */
/* #undef _GLIBCPP_HAVE_MMAP */

// Define if GCC supports weak symbols.
/* #undef _GLIBCPP_SUPPORTS_WEAK */

// Define if gthr-default.h exists (meaning that threading support is enabled).
/* #undef _GLIBCPP_HAVE_GTHR_DEFAULT */

// Include I/O support for 'long long' and 'unsigned long long'.
/* #undef _GLIBCPP_USE_LONG_LONG */

// Define if C99 features such as lldiv_t, llabs, lldiv should be exposed.
/* #undef _GLIBCPP_USE_C99 */

// Include support for shadow headers, ie --enable-cshadow-headers.
/* #undef _GLIBCPP_USE_SHADOW_HEADERS */

// Define if code specialized for wchar_t should be used.
/* #undef _GLIBCPP_USE_WCHAR_T */

// Define if using setrlimit to limit memory usage during 'make check'.
/* #undef _GLIBCPP_MEM_LIMITS */

// Define if mbstate_t exists in wchar.h.
/* #undef _GLIBCPP_HAVE_MBSTATE_T */

// Define if you have the modff function.
/* #undef _GLIBCPP_HAVE_MODFF */

// Define if you have the modfl function.
/* #undef _GLIBCPP_HAVE_MODFL */

// Define if the compiler/host combination has __builtin_abs
/* #undef _GLIBCPP_HAVE___BUILTIN_ABS */

// Define if the compiler/host combination has __builtin_labs
/* #undef _GLIBCPP_HAVE___BUILTIN_LABS */

// Define if the compiler/host combination has __builtin_cos
/* #undef _GLIBCPP_HAVE___BUILTIN_COS */

// Define if the compiler/host combination has __builtin_cosf
/* #undef _GLIBCPP_HAVE___BUILTIN_COSF */

// Define if the compiler/host combination has __builtin_cosl
/* #undef _GLIBCPP_HAVE___BUILTIN_COSL */

// Define if the compiler/host combination has __builtin_fabs
/* #undef _GLIBCPP_HAVE___BUILTIN_FABS */

// Define if the compiler/host combination has __builtin_fabsf
/* #undef _GLIBCPP_HAVE___BUILTIN_FABSF */

// Define if the compiler/host combination has __builtin_fabsl
/* #undef _GLIBCPP_HAVE___BUILTIN_FABSL */

// Define if the compiler/host combination has __builtin_sin
/* #undef _GLIBCPP_HAVE___BUILTIN_SIN */

// Define if the compiler/host combination has __builtin_sinf
/* #undef _GLIBCPP_HAVE___BUILTIN_SINF */

// Define if the compiler/host combination has __builtin_sinl
/* #undef _GLIBCPP_HAVE___BUILTIN_SINL */

// Define if the compiler/host combination has __builtin_fsqrt
/* #undef _GLIBCPP_HAVE___BUILTIN_FSQRT */

// Define if the compiler/host combination has __builtin_sqrtf
/* #undef _GLIBCPP_HAVE___BUILTIN_SQRTF */

// Define if the compiler/host combination has __builtin_sqrtl
/* #undef _GLIBCPP_HAVE___BUILTIN_SQRTL */

// Define if LC_MESSAGES is available in <locale.h>.
/* #undef _GLIBCPP_HAVE_LC_MESSAGES */

/* Define if you have the _acosf function.  */
/* #undef _GLIBCPP_HAVE__ACOSF */

/* Define if you have the _acosl function.  */
/* #undef _GLIBCPP_HAVE__ACOSL */

/* Define if you have the _asinf function.  */
/* #undef _GLIBCPP_HAVE__ASINF */

/* Define if you have the _asinl function.  */
/* #undef _GLIBCPP_HAVE__ASINL */

/* Define if you have the _atan2f function.  */
/* #undef _GLIBCPP_HAVE__ATAN2F */

/* Define if you have the _atan2l function.  */
/* #undef _GLIBCPP_HAVE__ATAN2L */

/* Define if you have the _atanf function.  */
/* #undef _GLIBCPP_HAVE__ATANF */

/* Define if you have the _atanl function.  */
/* #undef _GLIBCPP_HAVE__ATANL */

/* Define if you have the _ceilf function.  */
/* #undef _GLIBCPP_HAVE__CEILF */

/* Define if you have the _ceill function.  */
/* #undef _GLIBCPP_HAVE__CEILL */

/* Define if you have the _copysign function.  */
/* #undef _GLIBCPP_HAVE__COPYSIGN */

/* Define if you have the _copysignl function.  */
/* #undef _GLIBCPP_HAVE__COPYSIGNL */

/* Define if you have the _cosf function.  */
/* #undef _GLIBCPP_HAVE__COSF */

/* Define if you have the _coshf function.  */
/* #undef _GLIBCPP_HAVE__COSHF */

/* Define if you have the _coshl function.  */
/* #undef _GLIBCPP_HAVE__COSHL */

/* Define if you have the _cosl function.  */
/* #undef _GLIBCPP_HAVE__COSL */

/* Define if you have the _expl function.  */
/* #undef _GLIBCPP_HAVE__EXPL */

/* Define if you have the _fabsf function.  */
/* #undef _GLIBCPP_HAVE__FABSF */

/* Define if you have the _fabsl function.  */
/* #undef _GLIBCPP_HAVE__FABSL */

/* Define if you have the _finite function.  */
/* #undef _GLIBCPP_HAVE__FINITE */

/* Define if you have the _finitef function.  */
/* #undef _GLIBCPP_HAVE__FINITEF */

/* Define if you have the _finitel function.  */
/* #undef _GLIBCPP_HAVE__FINITEL */

/* Define if you have the _floorf function.  */
/* #undef _GLIBCPP_HAVE__FLOORF */

/* Define if you have the _floorl function.  */
/* #undef _GLIBCPP_HAVE__FLOORL */

/* Define if you have the _fmodf function.  */
/* #undef _GLIBCPP_HAVE__FMODF */

/* Define if you have the _fmodl function.  */
/* #undef _GLIBCPP_HAVE__FMODL */

/* Define if you have the _fpclass function.  */
/* #undef _GLIBCPP_HAVE__FPCLASS */

/* Define if you have the _frexpf function.  */
/* #undef _GLIBCPP_HAVE__FREXPF */

/* Define if you have the _frexpl function.  */
/* #undef _GLIBCPP_HAVE__FREXPL */

/* Define if you have the _hypot function.  */
/* #undef _GLIBCPP_HAVE__HYPOT */

/* Define if you have the _hypotf function.  */
/* #undef _GLIBCPP_HAVE__HYPOTF */

/* Define if you have the _hypotl function.  */
/* #undef _GLIBCPP_HAVE__HYPOTL */

/* Define if you have the _isinf function.  */
/* #undef _GLIBCPP_HAVE__ISINF */

/* Define if you have the _isinff function.  */
/* #undef _GLIBCPP_HAVE__ISINFF */

/* Define if you have the _isinfl function.  */
/* #undef _GLIBCPP_HAVE__ISINFL */

/* Define if you have the _isnan function.  */
/* #undef _GLIBCPP_HAVE__ISNAN */

/* Define if you have the _isnanf function.  */
/* #undef _GLIBCPP_HAVE__ISNANF */

/* Define if you have the _isnanl function.  */
/* #undef _GLIBCPP_HAVE__ISNANL */

/* Define if you have the _ldexpf function.  */
/* #undef _GLIBCPP_HAVE__LDEXPF */

/* Define if you have the _ldexpl function.  */
/* #undef _GLIBCPP_HAVE__LDEXPL */

/* Define if you have the _log10f function.  */
/* #undef _GLIBCPP_HAVE__LOG10F */

/* Define if you have the _log10l function.  */
/* #undef _GLIBCPP_HAVE__LOG10L */

/* Define if you have the _logf function.  */
/* #undef _GLIBCPP_HAVE__LOGF */

/* Define if you have the _logl function.  */
/* #undef _GLIBCPP_HAVE__LOGL */

/* Define if you have the _modff function.  */
/* #undef _GLIBCPP_HAVE__MODFF */

/* Define if you have the _modfl function.  */
/* #undef _GLIBCPP_HAVE__MODFL */

/* Define if you have the _powf function.  */
/* #undef _GLIBCPP_HAVE__POWF */

/* Define if you have the _powl function.  */
/* #undef _GLIBCPP_HAVE__POWL */

/* Define if you have the _qfpclass function.  */
/* #undef _GLIBCPP_HAVE__QFPCLASS */

/* Define if you have the _sincos function.  */
/* #undef _GLIBCPP_HAVE__SINCOS */

/* Define if you have the _sincosf function.  */
/* #undef _GLIBCPP_HAVE__SINCOSF */

/* Define if you have the _sincosl function.  */
/* #undef _GLIBCPP_HAVE__SINCOSL */

/* Define if you have the _sinf function.  */
/* #undef _GLIBCPP_HAVE__SINF */

/* Define if you have the _sinhf function.  */
/* #undef _GLIBCPP_HAVE__SINHF */

/* Define if you have the _sinhl function.  */
/* #undef _GLIBCPP_HAVE__SINHL */

/* Define if you have the _sinl function.  */
/* #undef _GLIBCPP_HAVE__SINL */

/* Define if you have the _sqrtf function.  */
/* #undef _GLIBCPP_HAVE__SQRTF */

/* Define if you have the _sqrtl function.  */
/* #undef _GLIBCPP_HAVE__SQRTL */

/* Define if you have the _tanf function.  */
/* #undef _GLIBCPP_HAVE__TANF */

/* Define if you have the _tanhf function.  */
/* #undef _GLIBCPP_HAVE__TANHF */

/* Define if you have the _tanhl function.  */
/* #undef _GLIBCPP_HAVE__TANHL */

/* Define if you have the _tanl function.  */
/* #undef _GLIBCPP_HAVE__TANL */

/* Define if you have the acosf function.  */
/* #undef _GLIBCPP_HAVE_ACOSF */

/* Define if you have the acosl function.  */
/* #undef _GLIBCPP_HAVE_ACOSL */

/* Define if you have the asinf function.  */
/* #undef _GLIBCPP_HAVE_ASINF */

/* Define if you have the asinl function.  */
/* #undef _GLIBCPP_HAVE_ASINL */

/* Define if you have the atan2f function.  */
/* #undef _GLIBCPP_HAVE_ATAN2F */

/* Define if you have the atan2l function.  */
/* #undef _GLIBCPP_HAVE_ATAN2L */

/* Define if you have the atanf function.  */
/* #undef _GLIBCPP_HAVE_ATANF */

/* Define if you have the atanl function.  */
/* #undef _GLIBCPP_HAVE_ATANL */

/* Define if you have the btowc function.  */
/* #undef _GLIBCPP_HAVE_BTOWC */

/* Define if you have the ceilf function.  */
/* #undef _GLIBCPP_HAVE_CEILF */

/* Define if you have the ceill function.  */
/* #undef _GLIBCPP_HAVE_CEILL */

/* Define if you have the copysign function.  */
/* #undef _GLIBCPP_HAVE_COPYSIGN */

/* Define if you have the copysignf function.  */
/* #undef _GLIBCPP_HAVE_COPYSIGNF */

/* Define if you have the copysignl function.  */
/* #undef _GLIBCPP_HAVE_COPYSIGNL */

/* Define if you have the cosf function.  */
/* #undef _GLIBCPP_HAVE_COSF */

/* Define if you have the coshf function.  */
/* #undef _GLIBCPP_HAVE_COSHF */

/* Define if you have the coshl function.  */
/* #undef _GLIBCPP_HAVE_COSHL */

/* Define if you have the cosl function.  */
/* #undef _GLIBCPP_HAVE_COSL */

/* Define if you have the drand48 function.  */
/* #undef _GLIBCPP_HAVE_DRAND48 */

/* Define if you have the expl function.  */
/* #undef _GLIBCPP_HAVE_EXPL */

/* Define if you have the fabsf function.  */
/* #undef _GLIBCPP_HAVE_FABSF */

/* Define if you have the fabsl function.  */
/* #undef _GLIBCPP_HAVE_FABSL */

/* Define if you have the fgetwc function.  */
/* #undef _GLIBCPP_HAVE_FGETWC */

/* Define if you have the fgetws function.  */
/* #undef _GLIBCPP_HAVE_FGETWS */

/* Define if you have the finite function.  */
#define _GLIBCPP_HAVE_FINITE 1

/* Define if you have the finitef function.  */
/* #undef _GLIBCPP_HAVE_FINITEF */

/* Define if you have the finitel function.  */
/* #undef _GLIBCPP_HAVE_FINITEL */

/* Define if you have the floorf function.  */
/* #undef _GLIBCPP_HAVE_FLOORF */

/* Define if you have the floorl function.  */
/* #undef _GLIBCPP_HAVE_FLOORL */

/* Define if you have the fmodf function.  */
/* #undef _GLIBCPP_HAVE_FMODF */

/* Define if you have the fmodl function.  */
/* #undef _GLIBCPP_HAVE_FMODL */

/* Define if you have the fpclass function.  */
/* #undef _GLIBCPP_HAVE_FPCLASS */

/* Define if you have the fputwc function.  */
/* #undef _GLIBCPP_HAVE_FPUTWC */

/* Define if you have the fputws function.  */
/* #undef _GLIBCPP_HAVE_FPUTWS */

/* Define if you have the frexpf function.  */
/* #undef _GLIBCPP_HAVE_FREXPF */

/* Define if you have the frexpl function.  */
/* #undef _GLIBCPP_HAVE_FREXPL */

/* Define if you have the fwide function.  */
/* #undef _GLIBCPP_HAVE_FWIDE */

/* Define if you have the fwprintf function.  */
/* #undef _GLIBCPP_HAVE_FWPRINTF */

/* Define if you have the fwscanf function.  */
/* #undef _GLIBCPP_HAVE_FWSCANF */

/* Define if you have the getpagesize function.  */
/* #undef _GLIBCPP_HAVE_GETPAGESIZE */

/* Define if you have the getwc function.  */
/* #undef _GLIBCPP_HAVE_GETWC */

/* Define if you have the getwchar function.  */
/* #undef _GLIBCPP_HAVE_GETWCHAR */

/* Define if you have the hypot function.  */
/* #undef _GLIBCPP_HAVE_HYPOT */

/* Define if you have the hypotf function.  */
/* #undef _GLIBCPP_HAVE_HYPOTF */

/* Define if you have the hypotl function.  */
/* #undef _GLIBCPP_HAVE_HYPOTL */

/* Define if you have the iconv function.  */
/* #undef _GLIBCPP_HAVE_ICONV */

/* Define if you have the iconv_close function.  */
/* #undef _GLIBCPP_HAVE_ICONV_CLOSE */

/* Define if you have the iconv_open function.  */
/* #undef _GLIBCPP_HAVE_ICONV_OPEN */

/* Define if you have the isinf function.  */
#define _GLIBCPP_HAVE_ISINF 1

/* Define if you have the isinff function.  */
#define _GLIBCPP_HAVE_ISINFF 1

/* Define if you have the isinfl function.  */
/* #undef _GLIBCPP_HAVE_ISINFL */

/* Define if you have the isnan function.  */
#define _GLIBCPP_HAVE_ISNAN 1

/* Define if you have the isnanf function.  */
#define _GLIBCPP_HAVE_ISNANF 1

/* Define if you have the isnanl function.  */
/* #undef _GLIBCPP_HAVE_ISNANL */

/* Define if you have the ldexpf function.  */
/* #undef _GLIBCPP_HAVE_LDEXPF */

/* Define if you have the ldexpl function.  */
/* #undef _GLIBCPP_HAVE_LDEXPL */

/* Define if you have the log10f function.  */
/* #undef _GLIBCPP_HAVE_LOG10F */

/* Define if you have the log10l function.  */
/* #undef _GLIBCPP_HAVE_LOG10L */

/* Define if you have the logf function.  */
/* #undef _GLIBCPP_HAVE_LOGF */

/* Define if you have the logl function.  */
/* #undef _GLIBCPP_HAVE_LOGL */

/* Define if you have the mbrlen function.  */
/* #undef _GLIBCPP_HAVE_MBRLEN */

/* Define if you have the mbrtowc function.  */
/* #undef _GLIBCPP_HAVE_MBRTOWC */

/* Define if you have the mbsinit function.  */
/* #undef _GLIBCPP_HAVE_MBSINIT */

/* Define if you have the mbsrtowcs function.  */
/* #undef _GLIBCPP_HAVE_MBSRTOWCS */

/* Define if you have the modff function.  */
/* #undef _GLIBCPP_HAVE_MODFF */

/* Define if you have the modfl function.  */
/* #undef _GLIBCPP_HAVE_MODFL */

/* Define if you have the nan function.  */
/* #undef _GLIBCPP_HAVE_NAN */

/* Define if you have the nl_langinfo function.  */
/* #undef _GLIBCPP_HAVE_NL_LANGINFO */

/* Define if you have the powf function.  */
/* #undef _GLIBCPP_HAVE_POWF */

/* Define if you have the powl function.  */
/* #undef _GLIBCPP_HAVE_POWL */

/* Define if you have the putwc function.  */
/* #undef _GLIBCPP_HAVE_PUTWC */

/* Define if you have the putwchar function.  */
/* #undef _GLIBCPP_HAVE_PUTWCHAR */

/* Define if you have the qfpclass function.  */
/* #undef _GLIBCPP_HAVE_QFPCLASS */

/* Define if you have the signbitl function.  */
/* #undef _GLIBCPP_HAVE_SIGNBITL */

/* Define if you have the sincos function.  */
/* #undef _GLIBCPP_HAVE_SINCOS */

/* Define if you have the sincosf function.  */
/* #undef _GLIBCPP_HAVE_SINCOSF */

/* Define if you have the sincosl function.  */
/* #undef _GLIBCPP_HAVE_SINCOSL */

/* Define if you have the sinf function.  */
/* #undef _GLIBCPP_HAVE_SINF */

/* Define if you have the sinhf function.  */
/* #undef _GLIBCPP_HAVE_SINHF */

/* Define if you have the sinhl function.  */
/* #undef _GLIBCPP_HAVE_SINHL */

/* Define if you have the sinl function.  */
/* #undef _GLIBCPP_HAVE_SINL */

/* Define if you have the sqrtf function.  */
/* #undef _GLIBCPP_HAVE_SQRTF */

/* Define if you have the sqrtl function.  */
/* #undef _GLIBCPP_HAVE_SQRTL */

/* Define if you have the strtold function.  */
/* #undef _GLIBCPP_HAVE_STRTOLD */

/* Define if you have the swprintf function.  */
/* #undef _GLIBCPP_HAVE_SWPRINTF */

/* Define if you have the swscanf function.  */
/* #undef _GLIBCPP_HAVE_SWSCANF */

/* Define if you have the tanf function.  */
/* #undef _GLIBCPP_HAVE_TANF */

/* Define if you have the tanhf function.  */
/* #undef _GLIBCPP_HAVE_TANHF */

/* Define if you have the tanhl function.  */
/* #undef _GLIBCPP_HAVE_TANHL */

/* Define if you have the tanl function.  */
/* #undef _GLIBCPP_HAVE_TANL */

/* Define if you have the ungetwc function.  */
/* #undef _GLIBCPP_HAVE_UNGETWC */

/* Define if you have the vfwprintf function.  */
/* #undef _GLIBCPP_HAVE_VFWPRINTF */

/* Define if you have the vfwscanf function.  */
/* #undef _GLIBCPP_HAVE_VFWSCANF */

/* Define if you have the vswprintf function.  */
/* #undef _GLIBCPP_HAVE_VSWPRINTF */

/* Define if you have the vswscanf function.  */
/* #undef _GLIBCPP_HAVE_VSWSCANF */

/* Define if you have the vwprintf function.  */
/* #undef _GLIBCPP_HAVE_VWPRINTF */

/* Define if you have the vwscanf function.  */
/* #undef _GLIBCPP_HAVE_VWSCANF */

/* Define if you have the wcrtomb function.  */
/* #undef _GLIBCPP_HAVE_WCRTOMB */

/* Define if you have the wcscat function.  */
/* #undef _GLIBCPP_HAVE_WCSCAT */

/* Define if you have the wcschr function.  */
/* #undef _GLIBCPP_HAVE_WCSCHR */

/* Define if you have the wcscmp function.  */
/* #undef _GLIBCPP_HAVE_WCSCMP */

/* Define if you have the wcscoll function.  */
/* #undef _GLIBCPP_HAVE_WCSCOLL */

/* Define if you have the wcscpy function.  */
/* #undef _GLIBCPP_HAVE_WCSCPY */

/* Define if you have the wcscspn function.  */
/* #undef _GLIBCPP_HAVE_WCSCSPN */

/* Define if you have the wcsftime function.  */
/* #undef _GLIBCPP_HAVE_WCSFTIME */

/* Define if you have the wcslen function.  */
/* #undef _GLIBCPP_HAVE_WCSLEN */

/* Define if you have the wcsncat function.  */
/* #undef _GLIBCPP_HAVE_WCSNCAT */

/* Define if you have the wcsncmp function.  */
/* #undef _GLIBCPP_HAVE_WCSNCMP */

/* Define if you have the wcsncpy function.  */
/* #undef _GLIBCPP_HAVE_WCSNCPY */

/* Define if you have the wcspbrk function.  */
/* #undef _GLIBCPP_HAVE_WCSPBRK */

/* Define if you have the wcsrchr function.  */
/* #undef _GLIBCPP_HAVE_WCSRCHR */

/* Define if you have the wcsrtombs function.  */
/* #undef _GLIBCPP_HAVE_WCSRTOMBS */

/* Define if you have the wcsspn function.  */
/* #undef _GLIBCPP_HAVE_WCSSPN */

/* Define if you have the wcsstr function.  */
/* #undef _GLIBCPP_HAVE_WCSSTR */

/* Define if you have the wcstod function.  */
/* #undef _GLIBCPP_HAVE_WCSTOD */

/* Define if you have the wcstof function.  */
/* #undef _GLIBCPP_HAVE_WCSTOF */

/* Define if you have the wcstok function.  */
/* #undef _GLIBCPP_HAVE_WCSTOK */

/* Define if you have the wcstol function.  */
/* #undef _GLIBCPP_HAVE_WCSTOL */

/* Define if you have the wcstoul function.  */
/* #undef _GLIBCPP_HAVE_WCSTOUL */

/* Define if you have the wcsxfrm function.  */
/* #undef _GLIBCPP_HAVE_WCSXFRM */

/* Define if you have the wctob function.  */
/* #undef _GLIBCPP_HAVE_WCTOB */

/* Define if you have the wmemchr function.  */
/* #undef _GLIBCPP_HAVE_WMEMCHR */

/* Define if you have the wmemcmp function.  */
/* #undef _GLIBCPP_HAVE_WMEMCMP */

/* Define if you have the wmemcpy function.  */
/* #undef _GLIBCPP_HAVE_WMEMCPY */

/* Define if you have the wmemmove function.  */
/* #undef _GLIBCPP_HAVE_WMEMMOVE */

/* Define if you have the wmemset function.  */
/* #undef _GLIBCPP_HAVE_WMEMSET */

/* Define if you have the wprintf function.  */
/* #undef _GLIBCPP_HAVE_WPRINTF */

/* Define if you have the wscanf function.  */
/* #undef _GLIBCPP_HAVE_WSCANF */

/* Define if you have the <endian.h> header file.  */
/* #undef _GLIBCPP_HAVE_ENDIAN_H */

/* Define if you have the <float.h> header file.  */
/* #undef _GLIBCPP_HAVE_FLOAT_H */

/* Define if you have the <fp.h> header file.  */
/* #undef _GLIBCPP_HAVE_FP_H */

/* Define if you have the <gconv.h> header file.  */
/* #undef _GLIBCPP_HAVE_GCONV_H */

/* Define if you have the <ieeefp.h> header file.  */
/* #undef _GLIBCPP_HAVE_IEEEFP_H */

/* Define if you have the <inttypes.h> header file.  */
/* #undef _GLIBCPP_HAVE_INTTYPES_H */

/* Define if you have the <locale.h> header file.  */
/* #undef _GLIBCPP_HAVE_LOCALE_H */

/* Define if you have the <machine/endian.h> header file.  */
/* #undef _GLIBCPP_HAVE_MACHINE_ENDIAN_H */

/* Define if you have the <machine/param.h> header file.  */
/* #undef _GLIBCPP_HAVE_MACHINE_PARAM_H */

/* Define if you have the <nan.h> header file.  */
/* #undef _GLIBCPP_HAVE_NAN_H */

/* Define if you have the <sys/isa_defs.h> header file.  */
/* #undef _GLIBCPP_HAVE_SYS_ISA_DEFS_H */

/* Define if you have the <sys/machine.h> header file.  */
/* #undef _GLIBCPP_HAVE_SYS_MACHINE_H */

/* Define if you have the <sys/resource.h> header file.  */
#define _GLIBCPP_HAVE_SYS_RESOURCE_H 1

/* Define if you have the <unistd.h> header file.  */
#define _GLIBCPP_HAVE_UNISTD_H 1

/* Define if you have the <wchar.h> header file.  */
/* #undef _GLIBCPP_HAVE_WCHAR_H */

/* Define if you have the m library (-lm).  */
/* #undef _GLIBCPP_HAVE_LIBM */

/* Name of package */
#define _GLIBCPP_PACKAGE "libstdc++"

/* Version number of package */
#define _GLIBCPP_VERSION "3.0.0"

/* Define if the compiler is configured for setjmp/longjmp exceptions. */
#define _GLIBCPP_SJLJ_EXCEPTIONS 1

/* Define if sigsetjmp is available.   */
/* #undef _GLIBCPP_HAVE_SIGSETJMP */

/* Only used in build directory testsuite_hooks.h. */
#define _GLIBCPP_HAVE_MEMLIMIT_DATA 0

/* Only used in build directory testsuite_hooks.h. */
#define _GLIBCPP_HAVE_MEMLIMIT_RSS 0

/* Only used in build directory testsuite_hooks.h. */
#define _GLIBCPP_HAVE_MEMLIMIT_VMEM 0

/* Only used in build directory testsuite_hooks.h. */
#define _GLIBCPP_HAVE_MEMLIMIT_AS 0

//
// Systems that have certain non-standard functions prefixed with an
// underscore, we'll handle those here. Must come after config.h.in.
//
#if defined (_GLIBCPP_HAVE__ISNAN) && ! defined (_GLIBCPP_HAVE_ISNAN)
# define _GLIBCPP_HAVE_ISNAN 1
# define isnan _isnan
#endif

#if defined (_GLIBCPP_HAVE__ISNANF) && ! defined (_GLIBCPP_HAVE_ISNANF)
# define _GLIBCPP_HAVE_ISNANF 1
# define isnanf _isnanf
#endif

#if defined (_GLIBCPP_HAVE__ISNANL) && ! defined (_GLIBCPP_HAVE_ISNANL)
# define _GLIBCPP_HAVE_ISNANL 1
# define isnanl _isnanl
#endif

#if defined (_GLIBCPP_HAVE__ISINF) && ! defined (_GLIBCPP_HAVE_ISINF)
# define _GLIBCPP_HAVE_ISINF 1
# define isinf _isinf
#endif

#if defined (_GLIBCPP_HAVE__ISINFF) && ! defined (_GLIBCPP_HAVE_ISINFF)
# define _GLIBCPP_HAVE_ISINFF 1
# define isinff _isinff
#endif

#if defined (_GLIBCPP_HAVE__ISINFL) && ! defined (_GLIBCPP_HAVE_ISINFL)
# define _GLIBCPP_HAVE_ISINFL 1
# define isinfl _isinfl
#endif

#if defined (_GLIBCPP_HAVE__COPYSIGN) && ! defined (_GLIBCPP_HAVE_COPYSIGN)
# define _GLIBCPP_HAVE_COPYSIGN 1
# define copysign _copysign
#endif

#if defined (_GLIBCPP_HAVE__COPYSIGNL) && ! defined (_GLIBCPP_HAVE_COPYSIGNL)
# define _GLIBCPP_HAVE_COPYSIGNL 1
# define copysignl _copysignl
#endif

#if defined (_GLIBCPP_HAVE__COSF) && ! defined (_GLIBCPP_HAVE_COSF)
# define _GLIBCPP_HAVE_COSF 1
# define cosf _cosf
#endif

#if defined (_GLIBCPP_HAVE__ACOSF) && ! defined (_GLIBCPP_HAVE_ACOSF)
# define _GLIBCPP_HAVE_ACOSF 1
# define acosf _acosf
#endif

#if defined (_GLIBCPP_HAVE__ACOSL) && ! defined (_GLIBCPP_HAVE_ACOSL)
# define _GLIBCPP_HAVE_ACOSL 1
# define acosl _acosl
#endif

#if defined (_GLIBCPP_HAVE__ASINF) && ! defined (_GLIBCPP_HAVE_ASINF)
# define _GLIBCPP_HAVE_ASINF 1
# define asinf _asinf
#endif

#if defined (_GLIBCPP_HAVE__ASINL) && ! defined (_GLIBCPP_HAVE_ASINL)
# define _GLIBCPP_HAVE_ASINL 1
# define asinl _asinl
#endif

#if defined (_GLIBCPP_HAVE__ATANF) && ! defined (_GLIBCPP_HAVE_ATANF)
# define _GLIBCPP_HAVE_ATANF 1
# define atanf _atanf
#endif

#if defined (_GLIBCPP_HAVE__ATANL) && ! defined (_GLIBCPP_HAVE_ATANL)
# define _GLIBCPP_HAVE_ATANL 1
# define atanl _atanl
#endif

#if defined (_GLIBCPP_HAVE__CEILF) && ! defined (_GLIBCPP_HAVE_CEILF)
# define _GLIBCPP_HAVE_CEILF 1
# define aceil _ceilf
#endif

#if defined (_GLIBCPP_HAVE__CEILL) && ! defined (_GLIBCPP_HAVE_CEILL)
# define _GLIBCPP_HAVE_CEILL 1
# define aceil _ceill
#endif

#if defined (_GLIBCPP_HAVE__COSHF) && ! defined (_GLIBCPP_HAVE_COSHF)
# define _GLIBCPP_HAVE_COSHF 1
# define coshf _coshf
#endif

#if defined (_GLIBCPP_HAVE__COSL) && ! defined (_GLIBCPP_HAVE_COSL)
# define _GLIBCPP_HAVE_COSL 1
# define cosl _cosl
#endif

#if defined (_GLIBCPP_HAVE__LOGF) && ! defined (_GLIBCPP_HAVE_LOGF)
# define _GLIBCPP_HAVE_LOGF 1
# define logf _logf
#endif

#if defined (_GLIBCPP_HAVE__COSHL) && ! defined (_GLIBCPP_HAVE_COSHL)
# define _GLIBCPP_HAVE_COSHL 1
# define coshl _coshl
#endif

#if defined (_GLIBCPP_HAVE__EXPF) && ! defined (_GLIBCPP_HAVE_EXPF)
# define _GLIBCPP_HAVE_EXPF 1
# define expf _expf
#endif

#if defined (_GLIBCPP_HAVE__EXPL) && ! defined (_GLIBCPP_HAVE_EXPL)
# define _GLIBCPP_HAVE_EXPL 1
# define expl _expl
#endif

#if defined (_GLIBCPP_HAVE__FABSF) && ! defined (_GLIBCPP_HAVE_FABSF)
# define _GLIBCPP_HAVE_FABSF 1
# define fabsf _fabsf
#endif

#if defined (_GLIBCPP_HAVE__FABSL) && ! defined (_GLIBCPP_HAVE_FABSL)
# define _GLIBCPP_HAVE_FABSL 1
# define fabsl _fabsl
#endif

#if defined (_GLIBCPP_HAVE__FLOORF) && ! defined (_GLIBCPP_HAVE_FLOORF)
# define _GLIBCPP_HAVE_FLOORF 1
# define floorf _floorf
#endif

#if defined (_GLIBCPP_HAVE__FLOORL) && ! defined (_GLIBCPP_HAVE_FLOORL)
# define _GLIBCPP_HAVE_FLOORL 1
# define floorl _floorl
#endif

#if defined (_GLIBCPP_HAVE__FMODF) && ! defined (_GLIBCPP_HAVE_FMODF)
# define _GLIBCPP_HAVE_FMODF 1
# define fmodf _fmodf
#endif

#if defined (_GLIBCPP_HAVE__FMODL) && ! defined (_GLIBCPP_HAVE_FMODL)
# define _GLIBCPP_HAVE_FMODL 1
# define fmodl _fmodl
#endif

#if defined (_GLIBCPP_HAVE__FREXPF) && ! defined (_GLIBCPP_HAVE_FREXPF)
# define _GLIBCPP_HAVE_FREXPF 1
# define frexpf _frexpf
#endif

#if defined (_GLIBCPP_HAVE__FREXPL) && ! defined (_GLIBCPP_HAVE_FREXPL)
# define _GLIBCPP_HAVE_FREXPL 1
# define frexpl _frexpl
#endif

#if defined (_GLIBCPP_HAVE__LDEXPF) && ! defined (_GLIBCPP_HAVE_LDEXPF)
# define _GLIBCPP_HAVE_LDEXPF 1
# define ldexpf _ldexpf
#endif

#if defined (_GLIBCPP_HAVE__LDEXPL) && ! defined (_GLIBCPP_HAVE_LDEXPL)
# define _GLIBCPP_HAVE_LDEXPL 1
# define ldexpl _ldexpl
#endif

#if defined (_GLIBCPP_HAVE__LOG10F) && ! defined (_GLIBCPP_HAVE_LOG10F)
# define _GLIBCPP_HAVE_LOG10F 1
# define log10f _log10f
#endif

#if defined (_GLIBCPP_HAVE__LOGL) && ! defined (_GLIBCPP_HAVE_LOGL)
# define _GLIBCPP_HAVE_LOGL 1
# define logl _logl
#endif

#if defined (_GLIBCPP_HAVE__POWF) && ! defined (_GLIBCPP_HAVE_POWF)
# define _GLIBCPP_HAVE_POWF 1
# define powf _powf
#endif

#if defined (_GLIBCPP_HAVE__LOG10L) && ! defined (_GLIBCPP_HAVE_LOG10L)
# define _GLIBCPP_HAVE_LOG10L 1
# define log10l _log10l
#endif

#if defined (_GLIBCPP_HAVE__MODF) && ! defined (_GLIBCPP_HAVE_MODF)
# define _GLIBCPP_HAVE_MODF 1
# define modf _modf
#endif

#if defined (_GLIBCPP_HAVE__MODL) && ! defined (_GLIBCPP_HAVE_MODL)
# define _GLIBCPP_HAVE_MODL 1
# define modl _modl
#endif

#if defined (_GLIBCPP_HAVE__SINF) && ! defined (_GLIBCPP_HAVE_SINF)
# define _GLIBCPP_HAVE_SINF 1
# define sinf _sinf
#endif

#if defined (_GLIBCPP_HAVE__POWL) && ! defined (_GLIBCPP_HAVE_POWL)
# define _GLIBCPP_HAVE_POWL 1
# define powl _powl
#endif

#if defined (_GLIBCPP_HAVE__SINHF) && ! defined (_GLIBCPP_HAVE_SINHF)
# define _GLIBCPP_HAVE_SINHF 1
# define sinhf _sinhf
#endif

#if defined (_GLIBCPP_HAVE__SINL) && ! defined (_GLIBCPP_HAVE_SINL)
# define _GLIBCPP_HAVE_SINL 1
# define sinl _sinl
#endif

#if defined (_GLIBCPP_HAVE__SQRTF) && ! defined (_GLIBCPP_HAVE_SQRTF)
# define _GLIBCPP_HAVE_SQRTF 1
# define sqrtf _sqrtf
#endif

#if defined (_GLIBCPP_HAVE__SINHL) && ! defined (_GLIBCPP_HAVE_SINHL)
# define _GLIBCPP_HAVE_SINHL 1
# define sinhl _sinhl
#endif

#if defined (_GLIBCPP_HAVE__TANF) && ! defined (_GLIBCPP_HAVE_TANF)
# define _GLIBCPP_HAVE_TANF 1
# define tanf _tanf
#endif

#if defined (_GLIBCPP_HAVE__SQRTL) && ! defined (_GLIBCPP_HAVE_SQRTL)
# define _GLIBCPP_HAVE_SQRTL 1
# define sqrtl _sqrtl
#endif

#if defined (_GLIBCPP_HAVE__TANHF) && ! defined (_GLIBCPP_HAVE_TANHF)
# define _GLIBCPP_HAVE_TANHF 1
# define tanhf _tanhf
#endif

#if defined (_GLIBCPP_HAVE__TANL) && ! defined (_GLIBCPP_HAVE_TANL)
# define _GLIBCPP_HAVE_TANF 1
# define tanf _tanf
#endif

#if defined (_GLIBCPP_HAVE__STRTOF) && ! defined (_GLIBCPP_HAVE_STRTOF)
# define _GLIBCPP_HAVE_STRTOF 1
# define strtof _strtof
#endif

#if defined (_GLIBCPP_HAVE__TANHL) && ! defined (_GLIBCPP_HAVE_TANHL)
# define _GLIBCPP_HAVE_TANHL 1
# define tanhl _tanhl
#endif

#if defined (_GLIBCPP_HAVE__STRTOLD) && ! defined (_GLIBCPP_HAVE_STRTOLD)
# define _GLIBCPP_HAVE_STRTOLD 1
# define strtold _strtold
#endif

#if defined (_GLIBCPP_HAVE__SINCOS) && ! defined (_GLIBCPP_HAVE_SINCOS)
# define _GLIBCPP_HAVE_SINCOS 1
# define sincos _sincos
#endif

#if defined (_GLIBCPP_HAVE__SINCOSF) && ! defined (_GLIBCPP_HAVE_SINCOSF)
# define _GLIBCPP_HAVE_SINCOSF 1
# define sincosf _sincosf
#endif

#if defined (_GLIBCPP_HAVE__SINCOSL) && ! defined (_GLIBCPP_HAVE_SINCOSL)
# define _GLIBCPP_HAVE_SINCOSL 1
# define sincosl _sincosl
#endif

#if defined (_GLIBCPP_HAVE__FINITE) && ! defined (_GLIBCPP_HAVE_FINITE)
# define _GLIBCPP_HAVE_FINITE 1
# define finite _finite
#endif

#if defined (_GLIBCPP_HAVE__FINITEF) && ! defined (_GLIBCPP_HAVE_FINITEF)
# define _GLIBCPP_HAVE_FINITEF 1
# define finitef _finitef
#endif

#if defined (_GLIBCPP_HAVE__FINITEL) && ! defined (_GLIBCPP_HAVE_FINITEL)
# define _GLIBCPP_HAVE_FINITEL 1
# define finitel _finitel
#endif

#if defined (_GLIBCPP_HAVE__QFINITE) && ! defined (_GLIBCPP_HAVE_QFINITE)
# define _GLIBCPP_HAVE_QFINITE 1
# define qfinite _qfinite
#endif

#if defined (_GLIBCPP_HAVE__FPCLASS) && ! defined (_GLIBCPP_HAVE_FPCLASS)
# define _GLIBCPP_HAVE_FPCLASS 1
# define fpclass _fpclass
#endif

#if defined (_GLIBCPP_HAVE__QFPCLASS) && ! defined (_GLIBCPP_HAVE_QFPCLASS)
# define _GLIBCPP_HAVE_QFPCLASS 1
# define qfpclass _qfpclass
#endif

#endif // _CPP_CPPCONFIG_
