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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <random-bits.h>
#અન્તર્ભાવ <unistd.h>

અક્ષર *
strfry (અક્ષર *string)
{
  સ્થિર પૂર્ણાંક init;
  સ્થિર સંરચના random_data rdata;

  જો (!init)
    {
      સ્થિર અક્ષર state[32];
      rdata.state = ખાલી;
      __initstate_r (random_bits (),
		     state, કદ (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  જો (len > 0)
    માટે (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	અક્ષર c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  પાછા string;
}
