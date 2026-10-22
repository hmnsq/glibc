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

#अन्तर्भाव <string.h>

#अपरिभाषय strpbrk

#यदि_अपरिभाषितम् STRPBRK
#परिभाषय STRPBRK strpbrk
#यदि_अन्तः

/* Find the first occurrence in S of any character in ACCEPT.  */
वर्ण *
STRPBRK (ध्रुव वर्ण *s, ध्रुव वर्ण *accept)
{
  s += strcspn (s, accept);
  प्रत्यागम *s ? (वर्ण *)s : रिक्त;
}
libc_hidden_builtin_def (strpbrk)
