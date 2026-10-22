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

#समावेश <string.h>

#अघोषित म_नकलन

#अगर_अघोषित STRNCPY
 #घोषणा STRNCPY म_नकलन
#पूर्ण_अगर

अक्षर *
STRNCPY (अक्षर *s1, स्थिर अक्षर *s2, माप_प्रकार n)
{
  माप_प्रकार आकार = __strnlen (s2, n);
  अगर (आकार != n)
    स_रखो (s1 + आकार, '\0', n - आकार);
  वापस स_नकल (s1, s2, आकार);
}
libc_hidden_builtin_def (म_नकलन)
