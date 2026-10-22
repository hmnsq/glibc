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
__argz_create_sep (ধ্রুব বর্ণ *string, পূর্ণাঙ্ক delim, বর্ণ **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  যদি (nlen > 1)
    {
      ধ্রুব বর্ণ *rp;
      বর্ণ *wp;

      *argz = (বর্ণ *) malloc (nlen);
      যদি (*argz == রিক্ত)
	প্রত্যাগম ENOMEM;

      rp = string;
      wp = *argz;
      কুরু
	যদি (*rp == delim)
	  {
	    যদি (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    অন্যথা
	      --nlen;
	  }
	অন্যথা
	  *wp++ = *rp;
      যাবত্ (*rp++ != '\0');

      যদি (nlen == 0)
	{
	  মুক্ত (*argz);
	  *argz = রিক্ত;
	  *len = 0;
	}

      *len = nlen;
    }
  অন্যথা
    {
      *argz = রিক্ত;
      *len = 0;
    }

  প্রত্যাগম 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
