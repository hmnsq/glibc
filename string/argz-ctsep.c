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

#ଅନ୍ତର୍ଭାଵ <argz.h>
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>


error_t
__argz_create_sep (ଅଚଳ ଅକ୍ଷର *string, ପୂର୍ଣ୍ଣସଂଖ୍ୟା delim, ଅକ୍ଷର **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  ଯଦି (nlen > 1)
    {
      ଅଚଳ ଅକ୍ଷର *rp;
      ଅକ୍ଷର *wp;

      *argz = (ଅକ୍ଷର *) malloc (nlen);
      ଯଦି (*argz == ଖାଲି)
	ଫେରନ୍ତୁ ENOMEM;

      rp = string;
      wp = *argz;
      କର
	ଯଦି (*rp == delim)
	  {
	    ଯଦି (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ଅନ୍ୟଥା
	      --nlen;
	  }
	ଅନ୍ୟଥା
	  *wp++ = *rp;
      ଯେତେବେଳେ (*rp++ != '\0');

      ଯଦି (nlen == 0)
	{
	  ମୁକ୍ତ (*argz);
	  *argz = ଖାଲି;
	  *len = 0;
	}

      *len = nlen;
    }
  ଅନ୍ୟଥା
    {
      *argz = ଖାଲି;
      *len = 0;
    }

  ଫେରନ୍ତୁ 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
