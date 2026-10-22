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

#यदि_परिभाषितम् STRLEN
# define __strlen STRLEN
#यदि_अन्तः

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ध्रुव वर्ण *str)
{
  /* Align pointer to sizeof op_t.  */
  ध्रुव uintptr_t s_int = (uintptr_t) str;
  ध्रुव op_t *word_ptr = (ध्रुव op_t*) PTR_ALIGN_अधस्तात् (str, परिमाण (op_t));

  op_t word = *word_ptr;
  find_t आवरणम् = सरणम्_find (find_zero_all (word), s_int);
  यदि (आवरणम् != 0)
    प्रत्यागम सूचकांक_first (आवरणम्);

  कुरु
    word = *++word_ptr;
  यावत् (! has_zero (word));

  प्रत्यागम ((ध्रुव वर्ण *) word_ptr) + सूचकांक_first_zero (word) - str;
}
#यदि_अपरिभाषितम् STRLEN
weak_alias (__strlen, वाक्यदैर्घ्यम्)
libc_hidden_builtin_def (वाक्यदैर्घ्यम्)
#यदि_अन्तः
