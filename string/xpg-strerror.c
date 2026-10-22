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

#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/param.h>


/* Fill buf with a string describing the errno code in ERRNUM.  */
പൂർണ്ണസംഖ്യ
__xpg_strerror_r (പൂർണ്ണസംഖ്യ errnum, അക്ഷരം *buf, size_t buflen)
{
  സ്ഥിരം അക്ഷരം *estr = __strerror_r (errnum, buf, buflen);

  /* We know that __strerror_r returns buf (with a dynamically computed
     string) if errnum is invalid, otherwise it returns a string whose
     storage has indefinite extent.  */
  എങ്കിൽ (estr == buf)
    തിരികെ EINVAL;
  അല്ലെങ്കിൽ
    {
      size_t estrlen = strlen (estr);

      /* Terminate the string in any case.  */
      എങ്കിൽ (buflen > 0)
	*((അക്ഷരം *) __mempcpy (buf, estr, MIN (buflen - 1, estrlen))) = '\0';

      തിരികെ buflen <= estrlen ? ERANGE : 0;
    }
}
