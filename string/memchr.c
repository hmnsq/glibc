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

#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>
#ಅನ್ತರ್ಭಾವ <string-fzb.h>
#ಅನ್ತರ್ಭಾವ <string-fzc.h>
#ಅನ್ತರ್ಭಾವ <string-fzi.h>
#ಅನ್ತರ್ಭಾವ <string-shift.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memchr

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MEMCHR
# define __memchr MEMCHR
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ __always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
sadd (uintptr_t x, uintptr_t y)
{
  ಹಿಂತಿರುಗಿ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)(y > UINTPTR_MAX - x ? UINTPTR_MAX : x + y);
}

/* Search no more than N bytes of S for C.  */
ಶೂನ್ಯ *
__memchr (ಶೂನ್ಯ ಸ್ಥಿರಾಂಕ *s, ಪೂರ್ಣಾಂಕ c_ಒಳ, size_t n)
{
  ಆದರೆ (__glibc_unlikely (n == 0))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  */
  ಸ್ಥಿರಾಂಕ op_t *ಶಬ್ದ_ptr = PTR_ALIGN_ಕೆಳಕ್ಕೆ (s, ಗಾತ್ರ (op_t));
  uintptr_t s_int = (uintptr_t) s;

  op_t ಶಬ್ದ = *ಶಬ್ದ_ptr;
  op_t repeated_c = repeat_ಬೈಟುಗಳು (c_ಒಳ);
  /* Compute the address of the last byte taking in consideration possible
     overflow.  */
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *lbyte = sadd (s_int, n - 1);
  /* And also the address of the word containing the last byte. */
  ಸ್ಥಿರಾಂಕ op_t *lword = (ಸ್ಥಿರಾಂಕ op_t *) PTR_ALIGN_ಕೆಳಕ್ಕೆ (lbyte, ಗಾತ್ರ (op_t));

  ಕಂಡುಹಿಡಿ_t ಮುಖವಾಡ = ಸರಿಸು_ಕಂಡುಹಿಡಿ (ಕಂಡುಹಿಡಿ_eq_all (ಶಬ್ದ, repeated_c), s_int);
  ಆದರೆ (ಮುಖವಾಡ != 0)
    {
      ಅಕ್ಷರ *ret = (ಅಕ್ಷರ *) s + ಸೂಚ್ಯಂಕ_ಮೊದಲ (ಮುಖವಾಡ);
      ಹಿಂತಿರುಗಿ (ret <= lbyte) ? ret : ಖಾಲಿ;
    }
  ಆದರೆ (ಶಬ್ದ_ptr == lword)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಶಬ್ದ = *++ಶಬ್ದ_ptr;
  ಆಗ (ಶಬ್ದ_ptr != lword)
    {
      ಆದರೆ (has_eq (ಶಬ್ದ, repeated_c))
	ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಮೊದಲ_eq (ಶಬ್ದ, repeated_c);
      ಶಬ್ದ = *++ಶಬ್ದ_ptr;
    }

  ಆದರೆ (has_eq (ಶಬ್ದ, repeated_c))
    {
      /* We found a match, but it might be in a byte past the end of the
	 array.  */
      ಅಕ್ಷರ *ret = (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಮೊದಲ_eq (ಶಬ್ದ, repeated_c);
      ಆದರೆ (ret <= lbyte)
	ಹಿಂತಿರುಗಿ ret;
    }
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMCHR
weak_alias (__memchr, memchr)
libc_hidden_builtin_def (memchr)
#ಆದರೆ_ಅಂತ್ಯ
