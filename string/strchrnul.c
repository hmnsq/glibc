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

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __strchrnul
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strchrnul

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ STRCHRNUL
# define __strchrnul STRCHRNUL
#ਜੇ_ਅੰਤ

/* Find the first occurrence of C in S or the final NUL byte.  */
ਅੱਖਰ *
__strchrnul (ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ c_ਵਿੱਚ)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ਅਚਲ op_t *ਸ਼ਬਦ_ptr = (ਅਚਲ op_t *) PTR_ALIGN_ਥੱਲੇ (str, ਆਕਾਰ (op_t));

  op_t repeated_c = repeat_ਬਾਈਟਾਂ (c_ਵਿੱਚ);

  op_t ਸ਼ਬਦ = *ਸ਼ਬਦ_ptr;
  ਲੱਭੋ_t ਨਕਾਬ = ਖਿਸਕਾਓ_ਲੱਭੋ (ਲੱਭੋ_zero_eq_all (ਸ਼ਬਦ, repeated_c), s_int);
  ਜੇ (ਨਕਾਬ != 0)
    ਵਾਪਸ (ਅੱਖਰ *) str + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ (ਨਕਾਬ);

  ਕਰੋ
    ਸ਼ਬਦ = *++ਸ਼ਬਦ_ptr;
  ਜਦੋਂ (! has_zero_eq (ਸ਼ਬਦ, repeated_c));

  ਵਾਪਸ (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ_zero_eq (ਸ਼ਬਦ, repeated_c);
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#ਜੇ_ਅੰਤ
