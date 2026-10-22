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

#समावेश <assert.h>
#समावेश <errno.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
पूर्णांक
__xpg_strerror_r (पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen)
{
  स्थिर अक्षर *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  अगर (estr == buf)
    वापस EINVAL;
  अन्यथा
    {
      माप_प्रकार estrlen = म_माप (estr);

      /* Terminate the string in any case.  */
      अगर (buflen > 0)
	*((अक्षर *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      वापस buflen <= estrlen ? दुस्फल : 0;
    }
}
