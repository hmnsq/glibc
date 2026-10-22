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
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <memcopy.h>
#അന്തര്ഭാവ <string-fzb.h>
#അന്തര്ഭാവ <string-misc.h>

#undef __stpcpy
#undef stpcpy

#ifndef STPCPY
# define STPCPY __stpcpy
#endif

സ്ഥിതം __always_inline അക്ഷരം *
write_byte_from_word (op_t *dest, op_t word)
{
  അക്ഷരം *d = (അക്ഷരം *) dest;
  വേണ്ടി (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      അക്ഷരം c = extractbyte (word, i);
      *d = c;
      എങ്കിൽ (c == '\0')
	നിർത്തുക;
    }
  തിരികെ d;
}

സ്ഥിതം __always_inline അക്ഷരം *
stpcpy_aligned_loop (op_t *restrict dst, സ്ഥിരം op_t *restrict src)
{
  op_t word;
  ആകുമ്പോൾ (1)
    {
      word = *src++;
      എങ്കിൽ (has_zero (word))
	നിർത്തുക;
      *dst++ = word;
    }

  തിരികെ write_byte_from_word (dst, word);
}

സ്ഥിതം __always_inline അക്ഷരം *
stpcpy_unaligned_loop (op_t *restrict dst, സ്ഥിരം op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  എങ്കിൽ (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ആകുമ്പോൾ (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  എങ്കിൽ (has_zero (w2))
	    പോകുക out;
	  *dst++ = w2;
	  എങ്കിൽ (has_zero (w2b))
	    നിർത്തുക;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  തിരികെ write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
അക്ഷരം *
STPCPY (അക്ഷരം *dest, സ്ഥിരം അക്ഷരം *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  വേണ്ടി (; len != 0; len--, ++dest)
    {
      അക്ഷരം c = *src++;
      *dest = c;
      എങ്കിൽ (c == '\0')
	തിരികെ dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  തിരികെ ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (സ്ഥിരം op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (സ്ഥിരം op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
