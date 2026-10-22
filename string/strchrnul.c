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

#અન્તર્ભાવ <libc-pointer-arith.h>
#અન્તર્ભાવ <string-fzb.h>
#અન્તર્ભાવ <string-fzc.h>
#અન્તર્ભાવ <string-fzi.h>
#અન્તર્ભાવ <string-shift.h>
#અન્તર્ભાવ <string.h>

#undef __strchrnul
#undef strchrnul

#ifdef STRCHRNUL
# define __strchrnul STRCHRNUL
#endif

/* Find the first occurrence of C in S or the final NUL byte.  */
અક્ષર *
__strchrnul (અચલ અક્ષર *str, પૂર્ણાંક c_in)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  અચલ op_t *word_ptr = (અચલ op_t *) PTR_ALIGN_DOWN (str, કદ (op_t));

  op_t repeated_c = repeat_bytes (c_in);

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_eq_all (word, repeated_c), s_int);
  જો (mask != 0)
    પાછા (અક્ષર *) str + index_first (mask);

  કરો
    word = *++word_ptr;
  જ્યારે (! has_zero_eq (word, repeated_c));

  પાછા (અક્ષર *) word_ptr + index_first_zero_eq (word, repeated_c);
}
#ifndef STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#endif
