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

#अन्तर्भाव <libc-pointer-arith.h>
#अन्तर्भाव <string-fzb.h>
#अन्तर्भाव <string-fzc.h>
#अन्तर्भाव <string-fzi.h>
#अन्तर्भाव <string-shift.h>
#अन्तर्भाव <string.h>

#undef स_प्रथम

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

स्थिर __always_inline स्थिरांक अक्षर *
sadd (uintptr_t x, uintptr_t y)
{
  परत (स्थिरांक अक्षर *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
शून्य *
__memchr (शून्य स्थिरांक *s, पूर्णांक c_in, माप_प्रकार n)
{
  जर (__glibc_unlikely (n == 0))
    परत रिक्त;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  स्थिरांक op_t *word_ptr = PTR_ALIGN_DOWN (s, आकार (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  स्थिरांक अक्षर *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  स्थिरांक op_t *lword = (स्थिरांक op_t *) PTR_ALIGN_DOWN (lbyte, आकार (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  जर (mask != 0)
    {
      अक्षर *ret = (अक्षर *) s + index_first (mask);
      परत (ret <= lbyte) ? ret : रिक्त;
    }
  जर (word_ptr == lword)
    परत रिक्त;

  word = *++word_ptr;
  पर्यंत (word_ptr != lword)
    {
      जर (has_eq (word, repeated_c))
	परत (अक्षर *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  जर (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      अक्षर *ret = (अक्षर *) word_ptr + index_first_eq (word, repeated_c);
      जर (ret <= lbyte)
	परत ret;
    }
  परत रिक्त;
}
#ifndef MEMCHR
weak_alias (__memchr, स_प्रथम)
libc_hidden_builtin_def (स_प्रथम)
#endif
