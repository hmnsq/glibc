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

#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-fzc.h>
#ಅನ್ತರ್ಭಾವ <string-fzi.h>
#ಅನ್ತರ್ಭಾವ <string-shift.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

ಶೂನ್ಯ *
__memrchr (ಧ್ರುವ ಶೂನ್ಯ *s, ಪೂರ್ಣಾಙ್ಕ c_in, size_t n)
{
  ಯದಿ (__glibc_unlikely (n == 0))
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  ಧ್ರುವ op_t *word_ptr = (ಧ್ರುವ op_t *) PTR_ALIGN_UP (s + n, ಪರಿಮಾಣ (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  ಧ್ರುವ op_t *sword = (ಧ್ರುವ op_t *) PTR_ALIGN_DOWN (s, ಪರಿಮಾಣ (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  ಯದಿ (mask != 0)
    {
      ವರ್ಣ *ret = (ವರ್ಣ *) word_ptr + index_last (mask);
      ಪ್ರತ್ಯಾಗಮ ret >= (ವರ್ಣ *) s ? ret : ರಿಕ್ತ;
    }
  ಯದಿ (word_ptr == sword)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
  word = *--word_ptr;

  ಯಾವತ್ (word_ptr != sword)
    {
      ಯದಿ (has_eq (word, repeated_c))
	ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  ಯದಿ (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ವರ್ಣ *ret = (ವರ್ಣ *) word_ptr + index_last_eq (word, repeated_c);
      ಯದಿ (ret >= (ವರ್ಣ *) s)
	ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
