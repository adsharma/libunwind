/*
    Copyright (C) 2010  ABRT team
    Copyright (C) 2010  RedHat Inc

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef _UCD_lib_h
#define _UCD_lib_h

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
/* Try to pull in PATH_MAX */
#include <limits.h>
#include <sys/param.h>
#ifndef PATH_MAX
# define PATH_MAX 256
#endif
#include <pwd.h>
#include <grp.h>
#include <syslog.h>


#ifndef NORETURN
#define NORETURN __attribute__((noreturn))
#endif


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


#define die_out_of_memory libunwind_die_out_of_memory
void die_out_of_memory(void) NORETURN;
#define xmalloc libunwind_xmalloc
void* xmalloc(size_t size);
#define xrealloc libunwind_xrealloc
void* xrealloc(void *ptr, size_t size);
#define xzalloc libunwind_xzalloc
void* xzalloc(size_t size);
#define xstrdup libunwind_xstrdup
char* xstrdup(const char *s);

#define xlseek libunwind_xlseek
off_t xlseek(int fd, off_t offset, int whence);


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
