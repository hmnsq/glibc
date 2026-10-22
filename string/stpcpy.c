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

#घोषणा NO_MEMPCPY_STPCPY_REDIRECT
#समावेश <string.h>
#समावेश <stdint.h>
#समावेश <memcopy.h>
#समावेश <string-fzb.h>
#समावेश <string-misc.h>

#अघोषित __stpcpy
#अघोषित stpcpy

#अगर_अघोषित STPCPY
# define STPCPY __stpcpy
#पूर्ण_अगर

अटल __always_inline अक्षर *
write_byte_from_word (op_t *dest, op_t word)
{
  अक्षर *d = (अक्षर *) dest;
  क्रम (माप_प्रकार i = 0; i < OPSIZ; i++, ++d)
    {
      अक्षर c = extractbyte (word, i);
      *d = c;
      अगर (c == '\0')
	अवरोध;
    }
  वापस d;
}

अटल __always_inline अक्षर *
stpcpy_aligned_loop (op_t *restrict dst, स्थिर op_t *restrict src)
{
  op_t word;
  जबतक (1)
    {
      word = *src++;
      अगर (has_zero (word))
	अवरोध;
      *dst++ = word;
    }

  वापस write_byte_from_word (dst, word);
}

अटल __always_inline अक्षर *
stpcpy_unaligned_loop (op_t *restrict dst, स्थिर op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * अक्षर_बिट;
  uintptr_t sh_2 = OPSIZ * अक्षर_बिट - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  अगर (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      जबतक (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  अगर (has_zero (w2))
	    जाओ out;
	  *dst++ = w2;
	  अगर (has_zero (w2b))
	    अवरोध;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  वापस write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
अक्षर *
STPCPY (अक्षर *dest, स्थिर अक्षर *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  माप_प्रकार len = (-(uintptr_t) dest) % OPSIZ;
  क्रम (; len != 0; len--, ++dest)
    {
      अक्षर c = *src++;
      *dest = c;
      अगर (c == '\0')
	वापस dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  वापस ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (स्थिर op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (स्थिर op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
