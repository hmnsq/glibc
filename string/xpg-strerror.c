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

#అన్తర్భావ <assert.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
పూర్ణాంకం
__xpg_strerror_r (పూర్ణాంకం errnum, అక్షరం *buf, size_t buflen)
{
  స్థిరరాశి అక్షరం *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  ఒకవేళ (estr == buf)
    తిరిగి EINVAL;
  లేకపోతే
    {
      size_t estrlen = అక్షరశ్రేణి_పొడవు (estr);

      /* Terminate the string in any case.  */
      ఒకవేళ (buflen > 0)
	*((అక్షరం *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      తిరిగి buflen <= estrlen ? ERANGE : 0;
    }
}
