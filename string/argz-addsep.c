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
__argz_add_sep (ಅಕ್ಷರ **argz, size_t *argz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *string, ಪೂರ್ಣಾಂಕ delim)
{
  size_t nlen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (string) + 1;

  ಆದರೆ (nlen > 1)
    {
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rp;
      ಅಕ್ಷರ *wp;

      *argz = (ಅಕ್ಷರ *) realloc (*argz, *argz_len + nlen);
      ಆದರೆ (*argz == ಖಾಲಿ)
	ಹಿಂತಿರುಗಿ ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      ಮಾಡು
	ಆದರೆ (*rp == delim)
	  {
	    ಆದರೆ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ಇಲ್ಲದಿದ್ದರೆ
	      --nlen;
	  }
	ಇಲ್ಲದಿದ್ದರೆ
	  *wp++ = *rp;
      ಆಗ (*rp++ != '\0');

      *argz_len += nlen;
    }

  ಹಿಂತಿರುಗಿ 0;
}
weak_alias (__argz_add_sep, argz_ಕೂಡಿಸು_sep)
