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

#समावेश <string.h>
#समावेश <stdlib.h>
#समावेश <random-bits.h>
#समावेश <unistd.h>

अक्षर *
strfry (अक्षर *string)
{
  अटल पूर्णांक init;
  अटल काष्ठा random_data rdata;

  अगर (!init)
    {
      अटल अक्षर state[32];
      rdata.state = शून्य;
      __initstate_r (random_bits (),
		     state, माप (state), &rdata);
      init = 1;
    }

  माप_प्रकार len = म_माप (string);
  अगर (len > 0)
    क्रम (माप_प्रकार i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	अक्षर c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  वापस string;
}
