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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strnlen"
#অন্যথা
# define TEST_NAME "wcsnlen"
#endif /* !WIDE */
#অন্তর্ভাব "test-string.h"

#ifndef WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR অক্ষর
# define BIG_CHAR CHAR_MAX
# define মধ্য_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#অন্যথা
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define মধ্য_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#endif /* !WIDE */

প্রকারলেখ size_t (*proto_t) (ধ্রুবক CHAR *, size_t);

/* Also check the default implementation.  */
#undef STRNLEN
#ifndef WIDE
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
#অন্যথা
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
#endif

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  যদি (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align, size_t len, size_t maxlen, পূর্ণসংখ্যা max_char)
{
  size_t i;

  align &= (getpagesize () / আকার (CHAR) - 1);
  যদি ((align + len) * আকার (CHAR) >= page_আকার)
    ফেরত;

  CHAR *buf = (CHAR *) (buf1);

  জন্য (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

স্থির শূন্য
do_overflow_tests (শূন্য)
{
  size_t i, j, al_idx, repeats, len;
  ধ্রুবক size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  ধ্রুবক size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  জন্য (al_idx = 0; al_idx < আকার (alignments) / আকার (alignments[0]);
       al_idx++)
    {
      জন্য (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= আকার (CHAR);
	  জন্য (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      জন্য (j = 8 * আকার (size_t) - 1; j; --j)
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

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_আকার - 512 * আকার (CHAR));

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      যদি (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      যদি (j > 512)
	j = 512;

      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == len + align)
	    p[i] = 0;
	  অন্যথা
	    {
	      p[i] = random () & 255;
	      যদি (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  যদি (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  যদি (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  যদি (CALL (impl, (CHAR *) (p + align), len + 1) != len)
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
স্থির শূন্য
do_page_tests (শূন্য)
{
  size_t i, exp_len, start_offset, offset;
  /* Calculate the null character offset.  */
  size_t last_offset = (page_আকার / আকার (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (last_offset - 1));
  s[last_offset] = 0;

  /* Place short strings ending at page boundary.  */
  offset = last_offset;
  জন্য (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      offset--;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + offset), page_আকার, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len, exp_len);
          যদি (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + offset), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  start_offset = (last_offset + 1) / 2;
  জন্য (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      offset = start_offset + i;
      যদি (offset >= (last_offset + 1))
        বিরতি;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + offset), page_আকার, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

স্থির শূন্য
do_page_2_tests (শূন্য)
{
  size_t i, exp_len, offset;
  size_t last_offset = page_আকার / আকার (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, last_offset);

  /* Place short strings ending at page boundary without the null
     byte.  */
  offset = last_offset;
  জন্য (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      offset--;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + offset), exp_len, exp_len);
	}
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i, দৈর্ঘ্য, char_per_page;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, মধ্য_CHAR);
      do_test (0, i, i, মধ্য_CHAR);
      do_test (0, i, i + 1, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, মধ্য_CHAR);
      do_test (i, i, i, মধ্য_CHAR);
      do_test (i, i, i + 1, মধ্য_CHAR);
    }

  জন্য (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, মধ্য_CHAR);
      do_test (1, 1 << i, 5000, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  জন্য (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  জন্য (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_per_page = getpagesize () / আকার (CHAR);

  জন্য (i = 0; i <= 127; i++)
    জন্য (দৈর্ঘ্য = i; দৈর্ঘ্য <= 512; দৈর্ঘ্য++)
      {
	do_test (i, দৈর্ঘ্য, 512, BIG_CHAR);
	do_test (char_per_page - i, দৈর্ঘ্য, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_page_tests ();
  do_page_2_tests ();
  do_overflow_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
