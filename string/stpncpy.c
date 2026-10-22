/* Copyright (C) 1993-2026 Free Software Foundation, Inc.
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

#నిర్వచితమైతే HAVE_CONFIG_H
# include <config.h>
#అయితే_ముగింపు

#నిర్వచితమైతే _LIBC
# include <string.h>
#లేకపోతే
# include <sys/types.h>
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# లేకపోతే
#  define STPNCPY	stpncpy
# endif
#అయితే_ముగింపు

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
అక్షరం *
STPNCPY (అక్షరం *dest, స్థిరరాశి అక్షరం *src, size_t n)
{
  size_t కొలత = __strnlen (src, n);
  జ్ఞాపకం_నకలు (dest, src, కొలత);
  dest += కొలత;
  ఒకవేళ (కొలత == n)
    తిరిగి dest;
  తిరిగి memset (dest, '\0', n - కొలత);
}
#నిర్వచితమైతే weak_alias
libc_hidden_def (__stpncpy)
#అయితే_ముగింపు
