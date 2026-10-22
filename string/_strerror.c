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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libintl.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Return a string describing the errno code in ERRNUM.  */
ವರ್ಣ *
__strerror_r (ಪೂರ್ಣಾಙ್ಕ errnum, ವರ್ಣ *buf, size_t buflen)
{
  ವರ್ಣ *err = (ವರ್ಣ *) __get_errlist (errnum);
  ಯದಿ (__glibc_unlikely (err == ರಿಕ್ತ))
    {
      __snprintf (buf, buflen, "%s%d", _("Unknown error "), errnum);
      ಪ್ರತ್ಯಾಗಮ buf;
    }

  ಪ್ರತ್ಯಾಗಮ _(err);
}
weak_alias (__strerror_r, strerror_r)
libc_hidden_def (__strerror_r)
