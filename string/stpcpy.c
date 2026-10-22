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

#define NO_MEMPCPY_STPCPY_REDIRECT
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <memcopy.h>
#ଅନ୍ତର୍ଭାଵ <string-fzb.h>
#ଅନ୍ତର୍ଭାଵ <string-misc.h>

#undef __stpcpy
#undef stpcpy

#ifndef STPCPY
# define STPCPY __stpcpy
#endif

ସ୍ଥିର __always_inline ଅକ୍ଷର *
write_byte_from_word (op_t *dest, op_t word)
{
  ଅକ୍ଷର *d = (ଅକ୍ଷର *) dest;
  ପାଇଁ (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      ଅକ୍ଷର c = extractbyte (word, i);
      *d = c;
      ଯଦି (c == '\0')
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ d;
}

ସ୍ଥିର __always_inline ଅକ୍ଷର *
stpcpy_aligned_loop (op_t *restrict dst, ଅଚଳ op_t *restrict src)
{
  op_t word;
  ଯେତେବେଳେ (1)
    {
      word = *src++;
      ଯଦି (has_zero (word))
	ଭାଙ୍ଗ;
      *dst++ = word;
    }

  ଫେରନ୍ତୁ write_byte_from_word (dst, word);
}

ସ୍ଥିର __always_inline ଅକ୍ଷର *
stpcpy_unaligned_loop (op_t *restrict dst, ଅଚଳ op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  ଯଦି (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ଯେତେବେଳେ (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  ଯଦି (has_zero (w2))
	    ଯାଅ out;
	  *dst++ = w2;
	  ଯଦି (has_zero (w2b))
	    ଭାଙ୍ଗ;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  ଫେରନ୍ତୁ write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ଅକ୍ଷର *
STPCPY (ଅକ୍ଷର *dest, ଅଚଳ ଅକ୍ଷର *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  ପାଇଁ (; len != 0; len--, ++dest)
    {
      ଅକ୍ଷର c = *src++;
      *dest = c;
      ଯଦି (c == '\0')
	ଫେରନ୍ତୁ dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  ଫେରନ୍ତୁ ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (ଅଚଳ op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (ଅଚଳ op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
