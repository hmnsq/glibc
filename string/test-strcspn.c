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

#define STRPBRK_RESULT(s, pos) (pos)
#define RES_TYPE size_t
#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strcspn"
#இல்லையெனில்
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#அந்தர்பாவ "test-string.h"

#ifndef WIDE
# define STRCSPN strcspn
# define CHAR எழுத்து
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN strlen
#இல்லையெனில்
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#endif /* WIDE */

வகைவரை size_t (*proto_t) (மாறிலி CHAR *, மாறிலி CHAR *);
size_t SIMPLE_STRCSPN (மாறிலி CHAR *, மாறிலி CHAR *);
size_t STUPID_STRCSPN (மாறிலி CHAR *, மாறிலி CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (மாறிலி CHAR *s, மாறிலி CHAR *rej)
{
  மாறிலி CHAR *r, *str = s;
  CHAR c;

  போது ((c = *s++) != '\0')
    க்கு (r = rej; *r != '\0'; ++r)
      எனில் (*r == c)
	திரும்பு s - str - 1;
  திரும்பு s - str - 1;
}

size_t
STUPID_STRCSPN (மாறிலி CHAR *s, மாறிலி CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  க்கு (i = 0; i < ns; ++i)
    க்கு (j = 0; j < nrej; ++j)
      எனில் (s[i] == rej[j])
	திரும்பு i;
  திரும்பு i;
}

#undef CHAR
#undef STRLEN
#அந்தர்பாவ "test-strpbrk.c"
