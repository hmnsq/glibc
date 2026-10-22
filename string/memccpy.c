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

#अघोषित __memccpy
#अघोषित memccpy

#अगर_घोषित MEMCCPY
# define __memccpy MEMCCPY
#पूर्ण_अगर

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied, or
   NULL if C was not found in the first N bytes of SRC.  */
व्योम *
__memccpy (व्योम *dest, स्थिर व्योम *src, पूर्णांक c, माप_प्रकार n)
{
  व्योम *p = स_प्रथम (src, c, n);

  अगर (p != शून्य)
    वापस __mempcpy (dest, src, p - src + 1);

  स_नकल (dest, src, n);
  वापस शून्य;
}

weak_alias (__memccpy, memccpy)
