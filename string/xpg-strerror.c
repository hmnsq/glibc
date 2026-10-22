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

#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
પૂર્ણાંક
__xpg_strerror_r (પૂર્ણાંક errnum, અક્ષર *buf, size_t buflen)
{
  અચલ અક્ષર *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  જો (estr == buf)
    પાછા EINVAL;
  નહીંતર
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      જો (buflen > 0)
	*((અક્ષર *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      પાછા buflen <= estrlen ? ERANGE : 0;
    }
}
