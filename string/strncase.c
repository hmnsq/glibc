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

#جيڪڏهن_وصف_ٿيل HAVE_CONFIG_H
# include <config.h>
#جيڪڏهن_پورو

#ضمن <string.h>
#ضمن <ctype.h>

#جيڪڏهن_وصف_نه_ٿيل weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#وإلا
# include <locale/localeinfo.h>
# ifdef USE_اندريون_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل USE_اندريون_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#وإلا
# define LOCALE_PARAM
#جيڪڏهن_پورو

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
صحيح
__strncasecmp (ثابت حرف *s1, ثابت حرف *s2, size_t n LOCALE_PARAM)
{
#إذا defined _LIBC && !defined USE_اندريون_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#جيڪڏهن_پورو
  ثابت بنانشان حرف *p1 = (ثابت بنانشان حرف *) s1;
  ثابت بنانشان حرف *p2 = (ثابت بنانشان حرف *) s2;
  صحيح نتيجو;

  إذا (p1 == p2 || n == 0)
    أرجع 0;

  طالما ((نتيجو = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    إذا (*p1++ == '\0' || --n == 0)
      اكسر;

  أرجع نتيجو;
}
#جيڪڏهن_وصف_نه_ٿيل __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#جيڪڏهن_پورو
