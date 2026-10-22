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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#অন্তর্ভাব <ctype.h>
#অন্তর্ভাব <string.h>

#ifndef _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#অন্যথা
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#অন্যথা
# define LOCALE_PARAM
#endif

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
পূর্ণসংখ্যা
__strcasecmp (ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2 LOCALE_PARAM)
{
#যদি defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  ধ্রুবক unsigned অক্ষর *p1 = (ধ্রুবক unsigned অক্ষর *) s1;
  ধ্রুবক unsigned অক্ষর *p2 = (ধ্রুবক unsigned অক্ষর *) s2;
  পূর্ণসংখ্যা ফলাফল;

  যদি (p1 == p2)
    ফেরত 0;

  যখন ((ফলাফল = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    যদি (*p1++ == '\0')
      বিরতি;

  ফেরত ফলাফল;
}
#ifndef __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#endif
