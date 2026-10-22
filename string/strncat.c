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

#ifndef STRNCAT
# undef म_जोड़न
# define STRNCAT  म_जोड़न
# define STRNCAT_PRIMARY
#endif

वर्ण *
STRNCAT (वर्ण *s1, अचर वर्ण *s2, माप_प्रकार n)
{
  वर्ण *s = s1;

  /* Find the end of S1.  */
  s1 += म_माप (s1);

  माप_प्रकार ss = __strnlen (s2, n);

  s1[ss] = '\0';
  स_नकल (s1, s2, ss);

  फर्काऊ s;
}
#ifdef STRNCAT_PRIMARY
strong_alias (STRNCAT, __strncat)
libc_hidden_def (__strncat)
#endif
