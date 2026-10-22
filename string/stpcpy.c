/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_MEMPCPY_STPCPY_REDIRECT
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <memcopy.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-misc.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __stpcpy
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ stpcpy

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STPCPY
# define STPCPY __stpcpy
#ਜੇ_ਅੰਤ

ਸਥਿਰ __always_inline ਅੱਖਰ *
write_byte_from_ਸ਼ਬਦ (op_t *dest, op_t ਸ਼ਬਦ)
{
  ਅੱਖਰ *d = (ਅੱਖਰ *) dest;
  ਲਈ (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      ਅੱਖਰ c = extractbyte (ਸ਼ਬਦ, i);
      *d = c;
      ਜੇ (c == '\0')
	ਰੋਕੋ;
    }
  ਵਾਪਸ d;
}

ਸਥਿਰ __always_inline ਅੱਖਰ *
stpcpy_aligned_loop (op_t *ਸੀਮਿਤ dst, ਅਚਲ op_t *ਸੀਮਿਤ src)
{
  op_t ਸ਼ਬਦ;
  ਜਦੋਂ (1)
    {
      ਸ਼ਬਦ = *src++;
      ਜੇ (has_zero (ਸ਼ਬਦ))
	ਰੋਕੋ;
      *dst++ = ਸ਼ਬਦ;
    }

  ਵਾਪਸ write_byte_from_ਸ਼ਬਦ (dst, ਸ਼ਬਦ);
}

ਸਥਿਰ __always_inline ਅੱਖਰ *
stpcpy_unaligned_loop (op_t *ਸੀਮਿਤ dst, ਅਚਲ op_t *ਸੀਮਿਤ src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = ਮਿਲਾਓ (w2a, sh_1, (op_t)-1, sh_2);
  ਜੇ (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ਜਦੋਂ (1)
	{
	  w2b = *src++;
	  w2 = ਮਿਲਾਓ (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  ਜੇ (has_zero (w2))
	    ਜਾਓ ਬਾਹਰਲਾ;
	  *dst++ = w2;
	  ਜੇ (has_zero (w2b))
	    ਰੋਕੋ;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = ਮਿਲਾਓ (w2b, sh_1, 0, sh_2);
    }

ਬਾਹਰਲਾ:
  ਵਾਪਸ write_byte_from_ਸ਼ਬਦ (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ਅੱਖਰ *
STPCPY (ਅੱਖਰ *dest, ਅਚਲ ਅੱਖਰ *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  ਲਈ (; len != 0; len--, ++dest)
    {
      ਅੱਖਰ c = *src++;
      *dest = c;
      ਜੇ (c == '\0')
	ਵਾਪਸ dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  ਵਾਪਸ ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (ਅਚਲ op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (ਅਚਲ op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
