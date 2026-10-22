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

#ಅನ್ತರ್ಭಾವ <string.h>

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strncpy

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRNCPY
 #ವ್ಯಾಖ್ಯಾನಿಸು STRNCPY strncpy
#ಆದರೆ_ಅಂತ್ಯ

ಅಕ್ಷರ *
STRNCPY (ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n)
{
  size_t ಗಾತ್ರ_2 = __strnlen (s2, n);
  ಆದರೆ (ಗಾತ್ರ_2 != n)
    memset (s1 + ಗಾತ್ರ_2, '\0', n - ಗಾತ್ರ_2);
  ಹಿಂತಿರುಗಿ ಸ್ಮರಣೆ_ನಕಲು (s1, s2, ಗಾತ್ರ_2);
}
libc_hidden_builtin_def (strncpy)
