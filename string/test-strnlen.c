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
#இல்லையெனில்
# define TEST_NAME "wcsnlen"
#endif /* !WIDE */
#அந்தர்பாவ "test-string.h"

#ifndef WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR எழுத்து
# define BIG_CHAR CHAR_MAX
# define நடு_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#இல்லையெனில்
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define நடு_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#endif /* !WIDE */

வகைவரை size_t (*proto_t) (மாறிலி CHAR *, size_t);

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
#இல்லையெனில்
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

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  எனில் (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      திரும்பு;
    }
}

நிலையான வெறுமை
do_test (size_t align, size_t len, size_t maxlen, முழு max_char)
{
  size_t i;

  align &= (getpagesize () / அளவு (CHAR) - 1);
  எனில் ((align + len) * அளவு (CHAR) >= page_size)
    திரும்பு;

  CHAR *buf = (CHAR *) (buf1);

  க்கு (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

நிலையான வெறுமை
do_overflow_tests (வெறுமை)
{
  size_t i, j, al_idx, repeats, len;
  மாறிலி size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  மாறிலி size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  க்கு (al_idx = 0; al_idx < அளவு (alignments) / அளவு (alignments[0]);
       al_idx++)
    {
      க்கு (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= அளவு (CHAR);
	  க்கு (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      க்கு (j = 8 * அளவு (size_t) - 1; j; --j)
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

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_size - 512 * அளவு (CHAR));

  க்கு (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      எனில் (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      எனில் (j > 512)
	j = 512;

      க்கு (i = 0; i < j; i++)
	{
	  எனில் (i == len + align)
	    p[i] = 0;
	  இல்லையெனில்
	    {
	      p[i] = random () & 255;
	      எனில் (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  எனில் (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  எனில் (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  எனில் (CALL (impl, (CHAR *) (p + align), len + 1) != len)
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
நிலையான வெறுமை
do_page_tests (வெறுமை)
{
  size_t i, exp_len, start_offset, offset;
  /* Calculate the null character offset.  */
  size_t last_offset = (page_size / அளவு (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (last_offset - 1));
  s[last_offset] = 0;

  /* Place short strings ending at page boundary.  */
  offset = last_offset;
  க்கு (i = 0; i < 128; i++)
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
          do_one_test (impl, (CHAR *) (s + offset), page_size, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len, exp_len);
          எனில் (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + offset), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  start_offset = (last_offset + 1) / 2;
  க்கு (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      offset = start_offset + i;
      எனில் (offset >= (last_offset + 1))
        நிறுத்து;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + offset), page_size, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

நிலையான வெறுமை
do_page_2_tests (வெறுமை)
{
  size_t i, exp_len, offset;
  size_t last_offset = page_size / அளவு (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, last_offset);

  /* Place short strings ending at page boundary without the null
     byte.  */
  offset = last_offset;
  க்கு (i = 0; i < 128; i++)
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

முழு
test_main (வெறுமை)
{
  size_t i, length, char_per_page;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, நடு_CHAR);
      do_test (0, i, i, நடு_CHAR);
      do_test (0, i, i + 1, நடு_CHAR);
    }

  க்கு (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, நடு_CHAR);
      do_test (i, i, i, நடு_CHAR);
      do_test (i, i, i + 1, நடு_CHAR);
    }

  க்கு (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, நடு_CHAR);
      do_test (1, 1 << i, 5000, நடு_CHAR);
    }

  க்கு (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  க்கு (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  க்கு (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_per_page = getpagesize () / அளவு (CHAR);

  க்கு (i = 0; i <= 127; i++)
    க்கு (length = i; length <= 512; length++)
      {
	do_test (i, length, 512, BIG_CHAR);
	do_test (char_per_page - i, length, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_page_tests ();
  do_page_2_tests ();
  do_overflow_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
