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

#define TEST_MAIN
#define TEST_NAME "memccpy"
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ *
simple_memccpy (ಶೂನ್ಯ *dst, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ c, size_t n)
{
  ಧ್ರುವ ವರ್ಣ *s = src;
  ವರ್ಣ *d = dst;

  ಯಾವತ್ (n-- > 0)
    ಯದಿ ((*d++ = *s++) == (ವರ್ಣ) c)
      ಪ್ರತ್ಯಾಗಮ d;

  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *(*proto_t) (ಶೂನ್ಯ *, ಧ್ರುವ ಶೂನ್ಯ *, ಪೂರ್ಣಾಙ್ಕ c, size_t);

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಶೂನ್ಯ *dst, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ c, size_t len,
	     size_t n)
{
  ಶೂನ್ಯ *expect = len > n ? ರಿಕ್ತ : (ವರ್ಣ *) dst + len;
  ಯದಿ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, ಪೂರ್ಣಾಙ್ಕ c, size_t len, size_t n,
	 ಪೂರ್ಣಾಙ್ಕ max_char)
{
  size_t i;
  ವರ್ಣ *s1, *s2;

  align1 &= 7;
  ಯದಿ (align1 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= 7;
  ಯದಿ (align2 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  s1 = (ವರ್ಣ *) (buf1 + align1);
  s2 = (ವರ್ಣ *) (buf2 + align2);

  ಪ್ರತಿ (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ಯದಿ (s1[i] == (ವರ್ಣ) c)
	--s1[i];
    }
  s1[len - 1] = c;
  ಪ್ರತಿ (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned ವರ್ಣ *p1 = buf1 + page_size - 512;
  unsigned ವರ್ಣ *p2 = buf2 + page_size - 512;
  unsigned ವರ್ಣ *res, c;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      ಯದಿ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ಯದಿ (mode & 2)
	    align2 = align1 - (random () & 24);
	  ಅನ್ಯಥಾ
	    align2 = align1 - (random () & 31);
	  ಯದಿ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ಯದಿ (mode & 8)
	    len = size - (random () & 31);
	  ಅನ್ಯಥಾ
	    len = 512;
	  ಯದಿ (len >= 512)
	    len = random () & 511;
	}
      ಅನ್ಯಥಾ
	{
	  align1 = random () & 31;
	  ಯದಿ (mode & 2)
	    align2 = random () & 31;
	  ಅನ್ಯಥಾ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ಯದಿ (align2 > j)
	    j = align2;
	  ಯದಿ (mode & 4)
	    {
	      size = random () & 511;
	      ಯದಿ (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  ಅನ್ಯಥಾ
	    size = 512 - j;
	  ಯದಿ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ಯದಿ (j > 512)
	j = 512;
      ಪ್ರತಿ (i = 0; i < j; i++)
	{
	  ಯದಿ (i == len + align1)
	    p1[i] = c;
	  ಅನ್ಯಥಾ
	    {
	      p1[i] = random () & 255;
	      ಯದಿ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned ವರ್ಣ *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (ವರ್ಣ) c, size);
	  ಯದಿ (len >= size)
	    expect = ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    expect = p2 + align2 + len + 1;

	  ಯದಿ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  ಪ್ರತಿ (j = 0; j < align2 + 64; ++j)
	    {
	      ಯದಿ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ಭಙ್ಗ;
		}
	    }
	  j = align2 + len + 1;
	  ಯದಿ (size + align2 < j)
	    j = size + align2;
	  ಪ್ರತಿ (; j < 512; ++j)
	    {
	      ಯದಿ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ಭಙ್ಗ;
		}
	    }
	  j = len + 1;
	  ಯದಿ (size < j)
	    j = size;
	  ಯದಿ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 1; i < 8; ++i)
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

  ಪ್ರತಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
