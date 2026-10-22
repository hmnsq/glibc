/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#ضمن <string.h>
#ضمن <stdlib.h>
#ضمن <random-bits.h>
#ضمن <unistd.h>

حرف *
strfry (حرف *string)
{
  ساكن صحيح init;
  ساكن بنية random_data rdata;

  إذا (!init)
    {
      ساكن حرف state[32];
      rdata.state = عدم;
      __initstate_r (random_bits (),
		     state, حجم (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  إذا (len > 0)
    لكل (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	حرف c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  إرجاع string;
}
