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

#جيڪڏهن_وصف_ٿيل HAVE_CONFIG_H
# include <config.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _LIBC
# include <string.h>
#وإلا
# include <sys/types.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# وإلا
#  define STPNCPY	stpncpy
# endif
#جيڪڏهن_پورو

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
حرف *
STPNCPY (حرف *dest, ثابت حرف *src, size_t n)
{
  size_t سائيز = __strnlen (src, n);
  يادگيري_نقل (dest, src, سائيز);
  dest += سائيز;
  إذا (سائيز == n)
    أرجع dest;
  أرجع memset (dest, '\0', n - سائيز);
}
#جيڪڏهن_وصف_ٿيل weak_alias
libc_hidden_def (__stpncpy)
#جيڪڏهن_پورو
