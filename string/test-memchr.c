/* Test memchr functions.
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
#ifndef WIDE
# define TEST_NAME "memchr"
#ଅନ୍ୟଥା
# define TEST_NAME "wmemchr"
#endif /* WIDE */

#ଅନ୍ତର୍ଭାଵ "test-string.h"
#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ifndef WIDE
# define MEMCHR memchr
# define CHAR ଅକ୍ଷର
# define UCHAR unsigned ଅକ୍ଷର
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ଅନ୍ୟଥା
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

ପ୍ରକାରବ୍ୟାଖ୍ୟା CHAR *(*proto_t) (ଅଚଳ CHAR *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, size_t);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#undef MEMCHR
#undef static_weak_alias
#define static_weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#ଅନ୍ୟଥା
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#endif
IMPL (MEMCHR_DEFAULT, 1)

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ CHAR *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  ଯଦି (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      ଫେରନ୍ତୁ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align, size_t pos, size_t len, size_t n, ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char)
{
  size_t i;
  CHAR *result;

  ଯଦି ((align + len) * ଆକାର (CHAR) >= page_size)
    ଫେରନ୍ତୁ;

  CHAR *buf = (CHAR *) (buf1);

  ପାଇଁ (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      ଯଦି (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  ଯଦି (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      result = (CHAR *) (buf + align + pos);
    }
  ଅନ୍ୟଥା
    {
      result = ଖାଲି;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, result);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_overflow_tests (ଶୂନ୍ୟ)
{
  size_t i, j, len;
  ଅଚଳ size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  ପାଇଁ (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      ପାଇଁ (j = 8 * ଆକାର(size_t) - 1; j ; --j)
        {
          len |= one << j;
          do_test (0, i, 751, len - i, BIG_CHAR);
          do_test (0, i, 751, len + i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr + i, BIG_CHAR);

          do_test (0, i, 751, ~len - i, BIG_CHAR);
          do_test (0, i, 751, ~len + i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr + i, BIG_CHAR);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align, pos, len;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;

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
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      ଯଦି (j > 512)
	j = 512;

      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == pos + align)
	    p[i] = seek_char;
	  ଅନ୍ୟଥା
	    {
	      p[i] = random () & BIG_CHAR;
	      ଯଦି (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ଯଦି (pos < len)
	{
	  size_t r = random ();
	  ଯଦି ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  result = (CHAR *) (p + pos + align);
	}
      ଅନ୍ୟଥା
	result = ଖାଲି;

      FOR_EACH_IMPL (impl, 1)
	ଯଦି (CALL (impl, (CHAR *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i, j;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      /* Test n == 0.  */
      do_test (i, i, 0, 0, 23);
      do_test (i, i, 0, 0, 0);

      do_test (0, 16 << i, 2048, 2048, 23);
      do_test (i, 64, 256, 256, 23);
      do_test (0, 16 << i, 2048, 2048, 0);
      do_test (i, 64, 256, 256, 0);

      /* Check for large input sizes and for these cases we need to
	 make sure the byte is within the size range (that's why
	 7 << i must be smaller than 2048).  */
      do_test (0, 7 << i, 2048, SIZE_MAX, 23);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 23);
      do_test (i, 64, 256, SIZE_MAX, 23);
      do_test (0, 7 << i, 2048, SIZE_MAX, 0);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 0);
      do_test (i, 64, 256, SIZE_MAX, 0);
    }

  ପାଇଁ (i = 1; i < 64; ++i)
    {
      ପାଇଁ (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  ପାଇଁ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  ପାଇଁ (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (page_size / 2 - i, i, i, 1, 0x9B);
      do_test (page_size / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (page_size / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_overflow_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
