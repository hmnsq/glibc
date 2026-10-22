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

#ضمن <libc-pointer-arith.h>
#ضمن <string-fzb.h>
#ضمن <string-fzc.h>
#ضمن <string-fzi.h>
#ضمن <string-shift.h>
#ضمن <string.h>

#undef memchr

#ifdef MEMCHR
# define __memchr MEMCHR
#endif

ساكن __always_inline ثابت حرف *
sadd (uintptr_t x, uintptr_t y)
{
  أرجع (ثابت حرف *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
فراغ *
__memchr (فراغ ثابت *s, صحيح c_in, size_t n)
{
  𐤀𐤌 (__glibc_unlikely (n == 0))
    أرجع عدم;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ثابت op_t *word_ptr = PTR_ALIGN_DOWN (s, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t word = *word_ptr;
  op_t repeated_c = repeat_bytes (c_in);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ثابت حرف *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ثابت op_t *lword = (ثابت op_t *) PTR_ALIGN_DOWN (lbyte, حجم (op_t));

  find_t mask = shift_find (find_eq_all (word, repeated_c), s_int);
  𐤀𐤌 (mask != 0)
    {
      حرف *ret = (حرف *) s + index_first (mask);
      أرجع (ret <= lbyte) ? ret : عدم;
    }
  𐤀𐤌 (word_ptr == lword)
    أرجع عدم;

  word = *++word_ptr;
  طالما (word_ptr != lword)
    {
      𐤀𐤌 (has_eq (word, repeated_c))
	أرجع (حرف *) word_ptr + index_first_eq (word, repeated_c);
      word = *++word_ptr;
    }

  𐤀𐤌 (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) word_ptr + index_first_eq (word, repeated_c);
      𐤀𐤌 (ret <= lbyte)
	أرجع ret;
    }
  أرجع عدم;
}
#ifndef MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#endif
