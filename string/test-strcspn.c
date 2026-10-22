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
#ಅನ್ಯಥಾ
# define TEST_NAME "wcscspn"
#endif /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ifndef WIDE
# define STRCSPN strcspn
# define CHAR ವರ್ಣ
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN strlen
#ಅನ್ಯಥಾ
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#endif /* WIDE */

ಪ್ರಕಾರನಿರ್ದೇಶ size_t (*proto_t) (ಧ್ರುವ CHAR *, ಧ್ರುವ CHAR *);
size_t SIMPLE_STRCSPN (ಧ್ರುವ CHAR *, ಧ್ರುವ CHAR *);
size_t STUPID_STRCSPN (ಧ್ರುವ CHAR *, ಧ್ರುವ CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ಧ್ರುವ CHAR *s, ಧ್ರುವ CHAR *rej)
{
  ಧ್ರುವ CHAR *r, *str = s;
  CHAR c;

  ಯಾವತ್ ((c = *s++) != '\0')
    ಪ್ರತಿ (r = rej; *r != '\0'; ++r)
      ಯದಿ (*r == c)
	ಪ್ರತ್ಯಾಗಮ s - str - 1;
  ಪ್ರತ್ಯಾಗಮ s - str - 1;
}

size_t
STUPID_STRCSPN (ಧ್ರುವ CHAR *s, ಧ್ರುವ CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  ಪ್ರತಿ (i = 0; i < ns; ++i)
    ಪ್ರತಿ (j = 0; j < nrej; ++j)
      ಯದಿ (s[i] == rej[j])
	ಪ್ರತ್ಯಾಗಮ i;
  ಪ್ರತ್ಯಾಗಮ i;
}

#undef CHAR
#undef STRLEN
#ಅನ್ತರ್ಭಾವ "test-strpbrk.c"
