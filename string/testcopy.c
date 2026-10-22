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

স্থির পূর্ণাঙ্ক
do_test (শূন্য)
{
  বর্ণ *mem, *memp;
  বর্ণ *rand_mem;
  বর্ণ *lo_around, *hi_around;
  পূর্ণাঙ্ক size, max_size;
  পূর্ণাঙ্ক src_off, dst_off;
  পূর্ণাঙ্ক i;
  পূর্ণাঙ্ক space_around = 10;

  max_size = 256;

  mem = xmalloc (max_size + 2 * max_size + 2 * space_around);
  rand_mem = xmalloc (max_size);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  প্রতি (i = 0; i < max_size; i++)
    {
      পূর্ণাঙ্ক x;
      কুরু
	x = random ();
      যাবত্ (x == 0);
      rand_mem[i] = x;
    }

  প্রতি (size = 0; size < max_size; size++)
    {
      printf("phase %d\n", size);
      প্রতি (src_off = 0; src_off <= 16; src_off++)
	{
	  প্রতি (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      প্রতি (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + size - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      প্রতি (i = 0; i < size; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      প্রতি (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + size - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, size);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      প্রতি (i = 0; i < size; i++)
		{
		  যদি (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      প্রতি (i = 1; i < space_around; i++)
		{
		  যদি (memp[dst_off - i] != lo_around[i])
		    abort ();
		  যদি (memp[dst_off + size - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>
