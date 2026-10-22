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

#جيڪڏهن_وصف_ٿيل HAVE_CONFIG_H
# include <config.h>
#جيڪڏهن_پورو

#ضمن <ctype.h>
#ضمن <string.h>

#جيڪڏهن_وصف_نه_ٿيل _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#وإلا
# include <locale/localeinfo.h>
# ifdef USE_اندريون_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل USE_اندريون_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#وإلا
# define LOCALE_PARAM
#جيڪڏهن_پورو

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
صحيح
__strcasecmp (ثابت حرف *s1, ثابت حرف *s2 LOCALE_PARAM)
{
#إذا defined _LIBC && !defined USE_اندريون_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#جيڪڏهن_پورو
  ثابت بنانشان حرف *p1 = (ثابت بنانشان حرف *) s1;
  ثابت بنانشان حرف *p2 = (ثابت بنانشان حرف *) s2;
  صحيح نتيجو;

  إذا (p1 == p2)
    أرجع 0;

  طالما ((نتيجو = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    إذا (*p1++ == '\0')
      اكسر;

  أرجع نتيجو;
}
#جيڪڏهن_وصف_نه_ٿيل __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#جيڪڏهن_پورو
