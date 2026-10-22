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

#घोषणा STRNCPY_परिणाम(dst, len, n) ((dst) + ((len) > (n) ? (n) : (len)))
#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "stpncpy"
#अन्यथा
# define TEST_NAME "wcpncpy"
#पूर्ण_अगर /* WIDE */
#समावेश "test-string.h"
#अगर_अघोषित WIDE
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
#पूर्ण_अगर /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, स्थिर CHAR *, माप_प्रकार);
CHAR *STUPID_STPNCPY (CHAR *, स्थिर CHAR *, माप_प्रकार);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, स्थिर CHAR *src, माप_प्रकार n)
{
  जबतक (n--)
    अगर ((*dst++ = *src++) == '\0')
      {
	माप_प्रकार i;

	क्रम (i = 0; i < n; ++i)
	  dst[i] = '\0';
	वापस dst - 1;
      }
  वापस dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, स्थिर CHAR *src, माप_प्रकार n)
{
  माप_प्रकार nc = STRNLEN (src, n);
  माप_प्रकार i;

  क्रम (i = 0; i < nc; ++i)
    dst[i] = src[i];
  क्रम (; i < n; ++i)
    dst[i] = '\0';
  वापस dst + nc;
}

#अघोषित CHAR
#समावेश "test-strncpy.c"
