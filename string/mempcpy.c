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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_MEMPCPY_STPCPY_REDIRECT
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ mempcpy
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __mempcpy

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMPCPY
# define MEMPCPY __mempcpy
#ਜੇ_ਅੰਤ

ਖਾਲੀ *
MEMPCPY (ਖਾਲੀ *dest, ਅਚਲ ਖਾਲੀ *src, size_t len)
{
  ਵਾਪਸ ਸਮ੍ਰਿਤੀ_ਨਕਲ (dest, src, len) + len;
}
libc_hidden_def (__mempcpy)
static_weak_alias (__mempcpy, mempcpy)
libc_hidden_builtin_def (mempcpy)
