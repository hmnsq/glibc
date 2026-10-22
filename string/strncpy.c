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

#undef म_नकलन

#ifndef STRNCPY
 #define STRNCPY म_नकलन
#endif

अक्षर *
STRNCPY (अक्षर *s1, स्थिरांक अक्षर *s2, माप_प्रकार n)
{
  माप_प्रकार size = __strnlen (s2, n);
  जर (size != n)
    स_रखो (s1 + size, '\0', n - size);
  परत स_नकल (s1, s2, size);
}
libc_hidden_builtin_def (म_नकलन)
