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

#અન્તર્ભાવ <libc-pointer-arith.h>
#અન્તર્ભાવ <string-fzb.h>
#અન્તર્ભાવ <string-fzc.h>
#અન્તર્ભાવ <string-fzi.h>
#અન્તર્ભાવ <string-shift.h>
#અન્તર્ભાવ <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

સ્થિર __always_inline અચલ અક્ષર *
sadd (uintptr_t x, uintptr_t y)
{
  પાછા (અચલ અક્ષર *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
શૂન્ય *
__memchr (શૂન્ય અચલ *s, પૂર્ણાંક c_in, size_t n)
{
  જો (__glibc_unlikely (n == 0))
    પાછા ખાલી;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  અચલ op_t *word_ptr = PTR_ALIGN_DOWN (s, કદ (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  અચલ અક્ષર *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  અચલ op_t *lword = (અચલ op_t *) PTR_ALIGN_DOWN (lbyte, કદ (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  જો (mask != 0)
    {
      અક્ષર *ret = (અક્ષર *) s + index_first (mask);
      પાછા (ret <= lbyte) ? ret : ખાલી;
    }
  જો (word_ptr == lword)
    પાછા ખાલી;

  word = *++word_ptr;
  જ્યારે (word_ptr != lword)
    {
      જો (has_eq (word, repeated_c))
	પાછા (અક્ષર *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  જો (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      અક્ષર *ret = (અક્ષર *) word_ptr + index_first_eq (word, repeated_c);
      જો (ret <= lbyte)
	પાછા ret;
    }
  પાછા ખાલી;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
