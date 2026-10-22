/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __strchrnul
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strchrnul

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ STRCHRNUL
# define __strchrnul STRCHRNUL
#ಆದರೆ_ಅಂತ್ಯ

/* Find the first occurrence of C in S or the final NUL byte.  */
ಅಕ್ಷರ *
__strchrnul (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ c_ಒಳ)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  ಸ್ಥಿರಾಂಕ op_t *ಶಬ್ದ_ptr = (ಸ್ಥಿರಾಂಕ op_t *) PTR_ALIGN_ಕೆಳಕ್ಕೆ (str, ಗಾತ್ರ (op_t));

  op_t repeated_c = repeat_ಬೈಟುಗಳು (c_ಒಳ);

  op_t ಶಬ್ದ = *ಶಬ್ದ_ptr;
  ಕಂಡುಹಿಡಿ_t ಮುಖವಾಡ = ಸರಿಸು_ಕಂಡುಹಿಡಿ (ಕಂಡುಹಿಡಿ_zero_eq_all (ಶಬ್ದ, repeated_c), s_int);
  ಆದರೆ (ಮುಖವಾಡ != 0)
    ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) str + ಸೂಚ್ಯಂಕ_ಮೊದಲ (ಮುಖವಾಡ);

  ಮಾಡು
    ಶಬ್ದ = *++ಶಬ್ದ_ptr;
  ಆಗ (! has_zero_eq (ಶಬ್ದ, repeated_c));

  ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) ಶಬ್ದ_ptr + ಸೂಚ್ಯಂಕ_ಮೊದಲ_zero_eq (ಶಬ್ದ, repeated_c);
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#ಆದರೆ_ಅಂತ್ಯ
