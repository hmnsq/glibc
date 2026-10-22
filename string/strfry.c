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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <random-bits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

ਅੱਖਰ *
strfry (ਅੱਖਰ *string)
{
  ਸਥਿਰ ਪੂਰਨ init;
  ਸਥਿਰ ਬਣਤਰ random_data rdata;

  ਜੇ (!init)
    {
      ਸਥਿਰ ਅੱਖਰ state[32];
      rdata.state = ਨਿਰਾ;
      __initstate_r (random_ਬਿੱਟ (),
		     state, ਆਕਾਰ (state), &rdata);
      init = 1;
    }

  size_t len = ਲੜੀ_ਲੰਬਾਈ (string);
  ਜੇ (len > 0)
    ਲਈ (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	ਅੱਖਰ c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  ਵਾਪਸ string;
}
