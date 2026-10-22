/* Find the length of STRING, but scan at most MAXLEN characters.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <https://www.gnu.org/licenses/>.  */

#అన్తర్భావ <string.h>

/* Find the length of S, but scan at most MAXLEN characters.  If no
   '\0' terminator is found in that many characters, return MAXLEN.  */

#నిర్వచితమైతే STRNLEN
# define __strnlen STRNLEN
#అయితే_ముగింపు

size_t
__strnlen (స్థిరరాశి అక్షరం *str, size_t maxlen)
{
  స్థిరరాశి అక్షరం *దొరికింది = memchr (str, '\0', maxlen);
  తిరిగి దొరికింది ? దొరికింది - str : maxlen;
}

#నిర్వచితం_కాకపోతే STRNLEN
weak_alias (__strnlen, strnlen)
libc_hidden_def (__strnlen)
libc_hidden_def (strnlen)
#అయితే_ముగింపు
