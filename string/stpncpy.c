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

#که_تعریف_شوی HAVE_CONFIG_H
# include <config.h>
#د_که_پای

#که_تعریف_شوی _LIBC
# include <string.h>
#وإلا
# include <sys/types.h>
#د_که_پای

#که_نه_تعریف_شوی STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# وإلا
#  define STPNCPY	stpncpy
# endif
#د_که_پای

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
حرف *
STPNCPY (حرف *dest, ثابت حرف *src, size_t n)
{
  size_t اندازه = __strnlen (src, n);
  حافظه_نقل (dest, src, اندازه);
  dest += اندازه;
  إذا (اندازه == n)
    أرجع dest;
  أرجع memset (dest, '\0', n - اندازه);
}
#که_تعریف_شوی weak_alias
libc_hidden_def (__stpncpy)
#د_که_پای
