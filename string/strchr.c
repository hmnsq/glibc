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

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strchr
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸೂಚ್ಯಂಕ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ STRCHR
# define strchr STRCHR
#ಆದರೆ_ಅಂತ್ಯ

/* Find the first occurrence of C in S.  */
ಅಕ್ಷರ *
strchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಪೂರ್ಣಾಂಕ c_ಒಳ)
{
  ಅಕ್ಷರ *r = __strchrnul (s, c_ಒಳ);
  ಹಿಂತಿರುಗಿ (*(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)r == (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)c_ಒಳ) ? r : ಖಾಲಿ;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRCHR
weak_alias (strchr, ಸೂಚ್ಯಂಕ)
libc_hidden_builtin_def (strchr)
#ಆದರೆ_ಅಂತ್ಯ
