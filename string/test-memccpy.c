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
simple_memccpy (void *dst, const void *src, 정수 c, size_t n)
{
  const char *s = src;
  char *d = dst;

  동안 (n-- > 0)
    만약 ((*d++ = *s++) == (char) c)
      반환 d;

  반환 NULL;
}

typedef void *(*proto_t) (void *, const void *, 정수 c, size_t);

static void
do_one_test (impl_t *impl, void *dst, const void *src, 정수 c, size_t len,
	     size_t n)
{
  void *expect = len > n ? NULL : (char *) dst + len;
  만약 (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      반환;
    }

  만약 (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      반환;
    }
}

static void
do_test (size_t align1, size_t align2, 정수 c, size_t len, size_t n,
	 정수 max_char)
{
  size_t i;
  char *s1, *s2;

  align1 &= 7;
  만약 (align1 + len >= page_size)
    반환;

  align2 &= 7;
  만약 (align2 + len >= page_size)
    반환;

  s1 = (char *) (buf1 + align1);
  s2 = (char *) (buf2 + align2);

  위해 (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      만약 (s1[i] == (char) c)
	--s1[i];
    }
  s1[len - 1] = c;
  위해 (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned char *p1 = buf1 + page_size - 512;
  unsigned char *p2 = buf2 + page_size - 512;
  unsigned char *res, c;

  위해 (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      만약 (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  만약 (mode & 2)
	    align2 = align1 - (random () & 24);
	  아니면
	    align2 = align1 - (random () & 31);
	  만약 (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  만약 (mode & 8)
	    len = size - (random () & 31);
	  아니면
	    len = 512;
	  만약 (len >= 512)
	    len = random () & 511;
	}
      아니면
	{
	  align1 = random () & 31;
	  만약 (mode & 2)
	    align2 = random () & 31;
	  아니면
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  만약 (align2 > j)
	    j = align2;
	  만약 (mode & 4)
	    {
	      size = random () & 511;
	      만약 (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  아니면
	    size = 512 - j;
	  만약 ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      만약 (j > 512)
	j = 512;
      위해 (i = 0; i < j; i++)
	{
	  만약 (i == len + align1)
	    p1[i] = c;
	  아니면
	    {
	      p1[i] = random () & 255;
	      만약 (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned char *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (char) c, size);
	  만약 (len >= size)
	    expect = NULL;
	  아니면
	    expect = p2 + align2 + len + 1;

	  만약 (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  위해 (j = 0; j < align2 + 64; ++j)
	    {
	      만약 (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  break;
		}
	    }
	  j = align2 + len + 1;
	  만약 (size + align2 < j)
	    j = size + align2;
	  위해 (; j < 512; ++j)
	    {
	      만약 (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  break;
		}
	    }
	  j = len + 1;
	  만약 (size < j)
	    j = size;
	  만약 (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

정수
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  위해 (i = 1; i < 8; ++i)
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

  위해 (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  반환 ret;
}

#include <support/test-driver.c>
