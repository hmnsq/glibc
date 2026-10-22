/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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
# include "config.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <sys/types.h>

#ಆದರೆ defined _LIBC || defined STDC_ಶೀರ್ಷಿಕೆಗಳು
# include <stdlib.h>
# include <string.h>
#ಇಲ್ಲದಿದ್ದರೆ
ಅಕ್ಷರ *ಸ್ಮರಣೆ_ಕೊಡು ();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __strndup
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strndup

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ weak_alias
# define __strndup strndup
#ಆದರೆ_ಅಂತ್ಯ

ಅಕ್ಷರ *
__strndup (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, size_t n)
{
  size_t len = __strnlen (s, n);
  ಅಕ್ಷರ *new = (ಅಕ್ಷರ *) ಸ್ಮರಣೆ_ಕೊಡು (len + 1);

  ಆದರೆ (new == ಖಾಲಿ)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  new[len] = '\0';
  ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) ಸ್ಮರಣೆ_ನಕಲು (new, s, len);
}
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ libc_hidden_def
libc_hidden_def (__strndup)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ weak_alias
weak_alias (__strndup, strndup)
#ಆದರೆ_ಅಂತ್ಯ
