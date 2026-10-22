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

#അന്തര്ഭാവ <ctype.h>
#അന്തര്ഭാവ <string.h>

#ifndef _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#അല്ലെങ്കിൽ
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#അല്ലെങ്കിൽ
# define LOCALE_PARAM
#endif

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
പൂർണ്ണസംഖ്യ
__strcasecmp (സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2 LOCALE_PARAM)
{
#എങ്കിൽ defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  സ്ഥിരം unsigned അക്ഷരം *p1 = (സ്ഥിരം unsigned അക്ഷരം *) s1;
  സ്ഥിരം unsigned അക്ഷരം *p2 = (സ്ഥിരം unsigned അക്ഷരം *) s2;
  പൂർണ്ണസംഖ്യ result;

  എങ്കിൽ (p1 == p2)
    തിരികെ 0;

  ആകുമ്പോൾ ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    എങ്കിൽ (*p1++ == '\0')
      നിർത്തുക;

  തിരികെ result;
}
#ifndef __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#endif
