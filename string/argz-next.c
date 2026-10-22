/* Iterate through the elements of an argz block.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <argz.h>
#అన్తర్భావ <string.h>

అక్షరం *
__argz_next (స్థిరరాశి అక్షరం *argz, size_t argz_len, స్థిరరాశి అక్షరం *నమోదు_2)
{
  ఒకవేళ (నమోదు_2)
    {
      ఒకవేళ (నమోదు_2 < argz + argz_len)
	నమోదు_2 = strchr (నమోదు_2, '\0') + 1;

      తిరిగి నమోదు_2 >= argz + argz_len ? ఖాళీ : (అక్షరం *) నమోదు_2;
    }
  లేకపోతే
    ఒకవేళ (argz_len > 0)
      తిరిగి (అక్షరం *) argz;
    లేకపోతే
      తిరిగి ఖాళీ;
}
libc_hidden_def (__argz_next)
static_weak_alias (__argz_next, argz_తదుపరి)
libc_hidden_weak (argz_తదుపరి)
