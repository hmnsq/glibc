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

#ਅਨ੍ਤਰ੍ਭਾਵ <libc-pointer-arith.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzi.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-shift.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memchr

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MEMCHR
# define __memchr MEMCHR
#ਜੇ_ਅੰਤ

ਸਥਿਰ __always_inline ਅਚਲ ਅੱਖਰ *
sadd (uintptr_t x, uintptr_t y)
{
  ਵਾਪਸ (ਅਚਲ ਅੱਖਰ *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
ਖਾਲੀ *
__memchr (ਖਾਲੀ ਅਚਲ *s, ਪੂਰਨ c_ਵਿੱਚ, size_t n)
{
  ਜੇ (__glibc_unlikely (n == 0))
    ਵਾਪਸ ਨਿਰਾ;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ਅਚਲ op_t *ਸ਼ਬਦ_ptr = PTR_ALIGN_ਥੱਲੇ (s, ਆਕਾਰ (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t ਸ਼ਬਦ = *ਸ਼ਬਦ_ptr;
  op_t repeated_c = repeat_ਬਾਈਟਾਂ (c_ਵਿੱਚ);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ਅਚਲ ਅੱਖਰ *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ਅਚਲ op_t *lword = (ਅਚਲ op_t *) PTR_ALIGN_ਥੱਲੇ (lbyte, ਆਕਾਰ (op_t));

  ਲੱਭੋ_t ਨਕਾਬ = ਖਿਸਕਾਓ_ਲੱਭੋ (ਲੱਭੋ_eq_all (ਸ਼ਬਦ, repeated_c), s_int);
  ਜੇ (ਨਕਾਬ != 0)
    {
      ਅੱਖਰ *ret = (ਅੱਖਰ *) s + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ (ਨਕਾਬ);
      ਵਾਪਸ (ret <= lbyte) ? ret : ਨਿਰਾ;
    }
  ਜੇ (ਸ਼ਬਦ_ptr == lword)
    ਵਾਪਸ ਨਿਰਾ;

  ਸ਼ਬਦ = *++ਸ਼ਬਦ_ptr;
  ਜਦੋਂ (ਸ਼ਬਦ_ptr != lword)
    {
      ਜੇ (has_eq (ਸ਼ਬਦ, repeated_c))
	ਵਾਪਸ (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ_eq (ਸ਼ਬਦ, repeated_c);
      ਸ਼ਬਦ = *++ਸ਼ਬਦ_ptr;
    }

  ਜੇ (has_eq (ਸ਼ਬਦ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ਅੱਖਰ *ret = (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਪਹਿਲਾ_eq (ਸ਼ਬਦ, repeated_c);
      ਜੇ (ret <= lbyte)
	ਵਾਪਸ ret;
    }
  ਵਾਪਸ ਨਿਰਾ;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#ਜੇ_ਅੰਤ
