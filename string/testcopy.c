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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <support/support.h>

static ཧྲིལ
do_test (void)
{
  var_na *mem, *memp;
  var_na *rand_mem;
  var_na *lo_around, *hi_around;
  ཧྲིལ size, max_size;
  ཧྲིལ src_off, dst_off;
  ཧྲིལ i;
  ཧྲིལ space_around = 10;

  max_size = 256;

  mem = xmalloc (max_size + 2 * max_size + 2 * space_around);
  rand_mem = xmalloc (max_size);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  ཆེད་དུ (i = 0; i < max_size; i++)
    {
      ཧྲིལ x;
      do
	x = random ();
      སྐབས (x == 0);
      rand_mem[i] = x;
    }

  ཆེད་དུ (size = 0; size < max_size; size++)
    {
      printf("phase %d\n", size);
      ཆེད་དུ (src_off = 0; src_off <= 16; src_off++)
	{
	  ཆེད་དུ (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      ཆེད་དུ (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + size - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      ཆེད་དུ (i = 0; i < size; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      ཆེད་དུ (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + size - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, size);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      ཆེད་དུ (i = 0; i < size; i++)
		{
		  གལ་ཏེ (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      ཆེད་དུ (i = 1; i < space_around; i++)
		{
		  གལ་ཏེ (memp[dst_off - i] != lo_around[i])
		    abort ();
		  གལ་ཏེ (memp[dst_off + size - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  ཕྱིར 0;
}

#include <support/test-driver.c>
