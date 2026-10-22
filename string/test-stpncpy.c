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

#define STRNCPY_RESULT(dst, len, n) ((dst) + ((len) > (n) ? (n) : (len)))
#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "stpncpy"
#નહીંતર
# define TEST_NAME "wcpncpy"
#endif /* WIDE */
#અન્તર્ભાવ "test-string.h"
#ifndef WIDE
# define CHAR અક્ષર
# define SIMPLE_STPNCPY simple_stpncpy
# define STUPID_STPNCPY stupid_stpncpy
# define STPNCPY stpncpy
# define STRNLEN strnlen
#નહીંતર
# include <wchar.h>
# define CHAR wchar_t
# define SIMPLE_STPNCPY simple_wcpncpy
# define STUPID_STPNCPY stupid_wcpncpy
# define STPNCPY wcpncpy
# define STRNLEN wcsnlen
#endif /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, અચલ CHAR *, size_t);
CHAR *STUPID_STPNCPY (CHAR *, અચલ CHAR *, size_t);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, અચલ CHAR *src, size_t n)
{
  જ્યારે (n--)
    જો ((*dst++ = *src++) == '\0')
      {
	size_t i;

	માટે (i = 0; i < n; ++i)
	  dst[i] = '\0';
	પાછા dst - 1;
      }
  પાછા dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, અચલ CHAR *src, size_t n)
{
  size_t nc = STRNLEN (src, n);
  size_t i;

  માટે (i = 0; i < nc; ++i)
    dst[i] = src[i];
  માટે (; i < n; ++i)
    dst[i] = '\0';
  પાછા dst + nc;
}

#undef CHAR
#અન્તર્ભાવ "test-strncpy.c"
