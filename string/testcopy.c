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

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/support.h>

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  അക്ഷരം *mem, *memp;
  അക്ഷരം *rand_mem;
  അക്ഷരം *lo_around, *hi_around;
  പൂർണ്ണസംഖ്യ size, max_size;
  പൂർണ്ണസംഖ്യ src_off, dst_off;
  പൂർണ്ണസംഖ്യ i;
  പൂർണ്ണസംഖ്യ space_around = 10;

  max_size = 256;

  mem = xmalloc (max_size + 2 * max_size + 2 * space_around);
  rand_mem = xmalloc (max_size);
  lo_around = xmalloc (space_around);
  hi_around = xmalloc (space_around);
  memp = mem + space_around;

  /* Fill RAND_MEM with random bytes, each non-zero.  */
  വേണ്ടി (i = 0; i < max_size; i++)
    {
      പൂർണ്ണസംഖ്യ x;
      ചെയ്യുക
	x = random ();
      ആകുമ്പോൾ (x == 0);
      rand_mem[i] = x;
    }

  വേണ്ടി (size = 0; size < max_size; size++)
    {
      printf("phase %d\n", size);
      വേണ്ടി (src_off = 0; src_off <= 16; src_off++)
	{
	  വേണ്ടി (dst_off = 0; dst_off <= 16; dst_off++)
	    {
	      /* Put zero around the intended destination, to check
		 that it's not clobbered.  */
	      വേണ്ടി (i = 1; i < space_around; i++)
		{
		  memp[dst_off - i] = 0;
		  memp[dst_off + size - 1 + i] = 0;
		}

	      /* Fill the source area with known contents.  */
	      വേണ്ടി (i = 0; i < size; i++)
		memp[src_off + i] = rand_mem[i];

	      /* Remember the contents around the destination area.
		 (It might not be what we wrote some lines above, since
		 the src area and the dst area overlap.)  */
	      വേണ്ടി (i = 1; i < space_around; i++)
		{
		  lo_around[i] = memp[dst_off - i];
		  hi_around[i] = memp[dst_off + size - 1 + i];
		}

	      memmove (memp + dst_off, memp + src_off, size);

	      /* Check that the destination area has the same
		 contents we wrote to the source area.  */
	      വേണ്ടി (i = 0; i < size; i++)
		{
		  എങ്കിൽ (memp[dst_off + i] != rand_mem[i])
		    abort ();
		}

	      /* Check that the area around the destination is not
		 clobbered.  */
	      വേണ്ടി (i = 1; i < space_around; i++)
		{
		  എങ്കിൽ (memp[dst_off - i] != lo_around[i])
		    abort ();
		  എങ്കിൽ (memp[dst_off + size - 1 + i] != hi_around[i])
		    abort ();
		}
	    }
	}
    }

  puts ("Test succeeded.");

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
