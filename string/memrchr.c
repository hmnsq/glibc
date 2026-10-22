/* memrchr -- find the last occurrence of a byte in a memory block
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <string-fzb.h>
#అన్తర్భావ <string-fzc.h>
#అన్తర్భావ <string-fzi.h>
#అన్తర్భావ <string-shift.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <libc-pointer-arith.h>

#నిర్వచనం_రద్దు __memrchr
#నిర్వచనం_రద్దు memrchr

#నిర్వచితమైతే MEMRCHR
# define __memrchr MEMRCHR
#అయితే_ముగింపు

శూన్య *
__memrchr (స్థిరరాశి శూన్య *s, పూర్ణాంకం c_లోపల, size_t n)
{
  ఒకవేళ (__glibc_unlikely (n == 0))
    తిరిగి ఖాళీ;

  స్థిరరాశి op_t *మాట_ptr = (స్థిరరాశి op_t *) PTR_ALIGN_పైకి (s + n, పరిమాణం (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t మాట = *--మాట_ptr;
  op_t repeated_c = repeat_బైట్లు (c_లోపల);

  /* Compute the address of the word containing the initial byte. */
  స్థిరరాశి op_t *sword = (స్థిరరాశి op_t *) PTR_ALIGN_కిందికి (s, పరిమాణం (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  కనుగొను_t ముసుగు = జరుపు_కనుగొను_చివరి (కనుగొను_eq_all (మాట, repeated_c), s_int);
  ఒకవేళ (ముసుగు != 0)
    {
      అక్షరం *ret = (అక్షరం *) మాట_ptr + సూచీ_చివరి (ముసుగు);
      తిరిగి ret >= (అక్షరం *) s ? ret : ఖాళీ;
    }
  ఒకవేళ (మాట_ptr == sword)
    తిరిగి ఖాళీ;
  మాట = *--మాట_ptr;

  అయితే (మాట_ptr != sword)
    {
      ఒకవేళ (has_eq (మాట, repeated_c))
	తిరిగి (అక్షరం *) మాట_ptr + సూచీ_చివరి_eq (మాట, repeated_c);
      మాట = *--మాట_ptr;
    }

  ఒకవేళ (has_eq (మాట, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      అక్షరం *ret = (అక్షరం *) మాట_ptr + సూచీ_చివరి_eq (మాట, repeated_c);
      ఒకవేళ (ret >= (అక్షరం *) s)
	తిరిగి ret;
    }
  తిరిగి ఖాళీ;
}
#నిర్వచితం_కాకపోతే MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#అయితే_ముగింపు
