/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#నిర్వచించు NO_MEMPCPY_STPCPY_REDIRECT
#అన్తర్భావ <string.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <memcopy.h>
#అన్తర్భావ <string-fzb.h>
#అన్తర్భావ <string-misc.h>

#నిర్వచనం_రద్దు __stpcpy
#నిర్వచనం_రద్దు stpcpy

#నిర్వచితం_కాకపోతే STPCPY
# define STPCPY __stpcpy
#అయితే_ముగింపు

స్థిర __always_inline అక్షరం *
write_byte_from_మాట (op_t *dest, op_t మాట)
{
  అక్షరం *d = (అక్షరం *) dest;
  కొరకు (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      అక్షరం c = extractbyte (మాట, i);
      *d = c;
      ఒకవేళ (c == '\0')
	ఆపు;
    }
  తిరిగి d;
}

స్థిర __always_inline అక్షరం *
stpcpy_aligned_loop (op_t *పరిమిత dst, స్థిరరాశి op_t *పరిమిత src)
{
  op_t మాట;
  అయితే (1)
    {
      మాట = *src++;
      ఒకవేళ (has_zero (మాట))
	ఆపు;
      *dst++ = మాట;
    }

  తిరిగి write_byte_from_మాట (dst, మాట);
}

స్థిర __always_inline అక్షరం *
stpcpy_unaligned_loop (op_t *పరిమిత dst, స్థిరరాశి op_t *పరిమిత src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = విలీనం (w2a, sh_1, (op_t)-1, sh_2);
  ఒకవేళ (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      అయితే (1)
	{
	  w2b = *src++;
	  w2 = విలీనం (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  ఒకవేళ (has_zero (w2))
	    వెళ్ళు బహిర్గతం;
	  *dst++ = w2;
	  ఒకవేళ (has_zero (w2b))
	    ఆపు;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = విలీనం (w2b, sh_1, 0, sh_2);
    }

బహిర్గతం:
  తిరిగి write_byte_from_మాట (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
అక్షరం *
STPCPY (అక్షరం *dest, స్థిరరాశి అక్షరం *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  కొరకు (; len != 0; len--, ++dest)
    {
      అక్షరం c = *src++;
      *dest = c;
      ఒకవేళ (c == '\0')
	తిరిగి dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  తిరిగి ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (స్థిరరాశి op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (స్థిరరాశి op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
