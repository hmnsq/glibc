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

#ଅନ୍ତର୍ଭାଵ <libc-pointer-arith.h>
#ଅନ୍ତର୍ଭାଵ <string-fzb.h>
#ଅନ୍ତର୍ଭାଵ <string-fzc.h>
#ଅନ୍ତର୍ଭାଵ <string-fzi.h>
#ଅନ୍ତର୍ଭାଵ <string-shift.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

ସ୍ଥିର __always_inline ଅଚଳ ଅକ୍ଷର *
sadd (uintptr_t x, uintptr_t y)
{
  ଫେରନ୍ତୁ (ଅଚଳ ଅକ୍ଷର *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
ଶୂନ୍ୟ *
__memchr (ଶୂନ୍ୟ ଅଚଳ *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_in, size_t n)
{
  ଯଦି (__glibc_unlikely (n == 0))
    ଫେରନ୍ତୁ ଖାଲି;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ଅଚଳ op_t *word_ptr = PTR_ALIGN_DOWN (s, ଆକାର (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ଅଚଳ ଅକ୍ଷର *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ଅଚଳ op_t *lword = (ଅଚଳ op_t *) PTR_ALIGN_DOWN (lbyte, ଆକାର (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  ଯଦି (mask != 0)
    {
      ଅକ୍ଷର *ret = (ଅକ୍ଷର *) s + index_first (mask);
      ଫେରନ୍ତୁ (ret <= lbyte) ? ret : ଖାଲି;
    }
  ଯଦି (word_ptr == lword)
    ଫେରନ୍ତୁ ଖାଲି;

  word = *++word_ptr;
  ଯେତେବେଳେ (word_ptr != lword)
    {
      ଯଦି (has_eq (word, repeated_c))
	ଫେରନ୍ତୁ (ଅକ୍ଷର *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  ଯଦି (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ଅକ୍ଷର *ret = (ଅକ୍ଷର *) word_ptr + index_first_eq (word, repeated_c);
      ଯଦି (ret <= lbyte)
	ଫେରନ୍ତୁ ret;
    }
  ଫେରନ୍ତୁ ଖାଲି;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
