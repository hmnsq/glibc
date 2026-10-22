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

#అన్తర్భావ <string.h>

#నిర్వచితం_కాకపోతే STRNCAT
# undef strncat
# define STRNCAT  strncat
# define STRNCAT_PRIMARY
#అయితే_ముగింపు

అక్షరం *
STRNCAT (అక్షరం *s1, స్థిరరాశి అక్షరం *s2, size_t n)
{
  అక్షరం *s = s1;

  /* Find the end of S1.  */
  s1 += అక్షరశ్రేణి_పొడవు (s1);

  size_t ss = __strnlen (s2, n);

  s1[ss] = '\0';
  జ్ఞాపకం_నకలు (s1, s2, ss);

  తిరిగి s;
}
#నిర్వచితమైతే STRNCAT_PRIMARY
strong_alias (STRNCAT, __strncat)
libc_hidden_def (__strncat)
#అయితే_ముగింపు
