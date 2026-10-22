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

#অন্তর্ভাব <string.h>

#undef strncpy

#ifndef STRNCPY
 #define STRNCPY strncpy
#endif

অক্ষর *
STRNCPY (অক্ষর *s1, ধ্রুবক অক্ষর *s2, size_t n)
{
  size_t আকার_2 = __strnlen (s2, n);
  যদি (আকার_2 != n)
    memset (s1 + আকার_2, '\0', n - আকার_2);
  ফেরত memcpy (s1, s2, আকার_2);
}
libc_hidden_builtin_def (strncpy)
