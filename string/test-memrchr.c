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
#ضمن "test-string.h"

تعريفنوع حرف *(*proto_t) (ثابت حرف *, صحيح, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#ضمن "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
حرف *
simple_memrchr (ثابت حرف *s, صحيح c, size_t n)
{
  s = s + n;
  طالما (n--)
    𐡄𐡍 (*--s == (حرف) c)
      أرجع (حرف *) s;
  أرجع عدم;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت حرف *s, صحيح c, size_t n, حرف *exp_res)
{
  حرف *res = CALL (impl, s, c, n);
  𐡄𐡍 (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, صحيح seek_char)
{
  size_t i;
  حرف *result;

  align &= 7;
  𐡄𐡍 (align + len >= page_size)
    أرجع;

  لكل (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      𐡄𐡍 (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  𐡄𐡍 (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (حرف *) (buf1 + align + pos);
    }
  وإلا
    {
      result = عدم;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (حرف *) (buf1 + align), seek_char, len, result);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  حرف *result;
  unsigned حرف *p = buf1 + page_size - 512;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      𐡄𐡍 (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      𐡄𐡍 (pos >= len)
	len = pos + (random () & 7);
      𐡄𐡍 (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      𐡄𐡍 (j > 512)
        j = 512;

      لكل (i = 0; i < j; i++)
	{
	  𐡄𐡍 (i == pos + align)
	    p[i] = seek_char;
	  وإلا
	    {
	      p[i] = random () & 255;
	      𐡄𐡍 (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      𐡄𐡍 (pos < len)
	result = (حرف *) (p + pos + align);
      وإلا
	result = عدم;

      FOR_EACH_IMPL (impl, 1)
	𐡄𐡍 (CALL (impl, (حرف *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (حرف *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  لكل (i = 1; i < 8; ++i)
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
  لكل (i = 1; i < 32; ++i)
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
  أرجع ret;
}

#ضمن <support/test-driver.c>
