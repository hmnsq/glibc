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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ضمن <string.h>
#ضمن <ctype.h>

#ifndef weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#אחרת
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#אחרת
# define LOCALE_PARAM
#endif

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
صحيح
__strncasecmp (ثابت حرف *s1, ثابت حرف *s2, size_t n LOCALE_PARAM)
{
#אם defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  ثابت unsigned حرف *p1 = (ثابت unsigned حرف *) s1;
  ثابت unsigned حرف *p2 = (ثابت unsigned حرف *) s2;
  صحيح result;

  אם (p1 == p2 || n == 0)
    החזר 0;

  כלעוד ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    אם (*p1++ == '\0' || --n == 0)
      اكسر;

  החזר result;
}
#ifndef __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#endif
