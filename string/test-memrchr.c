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

#define TEST_MAIN
#define TEST_NAME "memrchr"
#include "test-string.h"

typedef char *(*proto_t) (const char *, 整数, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#include "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
char *
simple_memrchr (const char *s, 整数 c, size_t n)
{
  s = s + n;
  当 (n--)
    如果 (*--s == (char) c)
      返回 (char *) s;
  返回 NULL;
}

static void
do_one_test (impl_t *impl, const char *s, 整数 c, size_t n, char *exp_res)
{
  char *res = CALL (impl, s, c, n);
  如果 (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      返回;
    }
}

static void
do_test (size_t align, size_t pos, size_t len, 整数 seek_char)
{
  size_t i;
  char *result;

  align &= 7;
  如果 (align + len >= page_size)
    返回;

  为 (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      如果 (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  如果 (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (char *) (buf1 + align + pos);
    }
  否则
    {
      result = NULL;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (char *) (buf1 + align), seek_char, len, result);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len;
  整数 seek_char;
  char *result;
  unsigned char *p = buf1 + page_size - 512;

  为 (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      如果 (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      如果 (pos >= len)
	len = pos + (random () & 7);
      如果 (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      如果 (j > 512)
        j = 512;

      为 (i = 0; i < j; i++)
	{
	  如果 (i == pos + align)
	    p[i] = seek_char;
	  否则
	    {
	      p[i] = random () & 255;
	      如果 (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      如果 (pos < len)
	result = (char *) (p + pos + align);
      否则
	result = NULL;

      FOR_EACH_IMPL (impl, 1)
	如果 (CALL (impl, (char *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (char *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

整数
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  为 (i = 1; i < 8; ++i)
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
  为 (i = 1; i < 32; ++i)
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
  返回 ret;
}

#include <support/test-driver.c>
