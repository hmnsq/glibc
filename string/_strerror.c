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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libintl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
ਅੱਖਰ *
__strerror_r (ਪੂਰਨ errnum, ਅੱਖਰ *buf, size_t buflen)
{
  ਅੱਖਰ *err = (ਅੱਖਰ *) __get_errlist (errnum);
  ਜੇ (__glibc_unlikely (err == ਨਿਰਾ))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      ਵਾਪਸ buf;
    }

  ਵਾਪਸ _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
