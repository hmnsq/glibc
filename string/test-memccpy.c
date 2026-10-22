/* Test and measure memccpy functions.
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
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "memccpy"
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ *
simple_memccpy (ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ c, size_t n)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s = src;
  ಅಕ್ಷರ *d = dst;

  ಆಗ (n-- > 0)
    ಆದರೆ ((*d++ = *s++) == (ಅಕ್ಷರ) c)
      ಹಿಂತಿರುಗಿ d;

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *(*proto_t) (ಶೂನ್ಯ *, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, ಪೂರ್ಣಾಂಕ c, size_t);

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಂಕ c, size_t len,
	     size_t n)
{
  ಶೂನ್ಯ *expect = len > n ? ಖಾಲಿ : (ಅಕ್ಷರ *) dst + len;
  ಆದರೆ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, ಪೂರ್ಣಾಂಕ c, size_t len, size_t n,
	 ಪೂರ್ಣಾಂಕ max_char)
{
  size_t i;
  ಅಕ್ಷರ *s1, *s2;

  align1 &= 7;
  ಆದರೆ (align1 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= 7;
  ಆದರೆ (align2 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (ಅಕ್ಷರ *) (buf1 + align1);
  s2 = (ಅಕ್ಷರ *) (buf2 + align2);

  ಗಾಗಿ (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ಆದರೆ (s1[i] == (ಅಕ್ಷರ) c)
	--s1[i];
    }
  s1[len - 1] = c;
  ಗಾಗಿ (i = len; i + align1 < ಪುಟ_ಗಾತ್ರ && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len, ಗಾತ್ರ_2, ಬಹುಲಕ;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = buf1 + ಪುಟ_ಗಾತ್ರ - 512;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = buf2 + ಪುಟ_ಗಾತ್ರ - 512;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *res, c;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      ಬಹುಲಕ = random ();
      c = random ();
      ಆದರೆ (ಬಹುಲಕ & 1)
	{
	  ಗಾತ್ರ_2 = random () & 255;
	  align1 = 512 - ಗಾತ್ರ_2 - (random () & 15);
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = align1 - (random () & 24);
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 - (random () & 31);
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ಆದರೆ (ಬಹುಲಕ & 8)
	    len = ಗಾತ್ರ_2 - (random () & 31);
	  ಇಲ್ಲದಿದ್ದರೆ
	    len = 512;
	  ಆದರೆ (len >= 512)
	    len = random () & 511;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  align1 = random () & 31;
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = random () & 31;
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ಆದರೆ (align2 > j)
	    j = align2;
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      ಗಾತ್ರ_2 = random () & 511;
	      ಆದರೆ (ಗಾತ್ರ_2 + j > 512)
		ಗಾತ್ರ_2 = 512 - j - (random() & 31);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಗಾತ್ರ_2 = 512 - j;
	  ಆದರೆ ((ಬಹುಲಕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ಆದರೆ (j > 512)
	j = 512;
      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == len + align1)
	    p1[i] = c;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p1[i] = random () & 255;
	      ಆದರೆ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (ಅಕ್ಷರ) c, ಗಾತ್ರ_2);
	  ಆದರೆ (len >= ಗಾತ್ರ_2)
	    expect = ಖಾಲಿ;
	  ಇಲ್ಲದಿದ್ದರೆ
	    expect = p2 + align2 + len + 1;

	  ಆದರೆ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, ಗಾತ್ರ_2, c, res, expect);
	      ret = 1;
	    }
	  ಗಾಗಿ (j = 0; j < align2 + 64; ++j)
	    {
	      ಆದರೆ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  j = align2 + len + 1;
	  ಆದರೆ (ಗಾತ್ರ_2 + align2 < j)
	    j = ಗಾತ್ರ_2 + align2;
	  ಗಾಗಿ (; j < 512; ++j)
	    {
	      ಆದರೆ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  j = len + 1;
	  ಆದರೆ (ಗಾತ್ರ_2 < j)
	    j = ಗಾತ್ರ_2;
	  ಆದರೆ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, i, 12, 16, 16, 127);
      do_test (i, i, 23, 16, 16, 255);
      do_test (i, 2 * i, 28, 16, 16, 127);
      do_test (2 * i, i, 31, 16, 16, 255);
      do_test (8 - i, 2 * i, 1, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 17, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 0, 1 << i, 2 << i, 255);
      do_test (2 * i, 8 - i, i, 2 << i, 1 << i, 255);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
