/* Scan memory for a character.  Generic version
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

#అన్తర్భావ <libc-pointer-arith.h>
#అన్తర్భావ <string-fzb.h>
#అన్తర్భావ <string-fzc.h>
#అన్తర్భావ <string-fzi.h>
#అన్తర్భావ <string-shift.h>
#అన్తర్భావ <string.h>

#నిర్వచనం_రద్దు memchr

#నిర్వచితమైతే MEMCHR
# define __memchr MEMCHR
#అయితే_ముగింపు

స్థిర __always_inline స్థిరరాశి అక్షరం *
sadd (uintptr_t x, uintptr_t y)
{
  తిరిగి (స్థిరరాశి అక్షరం *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
శూన్య *
__memchr (శూన్య స్థిరరాశి *s, పూర్ణాంకం c_లోపల, size_t n)
{
  ఒకవేళ (__glibc_unlikely (n == 0))
    తిరిగి ఖాళీ;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  స్థిరరాశి op_t *మాట_ptr = PTR_ALIGN_కిందికి (s, పరిమాణం (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t మాట = *మాట_ptr;
  op_t repeated_c = repeat_బైట్లు (c_లోపల);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  స్థిరరాశి అక్షరం *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  స్థిరరాశి op_t *lword = (స్థిరరాశి op_t *) PTR_ALIGN_కిందికి (lbyte, పరిమాణం (op_t));

  కనుగొను_t ముసుగు = జరుపు_కనుగొను (కనుగొను_eq_all (మాట, repeated_c), s_int);
  ఒకవేళ (ముసుగు != 0)
    {
      అక్షరం *ret = (అక్షరం *) s + సూచీ_మొదటి (ముసుగు);
      తిరిగి (ret <= lbyte) ? ret : ఖాళీ;
    }
  ఒకవేళ (మాట_ptr == lword)
    తిరిగి ఖాళీ;

  మాట = *++మాట_ptr;
  అయితే (మాట_ptr != lword)
    {
      ఒకవేళ (has_eq (మాట, repeated_c))
	తిరిగి (అక్షరం *) మాట_ptr + సూచీ_మొదటి_eq (మాట, repeated_c);
      మాట = *++మాట_ptr;
    }

  ఒకవేళ (has_eq (మాట, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      అక్షరం *ret = (అక్షరం *) మాట_ptr + సూచీ_మొదటి_eq (మాట, repeated_c);
      ఒకవేళ (ret <= lbyte)
	తిరిగి ret;
    }
  తిరిగి ఖాళీ;
}
#నిర్వచితం_కాకపోతే MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#అయితే_ముగింపు
