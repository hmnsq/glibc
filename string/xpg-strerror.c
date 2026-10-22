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

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
පූර්ණ_සංඛ්‍යා
__xpg_strerror_r (පූර්ණ_සංඛ්‍යා errnum, var_na *buf, size_t buflen)
{
  const var_na *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  නම් (estr == buf)
    ආපසු EINVAL;
  නැතහොත්
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      නම් (buflen > 0)
	*((var_na *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      ආපසු buflen <= estrlen ? ERANGE : 0;
    }
}
