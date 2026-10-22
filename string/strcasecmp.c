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

#اگر_تعریف_شده HAVE_CONFIG_H
# include <config.h>
#پایان_اگر

#ضمن <ctype.h>
#ضمن <string.h>

#اگر_تعریف_نشده _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#وإلا
# include <locale/localeinfo.h>
# ifdef USE_درون_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#پایان_اگر

#اگر_تعریف_شده USE_درون_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#وإلا
# define LOCALE_PARAM
#پایان_اگر

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
صحيح
__strcasecmp (ثابت حرف *s1, ثابت حرف *s2 LOCALE_PARAM)
{
#إذا defined _LIBC && !defined USE_درون_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#پایان_اگر
  ثابت بیعلامت حرف *p1 = (ثابت بیعلامت حرف *) s1;
  ثابت بیعلامت حرف *p2 = (ثابت بیعلامت حرف *) s2;
  صحيح نتیجه;

  إذا (p1 == p2)
    أرجع 0;

  طالما ((نتیجه = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    إذا (*p1++ == '\0')
      اكسر;

  أرجع نتیجه;
}
#اگر_تعریف_نشده __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#پایان_اگر
