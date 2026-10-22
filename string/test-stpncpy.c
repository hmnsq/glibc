/* Test and measure stpncpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು STRNCPY_ಫಲಿತಾಂಶ(dst, len, n) ((dst) + ((len) > (n) ? (n) : (len)))
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "stpncpy"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcpncpy"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define CHAR ಅಕ್ಷರ
# define SIMPLE_STPNCPY simple_stpncpy
# define STUPID_STPNCPY stupid_stpncpy
# define STPNCPY stpncpy
# define STRNLEN strnlen
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define CHAR wchar_t
# define SIMPLE_STPNCPY simple_wcpncpy
# define STUPID_STPNCPY stupid_wcpncpy
# define STPNCPY wcpncpy
# define STRNLEN wcsnlen
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, ಸ್ಥಿರಾಂಕ CHAR *, size_t);
CHAR *STUPID_STPNCPY (CHAR *, ಸ್ಥಿರಾಂಕ CHAR *, size_t);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src, size_t n)
{
  ಆಗ (n--)
    ಆದರೆ ((*dst++ = *src++) == '\0')
      {
	size_t i;

	ಗಾಗಿ (i = 0; i < n; ++i)
	  dst[i] = '\0';
	ಹಿಂತಿರುಗಿ dst - 1;
      }
  ಹಿಂತಿರುಗಿ dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src, size_t n)
{
  size_t nc = STRNLEN (src, n);
  size_t i;

  ಗಾಗಿ (i = 0; i < nc; ++i)
    dst[i] = src[i];
  ಗಾಗಿ (; i < n; ++i)
    dst[i] = '\0';
  ಹಿಂತಿರುಗಿ dst + nc;
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHAR
#ಅನ್ತರ್ಭಾವ "test-strncpy.c"
