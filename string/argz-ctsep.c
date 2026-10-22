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

#ಅನ್ತರ್ಭಾವ <argz.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>


error_t
__argz_create_sep (ಧ್ರುವ ವರ್ಣ *string, ಪೂರ್ಣಾಙ್ಕ delim, ವರ್ಣ **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  ಯದಿ (nlen > 1)
    {
      ಧ್ರುವ ವರ್ಣ *rp;
      ವರ್ಣ *wp;

      *argz = (ವರ್ಣ *) malloc (nlen);
      ಯದಿ (*argz == ರಿಕ್ತ)
	ಪ್ರತ್ಯಾಗಮ ENOMEM;

      rp = string;
      wp = *argz;
      ಕುರು
	ಯದಿ (*rp == delim)
	  {
	    ಯದಿ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ಅನ್ಯಥಾ
	      --nlen;
	  }
	ಅನ್ಯಥಾ
	  *wp++ = *rp;
      ಯಾವತ್ (*rp++ != '\0');

      ಯದಿ (nlen == 0)
	{
	  ಮುಕ್ತ (*argz);
	  *argz = ರಿಕ್ತ;
	  *len = 0;
	}

      *len = nlen;
    }
  ಅನ್ಯಥಾ
    {
      *argz = ರಿಕ್ತ;
      *len = 0;
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
