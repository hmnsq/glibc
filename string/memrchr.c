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

#شامل <string-fzb.h>
#شامل <string-fzc.h>
#شامل <string-fzi.h>
#شامل <string-shift.h>
#شامل <string.h>
#شامل <libc-pointer-arith.h>

#تعریف_منسوخ __memrchr
#تعریف_منسوخ memrchr

#اگر_تعریف_شدہ MEMRCHR
# define __memrchr MEMRCHR
#اگر_ختم

خالی *
__memrchr (ثابت خالی *s, صحیح c_اندر, size_t n)
{
  اگر (__glibc_unlikely (n == 0))
    واپس تہی;

  ثابت op_t *لفظ_ptr = (ثابت op_t *) PTR_ALIGN_اوپر (s + n, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t لفظ = *--لفظ_ptr;
  op_t repeated_c = repeat_بائٹیں (c_اندر);

  /* Compute the address of the word containing the initial byte. */
  ثابت op_t *sword = (ثابت op_t *) PTR_ALIGN_نیچے_کو (s, حجم (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  ڈھونڈو_t نقاب = سرکاؤ_ڈھونڈو_آخری (ڈھونڈو_eq_all (لفظ, repeated_c), s_int);
  اگر (نقاب != 0)
    {
      حرف *ret = (حرف *) لفظ_ptr + اشاریہ_آخری (نقاب);
      واپس ret >= (حرف *) s ? ret : تہی;
    }
  اگر (لفظ_ptr == sword)
    واپس تہی;
  لفظ = *--لفظ_ptr;

  جب (لفظ_ptr != sword)
    {
      اگر (has_eq (لفظ, repeated_c))
	واپس (حرف *) لفظ_ptr + اشاریہ_آخری_eq (لفظ, repeated_c);
      لفظ = *--لفظ_ptr;
    }

  اگر (has_eq (لفظ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) لفظ_ptr + اشاریہ_آخری_eq (لفظ, repeated_c);
      اگر (ret >= (حرف *) s)
	واپس ret;
    }
  واپس تہی;
}
#اگر_غیر_تعریف_شدہ MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#اگر_ختم
