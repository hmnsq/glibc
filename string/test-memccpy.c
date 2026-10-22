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
#অন্তর্ভাব "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
শূন্য *
simple_memccpy (শূন্য *dst, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা c, size_t n)
{
  ধ্রুবক অক্ষর *s = src;
  অক্ষর *d = dst;

  যখন (n-- > 0)
    যদি ((*d++ = *s++) == (অক্ষর) c)
      ফেরত d;

  ফেরত ফাঁকা;
}

প্রকারলেখ শূন্য *(*proto_t) (শূন্য *, ধ্রুবক শূন্য *, পূর্ণসংখ্যা c, size_t);

স্থির শূন্য
do_one_test (impl_t *impl, শূন্য *dst, ধ্রুবক শূন্য *src, পূর্ণসংখ্যা c, size_t len,
	     size_t n)
{
  শূন্য *expect = len > n ? ফাঁকা : (অক্ষর *) dst + len;
  যদি (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ফেরত;
    }

  যদি (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, পূর্ণসংখ্যা c, size_t len, size_t n,
	 পূর্ণসংখ্যা max_char)
{
  size_t i;
  অক্ষর *s1, *s2;

  align1 &= 7;
  যদি (align1 + len >= page_আকার)
    ফেরত;

  align2 &= 7;
  যদি (align2 + len >= page_আকার)
    ফেরত;

  s1 = (অক্ষর *) (buf1 + align1);
  s2 = (অক্ষর *) (buf2 + align2);

  জন্য (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      যদি (s1[i] == (অক্ষর) c)
	--s1[i];
    }
  s1[len - 1] = c;
  জন্য (i = len; i + align1 < page_আকার && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, len, আকার_2, mode;
  unsigned অক্ষর *p1 = buf1 + page_আকার - 512;
  unsigned অক্ষর *p2 = buf2 + page_আকার - 512;
  unsigned অক্ষর *res, c;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      যদি (mode & 1)
	{
	  আকার_2 = random () & 255;
	  align1 = 512 - আকার_2 - (random () & 15);
	  যদি (mode & 2)
	    align2 = align1 - (random () & 24);
	  অন্যথা
	    align2 = align1 - (random () & 31);
	  যদি (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  যদি (mode & 8)
	    len = আকার_2 - (random () & 31);
	  অন্যথা
	    len = 512;
	  যদি (len >= 512)
	    len = random () & 511;
	}
      অন্যথা
	{
	  align1 = random () & 31;
	  যদি (mode & 2)
	    align2 = random () & 31;
	  অন্যথা
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  যদি (align2 > j)
	    j = align2;
	  যদি (mode & 4)
	    {
	      আকার_2 = random () & 511;
	      যদি (আকার_2 + j > 512)
		আকার_2 = 512 - j - (random() & 31);
	    }
	  অন্যথা
	    আকার_2 = 512 - j;
	  যদি ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      যদি (j > 512)
	j = 512;
      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == len + align1)
	    p1[i] = c;
	  অন্যথা
	    {
	      p1[i] = random () & 255;
	      যদি (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned অক্ষর *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (অক্ষর) c, আকার_2);
	  যদি (len >= আকার_2)
	    expect = ফাঁকা;
	  অন্যথা
	    expect = p2 + align2 + len + 1;

	  যদি (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, আকার_2, c, res, expect);
	      ret = 1;
	    }
	  জন্য (j = 0; j < align2 + 64; ++j)
	    {
	      যদি (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  বিরতি;
		}
	    }
	  j = align2 + len + 1;
	  যদি (আকার_2 + align2 < j)
	    j = আকার_2 + align2;
	  জন্য (; j < 512; ++j)
	    {
	      যদি (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  বিরতি;
		}
	    }
	  j = len + 1;
	  যদি (আকার_2 < j)
	    j = আকার_2;
	  যদি (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 8; ++i)
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

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
