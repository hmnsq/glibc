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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libintl.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
বর্ণ *
__strerror_r (পূর্ণাঙ্ক errnum, বর্ণ *buf, size_t buflen)
{
  বর্ণ *err = (বর্ণ *) __get_errlist (errnum);
  যদি (__glibc_unlikely (err == রিক্ত))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      প্রত্যাগম buf;
    }

  প্রত্যাগম _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
