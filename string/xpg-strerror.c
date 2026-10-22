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

#ضمن <assert.h>
#ضمن <errno.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
صحيح
__xpg_strerror_r (صحيح errnum, حرف *buf, size_t buflen)
{
  ثابت حرف *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  إذا (estr == buf)
    إرجاع EINVAL;
  وإلا
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      إذا (buflen > 0)
	*((حرف *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      إرجاع buflen <= estrlen ? ERANGE : 0;
    }
}
