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

#अन्तर्भाव <string-fzb.h>
#अन्तर्भाव <string-fzc.h>
#अन्तर्भाव <string-fzi.h>
#अन्तर्भाव <string-shift.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

शून्य *
__memrchr (स्थिरांक शून्य *s, पूर्णांक c_in, माप_प्रकार n)
{
  जर (__glibc_unlikely (n == 0))
    परत रिक्त;

  स्थिरांक op_t *word_ptr = (स्थिरांक op_t *) PTR_ALIGN_UP (s + n, आकार (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  स्थिरांक op_t *sword = (स्थिरांक op_t *) PTR_ALIGN_DOWN (s, आकार (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  जर (mask != 0)
    {
      अक्षर *ret = (अक्षर *) word_ptr + index_last (mask);
      परत ret >= (अक्षर *) s ? ret : रिक्त;
    }
  जर (word_ptr == sword)
    परत रिक्त;
  word = *--word_ptr;

  पर्यंत (word_ptr != sword)
    {
      जर (has_eq (word, repeated_c))
	परत (अक्षर *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  जर (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      अक्षर *ret = (अक्षर *) word_ptr + index_last_eq (word, repeated_c);
      जर (ret >= (अक्षर *) s)
	परत ret;
    }
  परत रिक्त;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
