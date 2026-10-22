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

#ਅਨ੍ਤਰ੍ਭਾਵ <argz.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>


error_t
__argz_add_sep (ਅੱਖਰ **argz, size_t *argz_len, ਅਚਲ ਅੱਖਰ *string, ਪੂਰਨ delim)
{
  size_t nlen = ਲੜੀ_ਲੰਬਾਈ (string) + 1;

  ਜੇ (nlen > 1)
    {
      ਅਚਲ ਅੱਖਰ *rp;
      ਅੱਖਰ *wp;

      *argz = (ਅੱਖਰ *) realloc (*argz, *argz_len + nlen);
      ਜੇ (*argz == ਨਿਰਾ)
	ਵਾਪਸ ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      ਕਰੋ
	ਜੇ (*rp == delim)
	  {
	    ਜੇ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ਨਹੀਂਤਾਂ
	      --nlen;
	  }
	ਨਹੀਂਤਾਂ
	  *wp++ = *rp;
      ਜਦੋਂ (*rp++ != '\0');

      *argz_len += nlen;
    }

  ਵਾਪਸ 0;
}
weak_alias (__argz_add_sep, argz_ਜੋੜੋ_sep)
