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
#अन्यथा
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#अन्तर्भाव "test-string.h"

#ifndef WIDE
# define STRCSPN strcspn
# define CHAR वर्ण
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN strlen
#अन्यथा
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#endif /* WIDE */

प्रकारनिर्देश size_t (*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *);
size_t SIMPLE_STRCSPN (ध्रुव CHAR *, ध्रुव CHAR *);
size_t STUPID_STRCSPN (ध्रुव CHAR *, ध्रुव CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ध्रुव CHAR *s, ध्रुव CHAR *rej)
{
  ध्रुव CHAR *r, *str = s;
  CHAR c;

  यावत् ((c = *s++) != '\0')
    प्रति (r = rej; *r != '\0'; ++r)
      यदि (*r == c)
	प्रत्यागम s - str - 1;
  प्रत्यागम s - str - 1;
}

size_t
STUPID_STRCSPN (ध्रुव CHAR *s, ध्रुव CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  प्रति (i = 0; i < ns; ++i)
    प्रति (j = 0; j < nrej; ++j)
      यदि (s[i] == rej[j])
	प्रत्यागम i;
  प्रत्यागम i;
}

#undef CHAR
#undef STRLEN
#अन्तर्भाव "test-strpbrk.c"
