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

#ضمن <libc-pointer-arith.h>
#ضمن <string-fzb.h>
#ضمن <string-fzc.h>
#ضمن <string-fzi.h>
#ضمن <string-shift.h>
#ضمن <string.h>

#وصف_رد __strchrnul
#وصف_رد strchrnul

#جيڪڏهن_وصف_ٿيل STRCHRNUL
# define __strchrnul STRCHRNUL
#جيڪڏهن_پورو

/* Find the first occurrence of C in S or the final NUL byte.  */
حرف *
__strchrnul (ثابت حرف *str, صحيح c_اندريون)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *لفظ_ptr = (ثابت op_t *) PTR_ALIGN_هيٺ_ڏانهن (str, حجم (op_t));

  op_t repeated_c = repeat_بائيٽون (c_اندريون);

  op_t لفظ = *لفظ_ptr;
  ڳوليو_t نقاب = سرڪايو_ڳوليو (ڳوليو_zero_eq_all (لفظ, repeated_c), s_int);
  إذا (نقاب != 0)
    أرجع (حرف *) str + اشاريو_پهريون (نقاب);

  افعل
    لفظ = *++لفظ_ptr;
  طالما (! has_zero_eq (لفظ, repeated_c));

  أرجع (حرف *) لفظ_ptr + اشاريو_پهريون_zero_eq (لفظ, repeated_c);
}
#جيڪڏهن_وصف_نه_ٿيل STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#جيڪڏهن_پورو
