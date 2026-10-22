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

#અન્તર્ભાવ <string-fzb.h>
#અન્તર્ભાવ <string-fzc.h>
#અન્તર્ભાવ <string-fzi.h>
#અન્તર્ભાવ <string-shift.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

શૂન્ય *
__memrchr (અચલ શૂન્ય *s, પૂર્ણાંક c_in, size_t n)
{
  જો (__glibc_unlikely (n == 0))
    પાછા ખાલી;

  અચલ op_t *word_ptr = (અચલ op_t *) PTR_ALIGN_UP (s + n, કદ (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  અચલ op_t *sword = (અચલ op_t *) PTR_ALIGN_DOWN (s, કદ (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  જો (mask != 0)
    {
      અક્ષર *ret = (અક્ષર *) word_ptr + index_last (mask);
      પાછા ret >= (અક્ષર *) s ? ret : ખાલી;
    }
  જો (word_ptr == sword)
    પાછા ખાલી;
  word = *--word_ptr;

  જ્યારે (word_ptr != sword)
    {
      જો (has_eq (word, repeated_c))
	પાછા (અક્ષર *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  જો (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      અક્ષર *ret = (અક્ષર *) word_ptr + index_last_eq (word, repeated_c);
      જો (ret >= (અક્ષર *) s)
	પાછા ret;
    }
  પાછા ખાલી;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
