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

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strrchr

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRRCHR
# define STRRCHR strrchr
#ಆದರೆ_ಅಂತ್ಯ

/* Find the last occurrence of C in S.  */
ಅಕ್ಷರ *
STRRCHR (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಪೂರ್ಣಾಂಕ c)
{
  ಹಿಂತಿರುಗಿ __memrchr (s, c, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (s) + 1);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ weak_alias
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು rindex
weak_alias (strrchr, rindex)
#ಆದರೆ_ಅಂತ್ಯ
libc_hidden_builtin_def (strrchr)
