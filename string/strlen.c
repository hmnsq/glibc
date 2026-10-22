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

#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>
#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-fzc.h>
#ಅನ್ತರ್ಭಾವ <string-fzi.h>
#ಅನ್ತರ್ಭಾವ <string-shift.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ಧ್ರುವ ವರ್ಣ *str)
{
  /* Align pointer to sizeof op_t.  */
  ಧ್ರುವ uintptr_t s_int = (uintptr_t) str;
  ಧ್ರುವ op_t *word_ptr = (ಧ್ರುವ op_t*) PTR_ALIGN_DOWN (str, ಪರಿಮಾಣ (op_t));

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);
  ಯದಿ (mask != 0)
    ಪ್ರತ್ಯಾಗಮ index_first (mask);

  ಕುರು
    word = *++word_ptr;
  ಯಾವತ್ (! has_zero (word));

  ಪ್ರತ್ಯಾಗಮ ((ಧ್ರುವ ವರ್ಣ *) word_ptr) + index_first_zero (word) - str;
}
#ifndef STRLEN
weak_alias (__strlen, strlen)
libc_hidden_builtin_def (strlen)
#endif
