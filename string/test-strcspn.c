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
#define RES_TYPE माप_प्रकार
#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strcspn"
#अन्यथा
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#अन्तर्भाव "test-string.h"

#ifndef WIDE
# define STRCSPN म_खोज
# define CHAR वर्ण
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
#endif /* WIDE */

प्रकारनिर्देश माप_प्रकार (*proto_t) (अचर CHAR *, अचर CHAR *);
माप_प्रकार SIMPLE_STRCSPN (अचर CHAR *, अचर CHAR *);
माप_प्रकार STUPID_STRCSPN (अचर CHAR *, अचर CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

माप_प्रकार
SIMPLE_STRCSPN (अचर CHAR *s, अचर CHAR *rej)
{
  अचर CHAR *r, *str = s;
  CHAR c;

  जबसम्म ((c = *s++) != '\0')
    लागि (r = rej; *r != '\0'; ++r)
      यदि (*r == c)
	फर्काऊ s - str - 1;
  फर्काऊ s - str - 1;
}

माप_प्रकार
STUPID_STRCSPN (अचर CHAR *s, अचर CHAR *rej)
{
  माप_प्रकार ns = STRLEN (s), nrej = STRLEN (rej);
  माप_प्रकार i, j;

  लागि (i = 0; i < ns; ++i)
    लागि (j = 0; j < nrej; ++j)
      यदि (s[i] == rej[j])
	फर्काऊ i;
  फर्काऊ i;
}

#undef CHAR
#undef STRLEN
#अन्तर्भाव "test-strpbrk.c"
