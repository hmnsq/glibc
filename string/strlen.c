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

#अन्तर्भाव <libc-pointer-arith.h>
#अन्तर्भाव <string-fzb.h>
#अन्तर्भाव <string-fzc.h>
#अन्तर्भाव <string-fzi.h>
#अन्तर्भाव <string-shift.h>
#अन्तर्भाव <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
माप_प्रकार
__strlen (अचर वर्ण *str)
{
  /* Align pointer to sizeof op_t.  */
  अचर uintptr_t s_int = (uintptr_t) str;
  अचर op_t *word_ptr = (अचर op_t*) PTR_ALIGN_DOWN (str, परिमाण (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  यदि (mask != 0)
    फर्काऊ index_first (mask);

  गर
    word = *++word_ptr;
  जबसम्म (! has_zero (word));

  फर्काऊ ((अचर वर्ण *) word_ptr) + index_first_zero (word) - str;
}
#ifndef STRLEN
weak_alias (__strlen, म_माप)
libc_hidden_builtin_def (म_माप)
#endif
