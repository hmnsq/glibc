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
#شامل "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
تهی *
simple_memccpy (تهی *dst, ثابت تهی *src, صحیح c, size_t n)
{
  ثابت نویسه *s = src;
  نویسه *d = dst;

  وقتی (n-- > 0)
    اگر ((*d++ = *s++) == (نویسه) c)
      بازگشت d;

  بازگشت پوچ;
}

تعریفنوع تهی *(*proto_t) (تهی *, ثابت تهی *, صحیح c, size_t);

ایستا تهی
do_one_test (impl_t *impl, تهی *dst, ثابت تهی *src, صحیح c, size_t len,
	     size_t n)
{
  تهی *expect = len > n ? پوچ : (نویسه *) dst + len;
  اگر (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      بازگشت;
    }

  اگر (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      بازگشت;
    }
}

ایستا تهی
do_test (size_t align1, size_t align2, صحیح c, size_t len, size_t n,
	 صحیح max_char)
{
  size_t i;
  نویسه *s1, *s2;

  align1 &= 7;
  اگر (align1 + len >= page_size)
    بازگشت;

  align2 &= 7;
  اگر (align2 + len >= page_size)
    بازگشت;

  s1 = (نویسه *) (buf1 + align1);
  s2 = (نویسه *) (buf2 + align2);

  برای (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      اگر (s1[i] == (نویسه) c)
	--s1[i];
    }
  s1[len - 1] = c;
  برای (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ایستا تهی
do_random_tests (تهی)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned نویسه *p1 = buf1 + page_size - 512;
  unsigned نویسه *p2 = buf2 + page_size - 512;
  unsigned نویسه *res, c;

  برای (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      اگر (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  اگر (mode & 2)
	    align2 = align1 - (random () & 24);
	  وگرنه
	    align2 = align1 - (random () & 31);
	  اگر (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  اگر (mode & 8)
	    len = size - (random () & 31);
	  وگرنه
	    len = 512;
	  اگر (len >= 512)
	    len = random () & 511;
	}
      وگرنه
	{
	  align1 = random () & 31;
	  اگر (mode & 2)
	    align2 = random () & 31;
	  وگرنه
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  اگر (align2 > j)
	    j = align2;
	  اگر (mode & 4)
	    {
	      size = random () & 511;
	      اگر (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  وگرنه
	    size = 512 - j;
	  اگر ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      اگر (j > 512)
	j = 512;
      برای (i = 0; i < j; i++)
	{
	  اگر (i == len + align1)
	    p1[i] = c;
	  وگرنه
	    {
	      p1[i] = random () & 255;
	      اگر (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned نویسه *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (نویسه) c, size);
	  اگر (len >= size)
	    expect = پوچ;
	  وگرنه
	    expect = p2 + align2 + len + 1;

	  اگر (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  برای (j = 0; j < align2 + 64; ++j)
	    {
	      اگر (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  بشکن;
		}
	    }
	  j = align2 + len + 1;
	  اگر (size + align2 < j)
	    j = size + align2;
	  برای (; j < 512; ++j)
	    {
	      اگر (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  بشکن;
		}
	    }
	  j = len + 1;
	  اگر (size < j)
	    j = size;
	  اگر (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

صحیح
test_main (تهی)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  برای (i = 1; i < 8; ++i)
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

  برای (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  بازگشت ret;
}

#شامل <support/test-driver.c>
