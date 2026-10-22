/* Test strcspn functions.
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

#تعریف_کرو STRPBRK_نتیجہ(s, pos) (pos)
#تعریف_کرو RES_TYPE size_t
#تعریف_کرو TEST_MAIN
#جے_بنا_تعریف WIDE
# define TEST_NAME "strcspn"
#وإلا
# define TEST_NAME "wcscspn"
#جے_انت /* WIDE */
#ضمن "test-string.h"

#جے_بنا_تعریف WIDE
# define STRCSPN strcspn
# define CHAR حرف
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN لڑی_لمبائی
#وإلا
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#جے_انت /* WIDE */

تعريفنوع size_t (*proto_t) (ثابت CHAR *, ثابت CHAR *);
size_t SIMPLE_STRCSPN (ثابت CHAR *, ثابت CHAR *);
size_t STUPID_STRCSPN (ثابت CHAR *, ثابت CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ثابت CHAR *s, ثابت CHAR *rej)
{
  ثابت CHAR *r, *str = s;
  CHAR c;

  طالما ((c = *s++) != '\0')
    لكل (r = rej; *r != '\0'; ++r)
      إذا (*r == c)
	أرجع s - str - 1;
  أرجع s - str - 1;
}

size_t
STUPID_STRCSPN (ثابت CHAR *s, ثابت CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  لكل (i = 0; i < ns; ++i)
    لكل (j = 0; j < nrej; ++j)
      إذا (s[i] == rej[j])
	أرجع i;
  أرجع i;
}

#تعریف_رد CHAR
#تعریف_رد STRLEN
#ضمن "test-strpbrk.c"
