/* Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <string.h>

#నిర్వచితం_కాకపోతే STRING_TYPE
# define STRING_TYPE అక్షరం
# define STRCOLL strcoll
# define STRCOLL_L __strcoll_l
# define USE_HIDDEN_DEF
#అయితే_ముగింపు

#అన్తర్భావ "../locale/localeinfo.h"


పూర్ణాంకం
STRCOLL (స్థిరరాశి STRING_TYPE *s1, స్థిరరాశి STRING_TYPE *s2)
{
  తిరిగి STRCOLL_L (s1, s2, _NL_CURRENT_LOCALE);
}

#నిర్వచితమైతే USE_HIDDEN_DEF
libc_hidden_def (STRCOLL)
#అయితే_ముగింపు
