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

#include <libc-pointer-arith.h>
#include <string-fzb.h>
#include <string-fzc.h>
#include <string-fzi.h>
#include <string-shift.h>
#include <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

static __always_inline const char *
sadd (uintptr_t x, uintptr_t y)
{
  trả_về (const char *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
void *
__memchr (void const *s, số_nguyên c_in, size_t n)
{
  nếu (__glibc_unlikely (n == 0))
    trả_về NULL;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  const op_t *word_ptr = PTR_ALIGN_DOWN (s, sizeof (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  const char *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  const op_t *lword = (const op_t *) PTR_ALIGN_DOWN (lbyte, sizeof (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  nếu (mask != 0)
    {
      char *ret = (char *) s + index_first (mask);
      trả_về (ret <= lbyte) ? ret : NULL;
    }
  nếu (word_ptr == lword)
    trả_về NULL;

  word = *++word_ptr;
  trong_khi (word_ptr != lword)
    {
      nếu (has_eq (word, repeated_c))
	trả_về (char *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  nếu (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      char *ret = (char *) word_ptr + index_first_eq (word, repeated_c);
      nếu (ret <= lbyte)
	trả_về ret;
    }
  trả_về NULL;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
