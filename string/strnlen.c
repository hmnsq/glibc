/* Find the length of STRING, but scan at most MAXLEN characters.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <https://www.gnu.org/licenses/>.  */

#अन्तर्भाव <string.h>

/* Find the length of S, but scan at most MAXLEN characters.  If no
   '\0' terminator is found in that many characters, return MAXLEN.  */

#यदि_परिभाषितम् STRNLEN
# define __strnlen STRNLEN
#यदि_अन्तः

size_t
__strnlen (ध्रुव वर्ण *str, size_t maxlen)
{
  ध्रुव वर्ण *प्राप्तम् = memchr (str, '\0', maxlen);
  प्रत्यागम प्राप्तम् ? प्राप्तम् - str : maxlen;
}

#यदि_अपरिभाषितम् STRNLEN
weak_alias (__strnlen, strnlen)
libc_hidden_def (__strnlen)
libc_hidden_def (strnlen)
#यदि_अन्तः
