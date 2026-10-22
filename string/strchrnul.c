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

#لغو_تعریف __strchrnul
#لغو_تعریف strchrnul

#اگر_تعریف_شده STRCHRNUL
# define __strchrnul STRCHRNUL
#پایان_اگر

/* Find the first occurrence of C in S or the final NUL byte.  */
حرف *
__strchrnul (ثابت حرف *str, صحيح c_درون)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *کلمه_ptr = (ثابت op_t *) PTR_ALIGN_پایین (str, حجم (op_t));

  op_t repeated_c = repeat_بایتها (c_درون);

  op_t کلمه = *کلمه_ptr;
  پیدا_کن_t ماسک = لغزش_پیدا_کن (پیدا_کن_zero_eq_all (کلمه, repeated_c), s_int);
  إذا (ماسک != 0)
    أرجع (حرف *) str + شاخص_اولی (ماسک);

  افعل
    کلمه = *++کلمه_ptr;
  طالما (! has_zero_eq (کلمه, repeated_c));

  أرجع (حرف *) کلمه_ptr + شاخص_اولی_zero_eq (کلمه, repeated_c);
}
#اگر_تعریف_نشده STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#پایان_اگر
