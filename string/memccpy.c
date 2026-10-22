/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#ضمن <string.h>

#تعریف_رد __memccpy
#تعریف_رد memccpy

#جے_تعریف_شدہ MEMCCPY
# define __memccpy MEMCCPY
#جے_انت

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied, or
   NULL if C was not found in the first N bytes of SRC.  */
فراغ *
__memccpy (فراغ *dest, ثابت فراغ *src, صحيح c, size_t n)
{
  فراغ *p = memchr (src, c, n);

  إذا (p != عدم)
    أرجع __mempcpy (dest, src, p - src + 1);

  حافظہ_نقل (dest, src, n);
  أرجع عدم;
}

weak_alias (__memccpy, memccpy)
