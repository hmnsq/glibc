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

#شامل <string.h>

#تعریف_منسوخ strncpy

#اگر_غیر_تعریف_شدہ STRNCPY
 #تعریف_کرو STRNCPY strncpy
#اگر_ختم

حرف *
STRNCPY (حرف *s1, ثابت حرف *s2, size_t n)
{
  size_t سائز = __strnlen (s2, n);
  اگر (سائز != n)
    memset (s1 + سائز, '\0', n - سائز);
  واپس حافظہ_نقل (s1, s2, سائز);
}
libc_hidden_builtin_def (strncpy)
