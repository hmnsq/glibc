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

#അന്തര്ഭാവ <string-fzb.h>
#അന്തര്ഭാവ <string-fzc.h>
#അന്തര്ഭാവ <string-fzi.h>
#അന്തര്ഭാവ <string-shift.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <libc-pointer-arith.h>

#undef __memrchr
#undef memrchr

#ifdef MEMRCHR
# define __memrchr MEMRCHR
#endif

ശൂന്യം *
__memrchr (സ്ഥിരം ശൂന്യം *s, പൂർണ്ണസംഖ്യ c_in, size_t n)
{
  എങ്കിൽ (__glibc_unlikely (n == 0))
    തിരികെ ശൂന്യ;

  സ്ഥിരം op_t *word_ptr = (സ്ഥിരം op_t *) PTR_ALIGN_UP (s + n, വലുപ്പം (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t word = *--word_ptr;
  op_t repeated_c = repeat_bytes (c_in);

  /* Compute the address of the word containing the initial byte. */
  സ്ഥിരം op_t *sword = (സ്ഥിരം op_t *) PTR_ALIGN_DOWN (s, വലുപ്പം (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  find_t mask = shift_find_last (find_eq_all (word, repeated_c), s_int);
  എങ്കിൽ (mask != 0)
    {
      അക്ഷരം *ret = (അക്ഷരം *) word_ptr + index_last (mask);
      തിരികെ ret >= (അക്ഷരം *) s ? ret : ശൂന്യ;
    }
  എങ്കിൽ (word_ptr == sword)
    തിരികെ ശൂന്യ;
  word = *--word_ptr;

  ആകുമ്പോൾ (word_ptr != sword)
    {
      എങ്കിൽ (has_eq (word, repeated_c))
	തിരികെ (അക്ഷരം *) word_ptr + index_last_eq (word, repeated_c);
      word = *--word_ptr;
    }

  എങ്കിൽ (has_eq (word, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      അക്ഷരം *ret = (അക്ഷരം *) word_ptr + index_last_eq (word, repeated_c);
      എങ്കിൽ (ret >= (അക്ഷരം *) s)
	തിരികെ ret;
    }
  തിരികെ ശൂന്യ;
}
#ifndef MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#endif
