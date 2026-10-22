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

#ضمن <argz.h>
#ضمن <errno.h>
#ضمن <stdlib.h>
#ضمن <string.h>


error_t
__argz_create_sep (ثابت حرف *string, صحيح delim, حرف **argz, size_t *len)
{
  size_t nlen = طول_رشته (string) + 1;

  إذا (nlen > 1)
    {
      ثابت حرف *rp;
      حرف *wp;

      *argz = (حرف *) حافظه_بده (nlen);
      إذا (*argz == عدم)
	أرجع ENOMEM;

      rp = string;
      wp = *argz;
      افعل
	إذا (*rp == delim)
	  {
	    إذا (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    وإلا
	      --nlen;
	  }
	وإلا
	  *wp++ = *rp;
      طالما (*rp++ != '\0');

      إذا (nlen == 0)
	{
	  حرر (*argz);
	  *argz = عدم;
	  *len = 0;
	}

      *len = nlen;
    }
  وإلا
    {
      *argz = عدم;
      *len = 0;
    }

  أرجع 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
