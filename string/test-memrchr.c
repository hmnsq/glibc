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
#ଅନ୍ତର୍ଭାଵ "test-string.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅକ୍ଷର *(*proto_t) (ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#ଅନ୍ତର୍ଭାଵ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
ଅକ୍ଷର *
simple_memrchr (ଅଚଳ ଅକ୍ଷର *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t n)
{
  s = s + n;
  ଯେତେବେଳେ (n--)
    ଯଦି (*--s == (ଅକ୍ଷର) c)
      ଫେରନ୍ତୁ (ଅକ୍ଷର *) s;
  ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ ଅକ୍ଷର *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t n, ଅକ୍ଷର *exp_res)
{
  ଅକ୍ଷର *res = CALL (impl, s, c, n);
  ଯଦି (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ଫେରନ୍ତୁ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align, size_t pos, size_t len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char)
{
  size_t i;
  ଅକ୍ଷର *result;

  align &= 7;
  ଯଦି (align + len >= page_size)
    ଫେରନ୍ତୁ;

  ପାଇଁ (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ଯଦି (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ଯଦି (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (ଅକ୍ଷର *) (buf1 + align + pos);
    }
  ଅନ୍ୟଥା
    {
      result = ଖାଲି;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ଅକ୍ଷର *) (buf1 + align), seek_char, len, result);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align, pos, len;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char;
  ଅକ୍ଷର *result;
  unsigned ଅକ୍ଷର *p = buf1 + page_size - 512;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ଯଦି (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ଯଦି (pos >= len)
	len = pos + (random () & 7);
      ଯଦି (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      ଯଦି (j > 512)
        j = 512;

      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == pos + align)
	    p[i] = seek_char;
	  ଅନ୍ୟଥା
	    {
	      p[i] = random () & 255;
	      ଯଦି (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ଯଦି (pos < len)
	result = (ଅକ୍ଷର *) (p + pos + align);
      ଅନ୍ୟଥା
	result = ଖାଲି;

      FOR_EACH_IMPL (impl, 1)
	ଯଦି (CALL (impl, (ଅକ୍ଷର *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ଅକ୍ଷର *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 1; i < 8; ++i)
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
  ପାଇଁ (i = 1; i < 32; ++i)
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
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
