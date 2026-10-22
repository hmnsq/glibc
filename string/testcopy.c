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

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <support/support.h>

ساكن صحيح
do_test (فراغ)
{
  حرف *mem, *memp;
  حرف *rand_mem;
  حرف *lo_around, *hi_around;
  صحيح ناپ, max_ناپ;
  صحيح src_off, dst_off;
  صحيح i;
  صحيح space_around = 10;

  max_ناپ = 256;

  mem = xmalloc (max_ناپ + 2 * max_ناپ + 2 * space_around);
  rand_mem = xmalloc (max_ناپ);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  لكل (i = 0; i < max_ناپ; i++)
    {
      صحيح x;
      افعل
	x = random ();
      طالما (x == 0);
      rand_mem[i] = x;
    }

  لكل (ناپ = 0; ناپ < max_ناپ; ناپ++)
    {
      لکھو("phase %d\n", ناپ);
      لكل (src_off = 0; src_off <= 16; src_off++)
	{
	  لكل (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      لكل (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + ناپ - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      لكل (i = 0; i < ناپ; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      لكل (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + ناپ - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, ناپ);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      لكل (i = 0; i < ناپ; i++)
		{
		  إذا (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      لكل (i = 1; i < space_around; i++)
		{
		  إذا (memp[dst_off - i] != lo_around[i])
		    abort ();
		  إذا (memp[dst_off + ناپ - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  أرجع 0;
}

#ضمن <support/test-driver.c>
