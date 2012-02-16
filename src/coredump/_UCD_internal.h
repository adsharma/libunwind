/* libunwind - a platform-independent unwind library

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef _UCD_internal_h
#define _UCD_internal_h

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_PROCFS_H
#include <sys/procfs.h> /* struct elf_prstatus */
#endif
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <libunwind-coredump.h>

#include "libunwind_i.h"


#if SIZEOF_OFF_T == 4
typedef uint32_t uoff_t;
#elif SIZEOF_OFF_T == 8
typedef uint64_t uoff_t;
#else
# error Unknown size of off_t!
#endif


/* Similar to ELF phdrs. p_paddr element is absent,
 * since it's always 0 in coredumps.
 */
struct coredump_phdr
  {
    uint32_t p_type;
    uint32_t p_flags;
    uoff_t   p_offset;
    uoff_t   p_vaddr;
    uoff_t   p_filesz;
    uoff_t   p_memsz;
    uoff_t   p_align;
    /* Data for backing file. If backing_fd < 0, there is no file */
    uoff_t   backing_filesize;
    char    *backing_filename; /* for error meesages only */
    int      backing_fd;
  };

typedef struct coredump_phdr coredump_phdr_t;


struct UCD_info
  {
    int big_endian;  /* bool */
    int coredump_fd;
    char *coredump_filename; /* for error meesages only */
    coredump_phdr_t *phdrs; /* array, allocated */
    unsigned phdrs_count;
    void *note_phdr; /* allocated or NULL */
    struct elf_prstatus *prstatus; /* points inside note_phdr */

    struct elf_image ei;
    unw_dyn_info_t di_cache;
    unw_dyn_info_t di_debug;	/* additional table info for .debug_frame */
#if UNW_TARGET_IA64
    unw_dyn_info_t ktab;
#endif
#if UNW_TARGET_ARM
    unw_dyn_info_t di_arm;	/* additional table info for .ARM.exidx */
#endif
  };

extern int _UCDi_find_unwind_table (struct UCD_info *ui,
				    unw_addr_space_t as,
				    char *path,
				    unw_word_t segbase,
				    unw_word_t mapoff,
				    unw_word_t ip);

#endif
