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

#समावेश <libc-pointer-arith.h>
#समावेश <string-fzb.h>
#समावेश <string-fzc.h>
#समावेश <string-fzi.h>
#समावेश <string-shift.h>
#समावेश <string.h>

#अघोषित स_प्रथम

#अगर_घोषित MEMCHR
# define __memchr MEMCHR
#पूर्ण_अगर

अटल __always_inline स्थिर अक्षर *
sadd (uintptr_t x, uintptr_t y)
{
  वापस (स्थिर अक्षर *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
व्योम *
__memchr (व्योम स्थिर *s, पूर्णांक c_in, माप_प्रकार n)
{
  अगर (__glibc_unlikely (n == 0))
    वापस शून्य;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  स्थिर op_t *word_ptr = PTR_ALIGN_DOWN (s, माप (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  स्थिर अक्षर *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  स्थिर op_t *lword = (स्थिर op_t *) PTR_ALIGN_DOWN (lbyte, माप (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  अगर (mask != 0)
    {
      अक्षर *ret = (अक्षर *) s + सूचकांक_first (mask);
      वापस (ret <= lbyte) ? ret : शून्य;
    }
  अगर (word_ptr == lword)
    वापस शून्य;

  word = *++word_ptr;
  जबतक (word_ptr != lword)
    {
      अगर (has_eq (word, repeated_c))
	वापस (अक्षर *) word_ptr + सूचकांक_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  अगर (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      अक्षर *ret = (अक्षर *) word_ptr + सूचकांक_first_eq (word, repeated_c);
      अगर (ret <= lbyte)
	वापस ret;
    }
  वापस शून्य;
}
#अगर_अघोषित MEMCHR
weak_alias (__memchr, स_प्रथम)
libc_hidden_builtin_def (स_प्रथम)
#पूर्ण_अगर
