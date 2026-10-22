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

#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <libintl.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
ৱর্ণ *
__strerror_r (পূর্ণাঙ্ক errnum, ৱর্ণ *buf, size_t buflen)
{
  ৱর্ণ *err = (ৱর্ণ *) __get_errlist (errnum);
  যদি (__glibc_unlikely (err == রিক্ত))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      ঘূৰাই buf;
    }

  ঘূৰাই _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
