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
#अन्तर्भाव <libintl.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
अक्षर *
__strerror_r (पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen)
{
  अक्षर *err = (अक्षर *) __get_errlist (errnum);
  जर (__glibc_unlikely (err == रिक्त))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      परत buf;
    }

  परत _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
