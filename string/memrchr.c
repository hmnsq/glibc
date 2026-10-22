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

#وصف_رد __memrchr
#وصف_رد memrchr

#جيڪڏهن_وصف_ٿيل MEMRCHR
# define __memrchr MEMRCHR
#جيڪڏهن_پورو

فراغ *
__memrchr (ثابت فراغ *s, صحيح c_اندريون, size_t n)
{
  إذا (__glibc_unlikely (n == 0))
    أرجع عدم;

  ثابت op_t *لفظ_ptr = (ثابت op_t *) PTR_ALIGN_مٿي (s + n, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t لفظ = *--لفظ_ptr;
  op_t repeated_c = repeat_بائيٽون (c_اندريون);

  /* Compute the address of the word containing the initial byte. */
  ثابت op_t *sword = (ثابت op_t *) PTR_ALIGN_هيٺ_ڏانهن (s, حجم (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  ڳوليو_t نقاب = سرڪايو_ڳوليو_آخري (ڳوليو_eq_all (لفظ, repeated_c), s_int);
  إذا (نقاب != 0)
    {
      حرف *ret = (حرف *) لفظ_ptr + اشاريو_آخري (نقاب);
      أرجع ret >= (حرف *) s ? ret : عدم;
    }
  إذا (لفظ_ptr == sword)
    أرجع عدم;
  لفظ = *--لفظ_ptr;

  طالما (لفظ_ptr != sword)
    {
      إذا (has_eq (لفظ, repeated_c))
	أرجع (حرف *) لفظ_ptr + اشاريو_آخري_eq (لفظ, repeated_c);
      لفظ = *--لفظ_ptr;
    }

  إذا (has_eq (لفظ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) لفظ_ptr + اشاريو_آخري_eq (لفظ, repeated_c);
      إذا (ret >= (حرف *) s)
	أرجع ret;
    }
  أرجع عدم;
}
#جيڪڏهن_وصف_نه_ٿيل MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#جيڪڏهن_پورو
