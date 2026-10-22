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
#అన్తర్భావ <config.h>
#అయితే_ముగింపు

#ఒకవేళ defined _LIBC || defined  STDC_శీర్షికలు
# include <stdlib.h>
# include <string.h>
#లేకపోతే
అక్షరం *జ్ఞాపకం_ఇవ్వు ();
అక్షరం *జ్ఞాపకం_నకలు ();
#అయితే_ముగింపు

#నిర్వచనం_రద్దు __strdup
#నిర్వచనం_రద్దు strdup

#నిర్వచితం_కాకపోతే weak_alias
# define __strdup strdup
#అయితే_ముగింపు

/* Duplicate S, returning an identical malloc'd string.  */
అక్షరం *
__strdup (స్థిరరాశి అక్షరం *s)
{
  size_t len = అక్షరశ్రేణి_పొడవు (s) + 1;
  శూన్య *new = జ్ఞాపకం_ఇవ్వు (len);

  ఒకవేళ (new == ఖాళీ)
    తిరిగి ఖాళీ;

  తిరిగి (అక్షరం *) జ్ఞాపకం_నకలు (new, s, len);
}
#నిర్వచితమైతే libc_hidden_def
libc_hidden_def (__strdup)
#అయితే_ముగింపు
#నిర్వచితమైతే weak_alias
weak_alias (__strdup, strdup)
#అయితే_ముగింపు
