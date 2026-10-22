/* Copyright (C) 1990-2026 Free Software Foundation, Inc.
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

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/support.h>

स्थिर पूर्णांक
do_test (शून्य)
{
  अक्षर *mem, *memp;
  अक्षर *rand_mem;
  अक्षर *lo_around, *hi_around;
  पूर्णांक size, max_size;
  पूर्णांक src_off, dst_off;
  पूर्णांक i;
  पूर्णांक space_around = 10;

  max_size = 256;

  mem = xmalloc (max_size + 2 * max_size + 2 * space_around);
  rand_mem = xmalloc (max_size);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  साठी (i = 0; i < max_size; i++)
    {
      पूर्णांक x;
      करा
	x = random ();
      पर्यंत (x == 0);
      rand_mem[i] = x;
    }

  साठी (size = 0; size < max_size; size++)
    {
      म_लिखो("phase %d\n", size);
      साठी (src_off = 0; src_off <= 16; src_off++)
	{
	  साठी (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      साठी (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + size - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      साठी (i = 0; i < size; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      साठी (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + size - 1 + i];
		}

	      स_हटाओ (memp + dst_off, memp + src_off, size);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      साठी (i = 0; i < size; i++)
		{
		  जर (memp[dst_off + i] != rand_mem[i])
		    पात ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      साठी (i = 1; i < space_around; i++)
		{
		  जर (memp[dst_off - i] != lo_around[i])
		    पात ();
		  जर (memp[dst_off + size - 1 + i] != hi_around[i])
		    पात ();
		}
	    }
	}
    }

  माला_दो ("Test succeeded.");

  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
