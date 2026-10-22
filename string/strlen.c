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

#اگر_تعریف_شده STRLEN
# define __strlen STRLEN
#پایان_اگر

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ثابت حرف *str)
{
  /* Align pointer to sizeof op_t.  */
  ثابت uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *کلمه_ptr = (ثابت op_t*) PTR_ALIGN_پایین (str, حجم (op_t));

  op_t کلمه = *کلمه_ptr;
  پیدا_کن_t ماسک = لغزش_پیدا_کن (پیدا_کن_zero_all (کلمه), s_int);
  إذا (ماسک != 0)
    أرجع شاخص_اولی (ماسک);

  افعل
    کلمه = *++کلمه_ptr;
  طالما (! has_zero (کلمه));

  أرجع ((ثابت حرف *) کلمه_ptr) + شاخص_اولی_zero (کلمه) - str;
}
#اگر_تعریف_نشده STRLEN
weak_alias (__strlen, طول_رشته)
libc_hidden_builtin_def (طول_رشته)
#پایان_اگر
