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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRPBRK_ਨਤੀਜਾ(s, pos) (pos)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RES_TYPE size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "strcspn"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcscspn"
#ਜੇ_ਅੰਤ /* WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRCSPN strcspn
# define CHAR ਅੱਖਰ
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#ਜੇ_ਅੰਤ /* WIDE */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*proto_t) (ਅਚਲ CHAR *, ਅਚਲ CHAR *);
size_t SIMPLE_STRCSPN (ਅਚਲ CHAR *, ਅਚਲ CHAR *);
size_t STUPID_STRCSPN (ਅਚਲ CHAR *, ਅਚਲ CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ਅਚਲ CHAR *s, ਅਚਲ CHAR *rej)
{
  ਅਚਲ CHAR *r, *str = s;
  CHAR c;

  ਜਦੋਂ ((c = *s++) != '\0')
    ਲਈ (r = rej; *r != '\0'; ++r)
      ਜੇ (*r == c)
	ਵਾਪਸ s - str - 1;
  ਵਾਪਸ s - str - 1;
}

size_t
STUPID_STRCSPN (ਅਚਲ CHAR *s, ਅਚਲ CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  ਲਈ (i = 0; i < ns; ++i)
    ਲਈ (j = 0; j < nrej; ++j)
      ਜੇ (s[i] == rej[j])
	ਵਾਪਸ i;
  ਵਾਪਸ i;
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHAR
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRLEN
#ਅਨ੍ਤਰ੍ਭਾਵ "test-strpbrk.c"
