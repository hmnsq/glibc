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

#அந்தர்பாவ <string-fzb.h>
#அந்தர்பாவ <string-fzc.h>
#அந்தர்பாவ <string-fzi.h>
#அந்தர்பாவ <string-shift.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

வெறுமை *
__memrchr (மாறிலி வெறுமை *s, முழு c_in, size_t n)
{
  எனில் (__glibc_unlikely (n == 0))
    திரும்பு வெற்று;

  மாறிலி op_t *word_ptr = (மாறிலி op_t *) PTR_ALIGN_UP (s + n, அளவு (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  மாறிலி op_t *sword = (மாறிலி op_t *) PTR_ALIGN_DOWN (s, அளவு (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  எனில் (mask != 0)
    {
      எழுத்து *ret = (எழுத்து *) word_ptr + index_last (mask);
      திரும்பு ret >= (எழுத்து *) s ? ret : வெற்று;
    }
  எனில் (word_ptr == sword)
    திரும்பு வெற்று;
  word = *--word_ptr;

  போது (word_ptr != sword)
    {
      எனில் (has_eq (word, repeated_c))
	திரும்பு (எழுத்து *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  எனில் (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      எழுத்து *ret = (எழுத்து *) word_ptr + index_last_eq (word, repeated_c);
      எனில் (ret >= (எழுத்து *) s)
	திரும்பு ret;
    }
  திரும்பு வெற்று;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
