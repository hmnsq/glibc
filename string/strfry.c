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

ಅಕ್ಷರ *
strfry (ಅಕ್ಷರ *string)
{
  ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ init;
  ಸ್ಥಿರ ರಚನೆ random_data rdata;

  ಆದರೆ (!init)
    {
      ಸ್ಥಿರ ಅಕ್ಷರ state[32];
      rdata.state = ಖಾಲಿ;
      __initstate_r (random_ಬಿಟ್ಟುಗಳು (),
		     state, ಗಾತ್ರ (state), &rdata);
      init = 1;
    }

  size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (string);
  ಆದರೆ (len > 0)
    ಗಾಗಿ (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	ಅಕ್ಷರ c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  ಹಿಂತಿರುಗಿ string;
}
