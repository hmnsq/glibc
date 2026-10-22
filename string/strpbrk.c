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

#تعریف_منسوخ strpbrk

#اگر_غیر_تعریف_شدہ STRPBRK
#تعریف_کرو STRPBRK strpbrk
#اگر_ختم

/* Find the first occurrence in S of any character in ACCEPT.  */
حرف *
STRPBRK (ثابت حرف *s, ثابت حرف *accept)
{
  s += strcspn (s, accept);
  واپس *s ? (حرف *)s : تہی;
}
libc_hidden_builtin_def (strpbrk)
