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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <support/support.h>

স্থির পূর্ণসংখ্যা
do_test (শূন্য)
{
  অক্ষর *mem, *memp;
  অক্ষর *rand_mem;
  অক্ষর *lo_around, *hi_around;
  পূর্ণসংখ্যা আকার_2, max_আকার;
  পূর্ণসংখ্যা src_off, dst_off;
  পূর্ণসংখ্যা i;
  পূর্ণসংখ্যা space_around = 10;

  max_আকার = 256;

  mem = xmalloc (max_আকার + 2 * max_আকার + 2 * space_around);
  rand_mem = xmalloc (max_আকার);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  জন্য (i = 0; i < max_আকার; i++)
    {
      পূর্ণসংখ্যা x;
      করো
	x = random ();
      যখন (x == 0);
      rand_mem[i] = x;
    }

  জন্য (আকার_2 = 0; আকার_2 < max_আকার; আকার_2++)
    {
      printf("phase %d\n", আকার_2);
      জন্য (src_off = 0; src_off <= 16; src_off++)
	{
	  জন্য (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      জন্য (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + আকার_2 - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      জন্য (i = 0; i < আকার_2; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      জন্য (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + আকার_2 - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, আকার_2);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      জন্য (i = 0; i < আকার_2; i++)
		{
		  যদি (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      জন্য (i = 1; i < space_around; i++)
		{
		  যদি (memp[dst_off - i] != lo_around[i])
		    abort ();
		  যদি (memp[dst_off + আকার_2 - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
