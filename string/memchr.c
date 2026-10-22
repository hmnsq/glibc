/* Scan memory for a character.  Generic version
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

#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>
#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-fzc.h>
#ಅನ್ತರ್ಭಾವ <string-fzi.h>
#ಅನ್ತರ್ಭಾವ <string-shift.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

ಸ್ಥಿರ __always_inline ಧ್ರುವ ವರ್ಣ *
sadd (uintptr_t x, uintptr_t y)
{
  ಪ್ರತ್ಯಾಗಮ (ಧ್ರುವ ವರ್ಣ *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
ಶೂನ್ಯ *
__memchr (ಶೂನ್ಯ ಧ್ರುವ *s, ಪೂರ್ಣಾಙ್ಕ c_in, size_t n)
{
  ಯದಿ (__glibc_unlikely (n == 0))
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ಧ್ರುವ op_t *word_ptr = PTR_ALIGN_DOWN (s, ಪರಿಮಾಣ (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ಧ್ರುವ ವರ್ಣ *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ಧ್ರುವ op_t *lword = (ಧ್ರುವ op_t *) PTR_ALIGN_DOWN (lbyte, ಪರಿಮಾಣ (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  ಯದಿ (mask != 0)
    {
      ವರ್ಣ *ret = (ವರ್ಣ *) s + index_first (mask);
      ಪ್ರತ್ಯಾಗಮ (ret <= lbyte) ? ret : ರಿಕ್ತ;
    }
  ಯದಿ (word_ptr == lword)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  word = *++word_ptr;
  ಯಾವತ್ (word_ptr != lword)
    {
      ಯದಿ (has_eq (word, repeated_c))
	ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  ಯದಿ (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ವರ್ಣ *ret = (ವರ್ಣ *) word_ptr + index_first_eq (word, repeated_c);
      ಯದಿ (ret <= lbyte)
	ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
