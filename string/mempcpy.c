/* Copy memory to memory until the specified number of bytes
   has been copied, return pointer to following byte.
   Overlap is NOT handled correctly.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Torbjorn Granlund (tege@sics.se).

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

#परिभाषय NO_MEMPCPY_STPCPY_REDIRECT
#अन्तर्भाव <string.h>

#अपरिभाषय mempcpy
#अपरिभाषय __mempcpy

#यदि_अपरिभाषितम् MEMPCPY
# define MEMPCPY __mempcpy
#यदि_अन्तः

शून्य *
MEMPCPY (शून्य *dest, ध्रुव शून्य *src, size_t len)
{
  प्रत्यागम स्मृतिं_प्रतिलिख (dest, src, len) + len;
}
libc_hidden_def (__mempcpy)
static_weak_alias (__mempcpy, mempcpy)
libc_hidden_builtin_def (mempcpy)
