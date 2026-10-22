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
simple_memccpy (শূন্য *dst, ধ্রুব শূন্য *src, পূর্ণাঙ্ক c, size_t n)
{
  ধ্রুব বর্ণ *s = src;
  বর্ণ *d = dst;

  যাবত্ (n-- > 0)
    যদি ((*d++ = *s++) == (বর্ণ) c)
      প্রত্যাগম d;

  প্রত্যাগম রিক্ত;
}

প্রকারনির্দেশ শূন্য *(*proto_t) (শূন্য *, ধ্রুব শূন্য *, পূর্ণাঙ্ক c, size_t);

স্থির শূন্য
do_one_test (impl_t *impl, শূন্য *dst, ধ্রুব শূন্য *src, পূর্ণাঙ্ক c, size_t len,
	     size_t n)
{
  শূন্য *expect = len > n ? রিক্ত : (বর্ণ *) dst + len;
  যদি (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      প্রত্যাগম;
    }

  যদি (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      প্রত্যাগম;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, পূর্ণাঙ্ক c, size_t len, size_t n,
	 পূর্ণাঙ্ক max_char)
{
  size_t i;
  বর্ণ *s1, *s2;

  align1 &= 7;
  যদি (align1 + len >= page_size)
    প্রত্যাগম;

  align2 &= 7;
  যদি (align2 + len >= page_size)
    প্রত্যাগম;

  s1 = (বর্ণ *) (buf1 + align1);
  s2 = (বর্ণ *) (buf2 + align2);

  প্রতি (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      যদি (s1[i] == (বর্ণ) c)
	--s1[i];
    }
  s1[len - 1] = c;
  প্রতি (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned বর্ণ *p1 = buf1 + page_size - 512;
  unsigned বর্ণ *p2 = buf2 + page_size - 512;
  unsigned বর্ণ *res, c;

  প্রতি (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      যদি (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
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
	    len = size - (random () & 31);
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
	      size = random () & 511;
	      যদি (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  অন্যথা
	    size = 512 - j;
	  যদি ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      যদি (j > 512)
	j = 512;
      প্রতি (i = 0; i < j; i++)
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
	  unsigned বর্ণ *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (বর্ণ) c, size);
	  যদি (len >= size)
	    expect = রিক্ত;
	  অন্যথা
	    expect = p2 + align2 + len + 1;

	  যদি (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  প্রতি (j = 0; j < align2 + 64; ++j)
	    {
	      যদি (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ভঙ্গ;
		}
	    }
	  j = align2 + len + 1;
	  যদি (size + align2 < j)
	    j = size + align2;
	  প্রতি (; j < 512; ++j)
	    {
	      যদি (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ভঙ্গ;
		}
	    }
	  j = len + 1;
	  যদি (size < j)
	    j = size;
	  যদি (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  প্রতি (i = 1; i < 8; ++i)
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

  প্রতি (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  প্রত্যাগম ret;
}

#অন্তর্ভাব <support/test-driver.c>
