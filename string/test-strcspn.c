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

#define STRPBRK_ফলাফল(s, pos) (pos)
#define RES_TYPE size_t
#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strcspn"
#অন্যথা
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#অন্তর্ভাব "test-string.h"

#ifndef WIDE
# define STRCSPN strcspn
# define CHAR অক্ষর
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN strlen
#অন্যথা
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#endif /* WIDE */

প্রকারলেখ size_t (*proto_t) (ধ্রুবক CHAR *, ধ্রুবক CHAR *);
size_t SIMPLE_STRCSPN (ধ্রুবক CHAR *, ধ্রুবক CHAR *);
size_t STUPID_STRCSPN (ধ্রুবক CHAR *, ধ্রুবক CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ধ্রুবক CHAR *s, ধ্রুবক CHAR *rej)
{
  ধ্রুবক CHAR *r, *str = s;
  CHAR c;

  যখন ((c = *s++) != '\0')
    জন্য (r = rej; *r != '\0'; ++r)
      যদি (*r == c)
	ফেরত s - str - 1;
  ফেরত s - str - 1;
}

size_t
STUPID_STRCSPN (ধ্রুবক CHAR *s, ধ্রুবক CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  জন্য (i = 0; i < ns; ++i)
    জন্য (j = 0; j < nrej; ++j)
      যদি (s[i] == rej[j])
	ফেরত i;
  ফেরত i;
}

#undef CHAR
#undef STRLEN
#অন্তর্ভাব "test-strpbrk.c"
