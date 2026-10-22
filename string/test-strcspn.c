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

#घोषणा STRPBRK_परिणाम(s, pos) (pos)
#घोषणा RES_TYPE माप_प्रकार
#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "strcspn"
#अन्यथा
# define TEST_NAME "wcscspn"
#पूर्ण_अगर /* WIDE */
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRCSPN म_खोज
# define CHAR अक्षर
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN म_माप
#अन्यथा
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR ब_अक्षर_प्रकार
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#पूर्ण_अगर /* WIDE */

प्रकार माप_प्रकार (*proto_t) (स्थिर CHAR *, स्थिर CHAR *);
माप_प्रकार SIMPLE_STRCSPN (स्थिर CHAR *, स्थिर CHAR *);
माप_प्रकार STUPID_STRCSPN (स्थिर CHAR *, स्थिर CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

माप_प्रकार
SIMPLE_STRCSPN (स्थिर CHAR *s, स्थिर CHAR *rej)
{
  स्थिर CHAR *r, *str = s;
  CHAR c;

  जबतक ((c = *s++) != '\0')
    क्रम (r = rej; *r != '\0'; ++r)
      अगर (*r == c)
	वापस s - str - 1;
  वापस s - str - 1;
}

माप_प्रकार
STUPID_STRCSPN (स्थिर CHAR *s, स्थिर CHAR *rej)
{
  माप_प्रकार ns = STRLEN (s), nrej = STRLEN (rej);
  माप_प्रकार i, j;

  क्रम (i = 0; i < ns; ++i)
    क्रम (j = 0; j < nrej; ++j)
      अगर (s[i] == rej[j])
	वापस i;
  वापस i;
}

#अघोषित CHAR
#अघोषित STRLEN
#समावेश "test-strpbrk.c"
