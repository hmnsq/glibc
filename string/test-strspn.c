/* Test and measure strspn functions.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strspn"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcsspn"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRSPN strspn
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define SIMPLE_STRSPN simple_strspn
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *acc)
{
  ಸ್ಥಿರಾಂಕ CHAR *r, *str = s;
  CHAR c;

  ಆಗ ((c = *s++) != '\0')
    {
      ಗಾಗಿ (r = acc; *r != '\0'; ++r)
	ಆದರೆ (*r == c)
	  ನಿಲ್ಲಿಸು;
      ಆದರೆ (*r == '\0')
	ಹಿಂತಿರುಗಿ s - str - 1;
    }
  ಹಿಂತಿರುಗಿ s - str - 1;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಸ್ಥಿರಾಂಕ CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
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
  CHAR *acc, *s;

  align &= 7;
  ಆದರೆ ((align + pos + 10) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ || len > 240 || ! len)
    ಹಿಂತಿರುಗಿ;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      ಆದರೆ (!acc[i])
	acc[i] = random () & BIG_CHAR;
      ಆದರೆ (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  ಗಾಗಿ (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  ಆದರೆ (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಗಾಗಿ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 512;
  UCHAR *acc;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      ಆದರೆ (random () & 1)
	alen = random () & 63;
      ಇಲ್ಲದಿದ್ದರೆ
	alen = random () & 15;
      ಆದರೆ (!alen)
	pos = 0;
      ಇಲ್ಲದಿದ್ದರೆ
	pos = random () & 511;
      ಆದರೆ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ಆದರೆ (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ) - alen - 1 - (random () & 7);
      ಗಾಗಿ (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  ಆದರೆ (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  ಆದರೆ (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      ಆದರೆ (j > 512)
	j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == len + align)
	    p[i] = '\0';
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      ಆದರೆ (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ಇಲ್ಲದಿದ್ದರೆ
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (CHAR *) (p + align),
		  (CHAR *) acc) != (pos < len ? pos : len))
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %zd != %zd",
		   n, impl->name, align, acc, alen, pos, len,
		   CALL (impl, (CHAR *) (p + align), (CHAR *) acc),
		   (pos < len ? pos : len));
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
