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
#include "_UCD_lib.h"

#include "libunwind_i.h"

HIDDEN
void die_out_of_memory(void)
{
    write(2, "Out of memory, exiting\n",
      strlen("Out of memory, exiting\n")
    );
    _exit(1);
}

/* Die if we can't allocate size bytes of memory. */
HIDDEN
void* xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL && size != 0)
        die_out_of_memory();
    return ptr;
}

/* Die if we can't resize previously allocated memory. */
HIDDEN
void* xrealloc(void *ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if (ptr == NULL && size != 0)
        die_out_of_memory();
    return ptr;
}

/* Die if we can't allocate and zero size bytes of memory. */
HIDDEN
void* xzalloc(size_t size)
{
    void *ptr = xmalloc(size);
    memset(ptr, 0, size);
    return ptr;
}

/* Die if we can't copy a string to freshly allocated memory. */
HIDDEN
char* xstrdup(const char *s)
{
    char *t;
    if (s == NULL)
        return NULL;

    t = strdup(s);

    if (t == NULL)
        die_out_of_memory();

    return t;
}

/* Die with an error message if we can't lseek to the right spot. */
HIDDEN
off_t xlseek(int fd, off_t offset, int whence)
{
    off_t off = lseek(fd, offset, whence);
    if (off == (off_t)-1) {
        if (whence == SEEK_SET)
            fprintf(stderr, "lseek(%llu)\n", (unsigned long long)offset);
	else
            fprintf(stderr, "lseek\n");
        exit(1);
    }
    return off;
}
