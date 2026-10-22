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

#अपरिभाषय strncpy

#यदि_अपरिभाषितम् STRNCPY
 #परिभाषय STRNCPY strncpy
#यदि_अन्तः

वर्ण *
STRNCPY (वर्ण *s1, ध्रुव वर्ण *s2, size_t n)
{
  size_t आकार = __strnlen (s2, n);
  यदि (आकार != n)
    स्मृतिं_पूरय (s1 + आकार, '\0', n - आकार);
  प्रत्यागम स्मृतिं_प्रतिलिख (s1, s2, आकार);
}
libc_hidden_builtin_def (strncpy)
