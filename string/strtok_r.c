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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_CONFIG_H
# include <config.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <string.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _LIBC
/* Get specification.  */
# include "strtok_r.h"
# define __strtok_r strtok_r
#ಆದರೆ_ಅಂತ್ಯ

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
ಅಕ್ಷರ *
__strtok_r (ಅಕ್ಷರ *s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *delim, ಅಕ್ಷರ **save_ptr)
{
  ಅಕ್ಷರ *ಕೊನೆ;

  ಆದರೆ (s == ಖಾಲಿ)
    s = *save_ptr;

  ಆದರೆ (*s == '\0')
    {
      *save_ptr = s;
      ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  ಆದರೆ (*s == '\0')
    {
      *save_ptr = s;
      ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

  /* Find the end of the token.  */
  ಕೊನೆ = s + strcspn (s, delim);
  ಆದರೆ (*ಕೊನೆ == '\0')
    {
      *save_ptr = ಕೊನೆ;
      ಹಿಂತಿರುಗಿ s;
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *ಕೊನೆ = '\0';
  *save_ptr = ಕೊನೆ + 1;
  ಹಿಂತಿರುಗಿ s;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#ಆದರೆ_ಅಂತ್ಯ
