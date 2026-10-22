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

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/support.h>

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  అక్షరం *mem, *memp;
  అక్షరం *rand_mem;
  అక్షరం *lo_around, *hi_around;
  పూర్ణాంకం కొలత, max_కొలత;
  పూర్ణాంకం src_off, dst_off;
  పూర్ణాంకం i;
  పూర్ణాంకం space_around = 10;

  max_కొలత = 256;

  mem = xmalloc (max_కొలత + 2 * max_కొలత + 2 * space_around);
  rand_mem = xmalloc (max_కొలత);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  కొరకు (i = 0; i < max_కొలత; i++)
    {
      పూర్ణాంకం x;
      చేయి
	x = random ();
      అయితే (x == 0);
      rand_mem[i] = x;
    }

  కొరకు (కొలత = 0; కొలత < max_కొలత; కొలత++)
    {
      రాయి("phase %d\n", కొలత);
      కొరకు (src_off = 0; src_off <= 16; src_off++)
	{
	  కొరకు (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      కొరకు (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + కొలత - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      కొరకు (i = 0; i < కొలత; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      కొరకు (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + కొలత - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, కొలత);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      కొరకు (i = 0; i < కొలత; i++)
		{
		  ఒకవేళ (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      కొరకు (i = 1; i < space_around; i++)
		{
		  ఒకవేళ (memp[dst_off - i] != lo_around[i])
		    abort ();
		  ఒకవేళ (memp[dst_off + కొలత - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
