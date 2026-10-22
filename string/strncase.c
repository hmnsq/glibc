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

#اگر_تعریف_شدہ HAVE_CONFIG_H
# include <config.h>
#اگر_ختم

#شامل <string.h>
#شامل <ctype.h>

#اگر_غیر_تعریف_شدہ weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#ورنہ
# include <locale/localeinfo.h>
# ifdef USE_اندر_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#اگر_ختم

#اگر_تعریف_شدہ USE_اندر_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#ورنہ
# define LOCALE_PARAM
#اگر_ختم

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
صحیح
__strncasecmp (ثابت حرف *s1, ثابت حرف *s2, size_t n LOCALE_PARAM)
{
#اگر defined _LIBC && !defined USE_اندر_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#اگر_ختم
  ثابت غیرعلامتی حرف *p1 = (ثابت غیرعلامتی حرف *) s1;
  ثابت غیرعلامتی حرف *p2 = (ثابت غیرعلامتی حرف *) s2;
  صحیح نتیجہ;

  اگر (p1 == p2 || n == 0)
    واپس 0;

  جب ((نتیجہ = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    اگر (*p1++ == '\0' || --n == 0)
      توڑو;

  واپس نتیجہ;
}
#اگر_غیر_تعریف_شدہ __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#اگر_ختم
