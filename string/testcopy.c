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

#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <support/support.h>

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  અક્ષર *mem, *memp;
  અક્ષર *rand_mem;
  અક્ષર *lo_around, *hi_around;
  પૂર્ણાંક size, max_size;
  પૂર્ણાંક src_off, dst_off;
  પૂર્ણાંક i;
  પૂર્ણાંક space_around = 10;

  max_size = 256;

  mem = xmalloc (max_size + 2 * max_size + 2 * space_around);
  rand_mem = xmalloc (max_size);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  માટે (i = 0; i < max_size; i++)
    {
      પૂર્ણાંક x;
      કરો
	x = random ();
      જ્યારે (x == 0);
      rand_mem[i] = x;
    }

  માટે (size = 0; size < max_size; size++)
    {
      printf("phase %d\n", size);
      માટે (src_off = 0; src_off <= 16; src_off++)
	{
	  માટે (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      માટે (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + size - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      માટે (i = 0; i < size; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      માટે (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + size - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, size);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      માટે (i = 0; i < size; i++)
		{
		  જો (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      માટે (i = 1; i < space_around; i++)
		{
		  જો (memp[dst_off - i] != lo_around[i])
		    abort ();
		  જો (memp[dst_off + size - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
