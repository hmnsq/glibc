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

#परिभाषय NO_MEMPCPY_STPCPY_REDIRECT
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <memcopy.h>
#अन्तर्भाव <string-fzb.h>
#अन्तर्भाव <string-misc.h>

#अपरिभाषय __stpcpy
#अपरिभाषय stpcpy

#यदि_अपरिभाषितम् STPCPY
# define STPCPY __stpcpy
#यदि_अन्तः

स्थिर __always_inline वर्ण *
write_byte_from_word (op_t *dest, op_t word)
{
  वर्ण *d = (वर्ण *) dest;
  प्रति (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      वर्ण c = extractbyte (word, i);
      *d = c;
      यदि (c == '\0')
	भङ्ग;
    }
  प्रत्यागम d;
}

स्थिर __always_inline वर्ण *
stpcpy_aligned_loop (op_t *सीमित dst, ध्रुव op_t *सीमित src)
{
  op_t word;
  यावत् (1)
    {
      word = *src++;
      यदि (has_zero (word))
	भङ्ग;
      *dst++ = word;
    }

  प्रत्यागम write_byte_from_word (dst, word);
}

स्थिर __always_inline वर्ण *
stpcpy_unaligned_loop (op_t *सीमित dst, ध्रुव op_t *सीमित src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  यदि (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      यावत् (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  यदि (has_zero (w2))
	    गच्छ बहिर्गमनम्;
	  *dst++ = w2;
	  यदि (has_zero (w2b))
	    भङ्ग;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

बहिर्गमनम्:
  प्रत्यागम write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
वर्ण *
STPCPY (वर्ण *dest, ध्रुव वर्ण *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  प्रति (; len != 0; len--, ++dest)
    {
      वर्ण c = *src++;
      *dest = c;
      यदि (c == '\0')
	प्रत्यागम dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  प्रत्यागम ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (ध्रुव op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (ध्रुव op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
