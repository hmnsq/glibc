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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <random-bits.h>
#অন্তর্ভাব <unistd.h>

বর্ণ *
strfry (বর্ণ *string)
{
  স্থির পূর্ণাঙ্ক init;
  স্থির সংরচনা random_data rdata;

  যদি (!init)
    {
      স্থির বর্ণ state[32];
      rdata.state = রিক্ত;
      __initstate_r (random_bits (),
		     state, পরিমাণ (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  যদি (len > 0)
    প্রতি (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	বর্ণ c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  প্রত্যাগম string;
}
