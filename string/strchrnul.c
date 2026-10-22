/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#undef __strchrnul
#undef strchrnul

#ifdef STRCHRNUL
# define __strchrnul STRCHRNUL
#endif

/* Find the first occurrence of C in S or the final NUL byte.  */
ৱর্ণ *
__strchrnul (ধ্রুৱ ৱর্ণ *str, পূর্ণাঙ্ক c_in)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ধ্রুৱ op_t *word_ptr = (ধ্রুৱ op_t *) PTR_ALIGN_DOWN (str, পরিমাণ (op_t));

  op_t repeated_c = repeat_bytes (c_in);

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_eq_all (word, repeated_c), s_int);
  যদি (mask != 0)
    ঘূৰাই (ৱর্ণ *) str + index_first (mask);

  কৰা
    word = *++word_ptr;
  যেতিয়ালৈ (! has_zero_eq (word, repeated_c));

  ঘূৰাই (ৱর্ণ *) word_ptr + index_first_zero_eq (word, repeated_c);
}
#ifndef STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#endif
