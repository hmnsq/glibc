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
__argz_create_sep (ধ্রুবক অক্ষর *string, পূর্ণসংখ্যা delim, অক্ষর **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  যদি (nlen > 1)
    {
      ধ্রুবক অক্ষর *rp;
      অক্ষর *wp;

      *argz = (অক্ষর *) malloc (nlen);
      যদি (*argz == ফাঁকা)
	ফেরত ENOMEM;

      rp = string;
      wp = *argz;
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

      যদি (nlen == 0)
	{
	  মুক্ত (*argz);
	  *argz = ফাঁকা;
	  *len = 0;
	}

      *len = nlen;
    }
  অন্যথা
    {
      *argz = ফাঁকা;
      *len = 0;
    }

  ফেরত 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
