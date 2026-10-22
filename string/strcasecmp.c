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

#నిర్వచితమైతే HAVE_CONFIG_H
# include <config.h>
#అయితే_ముగింపు

#అన్తర్భావ <ctype.h>
#అన్తర్భావ <string.h>

#నిర్వచితం_కాకపోతే _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) tolower (Ch)
#లేకపోతే
# include <locale/localeinfo.h>
# ifdef USE_లోపల_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#అయితే_ముగింపు

#నిర్వచితమైతే USE_లోపల_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#లేకపోతే
# define LOCALE_PARAM
#అయితే_ముగింపు

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
పూర్ణాంకం
__strcasecmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2 LOCALE_PARAM)
{
#ఒకవేళ defined _LIBC && !defined USE_లోపల_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#అయితే_ముగింపు
  స్థిరరాశి గుర్తులేని అక్షరం *p1 = (స్థిరరాశి గుర్తులేని అక్షరం *) s1;
  స్థిరరాశి గుర్తులేని అక్షరం *p2 = (స్థిరరాశి గుర్తులేని అక్షరం *) s2;
  పూర్ణాంకం ఫలితం;

  ఒకవేళ (p1 == p2)
    తిరిగి 0;

  అయితే ((ఫలితం = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    ఒకవేళ (*p1++ == '\0')
      ఆపు;

  తిరిగి ఫలితం;
}
#నిర్వచితం_కాకపోతే __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#అయితే_ముగింపు
