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

#অন্তর্ভাৱ <assert.h>
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
পূর্ণাঙ্ক
__xpg_strerror_r (পূর্ণাঙ্ক errnum, ৱর্ণ *buf, size_t buflen)
{
  ধ্রুৱ ৱর্ণ *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  যদি (estr == buf)
    ঘূৰাই EINVAL;
  অন্যথা
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      যদি (buflen > 0)
	*((ৱর্ণ *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      ঘূৰাই buflen <= estrlen ? ERANGE : 0;
    }
}
