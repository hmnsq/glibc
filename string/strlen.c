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

#جے_تعریف_شدہ STRLEN
# define __strlen STRLEN
#جے_انت

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ثابت حرف *str)
{
  /* Align pointer to sizeof op_t.  */
  ثابت uintptr_t s_int = (uintptr_t) str;
  ثابت op_t *لفظ_ptr = (ثابت op_t*) PTR_ALIGN_تھلے (str, حجم (op_t));

  op_t لفظ = *لفظ_ptr;
  لبھو_t نقاب = کھسکاؤ_لبھو (لبھو_zero_all (لفظ), s_int);
  إذا (نقاب != 0)
    أرجع اشاریہ_پہلا (نقاب);

  افعل
    لفظ = *++لفظ_ptr;
  طالما (! has_zero (لفظ));

  أرجع ((ثابت حرف *) لفظ_ptr) + اشاریہ_پہلا_zero (لفظ) - str;
}
#جے_بنا_تعریف STRLEN
weak_alias (__strlen, لڑی_لمبائی)
libc_hidden_builtin_def (لڑی_لمبائی)
#جے_انت
