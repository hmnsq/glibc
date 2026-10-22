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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strncpy

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRNCPY
 #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRNCPY strncpy
#ਜੇ_ਅੰਤ

ਅੱਖਰ *
STRNCPY (ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, size_t n)
{
  size_t ਮਾਪ = __strnlen (s2, n);
  ਜੇ (ਮਾਪ != n)
    memset (s1 + ਮਾਪ, '\0', n - ਮਾਪ);
  ਵਾਪਸ ਸਮ੍ਰਿਤੀ_ਨਕਲ (s1, s2, ਮਾਪ);
}
libc_hidden_builtin_def (strncpy)
