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

#অন্তর্ভাব <libc-pointer-arith.h>
#অন্তর্ভাব <string-fzb.h>
#অন্তর্ভাব <string-fzc.h>
#অন্তর্ভাব <string-fzi.h>
#অন্তর্ভাব <string-shift.h>
#অন্তর্ভাব <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ধ্রুব বর্ণ *str)
{
  /* Align pointer to sizeof op_t.  */
  ধ্রুব uintptr_t s_int = (uintptr_t) str;
  ধ্রুব op_t *word_ptr = (ধ্রুব op_t*) PTR_ALIGN_DOWN (str, পরিমাণ (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  যদি (mask != 0)
    প্রত্যাগম index_first (mask);

  কুরু
    word = *++word_ptr;
  যাবত্ (! has_zero (word));

  প্রত্যাগম ((ধ্রুব বর্ণ *) word_ptr) + index_first_zero (word) - str;
}
#ifndef STRLEN
weak_alias (__strlen, strlen)
libc_hidden_builtin_def (strlen)
#endif
