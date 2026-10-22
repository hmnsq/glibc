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

#অন্তর্ভাব <argz.h>
#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>


error_t
__argz_add_sep (অক্ষর **argz, size_t *argz_len, ধ্রুবক অক্ষর *string, পূর্ণসংখ্যা delim)
{
  size_t nlen = strlen (string) + 1;

  যদি (nlen > 1)
    {
      ধ্রুবক অক্ষর *rp;
      অক্ষর *wp;

      *argz = (অক্ষর *) realloc (*argz, *argz_len + nlen);
      যদি (*argz == ফাঁকা)
	ফেরত ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      করো
	যদি (*rp == delim)
	  {
	    যদি (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    অন্যথা
	      --nlen;
	  }
	অন্যথা
	  *wp++ = *rp;
      যখন (*rp++ != '\0');

      *argz_len += nlen;
    }

  ফেরত 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
