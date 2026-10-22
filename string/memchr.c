/* Scan memory for a character.  Generic version
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

#ضمن <libc-pointer-arith.h>
#ضمن <string-fzb.h>
#ضمن <string-fzc.h>
#ضمن <string-fzi.h>
#ضمن <string-shift.h>
#ضمن <string.h>

#تعریف_رد memchr

#جے_تعریف_شدہ MEMCHR
# define __memchr MEMCHR
#جے_انت

ساكن __always_inline ثابت حرف *
sadd (uintptr_t x, uintptr_t y)
{
  أرجع (ثابت حرف *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
فراغ *
__memchr (فراغ ثابت *s, صحيح c_وچ, size_t n)
{
  إذا (__glibc_unlikely (n == 0))
    أرجع عدم;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ثابت op_t *لفظ_ptr = PTR_ALIGN_تھلے (s, حجم (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t لفظ = *لفظ_ptr;
  op_t repeated_c = repeat_بائٹاں (c_وچ);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ثابت حرف *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ثابت op_t *lword = (ثابت op_t *) PTR_ALIGN_تھلے (lbyte, حجم (op_t));

  لبھو_t نقاب = کھسکاؤ_لبھو (لبھو_eq_all (لفظ, repeated_c), s_int);
  إذا (نقاب != 0)
    {
      حرف *ret = (حرف *) s + اشاریہ_پہلا (نقاب);
      أرجع (ret <= lbyte) ? ret : عدم;
    }
  إذا (لفظ_ptr == lword)
    أرجع عدم;

  لفظ = *++لفظ_ptr;
  طالما (لفظ_ptr != lword)
    {
      إذا (has_eq (لفظ, repeated_c))
	أرجع (حرف *) لفظ_ptr + اشاریہ_پہلا_eq (لفظ, repeated_c);
      لفظ = *++لفظ_ptr;
    }

  إذا (has_eq (لفظ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      حرف *ret = (حرف *) لفظ_ptr + اشاریہ_پہلا_eq (لفظ, repeated_c);
      إذا (ret <= lbyte)
	أرجع ret;
    }
  أرجع عدم;
}
#جے_بنا_تعریف MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#جے_انت
