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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRNCPY_ਨਤੀਜਾ(dst, len, n) ((dst) + ((len) > (n) ? (n) : (len)))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "stpncpy"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcpncpy"
#ਜੇ_ਅੰਤ /* WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define CHAR ਅੱਖਰ
# define SIMPLE_STPNCPY simple_stpncpy
# define STUPID_STPNCPY stupid_stpncpy
# define STPNCPY stpncpy
# define STRNLEN strnlen
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define CHAR wchar_t
# define SIMPLE_STPNCPY simple_wcpncpy
# define STUPID_STPNCPY stupid_wcpncpy
# define STPNCPY wcpncpy
# define STRNLEN wcsnlen
#ਜੇ_ਅੰਤ /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, ਅਚਲ CHAR *, size_t);
CHAR *STUPID_STPNCPY (CHAR *, ਅਚਲ CHAR *, size_t);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, ਅਚਲ CHAR *src, size_t n)
{
  ਜਦੋਂ (n--)
    ਜੇ ((*dst++ = *src++) == '\0')
      {
	size_t i;

	ਲਈ (i = 0; i < n; ++i)
	  dst[i] = '\0';
	ਵਾਪਸ dst - 1;
      }
  ਵਾਪਸ dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, ਅਚਲ CHAR *src, size_t n)
{
  size_t nc = STRNLEN (src, n);
  size_t i;

  ਲਈ (i = 0; i < nc; ++i)
    dst[i] = src[i];
  ਲਈ (; i < n; ++i)
    dst[i] = '\0';
  ਵਾਪਸ dst + nc;
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHAR
#ਅਨ੍ਤਰ੍ਭਾਵ "test-strncpy.c"
