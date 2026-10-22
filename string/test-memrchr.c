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
#অন্তর্ভাৱ "test-string.h"

প্রকারনির্দেশ ৱর্ণ *(*proto_t) (ধ্রুৱ ৱর্ণ *, পূর্ণাঙ্ক, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#অন্তর্ভাৱ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
ৱর্ণ *
simple_memrchr (ধ্রুৱ ৱর্ণ *s, পূর্ণাঙ্ক c, size_t n)
{
  s = s + n;
  যেতিয়ালৈ (n--)
    যদি (*--s == (ৱর্ণ) c)
      ঘূৰাই (ৱর্ণ *) s;
  ঘূৰাই রিক্ত;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুৱ ৱর্ণ *s, পূর্ণাঙ্ক c, size_t n, ৱর্ণ *exp_res)
{
  ৱর্ণ *res = CALL (impl, s, c, n);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ঘূৰাই;
    }
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len, পূর্ণাঙ্ক seek_char)
{
  size_t i;
  ৱর্ণ *result;

  align &= 7;
  যদি (align + len >= page_size)
    ঘূৰাই;

  বাবে (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      যদি (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  যদি (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (ৱর্ণ *) (buf1 + align + pos);
    }
  অন্যথা
    {
      result = রিক্ত;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ৱর্ণ *) (buf1 + align), seek_char, len, result);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len;
  পূর্ণাঙ্ক seek_char;
  ৱর্ণ *result;
  unsigned ৱর্ণ *p = buf1 + page_size - 512;

  বাবে (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      যদি (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      যদি (pos >= len)
	len = pos + (random () & 7);
      যদি (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      যদি (j > 512)
        j = 512;

      বাবে (i = 0; i < j; i++)
	{
	  যদি (i == pos + align)
	    p[i] = seek_char;
	  অন্যথা
	    {
	      p[i] = random () & 255;
	      যদি (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      যদি (pos < len)
	result = (ৱর্ণ *) (p + pos + align);
      অন্যথা
	result = রিক্ত;

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (ৱর্ণ *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ৱর্ণ *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  বাবে (i = 1; i < 8; ++i)
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
  বাবে (i = 1; i < 32; ++i)
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
  ঘূৰাই ret;
}

#অন্তর্ভাৱ <support/test-driver.c>
