/* Copyright (C) 1993-2026 Free Software Foundation, Inc.
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

#यदि_परिभाषितम् HAVE_CONFIG_H
# include <config.h>
#यदि_अन्तः

#यदि_परिभाषितम् _LIBC
# include <string.h>
#अन्यथा
# include <sys/types.h>
#यदि_अन्तः

#यदि_अपरिभाषितम् STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# अन्यथा
#  define STPNCPY	stpncpy
# endif
#यदि_अन्तः

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
वर्ण *
STPNCPY (वर्ण *dest, ध्रुव वर्ण *src, size_t n)
{
  size_t आकार = __strnlen (src, n);
  स्मृतिं_प्रतिलिख (dest, src, आकार);
  dest += आकार;
  यदि (आकार == n)
    प्रत्यागम dest;
  प्रत्यागम स्मृतिं_पूरय (dest, '\0', n - आकार);
}
#यदि_परिभाषितम् weak_alias
libc_hidden_def (__stpncpy)
#यदि_अन्तः
