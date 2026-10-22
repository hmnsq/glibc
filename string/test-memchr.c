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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "memchr"
#లేకపోతే
# define TEST_NAME "wmemchr"
#అయితే_ముగింపు /* WIDE */

#అన్తర్భావ "test-string.h"
#అన్తర్భావ <stdint.h>

#నిర్వచితం_కాకపోతే WIDE
# define MEMCHR memchr
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#లేకపోతే
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#అయితే_ముగింపు /* WIDE */

రకనిర్వచనం CHAR *(*proto_t) (స్థిరరాశి CHAR *, పూర్ణాంకం, size_t);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు MEMCHR
#నిర్వచనం_రద్దు static_weak_alias
#నిర్వచించు static_weak_alias(a, b)
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు libc_hidden_weak
#నిర్వచించు libc_hidden_weak(a)
#నిర్వచితం_కాకపోతే WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#లేకపోతే
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#అయితే_ముగింపు
IMPL (MEMCHR_DEFAULT, 1)

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, పూర్ణాంకం c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len, size_t n, పూర్ణాంకం seek_char)
{
  size_t i;
  CHAR *ఫలితం;

  ఒకవేళ ((align + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  CHAR *buf = (CHAR *) (buf1);

  కొరకు (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      ఒకవేళ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  ఒకవేళ (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      ఫలితం = (CHAR *) (buf + align + pos);
    }
  లేకపోతే
    {
      ఫలితం = ఖాళీ;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, ఫలితం);
}

స్థిర శూన్య
do_అధికప్రవాహం_tests (శూన్య)
{
  size_t i, j, len;
  స్థిరరాశి size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  కొరకు (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      కొరకు (j = 8 * పరిమాణం(size_t) - 1; j ; --j)
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

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len;
  పూర్ణాంకం seek_char;
  CHAR *ఫలితం;
  UCHAR *p = (UCHAR *) (buf1 + పుట_కొలత) - 512;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ఒకవేళ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ఒకవేళ (pos >= len)
	len = pos + (random () & 7);
      ఒకవేళ (len + align >= 512)
	len = 512 - align - (random () & 7);
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == pos + align)
	    p[i] = seek_char;
	  లేకపోతే
	    {
	      p[i] = random () & BIG_CHAR;
	      ఒకవేళ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ఒకవేళ (pos < len)
	{
	  size_t r = random ();
	  ఒకవేళ ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  ఫలితం = (CHAR *) (p + pos + align);
	}
      లేకపోతే
	ఫలితం = ఖాళీ;

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align), seek_char, len) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   ఫలితం, p);
	    ret = 1;
	  }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, j;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
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

  కొరకు (i = 1; i < 64; ++i)
    {
      కొరకు (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  కొరకు (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  కొరకు (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (పుట_కొలత / 2 - i, i, i, 1, 0x9B);
      do_test (పుట_కొలత / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (పుట_కొలత / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_అధికప్రవాహం_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
