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

#அந்தர்பாவ <argz.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>


error_t
__argz_add_sep (எழுத்து **argz, size_t *argz_len, மாறிலி எழுத்து *string, முழு delim)
{
  size_t nlen = strlen (string) + 1;

  எனில் (nlen > 1)
    {
      மாறிலி எழுத்து *rp;
      எழுத்து *wp;

      *argz = (எழுத்து *) realloc (*argz, *argz_len + nlen);
      எனில் (*argz == வெற்று)
	திரும்பு ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      செய்
	எனில் (*rp == delim)
	  {
	    எனில் (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    இல்லையெனில்
	      --nlen;
	  }
	இல்லையெனில்
	  *wp++ = *rp;
      போது (*rp++ != '\0');

      *argz_len += nlen;
    }

  திரும்பு 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
