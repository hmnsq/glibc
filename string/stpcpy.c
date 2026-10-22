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

#ವ್ಯಾಖ್ಯಾನಿಸು NO_MEMPCPY_STPCPY_REDIRECT
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <memcopy.h>
#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-misc.h>

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __stpcpy
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು stpcpy

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STPCPY
# define STPCPY __stpcpy
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ __always_inline ಅಕ್ಷರ *
write_byte_from_ಶಬ್ದ (op_t *dest, op_t ಶಬ್ದ)
{
  ಅಕ್ಷರ *d = (ಅಕ್ಷರ *) dest;
  ಗಾಗಿ (size_t i = 0; i < OPSIZ; i++, ++d)
    {
      ಅಕ್ಷರ c = extractbyte (ಶಬ್ದ, i);
      *d = c;
      ಆದರೆ (c == '\0')
	ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ d;
}

ಸ್ಥಿರ __always_inline ಅಕ್ಷರ *
stpcpy_aligned_loop (op_t *ಸೀಮಿತ dst, ಸ್ಥಿರಾಂಕ op_t *ಸೀಮಿತ src)
{
  op_t ಶಬ್ದ;
  ಆಗ (1)
    {
      ಶಬ್ದ = *src++;
      ಆದರೆ (has_zero (ಶಬ್ದ))
	ನಿಲ್ಲಿಸು;
      *dst++ = ಶಬ್ದ;
    }

  ಹಿಂತಿರುಗಿ write_byte_from_ಶಬ್ದ (dst, ಶಬ್ದ);
}

ಸ್ಥಿರ __always_inline ಅಕ್ಷರ *
stpcpy_unaligned_loop (op_t *ಸೀಮಿತ dst, ಸ್ಥಿರಾಂಕ op_t *ಸೀಮಿತ src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;

  op_t w2 = ವಿಲೀನ (w2a, sh_1, (op_t)-1, sh_2);
  ಆದರೆ (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ಆಗ (1)
	{
	  w2b = *src++;
	  w2 = ವಿಲೀನ (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  ಆದರೆ (has_zero (w2))
	    ಹೋಗು ಹೊರಹೋಗು;
	  *dst++ = w2;
	  ಆದರೆ (has_zero (w2b))
	    ನಿಲ್ಲಿಸು;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = ವಿಲೀನ (w2b, sh_1, 0, sh_2);
    }

ಹೊರಹೋಗು:
  ಹಿಂತಿರುಗಿ write_byte_from_ಶಬ್ದ (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ಅಕ್ಷರ *
STPCPY (ಅಕ್ಷರ *dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;
  ಗಾಗಿ (; len != 0; len--, ++dest)
    {
      ಅಕ್ಷರ c = *src++;
      *dest = c;
      ಆದರೆ (c == '\0')
	ಹಿಂತಿರುಗಿ dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;
  ಹಿಂತಿರುಗಿ ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (ಸ್ಥಿರಾಂಕ op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (ಸ್ಥಿರಾಂಕ op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
