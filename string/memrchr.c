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

#include <string-fzb.h>
#include <string-fzc.h>
#include <string-fzi.h>
#include <string-shift.h>
#include <string.h>
#include <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

void *
__memrchr (const void *s, puur_naa_nka c_in, size_t n)
{
  ᨀᨘ (__glibc_unlikely (n == 0))
    ᨀᨘᨒ NULL;

  const op_t *word_ptr = (const op_t *) PTR_ALIGN_UP (s + n, parimaa_na (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  const op_t *sword = (const op_t *) PTR_ALIGN_DOWN (s, parimaa_na (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  ᨀᨘ (mask != 0)
    {
      var_na *ret = (var_na *) word_ptr + index_last (mask);
      ᨀᨘᨒ ret >= (var_na *) s ? ret : NULL;
    }
  ᨀᨘ (word_ptr == sword)
    ᨀᨘᨒ NULL;
  word = *--word_ptr;

  ᨀᨛ (word_ptr != sword)
    {
      ᨀᨘ (has_eq (word, repeated_c))
	ᨀᨘᨒ (var_na *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  ᨀᨘ (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      var_na *ret = (var_na *) word_ptr + index_last_eq (word, repeated_c);
      ᨀᨘ (ret >= (var_na *) s)
	ᨀᨘᨒ ret;
    }
  ᨀᨘᨒ NULL;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
