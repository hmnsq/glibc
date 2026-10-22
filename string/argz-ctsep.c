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

#include <argz.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


error_t
__argz_create_sep (const var_na *string, ຈຳນວນເຕັມ delim, var_na **argz, size_t *len)
{
  size_t nlen = strlen (string) + 1;

  ຖ້າ (nlen > 1)
    {
      const var_na *rp;
      var_na *wp;

      *argz = (var_na *) malloc (nlen);
      ຖ້າ (*argz == NULL)
	ສົ່ງຄືນ ENOMEM;

      rp = string;
      wp = *argz;
      do
	ຖ້າ (*rp == delim)
	  {
	    ຖ້າ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    ບໍ່ດັ່ງນັ້ນ
	      --nlen;
	  }
	ບໍ່ດັ່ງນັ້ນ
	  *wp++ = *rp;
      ໃນຂະນະທີ່ (*rp++ != '\0');

      ຖ້າ (nlen == 0)
	{
	  free (*argz);
	  *argz = NULL;
	  *len = 0;
	}

      *len = nlen;
    }
  ບໍ່ດັ່ງນັ້ນ
    {
      *argz = NULL;
      *len = 0;
    }

  ສົ່ງຄືນ 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
