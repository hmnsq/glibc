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

#شامل <ctype.h>
#شامل <string.h>

#ifndef _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#وگرنه
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#وگرنه
# define LOCALE_PARAM
#endif

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
صحیح
__strcasecmp (ثابت نویسه *s1, ثابت نویسه *s2 LOCALE_PARAM)
{
#اگر defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  ثابت unsigned نویسه *p1 = (ثابت unsigned نویسه *) s1;
  ثابت unsigned نویسه *p2 = (ثابت unsigned نویسه *) s2;
  صحیح result;

  اگر (p1 == p2)
    بازگشت 0;

  وقتی ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    اگر (*p1++ == '\0')
      بشکن;

  بازگشت result;
}
#ifndef __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#endif
