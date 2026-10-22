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
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <memcopy.h>
#அந்தர்பாவ <string-fzb.h>
#அந்தர்பாவ <string-misc.h>

#undef __stpcpy
#undef stpcpy

#ifndef STPCPY
# define STPCPY __stpcpy
#endif

நிலையான __always_inline எழுத்து *
write_byte_from_word (op_t *dest, op_t word)
{
  எழுத்து *d = (எழுத்து *) dest;
  க்கு (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      எழுத்து c = extractbyte (word, i);
      *d = c;
      எனில் (c == '\0')
	நிறுத்து;
    }
  திரும்பு d;
}

நிலையான __always_inline எழுத்து *
stpcpy_aligned_loop (op_t *restrict dst, மாறிலி op_t *restrict src)
{
  op_t word;
  போது (1)
    {
      word = *src++;
      எனில் (has_zero (word))
	நிறுத்து;
      *dst++ = word;
    }

  திரும்பு write_byte_from_word (dst, word);
}

நிலையான __always_inline எழுத்து *
stpcpy_unaligned_loop (op_t *restrict dst, மாறிலி op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  எனில் (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      போது (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  எனில் (has_zero (w2))
	    செல் out;
	  *dst++ = w2;
	  எனில் (has_zero (w2b))
	    நிறுத்து;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  திரும்பு write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
எழுத்து *
STPCPY (எழுத்து *dest, மாறிலி எழுத்து *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  க்கு (; len != 0; len--, ++dest)
    {
      எழுத்து c = *src++;
      *dest = c;
      எனில் (c == '\0')
	திரும்பு dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  திரும்பு ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (மாறிலி op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (மாறிலி op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
