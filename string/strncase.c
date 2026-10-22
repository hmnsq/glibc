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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <ctype.h>

#ifndef weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#অন্যথা
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#অন্যথা
# define LOCALE_PARAM
#endif

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
পূর্ণসংখ্যা
__strncasecmp (ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2, size_t n LOCALE_PARAM)
{
#যদি defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  ধ্রুবক unsigned অক্ষর *p1 = (ধ্রুবক unsigned অক্ষর *) s1;
  ধ্রুবক unsigned অক্ষর *p2 = (ধ্রুবক unsigned অক্ষর *) s2;
  পূর্ণসংখ্যা ফলাফল;

  যদি (p1 == p2 || n == 0)
    ফেরত 0;

  যখন ((ফলাফল = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    যদি (*p1++ == '\0' || --n == 0)
      বিরতি;

  ফেরত ফলাফল;
}
#ifndef __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#endif
