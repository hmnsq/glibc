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

#شامل <libc-pointer-arith.h>
#شامل <string-fzb.h>
#شامل <string-fzc.h>
#شامل <string-fzi.h>
#شامل <string-shift.h>
#شامل <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ثابت نویسه *str)
{
  /* Align pointer to sizeof op_t.  */
  ثابت uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *word_ptr = (ثابت op_t*) PTR_ALIGN_DOWN (str, اندازه (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  اگر (mask != 0)
    بازگشت index_first (mask);

  انجامبده
    word = *++word_ptr;
  وقتی (! has_zero (word));

  بازگشت ((ثابت نویسه *) word_ptr) + index_first_zero (word) - str;
}
#ifndef STRLEN
weak_alias (__strlen, strlen)
libc_hidden_builtin_def (strlen)
#endif
