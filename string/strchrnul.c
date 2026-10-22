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

#समावेश <libc-pointer-arith.h>
#समावेश <string-fzb.h>
#समावेश <string-fzc.h>
#समावेश <string-fzi.h>
#समावेश <string-shift.h>
#समावेश <string.h>

#अघोषित __strchrnul
#अघोषित strchrnul

#अगर_घोषित STRCHRNUL
# define __strchrnul STRCHRNUL
#पूर्ण_अगर

/* Find the first occurrence of C in S or the final NUL byte.  */
अक्षर *
__strchrnul (स्थिर अक्षर *str, पूर्णांक c_in)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  स्थिर op_t *word_ptr = (स्थिर op_t *) PTR_ALIGN_DOWN (str, माप (op_t));

  op_t repeated_c = repeat_bytes (c_in);

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_eq_all (word, repeated_c), s_int);
  अगर (mask != 0)
    वापस (अक्षर *) str + सूचकांक_first (mask);

  करो
    word = *++word_ptr;
  जबतक (! has_zero_eq (word, repeated_c));

  वापस (अक्षर *) word_ptr + सूचकांक_first_zero_eq (word, repeated_c);
}
#अगर_अघोषित STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#पूर्ण_अगर
