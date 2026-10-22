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

#அந்தர்பாவ <libc-pointer-arith.h>
#அந்தர்பாவ <string-fzb.h>
#அந்தர்பாவ <string-fzc.h>
#அந்தர்பாவ <string-fzi.h>
#அந்தர்பாவ <string-shift.h>
#அந்தர்பாவ <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

நிலையான __always_inline மாறிலி எழுத்து *
sadd (uintptr_t x, uintptr_t y)
{
  திரும்பு (மாறிலி எழுத்து *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
வெறுமை *
__memchr (வெறுமை மாறிலி *s, முழு c_in, size_t n)
{
  எனில் (__glibc_unlikely (n == 0))
    திரும்பு வெற்று;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  மாறிலி op_t *word_ptr = PTR_ALIGN_DOWN (s, அளவு (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  மாறிலி எழுத்து *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  மாறிலி op_t *lword = (மாறிலி op_t *) PTR_ALIGN_DOWN (lbyte, அளவு (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  எனில் (mask != 0)
    {
      எழுத்து *ret = (எழுத்து *) s + index_first (mask);
      திரும்பு (ret <= lbyte) ? ret : வெற்று;
    }
  எனில் (word_ptr == lword)
    திரும்பு வெற்று;

  word = *++word_ptr;
  போது (word_ptr != lword)
    {
      எனில் (has_eq (word, repeated_c))
	திரும்பு (எழுத்து *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  எனில் (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      எழுத்து *ret = (எழுத்து *) word_ptr + index_first_eq (word, repeated_c);
      எனில் (ret <= lbyte)
	திரும்பு ret;
    }
  திரும்பு வெற்று;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
