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

#ವ್ಯಾಖ್ಯಾನಿಸು STRPBRK_ಫಲಿತಾಂಶ(s, pos) (pos)
#ವ್ಯಾಖ್ಯಾನಿಸು RES_TYPE size_t
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strcspn"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcscspn"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRCSPN strcspn
# define CHAR ಅಕ್ಷರ
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);
size_t SIMPLE_STRCSPN (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);
size_t STUPID_STRCSPN (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *rej)
{
  ಸ್ಥಿರಾಂಕ CHAR *r, *str = s;
  CHAR c;

  ಆಗ ((c = *s++) != '\0')
    ಗಾಗಿ (r = rej; *r != '\0'; ++r)
      ಆದರೆ (*r == c)
	ಹಿಂತಿರುಗಿ s - str - 1;
  ಹಿಂತಿರುಗಿ s - str - 1;
}

size_t
STUPID_STRCSPN (ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  ಗಾಗಿ (i = 0; i < ns; ++i)
    ಗಾಗಿ (j = 0; j < nrej; ++j)
      ಆದರೆ (s[i] == rej[j])
	ಹಿಂತಿರುಗಿ i;
  ಹಿಂತಿರುಗಿ i;
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHAR
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRLEN
#ಅನ್ತರ್ಭಾವ "test-strpbrk.c"
