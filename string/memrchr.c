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

#ଅନ୍ତର୍ଭାଵ <string-fzb.h>
#ଅନ୍ତର୍ଭାଵ <string-fzc.h>
#ଅନ୍ତର୍ଭାଵ <string-fzi.h>
#ଅନ୍ତର୍ଭାଵ <string-shift.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

ଶୂନ୍ୟ *
__memrchr (ଅଚଳ ଶୂନ୍ୟ *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_in, size_t n)
{
  ଯଦି (__glibc_unlikely (n == 0))
    ଫେରନ୍ତୁ ଖାଲି;

  ଅଚଳ op_t *word_ptr = (ଅଚଳ op_t *) PTR_ALIGN_UP (s + n, ଆକାର (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  ଅଚଳ op_t *sword = (ଅଚଳ op_t *) PTR_ALIGN_DOWN (s, ଆକାର (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  ଯଦି (mask != 0)
    {
      ଅକ୍ଷର *ret = (ଅକ୍ଷର *) word_ptr + index_last (mask);
      ଫେରନ୍ତୁ ret >= (ଅକ୍ଷର *) s ? ret : ଖାଲି;
    }
  ଯଦି (word_ptr == sword)
    ଫେରନ୍ତୁ ଖାଲି;
  word = *--word_ptr;

  ଯେତେବେଳେ (word_ptr != sword)
    {
      ଯଦି (has_eq (word, repeated_c))
	ଫେରନ୍ତୁ (ଅକ୍ଷର *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  ଯଦି (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ଅକ୍ଷର *ret = (ଅକ୍ଷର *) word_ptr + index_last_eq (word, repeated_c);
      ଯଦି (ret >= (ଅକ୍ଷର *) s)
	ଫେରନ୍ତୁ ret;
    }
  ଫେରନ୍ତୁ ଖାଲି;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
