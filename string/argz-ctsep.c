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

#અન્તર્ભાવ <argz.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>


error_t
__argz_create_sep (અચલ અક્ષર *string, પૂર્ણાંક delim, અક્ષર **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  જો (nlen > 1)
    {
      અચલ અક્ષર *rp;
      અક્ષર *wp;

      *argz = (અક્ષર *) malloc (nlen);
      જો (*argz == ખાલી)
	પાછા ENOMEM;

      rp = string;
      wp = *argz;
      કરો
	જો (*rp == delim)
	  {
	    જો (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    નહીંતર
	      --nlen;
	  }
	નહીંતર
	  *wp++ = *rp;
      જ્યારે (*rp++ != '\0');

      જો (nlen == 0)
	{
	  મુક્ત (*argz);
	  *argz = ખાલી;
	  *len = 0;
	}

      *len = nlen;
    }
  નહીંતર
    {
      *argz = ખાલી;
      *len = 0;
    }

  પાછા 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
