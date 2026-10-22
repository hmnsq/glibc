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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <random-bits.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

ವರ್ಣ *
strfry (ವರ್ಣ *string)
{
  ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ init;
  ಸ್ಥಿರ ಸಂರಚನಾ random_data rdata;

  ಯದಿ (!init)
    {
      ಸ್ಥಿರ ವರ್ಣ state[32];
      rdata.state = ರಿಕ್ತ;
      __initstate_r (random_bits (),
		     state, ಪರಿಮಾಣ (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  ಯದಿ (len > 0)
    ಪ್ರತಿ (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	ವರ್ಣ c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  ಪ್ರತ್ಯಾಗಮ string;
}
