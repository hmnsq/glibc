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

#تعریف_لغوه __memrchr
#تعریف_لغوه memrchr

#که_تعریف_شوی MEMRCHR
# define __memrchr MEMRCHR
#د_که_پای

فراغ *
__memrchr (ثابت فراغ *s, صحيح c_دننه, size_t n)
{
  إذا (__glibc_unlikely (n == 0))
    أرجع عدم;

  ثابت op_t *کلمه_ptr = (ثابت op_t *) PTR_ALIGN_پورته (s + n, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t کلمه = *--کلمه_ptr;
  op_t repeated_c = repeat_بایټونه (c_دننه);

  /* Compute the address of the word containing the initial byte. */
  ثابت op_t *sword = (ثابت op_t *) PTR_ALIGN_ښکته (s, حجم (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  پیدا_کړه_t ماسک = ښويدنه_پیدا_کړه_وروستی (پیدا_کړه_eq_all (کلمه, repeated_c), s_int);
  إذا (ماسک != 0)
    {
      حرف *ret = (حرف *) کلمه_ptr + شاخص_وروستی (ماسک);
      أرجع ret >= (حرف *) s ? ret : عدم;
    }
  إذا (کلمه_ptr == sword)
    أرجع عدم;
  کلمه = *--کلمه_ptr;

  طالما (کلمه_ptr != sword)
    {
      إذا (has_eq (کلمه, repeated_c))
	أرجع (حرف *) کلمه_ptr + شاخص_وروستی_eq (کلمه, repeated_c);
      کلمه = *--کلمه_ptr;
    }

  إذا (has_eq (کلمه, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) کلمه_ptr + شاخص_وروستی_eq (کلمه, repeated_c);
      إذا (ret >= (حرف *) s)
	أرجع ret;
    }
  أرجع عدم;
}
#که_نه_تعریف_شوی MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#د_که_پای
