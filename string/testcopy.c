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

#समावेश <stdlib.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <support/support.h>

अटल पूर्णांक
do_test (व्योम)
{
  अक्षर *mem, *memp;
  अक्षर *rand_mem;
  अक्षर *lo_around, *hi_around;
  पूर्णांक आकार, max_आकार;
  पूर्णांक src_off, dst_off;
  पूर्णांक i;
  पूर्णांक space_around = 10;

  max_आकार = 256;

  mem = xmalloc (max_आकार + 2 * max_आकार + 2 * space_around);
  rand_mem = xmalloc (max_आकार);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  क्रम (i = 0; i < max_आकार; i++)
    {
      पूर्णांक x;
      करो
	x = random ();
      जबतक (x == 0);
      rand_mem[i] = x;
    }

  क्रम (आकार = 0; आकार < max_आकार; आकार++)
    {
      म_लिखो("phase %d\n", आकार);
      क्रम (src_off = 0; src_off <= 16; src_off++)
	{
	  क्रम (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      क्रम (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + आकार - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      क्रम (i = 0; i < आकार; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      क्रम (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + आकार - 1 + i];
		}

	      स_हटाओ (memp + dst_off, memp + src_off, आकार);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      क्रम (i = 0; i < आकार; i++)
		{
		  अगर (memp[dst_off + i] != rand_mem[i])
		    पात ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      क्रम (i = 1; i < space_around; i++)
		{
		  अगर (memp[dst_off - i] != lo_around[i])
		    पात ();
		  अगर (memp[dst_off + आकार - 1 + i] != hi_around[i])
		    पात ();
		}
	    }
	}
    }

  माला_दो ("Test succeeded.");

  वापस 0;
}

#समावेश <support/test-driver.c>
