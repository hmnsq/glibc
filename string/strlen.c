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

#अगर_घोषित STRLEN
# define __strlen STRLEN
#पूर्ण_अगर

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
माप_प्रकार
__strlen (स्थिर अक्षर *str)
{
  /* Align pointer to sizeof op_t.  */
  स्थिर uintptr_t s_int = (uintptr_t) str;
  स्थिर op_t *word_ptr = (स्थिर op_t*) PTR_ALIGN_DOWN (str, माप (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  अगर (mask != 0)
    वापस सूचकांक_first (mask);

  करो
    word = *++word_ptr;
  जबतक (! has_zero (word));

  वापस ((स्थिर अक्षर *) word_ptr) + सूचकांक_first_zero (word) - str;
}
#अगर_अघोषित STRLEN
weak_alias (__strlen, म_माप)
libc_hidden_builtin_def (म_माप)
#पूर्ण_अगर
