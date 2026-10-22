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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/support.h>

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਅੱਖਰ *mem, *memp;
  ਅੱਖਰ *rand_mem;
  ਅੱਖਰ *lo_around, *hi_around;
  ਪੂਰਨ ਮਾਪ, max_ਮਾਪ;
  ਪੂਰਨ src_off, dst_off;
  ਪੂਰਨ i;
  ਪੂਰਨ space_around = 10;

  max_ਮਾਪ = 256;

  mem = xmalloc (max_ਮਾਪ + 2 * max_ਮਾਪ + 2 * space_around);
  rand_mem = xmalloc (max_ਮਾਪ);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  ਲਈ (i = 0; i < max_ਮਾਪ; i++)
    {
      ਪੂਰਨ x;
      ਕਰੋ
	x = random ();
      ਜਦੋਂ (x == 0);
      rand_mem[i] = x;
    }

  ਲਈ (ਮਾਪ = 0; ਮਾਪ < max_ਮਾਪ; ਮਾਪ++)
    {
      ਲਿਖੋ("phase %d\n", ਮਾਪ);
      ਲਈ (src_off = 0; src_off <= 16; src_off++)
	{
	  ਲਈ (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      ਲਈ (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + ਮਾਪ - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      ਲਈ (i = 0; i < ਮਾਪ; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      ਲਈ (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + ਮਾਪ - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, ਮਾਪ);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      ਲਈ (i = 0; i < ਮਾਪ; i++)
		{
		  ਜੇ (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      ਲਈ (i = 1; i < space_around; i++)
		{
		  ਜੇ (memp[dst_off - i] != lo_around[i])
		    abort ();
		  ਜੇ (memp[dst_off + ਮਾਪ - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
