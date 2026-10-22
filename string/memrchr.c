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

#অন্তর্ভাব <string-fzb.h>
#অন্তর্ভাব <string-fzc.h>
#অন্তর্ভাব <string-fzi.h>
#অন্তর্ভাব <string-shift.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

শূন্য *
__memrchr (ধ্রুবক শূন্য *s, পূর্ণসংখ্যা c_in, size_t n)
{
  যদি (__glibc_unlikely (n == 0))
    ফেরত ফাঁকা;

  ধ্রুবক op_t *word_ptr = (ধ্রুবক op_t *) PTR_ALIGN_UP (s + n, আকার (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  ধ্রুবক op_t *sword = (ধ্রুবক op_t *) PTR_ALIGN_DOWN (s, আকার (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  যদি (mask != 0)
    {
      অক্ষর *ret = (অক্ষর *) word_ptr + সূচক_last (mask);
      ফেরত ret >= (অক্ষর *) s ? ret : ফাঁকা;
    }
  যদি (word_ptr == sword)
    ফেরত ফাঁকা;
  word = *--word_ptr;

  যখন (word_ptr != sword)
    {
      যদি (has_eq (word, repeated_c))
	ফেরত (অক্ষর *) word_ptr + সূচক_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  যদি (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      অক্ষর *ret = (অক্ষর *) word_ptr + সূচক_last_eq (word, repeated_c);
      যদি (ret >= (অক্ষর *) s)
	ফেরত ret;
    }
  ফেরত ফাঁকা;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
