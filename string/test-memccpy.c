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
#include "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
void *
simple_memccpy (void *dst, const void *src, ចំនួនគត់ c, size_t n)
{
  const var_na *s = src;
  var_na *d = dst;

  ខណៈពេល (n-- > 0)
    ប្រសិនបើ ((*d++ = *s++) == (var_na) c)
      ត្រឡប់ d;

  ត្រឡប់ NULL;
}

typedef void *(*proto_t) (void *, const void *, ចំនួនគត់ c, size_t);

static void
do_one_test (impl_t *impl, void *dst, const void *src, ចំនួនគត់ c, size_t len,
	     size_t n)
{
  void *expect = len > n ? NULL : (var_na *) dst + len;
  ប្រសិនបើ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ត្រឡប់;
    }

  ប្រសិនបើ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ត្រឡប់;
    }
}

static void
do_test (size_t align1, size_t align2, ចំនួនគត់ c, size_t len, size_t n,
	 ចំនួនគត់ max_char)
{
  size_t i;
  var_na *s1, *s2;

  align1 &= 7;
  ប្រសិនបើ (align1 + len >= page_size)
    ត្រឡប់;

  align2 &= 7;
  ប្រសិនបើ (align2 + len >= page_size)
    ត្រឡប់;

  s1 = (var_na *) (buf1 + align1);
  s2 = (var_na *) (buf2 + align2);

  សម្រាប់ (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ប្រសិនបើ (s1[i] == (var_na) c)
	--s1[i];
    }
  s1[len - 1] = c;
  សម្រាប់ (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned var_na *p1 = buf1 + page_size - 512;
  unsigned var_na *p2 = buf2 + page_size - 512;
  unsigned var_na *res, c;

  សម្រាប់ (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      ប្រសិនបើ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ប្រសិនបើ (mode & 2)
	    align2 = align1 - (random () & 24);
	  បើមិនដូច្នេះ
	    align2 = align1 - (random () & 31);
	  ប្រសិនបើ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ប្រសិនបើ (mode & 8)
	    len = size - (random () & 31);
	  បើមិនដូច្នេះ
	    len = 512;
	  ប្រសិនបើ (len >= 512)
	    len = random () & 511;
	}
      បើមិនដូច្នេះ
	{
	  align1 = random () & 31;
	  ប្រសិនបើ (mode & 2)
	    align2 = random () & 31;
	  បើមិនដូច្នេះ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ប្រសិនបើ (align2 > j)
	    j = align2;
	  ប្រសិនបើ (mode & 4)
	    {
	      size = random () & 511;
	      ប្រសិនបើ (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  បើមិនដូច្នេះ
	    size = 512 - j;
	  ប្រសិនបើ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ប្រសិនបើ (j > 512)
	j = 512;
      សម្រាប់ (i = 0; i < j; i++)
	{
	  ប្រសិនបើ (i == len + align1)
	    p1[i] = c;
	  បើមិនដូច្នេះ
	    {
	      p1[i] = random () & 255;
	      ប្រសិនបើ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned var_na *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (var_na) c, size);
	  ប្រសិនបើ (len >= size)
	    expect = NULL;
	  បើមិនដូច្នេះ
	    expect = p2 + align2 + len + 1;

	  ប្រសិនបើ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  សម្រាប់ (j = 0; j < align2 + 64; ++j)
	    {
	      ប្រសិនបើ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = align2 + len + 1;
	  ប្រសិនបើ (size + align2 < j)
	    j = size + align2;
	  សម្រាប់ (; j < 512; ++j)
	    {
	      ប្រសិនបើ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = len + 1;
	  ប្រសិនបើ (size < j)
	    j = size;
	  ប្រសិនបើ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ចំនួនគត់
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  សម្រាប់ (i = 1; i < 8; ++i)
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

  សម្រាប់ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ត្រឡប់ ret;
}

#include <support/test-driver.c>
