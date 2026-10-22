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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <libintl.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
ଅକ୍ଷର *
__strerror_r (ପୂର୍ଣ୍ଣସଂଖ୍ୟା errnum, ଅକ୍ଷର *buf, size_t buflen)
{
  ଅକ୍ଷର *err = (ଅକ୍ଷର *) __get_errlist (errnum);
  ଯଦି (__glibc_unlikely (err == ଖାଲି))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      ଫେରନ୍ତୁ buf;
    }

  ଫେରନ୍ତୁ _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
