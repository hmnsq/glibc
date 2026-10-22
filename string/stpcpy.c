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
#ضمن <string.h>
#ضمن <stdint.h>
#ضمن <memcopy.h>
#ضمن <string-fzb.h>
#ضمن <string-misc.h>

#undef __stpcpy
#undef stpcpy

#ifndef STPCPY
# define STPCPY __stpcpy
#endif

ساكن __always_inline حرف *
write_byte_from_word (op_t *dest, op_t word)
{
  حرف *d = (حرف *) dest;
  لكل (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      حرف c = extractbyte (word, i);
      *d = c;
      إذا (c == '\0')
	اكسر;
    }
  إرجاع d;
}

ساكن __always_inline حرف *
stpcpy_aligned_loop (op_t *restrict dst, ثابت op_t *restrict src)
{
  op_t word;
  بينما (1)
    {
      word = *src++;
      إذا (has_zero (word))
	اكسر;
      *dst++ = word;
    }

  إرجاع write_byte_from_word (dst, word);
}

ساكن __always_inline حرف *
stpcpy_unaligned_loop (op_t *restrict dst, ثابت op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  إذا (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      بينما (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  إذا (has_zero (w2))
	    اذهب out;
	  *dst++ = w2;
	  إذا (has_zero (w2b))
	    اكسر;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  إرجاع write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
حرف *
STPCPY (حرف *dest, ثابت حرف *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  لكل (; len != 0; len--, ++dest)
    {
      حرف c = *src++;
      *dest = c;
      إذا (c == '\0')
	إرجاع dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  إرجاع ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (ثابت op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (ثابت op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
