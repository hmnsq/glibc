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

#অন্তর্ভাব <libc-pointer-arith.h>
#অন্তর্ভাব <string-fzb.h>
#অন্তর্ভাব <string-fzc.h>
#অন্তর্ভাব <string-fzi.h>
#অন্তর্ভাব <string-shift.h>
#অন্তর্ভাব <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

স্থির __always_inline ধ্রুবক অক্ষর *
sadd (uintptr_t x, uintptr_t y)
{
  ফেরত (ধ্রুবক অক্ষর *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
শূন্য *
__memchr (শূন্য ধ্রুবক *s, পূর্ণসংখ্যা c_in, size_t n)
{
  যদি (__glibc_unlikely (n == 0))
    ফেরত ফাঁকা;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ধ্রুবক op_t *word_ptr = PTR_ALIGN_DOWN (s, আকার (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ধ্রুবক অক্ষর *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ধ্রুবক op_t *lword = (ধ্রুবক op_t *) PTR_ALIGN_DOWN (lbyte, আকার (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  যদি (mask != 0)
    {
      অক্ষর *ret = (অক্ষর *) s + সূচক_first (mask);
      ফেরত (ret <= lbyte) ? ret : ফাঁকা;
    }
  যদি (word_ptr == lword)
    ফেরত ফাঁকা;

  word = *++word_ptr;
  যখন (word_ptr != lword)
    {
      যদি (has_eq (word, repeated_c))
	ফেরত (অক্ষর *) word_ptr + সূচক_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  যদি (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      অক্ষর *ret = (অক্ষর *) word_ptr + সূচক_first_eq (word, repeated_c);
      যদি (ret <= lbyte)
	ফেরত ret;
    }
  ফেরত ফাঁকা;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
