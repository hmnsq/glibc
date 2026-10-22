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

#నిర్వచితమైతే HAVE_CONFIG_H
# include <config.h>
#అయితే_ముగింపు

#అన్తర్భావ <string.h>
#అన్తర్భావ <ctype.h>

#నిర్వచితం_కాకపోతే weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#లేకపోతే
# include <locale/localeinfo.h>
# ifdef USE_లోపల_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#అయితే_ముగింపు

#నిర్వచితమైతే USE_లోపల_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#లేకపోతే
# define LOCALE_PARAM
#అయితే_ముగింపు

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
పూర్ణాంకం
__strncasecmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2, size_t n LOCALE_PARAM)
{
#ఒకవేళ defined _LIBC && !defined USE_లోపల_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#అయితే_ముగింపు
  స్థిరరాశి గుర్తులేని అక్షరం *p1 = (స్థిరరాశి గుర్తులేని అక్షరం *) s1;
  స్థిరరాశి గుర్తులేని అక్షరం *p2 = (స్థిరరాశి గుర్తులేని అక్షరం *) s2;
  పూర్ణాంకం ఫలితం;

  ఒకవేళ (p1 == p2 || n == 0)
    తిరిగి 0;

  అయితే ((ఫలితం = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    ఒకవేళ (*p1++ == '\0' || --n == 0)
      ఆపు;

  తిరిగి ఫలితం;
}
#నిర్వచితం_కాకపోతే __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#అయితే_ముగింపు
