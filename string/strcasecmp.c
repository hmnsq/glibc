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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_CONFIG_H
# include <config.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#ਨਹੀਂਤਾਂ
# include <locale/localeinfo.h>
# ifdef USE_ਵਿੱਚ_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਵਿੱਚ_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#ਨਹੀਂਤਾਂ
# define LOCALE_PARAM
#ਜੇ_ਅੰਤ

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
ਪੂਰਨ
__strcasecmp (ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2 LOCALE_PARAM)
{
#ਜੇ defined _LIBC && !defined USE_ਵਿੱਚ_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#ਜੇ_ਅੰਤ
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s1;
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s2;
  ਪੂਰਨ ਨਤੀਜਾ;

  ਜੇ (p1 == p2)
    ਵਾਪਸ 0;

  ਜਦੋਂ ((ਨਤੀਜਾ = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    ਜੇ (*p1++ == '\0')
      ਰੋਕੋ;

  ਵਾਪਸ ਨਤੀਜਾ;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#ਜੇ_ਅੰਤ
