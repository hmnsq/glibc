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
#অন্যথা
# define TEST_NAME "wmemchr"
#endif /* WIDE */

#অন্তর্ভাব "test-string.h"
#অন্তর্ভাব <stdint.h>

#ifndef WIDE
# define MEMCHR memchr
# define CHAR অক্ষর
# define UCHAR unsigned অক্ষর
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#অন্যথা
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

প্রকারলেখ CHAR *(*proto_t) (ধ্রুবক CHAR *, পূর্ণসংখ্যা, size_t);

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
#অন্যথা
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#endif
IMPL (MEMCHR_DEFAULT, 1)

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক CHAR *s, পূর্ণসংখ্যা c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len, size_t n, পূর্ণসংখ্যা seek_char)
{
  size_t i;
  CHAR *ফলাফল;

  যদি ((align + len) * আকার (CHAR) >= page_আকার)
    ফেরত;

  CHAR *buf = (CHAR *) (buf1);

  জন্য (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      যদি (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  যদি (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      ফলাফল = (CHAR *) (buf + align + pos);
    }
  অন্যথা
    {
      ফলাফল = ফাঁকা;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, ফলাফল);
}

স্থির শূন্য
do_overflow_tests (শূন্য)
{
  size_t i, j, len;
  ধ্রুবক size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  জন্য (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      জন্য (j = 8 * আকার(size_t) - 1; j ; --j)
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

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len;
  পূর্ণসংখ্যা seek_char;
  CHAR *ফলাফল;
  UCHAR *p = (UCHAR *) (buf1 + page_আকার) - 512;

  জন্য (n = 0; n < ITERATIONS; n++)
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
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      যদি (j > 512)
	j = 512;

      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == pos + align)
	    p[i] = seek_char;
	  অন্যথা
	    {
	      p[i] = random () & BIG_CHAR;
	      যদি (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      যদি (pos < len)
	{
	  size_t r = random ();
	  যদি ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  ফলাফল = (CHAR *) (p + pos + align);
	}
      অন্যথা
	ফলাফল = ফাঁকা;

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (CHAR *) (p + align), seek_char, len) != ফলাফল)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   ফলাফল, p);
	    ret = 1;
	  }
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i, j;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 8; ++i)
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

  জন্য (i = 1; i < 64; ++i)
    {
      জন্য (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  জন্য (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  জন্য (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (page_আকার / 2 - i, i, i, 1, 0x9B);
      do_test (page_আকার / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (page_আকার / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_overflow_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
