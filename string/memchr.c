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

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

स्थिर __always_inline ध्रुव वर्ण *
sadd (uintptr_t x, uintptr_t y)
{
  प्रत्यागम (ध्रुव वर्ण *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
शून्य *
__memchr (शून्य ध्रुव *s, पूर्णाङ्क c_in, size_t n)
{
  यदि (__glibc_unlikely (n == 0))
    प्रत्यागम रिक्त;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ध्रुव op_t *word_ptr = PTR_ALIGN_DOWN (s, परिमाण (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ध्रुव वर्ण *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ध्रुव op_t *lword = (ध्रुव op_t *) PTR_ALIGN_DOWN (lbyte, परिमाण (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  यदि (mask != 0)
    {
      वर्ण *ret = (वर्ण *) s + index_first (mask);
      प्रत्यागम (ret <= lbyte) ? ret : रिक्त;
    }
  यदि (word_ptr == lword)
    प्रत्यागम रिक्त;

  word = *++word_ptr;
  यावत् (word_ptr != lword)
    {
      यदि (has_eq (word, repeated_c))
	प्रत्यागम (वर्ण *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  यदि (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      वर्ण *ret = (वर्ण *) word_ptr + index_first_eq (word, repeated_c);
      यदि (ret <= lbyte)
	प्रत्यागम ret;
    }
  प्रत्यागम रिक्त;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
