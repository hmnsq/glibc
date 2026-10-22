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
#അല്ലെങ്കിൽ
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#അന്തര്ഭാവ "test-string.h"

#ifndef WIDE
# define STRCSPN strcspn
# define CHAR അക്ഷരം
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN strlen
#അല്ലെങ്കിൽ
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#endif /* WIDE */

തരനിർവചനം size_t (*proto_t) (സ്ഥിരം CHAR *, സ്ഥിരം CHAR *);
size_t SIMPLE_STRCSPN (സ്ഥിരം CHAR *, സ്ഥിരം CHAR *);
size_t STUPID_STRCSPN (സ്ഥിരം CHAR *, സ്ഥിരം CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (സ്ഥിരം CHAR *s, സ്ഥിരം CHAR *rej)
{
  സ്ഥിരം CHAR *r, *str = s;
  CHAR c;

  ആകുമ്പോൾ ((c = *s++) != '\0')
    വേണ്ടി (r = rej; *r != '\0'; ++r)
      എങ്കിൽ (*r == c)
	തിരികെ s - str - 1;
  തിരികെ s - str - 1;
}

size_t
STUPID_STRCSPN (സ്ഥിരം CHAR *s, സ്ഥിരം CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  വേണ്ടി (i = 0; i < ns; ++i)
    വേണ്ടി (j = 0; j < nrej; ++j)
      എങ്കിൽ (s[i] == rej[j])
	തിരികെ i;
  തിരികെ i;
}

#undef CHAR
#undef STRLEN
#അന്തര്ഭാവ "test-strpbrk.c"
