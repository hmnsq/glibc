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

#অন্তর্ভাৱ <libc-pointer-arith.h>
#অন্তর্ভাৱ <string-fzb.h>
#অন্তর্ভাৱ <string-fzc.h>
#অন্তর্ভাৱ <string-fzi.h>
#অন্তর্ভাৱ <string-shift.h>
#অন্তর্ভাৱ <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

স্থির __always_inline ধ্রুৱ ৱর্ণ *
sadd (uintptr_t x, uintptr_t y)
{
  ঘূৰাই (ধ্রুৱ ৱর্ণ *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
শূন্য *
__memchr (শূন্য ধ্রুৱ *s, পূর্ণাঙ্ক c_in, size_t n)
{
  যদি (__glibc_unlikely (n == 0))
    ঘূৰাই রিক্ত;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ধ্রুৱ op_t *word_ptr = PTR_ALIGN_DOWN (s, পরিমাণ (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ধ্রুৱ ৱর্ণ *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ধ্রুৱ op_t *lword = (ধ্রুৱ op_t *) PTR_ALIGN_DOWN (lbyte, পরিমাণ (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  যদি (mask != 0)
    {
      ৱর্ণ *ret = (ৱর্ণ *) s + index_first (mask);
      ঘূৰাই (ret <= lbyte) ? ret : রিক্ত;
    }
  যদি (word_ptr == lword)
    ঘূৰাই রিক্ত;

  word = *++word_ptr;
  যেতিয়ালৈ (word_ptr != lword)
    {
      যদি (has_eq (word, repeated_c))
	ঘূৰাই (ৱর্ণ *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  যদি (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ৱর্ণ *ret = (ৱর্ণ *) word_ptr + index_first_eq (word, repeated_c);
      যদি (ret <= lbyte)
	ঘূৰাই ret;
    }
  ঘূৰাই রিক্ত;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
