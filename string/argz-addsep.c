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

#شامل <argz.h>
#شامل <errno.h>
#شامل <stdlib.h>
#شامل <string.h>


error_t
__argz_add_sep (نویسه **argz, size_t *argz_len, ثابت نویسه *string, صحیح delim)
{
  size_t nlen = strlen (string) + 1;

  اگر (nlen > 1)
    {
      ثابت نویسه *rp;
      نویسه *wp;

      *argz = (نویسه *) realloc (*argz, *argz_len + nlen);
      اگر (*argz == پوچ)
	بازگشت ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      انجامبده
	اگر (*rp == delim)
	  {
	    اگر (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    وگرنه
	      --nlen;
	  }
	وگرنه
	  *wp++ = *rp;
      وقتی (*rp++ != '\0');

      *argz_len += nlen;
    }

  بازگشت 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
