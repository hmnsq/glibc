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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <ctype.h>

#ifndef weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#അല്ലെങ്കിൽ
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#അല്ലെങ്കിൽ
# define LOCALE_PARAM
#endif

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
പൂർണ്ണസംഖ്യ
__strncasecmp (സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2, size_t n LOCALE_PARAM)
{
#എങ്കിൽ defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  സ്ഥിരം unsigned അക്ഷരം *p1 = (സ്ഥിരം unsigned അക്ഷരം *) s1;
  സ്ഥിരം unsigned അക്ഷരം *p2 = (സ്ഥിരം unsigned അക്ഷരം *) s2;
  പൂർണ്ണസംഖ്യ result;

  എങ്കിൽ (p1 == p2 || n == 0)
    തിരികെ 0;

  ആകുമ്പോൾ ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    എങ്കിൽ (*p1++ == '\0' || --n == 0)
      നിർത്തുക;

  തിരികെ result;
}
#ifndef __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#endif
