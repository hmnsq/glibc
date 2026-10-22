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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <random-bits.h>
#അന്തര്ഭാവ <unistd.h>

അക്ഷരം *
strfry (അക്ഷരം *string)
{
  സ്ഥിതം പൂർണ്ണസംഖ്യ init;
  സ്ഥിതം ഘടന random_data rdata;

  എങ്കിൽ (!init)
    {
      സ്ഥിതം അക്ഷരം state[32];
      rdata.state = ശൂന്യ;
      __initstate_r (random_bits (),
		     state, വലുപ്പം (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  എങ്കിൽ (len > 0)
    വേണ്ടി (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	അക്ഷരം c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  തിരികെ string;
}
