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

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/support.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಅಕ್ಷರ *mem, *memp;
  ಅಕ್ಷರ *rand_mem;
  ಅಕ್ಷರ *lo_around, *hi_around;
  ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, max_ಗಾತ್ರ;
  ಪೂರ್ಣಾಂಕ src_off, dst_off;
  ಪೂರ್ಣಾಂಕ i;
  ಪೂರ್ಣಾಂಕ space_around = 10;

  max_ಗಾತ್ರ = 256;

  mem = xmalloc (max_ಗಾತ್ರ + 2 * max_ಗಾತ್ರ + 2 * space_around);
  rand_mem = xmalloc (max_ಗಾತ್ರ);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  ಗಾಗಿ (i = 0; i < max_ಗಾತ್ರ; i++)
    {
      ಪೂರ್ಣಾಂಕ x;
      ಮಾಡು
	x = random ();
      ಆಗ (x == 0);
      rand_mem[i] = x;
    }

  ಗಾಗಿ (ಗಾತ್ರ_2 = 0; ಗಾತ್ರ_2 < max_ಗಾತ್ರ; ಗಾತ್ರ_2++)
    {
      ಬರೆ("phase %d\n", ಗಾತ್ರ_2);
      ಗಾಗಿ (src_off = 0; src_off <= 16; src_off++)
	{
	  ಗಾಗಿ (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      ಗಾಗಿ (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + ಗಾತ್ರ_2 - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      ಗಾಗಿ (i = 0; i < ಗಾತ್ರ_2; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      ಗಾಗಿ (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + ಗಾತ್ರ_2 - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, ಗಾತ್ರ_2);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      ಗಾಗಿ (i = 0; i < ಗಾತ್ರ_2; i++)
		{
		  ಆದರೆ (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      ಗಾಗಿ (i = 1; i < space_around; i++)
		{
		  ಆದರೆ (memp[dst_off - i] != lo_around[i])
		    abort ();
		  ಆದರೆ (memp[dst_off + ಗಾತ್ರ_2 - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
