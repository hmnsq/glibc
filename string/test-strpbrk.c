/* Test and measure strpbrk functions.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRPBRK_ಫಲಿತಾಂಶ
# define STRPBRK_ಫಲಿತಾಂಶ(s, pos) ((s)[(pos)] ? (s) + (pos) : ಖಾಲಿ)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# ಇಲ್ಲದಿದ್ದರೆ
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# ಇಲ್ಲದಿದ್ದರೆ
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CHAR *(*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *rej)
{
  ಸ್ಥಿರಾಂಕ CHAR *r;
  CHAR c;

  ಆಗ ((c = *s++) != '\0')
    ಗಾಗಿ (r = rej; *r != '\0'; ++r)
      ಆದರೆ (*r == c)
       ಹಿಂತಿರುಗಿ (CHAR *) s - 1;
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ /* !STRPBRK_RESULT */

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  ಆದರೆ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (ಶೂನ್ಯ *) res, (ಶೂನ್ಯ *) exp_res);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  ಪೂರ್ಣಾಂಕ c;
  RES_TYPE ಫಲಿತಾಂಶ;
  CHAR *rej, *s;

  align &= 7;
  ಆದರೆ ((align + pos + 10) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ || len > 240)
    ಹಿಂತಿರುಗಿ;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      ಆದರೆ (!rej[i])
	rej[i] = random () & BIG_CHAR;
      ಆದರೆ (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  ಗಾಗಿ (c = 1; c <= BIG_CHAR; ++c)
    ಆದರೆ (STRCHR (rej, c) == ಖಾಲಿ)
      ನಿಲ್ಲಿಸು;

  ಗಾಗಿ (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      ಆದರೆ (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  ಆದರೆ (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  ಆದರೆ (s[pos])
    {
      ಗಾಗಿ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  ಫಲಿತಾಂಶ = STRPBRK_ಫಲಿತಾಂಶ (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE ಫಲಿತಾಂಶ;
  ಪೂರ್ಣಾಂಕ c;
  UCHAR *p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 512;
  UCHAR *rej;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ಆದರೆ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ಆದರೆ (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      ಆದರೆ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ಆದರೆ (random () & 1)
	rlen = random () & 63;
      ಇಲ್ಲದಿದ್ದರೆ
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ) - rlen - 1 - (random () & 7);
      ಗಾಗಿ (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  ಆದರೆ (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  ಆದರೆ (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      ಗಾಗಿ (c = 1; c <= BIG_CHAR; ++c)
	ಆದರೆ (STRCHR ((CHAR *) rej, c) == ಖಾಲಿ)
	  ನಿಲ್ಲಿಸು;
      j = (pos > len ? pos : len) + align + 64;
      ಆದರೆ (j > 512)
	j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == len + align)
	    p[i] = '\0';
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p[i] = random () & BIG_CHAR;
	      ಆದರೆ (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  ಆದರೆ (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      ಫಲಿತಾಂಶ = STRPBRK_ಫಲಿತಾಂಶ ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != ಫಲಿತಾಂಶ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (ಶೂನ್ಯ *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (ಶೂನ್ಯ *) ಫಲಿತಾಂಶ);
	    ret = 1;
	  }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  ಗಾಗಿ (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
