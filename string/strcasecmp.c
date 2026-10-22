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

#ଅନ୍ତର୍ଭାଵ <ctype.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ifndef _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#ଅନ୍ୟଥା
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#ଅନ୍ୟଥା
# define LOCALE_PARAM
#endif

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା
__strcasecmp (ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2 LOCALE_PARAM)
{
#ଯଦି defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  ଅଚଳ unsigned ଅକ୍ଷର *p1 = (ଅଚଳ unsigned ଅକ୍ଷର *) s1;
  ଅଚଳ unsigned ଅକ୍ଷର *p2 = (ଅଚଳ unsigned ଅକ୍ଷର *) s2;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result;

  ଯଦି (p1 == p2)
    ଫେରନ୍ତୁ 0;

  ଯେତେବେଳେ ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    ଯଦି (*p1++ == '\0')
      ଭାଙ୍ଗ;

  ଫେରନ୍ତୁ result;
}
#ifndef __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#endif
