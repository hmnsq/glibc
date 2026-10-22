/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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
# include "config.h"
#అయితే_ముగింపు

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <sys/types.h>

#ఒకవేళ defined _LIBC || defined STDC_శీర్షికలు
# include <stdlib.h>
# include <string.h>
#లేకపోతే
అక్షరం *జ్ఞాపకం_ఇవ్వు ();
#అయితే_ముగింపు

#నిర్వచనం_రద్దు __strndup
#నిర్వచనం_రద్దు strndup

#నిర్వచితం_కాకపోతే weak_alias
# define __strndup strndup
#అయితే_ముగింపు

అక్షరం *
__strndup (స్థిరరాశి అక్షరం *s, size_t n)
{
  size_t len = __strnlen (s, n);
  అక్షరం *new = (అక్షరం *) జ్ఞాపకం_ఇవ్వు (len + 1);

  ఒకవేళ (new == ఖాళీ)
    తిరిగి ఖాళీ;

  new[len] = '\0';
  తిరిగి (అక్షరం *) జ్ఞాపకం_నకలు (new, s, len);
}
#నిర్వచితమైతే libc_hidden_def
libc_hidden_def (__strndup)
#అయితే_ముగింపు
#నిర్వచితమైతే weak_alias
weak_alias (__strndup, strndup)
#అయితే_ముగింపు
