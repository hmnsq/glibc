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

#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzi.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-shift.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-pointer-arith.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __memrchr
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memrchr

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MEMRCHR
# define __memrchr MEMRCHR
#ਜੇ_ਅੰਤ

ਖਾਲੀ *
__memrchr (ਅਚਲ ਖਾਲੀ *s, ਪੂਰਨ c_ਵਿੱਚ, size_t n)
{
  ਜੇ (__glibc_unlikely (n == 0))
    ਵਾਪਸ ਨਿਰਾ;

  ਅਚਲ op_t *ਸ਼ਬਦ_ptr = (ਅਚਲ op_t *) PTR_ALIGN_ਉੱਪਰ (s + n, ਆਕਾਰ (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t ਸ਼ਬਦ = *--ਸ਼ਬਦ_ptr;
  op_t repeated_c = repeat_ਬਾਈਟਾਂ (c_ਵਿੱਚ);

  /* Compute the address of the word containing the initial byte. */
  ਅਚਲ op_t *sword = (ਅਚਲ op_t *) PTR_ALIGN_ਥੱਲੇ (s, ਆਕਾਰ (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  ਲੱਭੋ_t ਨਕਾਬ = ਖਿਸਕਾਓ_ਲੱਭੋ_ਆਖਰੀ (ਲੱਭੋ_eq_all (ਸ਼ਬਦ, repeated_c), s_int);
  ਜੇ (ਨਕਾਬ != 0)
    {
      ਅੱਖਰ *ret = (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਆਖਰੀ (ਨਕਾਬ);
      ਵਾਪਸ ret >= (ਅੱਖਰ *) s ? ret : ਨਿਰਾ;
    }
  ਜੇ (ਸ਼ਬਦ_ptr == sword)
    ਵਾਪਸ ਨਿਰਾ;
  ਸ਼ਬਦ = *--ਸ਼ਬਦ_ptr;

  ਜਦੋਂ (ਸ਼ਬਦ_ptr != sword)
    {
      ਜੇ (has_eq (ਸ਼ਬਦ, repeated_c))
	ਵਾਪਸ (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਆਖਰੀ_eq (ਸ਼ਬਦ, repeated_c);
      ਸ਼ਬਦ = *--ਸ਼ਬਦ_ptr;
    }

  ਜੇ (has_eq (ਸ਼ਬਦ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ਅੱਖਰ *ret = (ਅੱਖਰ *) ਸ਼ਬਦ_ptr + ਸੂਚਕਾਂਕ_ਆਖਰੀ_eq (ਸ਼ਬਦ, repeated_c);
      ਜੇ (ret >= (ਅੱਖਰ *) s)
	ਵਾਪਸ ret;
    }
  ਵਾਪਸ ਨਿਰਾ;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#ਜੇ_ਅੰਤ
