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

#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <random-bits.h>
#अन्तर्भाव <unistd.h>

अक्षर *
strfry (अक्षर *string)
{
  स्थिर पूर्णांक init;
  स्थिर संरचना random_data rdata;

  जर (!init)
    {
      स्थिर अक्षर state[32];
      rdata.state = रिक्त;
      __initstate_r (random_bits (),
		     state, आकार (state), &rdata);
      init = 1;
    }

  माप_प्रकार len = म_माप (string);
  जर (len > 0)
    साठी (माप_प्रकार i = 0; i < len - 1; ++i)
      {
	int32_t j;
	__random_r (&rdata, &j);
	j = j % (len - i) + i;

	अक्षर c = string[i];
	string[i] = string[j];
	string[j] = c;
      }

  परत string;
}
