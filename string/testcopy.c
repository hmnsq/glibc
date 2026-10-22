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

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <support/support.h>

ساکن صحیح
do_test (خالی)
{
  حرف *mem, *memp;
  حرف *rand_mem;
  حرف *lo_around, *hi_around;
  صحیح سائز, max_سائز;
  صحیح src_off, dst_off;
  صحیح i;
  صحیح space_around = 10;

  max_سائز = 256;

  mem = xmalloc (max_سائز + 2 * max_سائز + 2 * space_around);
  rand_mem = xmalloc (max_سائز);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  برائے (i = 0; i < max_سائز; i++)
    {
      صحیح x;
      کرو
	x = random ();
      جب (x == 0);
      rand_mem[i] = x;
    }

  برائے (سائز = 0; سائز < max_سائز; سائز++)
    {
      لکھو("phase %d\n", سائز);
      برائے (src_off = 0; src_off <= 16; src_off++)
	{
	  برائے (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      برائے (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + سائز - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      برائے (i = 0; i < سائز; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      برائے (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + سائز - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, سائز);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      برائے (i = 0; i < سائز; i++)
		{
		  اگر (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      برائے (i = 1; i < space_around; i++)
		{
		  اگر (memp[dst_off - i] != lo_around[i])
		    abort ();
		  اگر (memp[dst_off + سائز - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  واپس 0;
}

#شامل <support/test-driver.c>
