/* Copyright (C) 1993-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_CONFIG_H
# include <config.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _LIBC
# include <string.h>
#ಇಲ್ಲದಿದ್ದರೆ
# include <sys/types.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STPNCPY
# ifdef weak_alias
#  define STPNCPY	__stpncpy
weak_alias (__stpncpy, stpncpy)
# ಇಲ್ಲದಿದ್ದರೆ
#  define STPNCPY	stpncpy
# endif
#ಆದರೆ_ಅಂತ್ಯ

/* Copy no more than N characters of SRC to DEST, returning the address of
   the terminating '\0' in DEST, if any, or else DEST + N.  */
ಅಕ್ಷರ *
STPNCPY (ಅಕ್ಷರ *dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t n)
{
  size_t ಗಾತ್ರ_2 = __strnlen (src, n);
  ಸ್ಮರಣೆ_ನಕಲು (dest, src, ಗಾತ್ರ_2);
  dest += ಗಾತ್ರ_2;
  ಆದರೆ (ಗಾತ್ರ_2 == n)
    ಹಿಂತಿರುಗಿ dest;
  ಹಿಂತಿರುಗಿ memset (dest, '\0', n - ಗಾತ್ರ_2);
}
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ weak_alias
libc_hidden_def (__stpncpy)
#ಆದರೆ_ಅಂತ್ಯ
