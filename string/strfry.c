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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <random-bits.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

ଅକ୍ଷର *
strfry (ଅକ୍ଷର *string)
{
  ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା init;
  ସ୍ଥିର ସଂରଚନା random_data rdata;

  ଯଦି (!init)
    {
      ସ୍ଥିର ଅକ୍ଷର state[32];
      rdata.state = ଖାଲି;
      __initstate_r (random_bits (),
		     state, ଆକାର (state), &rdata);
      init = 1;
    }

  size_t len = strlen (string);
  ଯଦି (len > 0)
    ପାଇଁ (size_t i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	ଅକ୍ଷର c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  ଫେରନ୍ତୁ string;
}
