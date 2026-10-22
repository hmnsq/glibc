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

#تعریف_منسوخ __strchrnul
#تعریف_منسوخ strchrnul

#اگر_تعریف_شدہ STRCHRNUL
# define __strchrnul STRCHRNUL
#اگر_ختم

/* Find the first occurrence of C in S or the final NUL byte.  */
حرف *
__strchrnul (ثابت حرف *str, صحیح c_اندر)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *لفظ_ptr = (ثابت op_t *) PTR_ALIGN_نیچے_کو (str, حجم (op_t));

  op_t repeated_c = repeat_بائٹیں (c_اندر);

  op_t لفظ = *لفظ_ptr;
  ڈھونڈو_t نقاب = سرکاؤ_ڈھونڈو (ڈھونڈو_zero_eq_all (لفظ, repeated_c), s_int);
  اگر (نقاب != 0)
    واپس (حرف *) str + اشاریہ_پہلا (نقاب);

  کرو
    لفظ = *++لفظ_ptr;
  جب (! has_zero_eq (لفظ, repeated_c));

  واپس (حرف *) لفظ_ptr + اشاریہ_پہلا_zero_eq (لفظ, repeated_c);
}
#اگر_غیر_تعریف_شدہ STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#اگر_ختم
