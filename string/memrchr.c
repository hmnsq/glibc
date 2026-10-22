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
__memrchr (ध्रुव शून्य *s, पूर्णाङ्क c_in, माप_प्रकार n)
{
  यदि (__glibc_unlikely (n == 0))
    प्रत्यागम रिक्त;

  ध्रुव op_t *word_ptr = (ध्रुव op_t *) PTR_ALIGN_UP (s + n, परिमाण (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  ध्रुव op_t *sword = (ध्रुव op_t *) PTR_ALIGN_DOWN (s, परिमाण (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  यदि (mask != 0)
    {
      वर्ण *ret = (वर्ण *) word_ptr + index_last (mask);
      प्रत्यागम ret >= (वर्ण *) s ? ret : रिक्त;
    }
  यदि (word_ptr == sword)
    प्रत्यागम रिक्त;
  word = *--word_ptr;

  यावत् (word_ptr != sword)
    {
      यदि (has_eq (word, repeated_c))
	प्रत्यागम (वर्ण *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  यदि (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      वर्ण *ret = (वर्ण *) word_ptr + index_last_eq (word, repeated_c);
      यदि (ret >= (वर्ण *) s)
	प्रत्यागम ret;
    }
  प्रत्यागम रिक्त;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
