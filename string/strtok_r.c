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

#اگر_تعریف_شده HAVE_CONFIG_H
# include <config.h>
#پایان_اگر

#ضمن <string.h>

#اگر_تعریف_نشده _LIBC
/* Get specification.  */
# include "strtok_r.h"
# define __strtok_r strtok_r
#پایان_اگر

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
  حرف *انتها;

  إذا (s == عدم)
    s = *save_ptr;

  إذا (*s == '\0')
    {
      *save_ptr = s;
      أرجع عدم;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  إذا (*s == '\0')
    {
      *save_ptr = s;
      أرجع عدم;
    }

  /* Find the end of the token.  */
  انتها = s + strcspn (s, delim);
  إذا (*انتها == '\0')
    {
      *save_ptr = انتها;
      أرجع s;
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *انتها = '\0';
  *save_ptr = انتها + 1;
  أرجع s;
}
#اگر_تعریف_شده weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#پایان_اگر
