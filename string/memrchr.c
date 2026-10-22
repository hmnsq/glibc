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

#समावेश <string-fzb.h>
#समावेश <string-fzc.h>
#समावेश <string-fzi.h>
#समावेश <string-shift.h>
#समावेश <string.h>
#समावेश <libc-pointer-arith.h>

#अघोषित __memrchr
#अघोषित memrchr

#अगर_घोषित MEMRCHR
# define __memrchr MEMRCHR
#पूर्ण_अगर

व्योम *
__memrchr (स्थिर व्योम *s, पूर्णांक c_in, माप_प्रकार n)
{
  अगर (__glibc_unlikely (n == 0))
    वापस शून्य;

  स्थिर op_t *word_ptr = (स्थिर op_t *) PTR_ALIGN_UP (s + n, माप (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  स्थिर op_t *sword = (स्थिर op_t *) PTR_ALIGN_DOWN (s, माप (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  अगर (mask != 0)
    {
      अक्षर *ret = (अक्षर *) word_ptr + सूचकांक_last (mask);
      वापस ret >= (अक्षर *) s ? ret : शून्य;
    }
  अगर (word_ptr == sword)
    वापस शून्य;
  word = *--word_ptr;

  जबतक (word_ptr != sword)
    {
      अगर (has_eq (word, repeated_c))
	वापस (अक्षर *) word_ptr + सूचकांक_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  अगर (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      अक्षर *ret = (अक्षर *) word_ptr + सूचकांक_last_eq (word, repeated_c);
      अगर (ret >= (अक्षर *) s)
	वापस ret;
    }
  वापस शून्य;
}
#अगर_अघोषित MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#पूर्ण_अगर
