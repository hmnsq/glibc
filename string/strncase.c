/* Compare at most N characters of two strings without taking care for
   the case.
   Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#ಇಲ್ಲದಿದ್ದರೆ
# include <locale/localeinfo.h>
# ifdef USE_ಒಳ_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ಒಳ_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#ಇಲ್ಲದಿದ್ದರೆ
# define LOCALE_PARAM
#ಆದರೆ_ಅಂತ್ಯ

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
ಪೂರ್ಣಾಂಕ
__strncasecmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n LOCALE_PARAM)
{
#ಆದರೆ defined _LIBC && !defined USE_ಒಳ_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#ಆದರೆ_ಅಂತ್ಯ
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s1;
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s2;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;

  ಆದರೆ (p1 == p2 || n == 0)
    ಹಿಂತಿರುಗಿ 0;

  ಆಗ ((ಫಲಿತಾಂಶ = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    ಆದರೆ (*p1++ == '\0' || --n == 0)
      ನಿಲ್ಲಿಸು;

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#ಆದರೆ_ಅಂತ್ಯ
