/* Reentrant string tokenizer.  Generic version.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#నిర్వచితం_కాకపోతే _LIBC
/* Get specification.  */
# include "strtok_r.h"
# define __strtok_r strtok_r
#అయితే_ముగింపు

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/
అక్షరం *
__strtok_r (అక్షరం *s, స్థిరరాశి అక్షరం *delim, అక్షరం **save_ptr)
{
  అక్షరం *చివర;

  ఒకవేళ (s == ఖాళీ)
    s = *save_ptr;

  ఒకవేళ (*s == '\0')
    {
      *save_ptr = s;
      తిరిగి ఖాళీ;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  ఒకవేళ (*s == '\0')
    {
      *save_ptr = s;
      తిరిగి ఖాళీ;
    }

  /* Find the end of the token.  */
  చివర = s + strcspn (s, delim);
  ఒకవేళ (*చివర == '\0')
    {
      *save_ptr = చివర;
      తిరిగి s;
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *చివర = '\0';
  *save_ptr = చివర + 1;
  తిరిగి s;
}
#నిర్వచితమైతే weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#అయితే_ముగింపు
