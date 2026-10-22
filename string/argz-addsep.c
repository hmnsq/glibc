/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#അന്തര്ഭാവ <argz.h>
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>


error_t
__argz_add_sep (അക്ഷരം **argz, size_t *argz_len, സ്ഥിരം അക്ഷരം *string, പൂർണ്ണസംഖ്യ delim)
{
  size_t nlen = strlen (string) + 1;

  എങ്കിൽ (nlen > 1)
    {
      സ്ഥിരം അക്ഷരം *rp;
      അക്ഷരം *wp;

      *argz = (അക്ഷരം *) realloc (*argz, *argz_len + nlen);
      എങ്കിൽ (*argz == ശൂന്യ)
	തിരികെ ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      ചെയ്യുക
	എങ്കിൽ (*rp == delim)
	  {
	    എങ്കിൽ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    അല്ലെങ്കിൽ
	      --nlen;
	  }
	അല്ലെങ്കിൽ
	  *wp++ = *rp;
      ആകുമ്പോൾ (*rp++ != '\0');

      *argz_len += nlen;
    }

  തിരികെ 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
