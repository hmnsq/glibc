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

#include <argz.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


error_t
__argz_add_sep (var_na **argz, size_t *argz_len, const var_na *string, puur_naa_nka delim)
{
  size_t nlen = strlen (string) + 1;

  ᬬᬾᬦ᭄ (nlen > 1)
    {
      const var_na *rp;
      var_na *wp;

      *argz = (var_na *) realloc (*argz, *argz_len + nlen);
      ᬬᬾᬦ᭄ (*argz == NULL)
	ᬯᬮᬶ ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      do
	ᬬᬾᬦ᭄ (*rp == delim)
	  {
	    ᬬᬾᬦ᭄ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ᬮᬶᬬ
	      --nlen;
	  }
	ᬮᬶᬬ
	  *wp++ = *rp;
      ᬲᭂᬤᭂᬮ (*rp++ != '\0');

      *argz_len += nlen;
    }

  ᬯᬮᬶ 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
