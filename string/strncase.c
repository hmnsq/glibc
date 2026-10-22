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

#यदि_परिभाषितम् HAVE_CONFIG_H
# include <config.h>
#यदि_अन्तः

#अन्तर्भाव <string.h>
#अन्तर्भाव <ctype.h>

#यदि_अपरिभाषितम् weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#अन्यथा
# include <locale/localeinfo.h>
# ifdef USE_अन्तर्_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#यदि_अन्तः

#यदि_परिभाषितम् USE_अन्तर्_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#अन्यथा
# define LOCALE_PARAM
#यदि_अन्तः

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
पूर्णाङ्क
__strncasecmp (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2, size_t n LOCALE_PARAM)
{
#यदि defined _LIBC && !defined USE_अन्तर्_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#यदि_अन्तः
  ध्रुव अचिह्नित वर्ण *p1 = (ध्रुव अचिह्नित वर्ण *) s1;
  ध्रुव अचिह्नित वर्ण *p2 = (ध्रुव अचिह्नित वर्ण *) s2;
  पूर्णाङ्क परिणाम;

  यदि (p1 == p2 || n == 0)
    प्रत्यागम 0;

  यावत् ((परिणाम = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    यदि (*p1++ == '\0' || --n == 0)
      भङ्ग;

  प्रत्यागम परिणाम;
}
#यदि_अपरिभाषितम् __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#यदि_अन्तः
