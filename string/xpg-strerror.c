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

#شامل <assert.h>
#شامل <errno.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
صحیح
__xpg_strerror_r (صحیح errnum, نویسه *buf, size_t buflen)
{
  ثابت نویسه *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  اگر (estr == buf)
    بازگشت EINVAL;
  وگرنه
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      اگر (buflen > 0)
	*((نویسه *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      بازگشت buflen <= estrlen ? ERANGE : 0;
    }
}
