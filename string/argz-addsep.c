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

#अन्तर्भाव <argz.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


error_t
__argz_add_sep (वर्ण **argz, माप_प्रकार *argz_len, ध्रुव वर्ण *string, पूर्णाङ्क delim)
{
  माप_प्रकार nlen = म_माप (string) + 1;

  यदि (nlen > 1)
    {
      ध्रुव वर्ण *rp;
      वर्ण *wp;

      *argz = (वर्ण *) पुनः_स्मृति (*argz, *argz_len + nlen);
      यदि (*argz == रिक्त)
	प्रत्यागम ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      कुरु
	यदि (*rp == delim)
	  {
	    यदि (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    अन्यथा
	      --nlen;
	  }
	अन्यथा
	  *wp++ = *rp;
      यावत् (*rp++ != '\0');

      *argz_len += nlen;
    }

  प्रत्यागम 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
