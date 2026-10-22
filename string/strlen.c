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

#ଅନ୍ତର୍ଭାଵ <libc-pointer-arith.h>
#ଅନ୍ତର୍ଭାଵ <string-fzb.h>
#ଅନ୍ତର୍ଭାଵ <string-fzc.h>
#ଅନ୍ତର୍ଭାଵ <string-fzi.h>
#ଅନ୍ତର୍ଭାଵ <string-shift.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ଅଚଳ ଅକ୍ଷର *str)
{
  /* Align pointer to sizeof op_t.  */
  ଅଚଳ uintptr_t s_int = (uintptr_t) str;
  ଅଚଳ op_t *word_ptr = (ଅଚଳ op_t*) PTR_ALIGN_DOWN (str, ଆକାର (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  ଯଦି (mask != 0)
    ଫେରନ୍ତୁ index_first (mask);

  କର
    word = *++word_ptr;
  ଯେତେବେଳେ (! has_zero (word));

  ଫେରନ୍ତୁ ((ଅଚଳ ଅକ୍ଷର *) word_ptr) + index_first_zero (word) - str;
}
#ifndef STRLEN
weak_alias (__strlen, strlen)
libc_hidden_builtin_def (strlen)
#endif
