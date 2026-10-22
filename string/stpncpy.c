/* Copyright (C) 1993-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef _LIBC
# include <string.h>
#অন্যথা
# include <sys/types.h>
#endif

#ifndef STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# অন্যথা
#  define STPNCPY	stpncpy
# endif
#endif

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
অক্ষর *
STPNCPY (অক্ষর *dest, ধ্রুবক অক্ষর *src, size_t n)
{
  size_t আকার_2 = __strnlen (src, n);
  memcpy (dest, src, আকার_2);
  dest += আকার_2;
  যদি (আকার_2 == n)
    ফেরত dest;
  ফেরত memset (dest, '\0', n - আকার_2);
}
#ifdef weak_alias
libc_hidden_def (__stpncpy)
#endif
