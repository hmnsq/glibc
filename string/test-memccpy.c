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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "memccpy"
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
ਖਾਲੀ *
simple_memccpy (ਖਾਲੀ *dst, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ c, size_t n)
{
  ਅਚਲ ਅੱਖਰ *s = src;
  ਅੱਖਰ *d = dst;

  ਜਦੋਂ (n-- > 0)
    ਜੇ ((*d++ = *s++) == (ਅੱਖਰ) c)
      ਵਾਪਸ d;

  ਵਾਪਸ ਨਿਰਾ;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(*proto_t) (ਖਾਲੀ *, ਅਚਲ ਖਾਲੀ *, ਪੂਰਨ c, size_t);

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਖਾਲੀ *dst, ਅਚਲ ਖਾਲੀ *src, ਪੂਰਨ c, size_t len,
	     size_t n)
{
  ਖਾਲੀ *expect = len > n ? ਨਿਰਾ : (ਅੱਖਰ *) dst + len;
  ਜੇ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ਵਾਪਸ;
    }

  ਜੇ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, ਪੂਰਨ c, size_t len, size_t n,
	 ਪੂਰਨ max_char)
{
  size_t i;
  ਅੱਖਰ *s1, *s2;

  align1 &= 7;
  ਜੇ (align1 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= 7;
  ਜੇ (align2 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (ਅੱਖਰ *) (buf1 + align1);
  s2 = (ਅੱਖਰ *) (buf2 + align2);

  ਲਈ (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ਜੇ (s1[i] == (ਅੱਖਰ) c)
	--s1[i];
    }
  s1[len - 1] = c;
  ਲਈ (i = len; i + align1 < ਪੰਨਾ_ਮਾਪ && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, len, ਮਾਪ, ਬਹੁਲਕ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = buf1 + ਪੰਨਾ_ਮਾਪ - 512;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = buf2 + ਪੰਨਾ_ਮਾਪ - 512;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *res, c;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      ਬਹੁਲਕ = random ();
      c = random ();
      ਜੇ (ਬਹੁਲਕ & 1)
	{
	  ਮਾਪ = random () & 255;
	  align1 = 512 - ਮਾਪ - (random () & 15);
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = align1 - (random () & 24);
	  ਨਹੀਂਤਾਂ
	    align2 = align1 - (random () & 31);
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ਜੇ (ਬਹੁਲਕ & 8)
	    len = ਮਾਪ - (random () & 31);
	  ਨਹੀਂਤਾਂ
	    len = 512;
	  ਜੇ (len >= 512)
	    len = random () & 511;
	}
      ਨਹੀਂਤਾਂ
	{
	  align1 = random () & 31;
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = random () & 31;
	  ਨਹੀਂਤਾਂ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ਜੇ (align2 > j)
	    j = align2;
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      ਮਾਪ = random () & 511;
	      ਜੇ (ਮਾਪ + j > 512)
		ਮਾਪ = 512 - j - (random() & 31);
	    }
	  ਨਹੀਂਤਾਂ
	    ਮਾਪ = 512 - j;
	  ਜੇ ((ਬਹੁਲਕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ਜੇ (j > 512)
	j = 512;
      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align1)
	    p1[i] = c;
	  ਨਹੀਂਤਾਂ
	    {
	      p1[i] = random () & 255;
	      ਜੇ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (ਅੱਖਰ) c, ਮਾਪ);
	  ਜੇ (len >= ਮਾਪ)
	    expect = ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    expect = p2 + align2 + len + 1;

	  ਜੇ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, ਮਾਪ, c, res, expect);
	      ret = 1;
	    }
	  ਲਈ (j = 0; j < align2 + 64; ++j)
	    {
	      ਜੇ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }
	  j = align2 + len + 1;
	  ਜੇ (ਮਾਪ + align2 < j)
	    j = ਮਾਪ + align2;
	  ਲਈ (; j < 512; ++j)
	    {
	      ਜੇ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }
	  j = len + 1;
	  ਜੇ (ਮਾਪ < j)
	    j = ਮਾਪ;
	  ਜੇ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
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

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
