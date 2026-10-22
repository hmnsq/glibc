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

#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-fzc.h>
#ಅನ್ತರ್ಭಾವ <string-fzi.h>
#ಅನ್ತರ್ಭಾವ <string-shift.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __memrchr
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memrchr

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MEMRCHR
# define __memrchr MEMRCHR
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ *
__memrchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s, ಪೂರ್ಣಾಂಕ c_ಒಳ, size_t n)
{
  ಆದರೆ (__glibc_unlikely (n == 0))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಸ್ಥಿರಾಂಕ op_t *ಶಬ್ದ_ptr = (ಸ್ಥಿರಾಂಕ op_t *) PTR_ALIGN_ಮೇಲೆ (s + n, ಗಾತ್ರ (op_t));
  uintptr_t s_int = (uintptr_t) s + n;

  op_t ಶಬ್ದ = *--ಶಬ್ದ_ptr;
  op_t repeated_c = repeat_ಬೈಟುಗಳು (c_ಒಳ);

  /* Compute the address of the word containing the initial byte. */
  ಸ್ಥಿರಾಂಕ op_t *sword = (ಸ್ಥಿರಾಂಕ op_t *) PTR_ALIGN_ಕೆಳಕ್ಕೆ (s, ಗಾತ್ರ (op_t));

  /* If the end of buffer is not op_t aligned, mask off the undesirable bits
     before find the last byte position.  */
  ಕಂಡುಹಿಡಿ_t ಮುಖವಾಡ = ಸರಿಸು_ಕಂಡುಹಿಡಿ_ಕೊನೆಯ (ಕಂಡುಹಿಡಿ_eq_all (ಶಬ್ದ, repeated_c), s_int);
  ಆದರೆ (ಮುಖವಾಡ != 0)
    {
      ಅಕ್ಷರ *ret = (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಕೊನೆಯ (ಮುಖವಾಡ);
      ಹಿಂತಿರುಗಿ ret >= (ಅಕ್ಷರ *) s ? ret : ಖಾಲಿ;
    }
  ಆದರೆ (ಶಬ್ದ_ptr == sword)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  ಶಬ್ದ = *--ಶಬ್ದ_ptr;

  ಆಗ (ಶಬ್ದ_ptr != sword)
    {
      ಆದರೆ (has_eq (ಶಬ್ದ, repeated_c))
	ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಕೊನೆಯ_eq (ಶಬ್ದ, repeated_c);
      ಶಬ್ದ = *--ಶಬ್ದ_ptr;
    }

  ಆದರೆ (has_eq (ಶಬ್ದ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ಅಕ್ಷರ *ret = (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಕೊನೆಯ_eq (ಶಬ್ದ, repeated_c);
      ಆದರೆ (ret >= (ಅಕ್ಷರ *) s)
	ಹಿಂತಿರುಗಿ ret;
    }
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMRCHR
libc_hidden_def (__memrchr)
weak_alias (__memrchr, memrchr)
#ಆದರೆ_ಅಂತ್ಯ
