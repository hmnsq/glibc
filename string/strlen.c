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

#ਅਨ੍ਤਰ੍ਭਾਵ <libc-pointer-arith.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzi.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-shift.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ STRLEN
# define __strlen STRLEN
#ਜੇ_ਅੰਤ

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ਅਚਲ ਅੱਖਰ *str)
{
  /* Align pointer to sizeof op_t.  */
  ਅਚਲ uintptr_t s_int = (uintptr_t) str;
  ਅਚਲ op_t *ਸ਼ਬਦ_ptr = (ਅਚਲ op_t*) PTR_ALIGN_ਥੱਲੇ (str, ਆਕਾਰ (op_t));

  op_t ਸ਼ਬਦ = *ਸ਼ਬਦ_ptr;
  ਲੱਭੋ_t ਨਕਾਬ = ਖਿਸਕਾਓ_ਲੱਭੋ (ਲੱਭੋ_zero_all (ਸ਼ਬਦ), s_int);
  ਜੇ (ਨਕਾਬ != 0)
    ਵਾਪਸ ਸੂਚਕਾਂਕ_ਪਹਿਲਾ (ਨਕਾਬ);

  ਕਰੋ
    ਸ਼ਬਦ = *++ਸ਼ਬਦ_ptr;
  ਜਦੋਂ (! has_zero (ਸ਼ਬਦ));

  ਵਾਪਸ ((ਅਚਲ ਅੱਖਰ *) ਸ਼ਬਦ_ptr) + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ_zero (ਸ਼ਬਦ) - str;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRLEN
weak_alias (__strlen, ਲੜੀ_ਲੰਬਾਈ)
libc_hidden_builtin_def (ਲੜੀ_ਲੰਬਾਈ)
#ਜੇ_ਅੰਤ
