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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ STRLEN
# define __strlen STRLEN
#ಆದರೆ_ಅಂತ್ಯ

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
  /* Align pointer to sizeof op_t.  */
  ಸ್ಥಿರಾಂಕ uintptr_t s_int = (uintptr_t) str;
  ಸ್ಥಿರಾಂಕ op_t *ಶಬ್ದ_ptr = (ಸ್ಥಿರಾಂಕ op_t*) PTR_ALIGN_ಕೆಳಕ್ಕೆ (str, ಗಾತ್ರ (op_t));

  op_t ಶಬ್ದ = *ಶಬ್ದ_ptr;
  ಕಂಡುಹಿಡಿ_t ಮುಖವಾಡ = ಸರಿಸು_ಕಂಡುಹಿಡಿ (ಕಂಡುಹಿಡಿ_zero_all (ಶಬ್ದ), s_int);
  ಆದರೆ (ಮುಖವಾಡ != 0)
    ಹಿಂತಿರುಗಿ ಸೂಚ್ಯಂಕ_ಮೊದಲ (ಮುಖವಾಡ);

  ಮಾಡು
    ಶಬ್ದ = *++ಶಬ್ದ_ptr;
  ಆಗ (! has_zero (ಶಬ್ದ));

  ಹಿಂತಿರುಗಿ ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) ಶಬ್ದ_ptr) + ಸೂಚ್ಯಂಕ_ಮೊದಲ_zero (ಶಬ್ದ) - str;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRLEN
weak_alias (__strlen, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ)
libc_hidden_builtin_def (ಅಕ್ಷರಸರಣಿ_ಉದ್ದ)
#ಆದರೆ_ಅಂತ್ಯ
