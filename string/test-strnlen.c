/* Test strlen functions.
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
# define TEST_NAME "strnlen"
#లేకపోతే
# define TEST_NAME "wcsnlen"
#అయితే_ముగింపు /* !WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR అక్షరం
# define BIG_CHAR CHAR_MAX
# define మధ్య_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#లేకపోతే
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define మధ్య_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#అయితే_ముగింపు /* !WIDE */

రకనిర్వచనం size_t (*proto_t) (స్థిరరాశి CHAR *, size_t);

/* Also check the default implementation.  */
#నిర్వచనం_రద్దు STRNLEN
#నిర్వచితం_కాకపోతే WIDE
# define MEMCHR __memchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_builtin_def(a)
# include "string/memchr.c"
# undef STRNLEN
# define STRNLEN __strnlen_default
# define memchr __memchr_default
# include "string/strnlen.c"
IMPL (__strnlen_default, 1)
#లేకపోతే
# define WMEMCHR __wmemchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_weak(a)
# include "wcsmbs/wmemchr.c"
# define WCSNLEN __wcsnlen_default
# undef wmemchr
# define wmemchr __wmemchr_default
# include "wcsmbs/wcsnlen.c"
IMPL (__wcsnlen_default, 1)
#అయితే_ముగింపు

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  ఒకవేళ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t len, size_t maxlen, పూర్ణాంకం max_char)
{
  size_t i;

  align &= (getpagesize () / పరిమాణం (CHAR) - 1);
  ఒకవేళ ((align + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  CHAR *buf = (CHAR *) (buf1);

  కొరకు (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

స్థిర శూన్య
do_అధికప్రవాహం_tests (శూన్య)
{
  size_t i, j, al_idx, repeats, len;
  స్థిరరాశి size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  స్థిరరాశి size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  కొరకు (al_idx = 0; al_idx < పరిమాణం (alignments) / పరిమాణం (alignments[0]);
       al_idx++)
    {
      కొరకు (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= పరిమాణం (CHAR);
	  కొరకు (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      కొరకు (j = 8 * పరిమాణం (size_t) - 1; j; --j)
		{
		  len |= one << j;
		  do_test (align, i, len, BIG_CHAR);
		  do_test (align, i, len - i, BIG_CHAR);
		  do_test (align, i, len + i, BIG_CHAR);
		  do_test (align, i, len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, ~len - i, BIG_CHAR);
		  do_test (align, i, ~len + i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, -buf_addr, BIG_CHAR);
		  do_test (align, i, j - buf_addr, BIG_CHAR);
		  do_test (align, i, -buf_addr - j, BIG_CHAR);
		}
	    }
	}
    }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + పుట_కొలత - 512 * పరిమాణం (CHAR));

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      ఒకవేళ (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align)
	    p[i] = 0;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  ఒకవేళ (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  ఒకవేళ (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  ఒకవేళ (CALL (impl, (CHAR *) (p + align), len + 1) != len)
	    {
	      error (0, 0, "Iteration %zd (long) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len + 1), len, p);
	      ret = 1;
	    }
	}
    }
}

/* Tests meant to unveil fail on implementation that does not access bytes
   around the page boundary accordingly.  */
స్థిర శూన్య
do_పుట_tests (శూన్య)
{
  size_t i, exp_len, ప్రారంభం_స్థానభ్రంశం, స్థానభ్రంశం;
  /* Calculate the null character offset.  */
  size_t చివరి_స్థానభ్రంశం = (పుట_కొలత / పరిమాణం (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (చివరి_స్థానభ్రంశం - 1));
  s[చివరి_స్థానభ్రంశం] = 0;

  /* Place short strings ending at page boundary.  */
  స్థానభ్రంశం = చివరి_స్థానభ్రంశం;
  కొరకు (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      స్థానభ్రంశం--;
      exp_len = చివరి_స్థానభ్రంశం - స్థానభ్రంశం;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), పుట_కొలత, exp_len);
          do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), exp_len, exp_len);
          ఒకవేళ (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  ప్రారంభం_స్థానభ్రంశం = (చివరి_స్థానభ్రంశం + 1) / 2;
  కొరకు (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      స్థానభ్రంశం = ప్రారంభం_స్థానభ్రంశం + i;
      ఒకవేళ (స్థానభ్రంశం >= (చివరి_స్థానభ్రంశం + 1))
        ఆపు;
      exp_len = చివరి_స్థానభ్రంశం - స్థానభ్రంశం;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), పుట_కొలత, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

స్థిర శూన్య
do_పుట_2_tests (శూన్య)
{
  size_t i, exp_len, స్థానభ్రంశం;
  size_t చివరి_స్థానభ్రంశం = పుట_కొలత / పరిమాణం (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, చివరి_స్థానభ్రంశం);

  /* Place short strings ending at page boundary without the null
     byte.  */
  స్థానభ్రంశం = చివరి_స్థానభ్రంశం;
  కొరకు (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      స్థానభ్రంశం--;
      exp_len = చివరి_స్థానభ్రంశం - స్థానభ్రంశం;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + స్థానభ్రంశం), exp_len, exp_len);
	}
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, నిడివి, char_చొప్పున_పుట;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, మధ్య_CHAR);
      do_test (0, i, i, మధ్య_CHAR);
      do_test (0, i, i + 1, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, మధ్య_CHAR);
      do_test (i, i, i, మధ్య_CHAR);
      do_test (i, i, i + 1, మధ్య_CHAR);
    }

  కొరకు (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, మధ్య_CHAR);
      do_test (1, 1 << i, 5000, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  కొరకు (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  కొరకు (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_చొప్పున_పుట = getpagesize () / పరిమాణం (CHAR);

  కొరకు (i = 0; i <= 127; i++)
    కొరకు (నిడివి = i; నిడివి <= 512; నిడివి++)
      {
	do_test (i, నిడివి, 512, BIG_CHAR);
	do_test (char_చొప్పున_పుట - i, నిడివి, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_పుట_tests ();
  do_పుట_2_tests ();
  do_అధికప్రవాహం_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
