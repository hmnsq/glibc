/* Test and measure memrchr functions.
   Copyright (C) 2013-2026 Free Software Foundation, Inc.
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
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "memrchr"
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(*proto_t) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನಿಸು MEMRCHR __memrchr_default
#ಅನ್ತರ್ಭಾವ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
ಅಕ್ಷರ *
simple_memrchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಪೂರ್ಣಾಂಕ c, size_t n)
{
  s = s + n;
  ಆಗ (n--)
    ಆದರೆ (*--s == (ಅಕ್ಷರ) c)
      ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) s;
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಪೂರ್ಣಾಂಕ c, size_t n, ಅಕ್ಷರ *exp_res)
{
  ಅಕ್ಷರ *res = CALL (impl, s, c, n);
  ಆದರೆ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len, ಪೂರ್ಣಾಂಕ seek_char)
{
  size_t i;
  ಅಕ್ಷರ *ಫಲಿತಾಂಶ;

  align &= 7;
  ಆದರೆ (align + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ಆದರೆ (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ಆದರೆ (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      ಫಲಿತಾಂಶ = (ಅಕ್ಷರ *) (buf1 + align + pos);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಫಲಿತಾಂಶ = ಖಾಲಿ;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ಅಕ್ಷರ *) (buf1 + align), seek_char, len, ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len;
  ಪೂರ್ಣಾಂಕ seek_char;
  ಅಕ್ಷರ *ಫಲಿತಾಂಶ;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p = buf1 + ಪುಟ_ಗಾತ್ರ - 512;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ಆದರೆ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ಆದರೆ (pos >= len)
	len = pos + (random () & 7);
      ಆದರೆ (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      ಆದರೆ (j > 512)
        j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == pos + align)
	    p[i] = seek_char;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p[i] = random () & 255;
	      ಆದರೆ (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ಆದರೆ (pos < len)
	ಫಲಿತಾಂಶ = (ಅಕ್ಷರ *) (p + pos + align);
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ = ಖಾಲಿ;

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (ಅಕ್ಷರ *) (p + align), seek_char, len) != ಫಲಿತಾಂಶ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ಅಕ್ಷರ *) (p + align), seek_char, len),
		   ಫಲಿತಾಂಶ, p);
	    ret = 1;
	  }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      /* Test len == 0.  */
      do_test (i, i, 0, 0);
      do_test (i, i, 0, 23);

      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (0, i, 256, 23);
      do_test (0, i, 256, 0);
      do_test (i, i, 256, 23);
      do_test (i, i, 256, 0);

    }
  ಗಾಗಿ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);
      do_test (i, i, i + 1, 23);
      do_test (i, i, i + 1, 0);

      do_test (0, 1, i + 1, 23);
      do_test (0, 2, i + 1, 0);
      do_test (i, 1, i + 1, 23);
      do_test (i, 2, i + 1, 0);
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
