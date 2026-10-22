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

#ଅନ୍ତର୍ଭାଵ <libc-pointer-arith.h>
#ଅନ୍ତର୍ଭାଵ <string-fzb.h>
#ଅନ୍ତର୍ଭାଵ <string-fzc.h>
#ଅନ୍ତର୍ଭାଵ <string-fzi.h>
#ଅନ୍ତର୍ଭାଵ <string-shift.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#undef __strchrnul
#undef strchrnul

#ifdef STRCHRNUL
# define __strchrnul STRCHRNUL
#endif

/* Find the first occurrence of C in S or the final NUL byte.  */
ଅକ୍ଷର *
__strchrnul (ଅଚଳ ଅକ୍ଷର *str, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_in)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ଅଚଳ op_t *word_ptr = (ଅଚଳ op_t *) PTR_ALIGN_DOWN (str, ଆକାର (op_t));

  op_t repeated_c = repeat_bytes (c_in);

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_eq_all (word, repeated_c), s_int);
  ଯଦି (mask != 0)
    ଫେରନ୍ତୁ (ଅକ୍ଷର *) str + index_first (mask);

  କର
    word = *++word_ptr;
  ଯେତେବେଳେ (! has_zero_eq (word, repeated_c));

  ଫେରନ୍ତୁ (ଅକ୍ଷର *) word_ptr + index_first_zero_eq (word, repeated_c);
}
#ifndef STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#endif
