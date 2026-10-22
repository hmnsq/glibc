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

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strcat

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRCAT
# define STRCAT strcat
#ಆದರೆ_ಅಂತ್ಯ

/* Append SRC on the end of DEST.  */
ಅಕ್ಷರ *
STRCAT (ಅಕ್ಷರ *dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src)
{
  strcpy (dest + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (dest), src);
  ಹಿಂತಿರುಗಿ dest;
}
libc_hidden_builtin_def (strcat)
