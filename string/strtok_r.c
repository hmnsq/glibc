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

#اگر_تعریف_شدہ HAVE_CONFIG_H
# include <config.h>
#اگر_ختم

#شامل <string.h>

#اگر_غیر_تعریف_شدہ _LIBC
/* Get specification.  */
# include "strtok_r.h"
# define __strtok_r strtok_r
#اگر_ختم

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
حرف *
__strtok_r (حرف *s, ثابت حرف *delim, حرف **save_ptr)
{
  حرف *انتہا;

  اگر (s == تہی)
    s = *save_ptr;

  اگر (*s == '\0')
    {
      *save_ptr = s;
      واپس تہی;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  اگر (*s == '\0')
    {
      *save_ptr = s;
      واپس تہی;
    }

  /* Find the end of the token.  */
  انتہا = s + strcspn (s, delim);
  اگر (*انتہا == '\0')
    {
      *save_ptr = انتہا;
      واپس s;
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *انتہا = '\0';
  *save_ptr = انتہا + 1;
  واپس s;
}
#اگر_تعریف_شدہ weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#اگر_ختم
