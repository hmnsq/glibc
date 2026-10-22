/* memrchr -- find the last occurrence of a byte in a memory block
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#ضمن <string-fzb.h>
#ضمن <string-fzc.h>
#ضمن <string-fzi.h>
#ضمن <string-shift.h>
#ضمن <string.h>
#ضمن <libc-pointer-arith.h>

#تعریف_رد __memrchr
#تعریف_رد memrchr

#جے_تعریف_شدہ MEMRCHR
# define __memrchr MEMRCHR
#جے_انت

فراغ *
__memrchr (ثابت فراغ *s, صحيح c_وچ, size_t n)
{
  إذا (__glibc_unlikely (n == 0))
    أرجع عدم;

  ثابت op_t *لفظ_ptr = (ثابت op_t *) PTR_ALIGN_اتے (s + n, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t لفظ = *--لفظ_ptr;
  op_t repeated_c = repeat_بائٹاں (c_وچ);

  /* Compute the address of the word containing the initial byte. */
  ثابت op_t *sword = (ثابت op_t *) PTR_ALIGN_تھلے (s, حجم (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  لبھو_t نقاب = کھسکاؤ_لبھو_آخری (لبھو_eq_all (لفظ, repeated_c), s_int);
  إذا (نقاب != 0)
    {
      حرف *ret = (حرف *) لفظ_ptr + اشاریہ_آخری (نقاب);
      أرجع ret >= (حرف *) s ? ret : عدم;
    }
  إذا (لفظ_ptr == sword)
    أرجع عدم;
  لفظ = *--لفظ_ptr;

  طالما (لفظ_ptr != sword)
    {
      إذا (has_eq (لفظ, repeated_c))
	أرجع (حرف *) لفظ_ptr + اشاریہ_آخری_eq (لفظ, repeated_c);
      لفظ = *--لفظ_ptr;
    }

  إذا (has_eq (لفظ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) لفظ_ptr + اشاریہ_آخری_eq (لفظ, repeated_c);
      إذا (ret >= (حرف *) s)
	أرجع ret;
    }
  أرجع عدم;
}
#جے_بنا_تعریف MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#جے_انت
