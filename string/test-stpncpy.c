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
#അല്ലെങ്കിൽ
# define TEST_NAME "wcpncpy"
#endif /* WIDE */
#അന്തര്ഭാവ "test-string.h"
#ifndef WIDE
# define CHAR അക്ഷരം
# define SIMPLE_STPNCPY simple_stpncpy
# define STUPID_STPNCPY stupid_stpncpy
# define STPNCPY stpncpy
# define STRNLEN strnlen
#അല്ലെങ്കിൽ
# include <wchar.h>
# define CHAR wchar_t
# define SIMPLE_STPNCPY simple_wcpncpy
# define STUPID_STPNCPY stupid_wcpncpy
# define STPNCPY wcpncpy
# define STRNLEN wcsnlen
#endif /* WIDE */

CHAR *SIMPLE_STPNCPY (CHAR *, സ്ഥിരം CHAR *, size_t);
CHAR *STUPID_STPNCPY (CHAR *, സ്ഥിരം CHAR *, size_t);

IMPL (STUPID_STPNCPY, 0)
IMPL (SIMPLE_STPNCPY, 0)
IMPL (STPNCPY, 1)

CHAR *
SIMPLE_STPNCPY (CHAR *dst, സ്ഥിരം CHAR *src, size_t n)
{
  ആകുമ്പോൾ (n--)
    എങ്കിൽ ((*dst++ = *src++) == '\0')
      {
	size_t i;

	വേണ്ടി (i = 0; i < n; ++i)
	  dst[i] = '\0';
	തിരികെ dst - 1;
      }
  തിരികെ dst;
}

CHAR *
STUPID_STPNCPY (CHAR *dst, സ്ഥിരം CHAR *src, size_t n)
{
  size_t nc = STRNLEN (src, n);
  size_t i;

  വേണ്ടി (i = 0; i < nc; ++i)
    dst[i] = src[i];
  വേണ്ടി (; i < n; ++i)
    dst[i] = '\0';
  തിരികെ dst + nc;
}

#undef CHAR
#അന്തര്ഭാവ "test-strncpy.c"
