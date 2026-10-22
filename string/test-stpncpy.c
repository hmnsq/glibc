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
#अन्यथा
# define TEST_NAME "wcpncpy"
#endif /* WIDE */
#अन्तर्भाव "test-string.h"
#ifndef WIDE
# define CHAR अक्षर
# define SIMPLE_STPNCPY simple_stpncpy
# define STUPID_STPNCPY stupid_stpncpy
# define STPNCPY stpncpy
# define STRNLEN strnlen
#अन्यथा
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define SIMPLE_STPNCPY simple_wcpncpy
# define STUPID_STPNCPY stupid_wcpncpy
# define STPNCPY wcpncpy
# define STRNLEN wcsnlen
#endif /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, स्थिरांक CHAR *, माप_प्रकार);
CHAR *STUPID_STPNCPY (CHAR *, स्थिरांक CHAR *, माप_प्रकार);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, स्थिरांक CHAR *src, माप_प्रकार n)
{
  पर्यंत (n--)
    जर ((*dst++ = *src++) == '\0')
      {
	माप_प्रकार i;

	साठी (i = 0; i < n; ++i)
	  dst[i] = '\0';
	परत dst - 1;
      }
  परत dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, स्थिरांक CHAR *src, माप_प्रकार n)
{
  माप_प्रकार nc = STRNLEN (src, n);
  माप_प्रकार i;

  साठी (i = 0; i < nc; ++i)
    dst[i] = src[i];
  साठी (; i < n; ++i)
    dst[i] = '\0';
  परत dst + nc;
}

#undef CHAR
#अन्तर्भाव "test-strncpy.c"
