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

#ಅನ್ತರ್ಭಾವ <string.h>

/* Find the length of S, but scan at most MAXLEN characters.  If no
   '\0' terminator is found in that many characters, return MAXLEN.  */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ STRNLEN
# define __strnlen STRNLEN
#ಆದರೆ_ಅಂತ್ಯ

size_t
__strnlen (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, size_t maxlen)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಿಕ್ಕಿತು = memchr (str, '\0', maxlen);
  ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು ? ಸಿಕ್ಕಿತು - str : maxlen;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRNLEN
weak_alias (__strnlen, strnlen)
libc_hidden_def (__strnlen)
libc_hidden_def (strnlen)
#ಆದರೆ_ಅಂತ್ಯ
