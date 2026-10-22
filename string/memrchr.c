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

#ضمن <string-fzb.h>
#ضمن <string-fzc.h>
#ضمن <string-fzi.h>
#ضمن <string-shift.h>
#ضمن <string.h>
#ضمن <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

فراغ *
__memrchr (ثابت فراغ *s, صحيح c_in, size_t n)
{
  إذا (__glibc_unlikely (n == 0))
    إرجاع عدم;

  ثابت op_t *word_ptr = (ثابت op_t *) PTR_ALIGN_UP (s + n, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  ثابت op_t *sword = (ثابت op_t *) PTR_ALIGN_DOWN (s, حجم (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  إذا (mask != 0)
    {
      حرف *ret = (حرف *) word_ptr + index_last (mask);
      إرجاع ret >= (حرف *) s ? ret : عدم;
    }
  إذا (word_ptr == sword)
    إرجاع عدم;
  word = *--word_ptr;

  بينما (word_ptr != sword)
    {
      إذا (has_eq (word, repeated_c))
	إرجاع (حرف *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  إذا (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) word_ptr + index_last_eq (word, repeated_c);
      إذا (ret >= (حرف *) s)
	إرجاع ret;
    }
  إرجاع عدم;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
