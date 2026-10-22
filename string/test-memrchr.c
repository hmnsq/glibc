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

typedef var_na *(*proto_t) (const var_na *, จำนวนเต็ม, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#include "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
var_na *
simple_memrchr (const var_na *s, จำนวนเต็ม c, size_t n)
{
  s = s + n;
  ขณะ (n--)
    ถ้า (*--s == (var_na) c)
      คืน (var_na *) s;
  คืน NULL;
}

static void
do_one_test (impl_t *impl, const var_na *s, จำนวนเต็ม c, size_t n, var_na *exp_res)
{
  var_na *res = CALL (impl, s, c, n);
  ถ้า (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      คืน;
    }
}

static void
do_test (size_t align, size_t pos, size_t len, จำนวนเต็ม seek_char)
{
  size_t i;
  var_na *result;

  align &= 7;
  ถ้า (align + len >= page_size)
    คืน;

  สำหรับ (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ถ้า (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ถ้า (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (var_na *) (buf1 + align + pos);
    }
  มิฉะนั้น
    {
      result = NULL;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (var_na *) (buf1 + align), seek_char, len, result);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len;
  จำนวนเต็ม seek_char;
  var_na *result;
  unsigned var_na *p = buf1 + page_size - 512;

  สำหรับ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ถ้า (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ถ้า (pos >= len)
	len = pos + (random () & 7);
      ถ้า (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      ถ้า (j > 512)
        j = 512;

      สำหรับ (i = 0; i < j; i++)
	{
	  ถ้า (i == pos + align)
	    p[i] = seek_char;
	  มิฉะนั้น
	    {
	      p[i] = random () & 255;
	      ถ้า (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ถ้า (pos < len)
	result = (var_na *) (p + pos + align);
      มิฉะนั้น
	result = NULL;

      FOR_EACH_IMPL (impl, 1)
	ถ้า (CALL (impl, (var_na *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (var_na *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

จำนวนเต็ม
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  สำหรับ (i = 1; i < 8; ++i)
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
  สำหรับ (i = 1; i < 32; ++i)
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
  คืน ret;
}

#include <support/test-driver.c>
