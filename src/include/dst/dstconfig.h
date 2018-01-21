/*
* Copyright (c) 2017 Calvin Rose
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef DST_CONFIG_H_defined
#define DST_CONFIG_H_defined

#include <stdint.h>

#define DST_VERSION "0.0.0"

/*
 * Detect OS and endianess.
 * From webkit source. There is likely some extreneous
 * detection for unsupported platforms
 */

/* Check Unix */
#if defined(_AIX) \
    || defined(__APPLE__) /* Darwin */ \
    || defined(__FreeBSD__) || defined(__DragonFly__) \
    || defined(__FreeBSD_kernel__) \
    || defined(__GNU__) /* GNU/Hurd */ \
    || defined(__linux__) \
    || defined(__NetBSD__) \
    || defined(__OpenBSD__) \
    || defined(__QNXNTO__) \
    || defined(sun) || defined(__sun) /* Solaris */ \
    || defined(unix) || defined(__unix) || defined(__unix__)
#define DST_UNIX 1
#endif

/* Check Windows */
#if defined(WIN32) || defined(_WIN32)
#define DST_WINDOWS 1
#endif

/* Check 64-bit vs 32-bit */
#if ((defined(__x86_64__) || defined(_M_X64)) \
     && (defined(DST_UNIX) || defined(DST_WINDOWS))) \
    || (defined(__ia64__) && defined(__LP64__)) /* Itanium in LP64 mode */ \
    || defined(__alpha__) /* DEC Alpha */ \
    || (defined(__sparc__) && defined(__arch64__) || defined (__sparcv9)) /* BE */ \
    || defined(__s390x__) /* S390 64-bit (BE) */ \
    || (defined(__ppc64__) || defined(__PPC64__)) \
    || defined(__aarch64__) /* ARM 64-bit */
#define DST_64 1
#else
#define DST_32 1
#endif

/* Check big endian */
#if defined(__MIPSEB__) /* MIPS 32-bit */ \
    || defined(__ppc__) || defined(__PPC__) /* CPU(PPC) - PowerPC 32-bit */ \
    || defined(__powerpc__) || defined(__powerpc) || defined(__POWERPC__) \
    || defined(_M_PPC) || defined(__PPC) \
    || defined(__ppc64__) || defined(__PPC64__) /* PowerPC 64-bit */ \
    || defined(__sparc)   /* Sparc 32bit */  \
    || defined(__sparc__) /* Sparc 64-bit */ \
    || defined(__s390x__) /* S390 64-bit */ \
    || defined(__s390__)  /* S390 32-bit */ \
    || defined(__ARMEB__) /* ARM big endian */ \
    || ((defined(__CC_ARM) || defined(__ARMCC__)) /* ARM RealView compiler */ \
        && defined(__BIG_ENDIAN))
#define DST_BIG_ENDIAN 1
#else
#define DST_LITTLE_ENDIAN 1
#endif

/* Handle runtime errors */
#ifndef dst_exit
#include <stdlib.h>
#include <stdio.h>
#define dst_exit(m) do { \
    printf("runtime error at line %d in file %s: %s\n",\
        __LINE__,\
        __FILE__,\
        (m));\
    exit(-1);\
} while (0)
#endif

#define dst_assert(c, m) do { \
    if (!(c)) dst_exit((m)); \
} while (0)

/* What to do when out of memory */
#ifndef DST_OUT_OF_MEMORY
#include <stdio.h>
#define DST_OUT_OF_MEMORY do { printf("out of memory\n"); exit(1); } while (0)
#endif

/* Helper for debugging */
#define dst_trace(x) dst_puts(dst_formatc("DST TRACE %s, %d: %v\n", __FILE__, __LINE__, x))

/* Prevent some recursive functions from recursing too deeply
 * ands crashing (the parser). Instead, error out. */
#define DST_RECURSION_GUARD 1024

/* Use nanboxed values - uses 8 bytes per value instead of 12 or 16. */
#define DST_NANBOX
#define DST_NANBOX_47

/* Alignment for pointers */
#ifdef DST_32
#define DST_WALIGN 4
#else
#define DST_WALIGN 8
#endif

#endif /* DST_CONFIG_H_defined */